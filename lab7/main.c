#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>

#define uchar unsigned char
#define uint unsigned int
#define ull unsigned long long

typedef struct _Bitmap
{
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER info;
	uchar *data;
	uchar *dataCopy;
} Bitmap;

typedef struct _Color
{
	uint r;
	uint g;
	uint b;
} Color;

int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}


Color getPixel(Bitmap *bmp, uint x, uint y)
{

	uint bytesPerPixel = bmp->info.biBitCount / 8;
	int bytesPerColumn = bmp->info.biSizeImage / bmp->info.biHeight;
	uint pixelIndex = x * bytesPerColumn + y * bytesPerPixel;
	Color color;
	color.r = bmp->data[pixelIndex + 2];
	color.g = bmp->data[pixelIndex + 1];
	color.b = bmp->data[pixelIndex];
	return color;
}

void setPixel(Bitmap *bmp, uint x, uint y, uint r, uint g, uint b)
{
	uint bytesPerPixel = bmp->info.biBitCount / 8;
	int bytesPerColumn = bmp->info.biSizeImage / bmp->info.biHeight;
	uint pixelIndex = x * bytesPerColumn + y * bytesPerPixel;
	bmp->dataCopy[pixelIndex + 2] = r;
	bmp->dataCopy[pixelIndex + 1] = g;
	bmp->dataCopy[pixelIndex] = b;
}

int readBitmap(const char *filename, Bitmap *bmp)
{
	FILE *file = fopen(filename, "rb");
	if (!file)
		return 0;
	fread(&bmp->header, sizeof(BITMAPFILEHEADER), 1, file);
	fread(&bmp->info, sizeof(BITMAPINFOHEADER), 1, file);
	bmp->data = (uchar*)malloc(sizeof(uchar) * bmp->info.biSizeImage);
	fread(bmp->data, sizeof(uchar), bmp->info.biSizeImage, file);
	fclose(file);

	bmp->dataCopy = (uchar*)malloc(sizeof(uchar) * bmp->info.biSizeImage);
	for (int i = 0; i < bmp->info.biSizeImage; i++)
	{
		bmp->dataCopy[i] = bmp->data[i];
	}
	return 1;
}

int writeBitmap(const char *filename, Bitmap *bmp)
{

	FILE *file = fopen(filename, "wb");
	if (!file)
		return 0;
	fwrite(&bmp->header, sizeof(BITMAPFILEHEADER), 1, file);
	fwrite(&bmp->info, sizeof(BITMAPINFOHEADER), 1, file);
	fwrite(bmp->dataCopy, sizeof(uchar), bmp->info.biSizeImage, file);
	fclose(file);
	return 1;
}


void median(int height, int width, Bitmap *bmp)
{
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			Color temp[9];
			temp[0] = getPixel(bmp, i - 1, j - 1);
			temp[1] = getPixel(bmp, i - 1, j);
			temp[2] = getPixel(bmp, i - 1, j + 1);
			temp[3] = getPixel(bmp, i, j - 1);
			temp[4] = getPixel(bmp, i, j);
			temp[5] = getPixel(bmp, i, j + 1);
			temp[6] = getPixel(bmp, i + 1, j - 1);
			temp[7] = getPixel(bmp, i + 1, j);
			temp[8] = getPixel(bmp, i + 1, j + 1);
			int tempR[9], tempG[9], tempB[9];
			for (int i = 0; i < 9; i++)
			{
				tempR[i] = temp[i].r;
				tempG[i] = temp[i].g;
				tempB[i] = temp[i].b;
			}
			qsort(tempR, 9, sizeof(int), compare);
			qsort(tempG, 9, sizeof(int), compare);
			qsort(tempB, 9, sizeof(int), compare);
			setPixel(bmp, i, j, tempR[5], tempG[5], tempB[5]);
		}
	}
}

void gray(int height, int width, Bitmap *bmp)
{
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			Color color = getPixel(bmp, i, j);
			int gr = (color.r + color.g + color.b) / 3;
			setPixel(bmp, i, j, gr, gr, gr);
		}
	}
}

void sobelX(int height, int width, Bitmap *bmp)
{
	int mat[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			Color temp[9];
			temp[0] = getPixel(bmp, i - 1, j - 1);
			temp[1] = getPixel(bmp, i - 1, j);
			temp[2] = getPixel(bmp, i - 1, j + 1);
			temp[3] = getPixel(bmp, i, j - 1);
			temp[4] = getPixel(bmp, i, j);
			temp[5] = getPixel(bmp, i, j + 1);
			temp[6] = getPixel(bmp, i + 1, j - 1);
			temp[7] = getPixel(bmp, i + 1, j);
			temp[8] = getPixel(bmp, i + 1, j + 1);
			int tempR = 0, tempG = 0, tempB = 0;
			for (int i = 0; i < 9; i++)
			{
				tempR += temp[i].r * mat[i];
				tempG += temp[i].g * mat[i];
				tempB += temp[i].b * mat[i];
			}
			int result = (tempR + tempG + tempB) / 3;
			if (result > 25)
			{
				result = 255;
			}
			else
			{
				result = 0;
			}
			setPixel(bmp, i, j, result, result, result);
		}
	}
}

void sobelY(int height, int width, Bitmap *bmp)
{
	int mat[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			Color temp[9];
			temp[0] = getPixel(bmp, i - 1, j - 1);
			temp[1] = getPixel(bmp, i - 1, j);
			temp[2] = getPixel(bmp, i - 1, j + 1);
			temp[3] = getPixel(bmp, i, j - 1);
			temp[4] = getPixel(bmp, i, j);
			temp[5] = getPixel(bmp, i, j + 1);
			temp[6] = getPixel(bmp, i + 1, j - 1);
			temp[7] = getPixel(bmp, i + 1, j);
			temp[8] = getPixel(bmp, i + 1, j + 1);
			int tempR = 0, tempG = 0, tempB = 0;
			for (int i = 0; i < 9; i++)
			{
				tempR += temp[i].r * mat[i];
				tempG += temp[i].g * mat[i];
				tempB += temp[i].b * mat[i];
			}
			int result = (tempR + tempG + tempB) / 3;
			if (result > 25)
			{
				result = 255;
			}
			else
			{
				result = 0;
			}
			setPixel(bmp, i, j, result, result, result);
		}
	}
}

void gauss(int height, int width, Bitmap *bmp)
{
	int mat[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			Color temp[9];
			temp[0] = getPixel(bmp, i - 1, j - 1);
			temp[1] = getPixel(bmp, i - 1, j);
			temp[2] = getPixel(bmp, i - 1, j + 1);
			temp[3] = getPixel(bmp, i, j - 1);
			temp[4] = getPixel(bmp, i, j);
			temp[5] = getPixel(bmp, i, j + 1);
			temp[6] = getPixel(bmp, i + 1, j - 1);
			temp[7] = getPixel(bmp, i + 1, j);
			temp[8] = getPixel(bmp, i + 1, j + 1);
			int tempR = 0, tempG = 0, tempB = 0;
			for (int k = 0; k < 9; k++)
			{
				tempR += temp[k].r * mat[k];
				tempG += temp[k].g * mat[k];
				tempB += temp[k].b * mat[k];
			}
			tempR = tempR / 16;
			tempG = tempG / 16;
			tempB = tempB / 16;
			setPixel(bmp, i, j, tempR, tempG, tempB);
		}
	}
}

void freeBitmap(Bitmap *bmp)
{
	free(bmp->data);
	free(bmp->dataCopy);
	free(bmp);
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Incorrect number of arguments, need 3");

		return 0;
	}
	Bitmap *bmp = (Bitmap*)malloc(sizeof(Bitmap));

	if (!readBitmap(argv[1], bmp))
	{
		printf("Error while reading file");
		return 0;
	}

	char *filter[5] = { "median", "gauss", "sobelX", "sobelY", "gray" };
	int filterIndex = 10;
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(argv[2], filter[i]) == 0)
		{
			filterIndex = i;
			break;
		}
	}

	switch (filterIndex)
	{
	case 0: median(bmp->info.biHeight, bmp->info.biWidth, bmp);
		break;
	case 1: gauss(bmp->info.biHeight, bmp->info.biWidth, bmp);
		break;
	case 2: sobelX(bmp->info.biHeight, bmp->info.biWidth, bmp);
		break;
	case 3: sobelY(bmp->info.biHeight, bmp->info.biWidth, bmp);
		break;
	case 4: gray(bmp->info.biHeight, bmp->info.biWidth, bmp);
		break;
	default: printf("Incorrect filter name");
		return 0;
	}
	if (!writeBitmap(argv[3], bmp))
	{
		printf("Error while writing output file");
		return 0;
	}

	freeBitmap(bmp);
	return 0;
}