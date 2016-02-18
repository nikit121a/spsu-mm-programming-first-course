#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include < math.h >

BITMAPFILEHEADER bitmapFileHeader;
BITMAPINFOHEADER bitmapInfoHeader;

typedef struct _Color
{
	BYTE rgbtRed;
	BYTE rgbtGreen;
	BYTE rgbtBlue;
} Color;

char *buf;
Color **bitecolor;
Color **bitecolorcopy;


createbmp(char close[], BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, Color **bitecolor)
{
	FILE *newfile = fopen(close, "wb");
	if (newfile == NULL)
	{
		printf("Error name\n");
		return 0;
	}
	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, newfile);
	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, newfile);
	buf = malloc(sizeof(char) * 4);
	for (int i = 0; i < bitmapInfoHeader.biHeight; i++)
	{
		for (int j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			fwrite(&(bitecolor[i][j]), sizeof(bitecolor[i][j]), 1, newfile);
			if (bitmapInfoHeader.biBitCount == 32) fwrite(&buf, 1, 1, newfile);
		}
		if (bitmapInfoHeader.biBitCount == 24) fwrite(buf, sizeof(BYTE), bitmapInfoHeader.biWidth % 4, newfile);
	}

	fclose(newfile);
}

grey(char close[], BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, Color **bitecolor)
{
	int R, G, B, Y;

	for (int i = 0; i < bitmapInfoHeader.biHeight; i++)
		for (int j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			R = bitecolor[i][j].rgbtRed;
			G = bitecolor[i][j].rgbtGreen;
			B = bitecolor[i][j].rgbtBlue;
			Y = (R + G + B) / 3;
			bitecolor[i][j].rgbtRed = Y;
			bitecolor[i][j].rgbtGreen = Y;
			bitecolor[i][j].rgbtBlue = Y;
		}
	createbmp(close, bitmapInfoHeader, bitmapFileHeader, bitecolor);
}

int comp(const void *i, const void *j)
{
	return *(int *)i - *(int *)j;
}
median(char close[], BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, Color **bitecolor)
{
	int R[9], B[9], G[9];

	for (int a = 1; a < bitmapInfoHeader.biHeight - 1; a++)
		for (int b = 1; b < bitmapInfoHeader.biWidth - 1; b++)
		{
			int k = 0;
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
				{
					R[k] = bitecolor[i + a][j + b].rgbtRed;
					G[k] = bitecolor[i + a][j + b].rgbtGreen;
					B[k] = bitecolor[i + a][j + b].rgbtBlue;
					k++;
				}
			qsort(R, 9, sizeof(int), comp);
			qsort(G, 9, sizeof(int), comp);
			qsort(B, 9, sizeof(int), comp);
			bitecolorcopy[a][b].rgbtBlue = B[4];
			bitecolorcopy[a][b].rgbtRed = R[4];
			bitecolorcopy[a][b].rgbtGreen = G[4];
		}
	createbmp(close, bitmapInfoHeader, bitmapFileHeader, bitecolorcopy);
}

gauss(char close[], int r, BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, Color **bitecolor)
{

	double gaussArray[5][5], div = 0;
	int pixelPosX, pixelPosY;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			gaussArray[i][j] = (double)(1 / (3.14 * 2 * r * r)) * exp((abs((5 / 2) - i) * abs((5 / 2) - i)) * (-1.0) / (2 * r * r));
			div += gaussArray[i][j];
		}

	for (int y = 2; y < bitmapInfoHeader.biHeight - 2; y++)
		for (int x = 2; x < bitmapInfoHeader.biWidth - 2; x++)
		{
			double rSum = 0, gSum = 0, bSum = 0, kSum = 0;
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
				{
					pixelPosX = x + j - 2;
					pixelPosY = y + i - 2;

					byte red = bitecolorcopy[pixelPosY][pixelPosX].rgbtRed;
					byte green = bitecolorcopy[pixelPosY][pixelPosX].rgbtGreen;
					byte blue = bitecolorcopy[pixelPosY][pixelPosX].rgbtBlue;

					rSum += red * gaussArray[i][j];
					gSum += green *gaussArray[i][j];
					bSum += blue * gaussArray[i][j];

					kSum += gaussArray[i][j];
				}

			if (kSum <= 0) kSum = 1;

			rSum /= kSum;
			if (rSum < 0) rSum = 0;
			if (rSum > 255) rSum = 255;

			gSum /= kSum;
			if (gSum < 0) gSum = 0;
			if (gSum > 255) gSum = 255;

			bSum /= kSum;
			if (bSum < 0) bSum = 0;
			if (bSum > 255) bSum = 255;

			bitecolorcopy[y][x].rgbtRed = (byte)rSum;
			bitecolorcopy[y][x].rgbtGreen = (byte)gSum;
			bitecolorcopy[y][x].rgbtBlue = (byte)bSum;
		}

	createbmp(close, bitmapInfoHeader, bitmapFileHeader, bitecolorcopy);
}



sobelx(char close[], BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, Color **bitecolor)
{
	int g[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
	int gy[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };

	int newry = 0, newgy = 0, newby = 0;
	int rcy, gcy, bcy;
	int newr = 0, newg = 0, newb = 0;
	int rc, gc, bc;

	for (int i = 1; i < bitmapInfoHeader.biHeight - 1; i++)
		for (int j = 1; j < bitmapInfoHeader.biWidth - 1; j++)
		{
			newry = 0; newgy = 0; newby = 0;
			rcy = 0; gcy = 0; bcy = 0;
			newr = 0; newg = 0; newb = 0;

			for (int wi = -1; wi < 2; wi++)
				for (int hw = -1; hw < 2; hw++)
				{
					rcy = bitecolor[i + hw][j + wi].rgbtRed;
					bcy = bitecolor[i + hw][j + wi].rgbtBlue;
					gcy = bitecolor[i + hw][j + wi].rgbtGreen;

					newry += gy[wi + 1][hw + 1] * rcy;
					newgy += gy[wi + 1][hw + 1] * gcy;
					newby += gy[wi + 1][hw + 1] * bcy;
					//	newr += g[wi + 1][hw + 1] * rcy;
					//	newg += g[wi + 1][hw + 1] * gcy;
					//	newb += g[wi + 1][hw + 1] * bcy;
				}

			int sum = sqrt((newb + newg + newr)*(newb + newg + newr) + (newby + newgy + newry) * (newby + newgy + newry));

			if (sum <= 101)
			{
				bitecolorcopy[i][j].rgbtBlue = 0;
				bitecolorcopy[i][j].rgbtGreen = 0;
				bitecolorcopy[i][j].rgbtRed = 0;
			}
			else
			{
				bitecolorcopy[i][j].rgbtBlue = 255;
				bitecolorcopy[i][j].rgbtGreen = 255;
				bitecolorcopy[i][j].rgbtRed = 255;
			}
		}

	createbmp(close, bitmapInfoHeader, bitmapFileHeader, bitecolorcopy);
}


sobely(char close[], BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, Color **bitecolor)
{
	int g[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
	int gy[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };

	int newry = 0, newgy = 0, newby = 0;
	int rcy, gcy, bcy;
	int newr = 0, newg = 0, newb = 0;
	int rc, gc, bc;

	for (int i = 1; i < bitmapInfoHeader.biHeight - 1; i++)
		for (int j = 1; j < bitmapInfoHeader.biWidth - 1; j++)
		{
			newry = 0; newgy = 0; newby = 0;
			rcy = 0; gcy = 0; bcy = 0;
			newr = 0; newg = 0; newb = 0;

			for (int wi = -1; wi < 2; wi++)
				for (int hw = -1; hw < 2; hw++)
				{
					rcy = bitecolor[i + hw][j + wi].rgbtRed;
					bcy = bitecolor[i + hw][j + wi].rgbtBlue;
					gcy = bitecolor[i + hw][j + wi].rgbtGreen;

					//	newry += gy[wi + 1][hw + 1] * rcy;
					//	newgy += gy[wi + 1][hw + 1] * gcy;
					//	newby += gy[wi + 1][hw + 1] * bcy;
					newr += g[wi + 1][hw + 1] * rcy;
					newg += g[wi + 1][hw + 1] * gcy;
					newb += g[wi + 1][hw + 1] * bcy;
				}

			int sum = sqrt((newb + newg + newr)*(newb + newg + newr) + (newby + newgy + newry) * (newby + newgy + newry));

			if (sum <= 101)
			{
				bitecolorcopy[i][j].rgbtBlue = 0;
				bitecolorcopy[i][j].rgbtGreen = 0;
				bitecolorcopy[i][j].rgbtRed = 0;
			}
			else
			{
				bitecolorcopy[i][j].rgbtBlue = 255;
				bitecolorcopy[i][j].rgbtGreen = 255;
				bitecolorcopy[i][j].rgbtRed = 255;
			}
		}

	createbmp(close, bitmapInfoHeader, bitmapFileHeader, bitecolorcopy);
}

int main(int argc, char *argv[])
{
	FILE *file;
	char *open, *close, *filters;
	//printf("Enter the path to the BMP, which you plan to change\n");
	open = argv[1];
	file = fopen(open, "rb");

	if (file == NULL)
	{
		printf("Error name\n");
	}

	//printf("Select filter: 0 - median, 1 - gauss, 2 - sobelx,3 -  sobely or 4 - grey\n");
	filters = argv[2];

	//printf("Enter the path to the BMP, where you plan to save the image\n");
	close = argv[3];

	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);

	bitecolor = (Color **)malloc(sizeof(Color*) * bitmapInfoHeader.biHeight);
	for (int j = 0; j < bitmapInfoHeader.biHeight; j++)
		bitecolor[j] = (Color *)malloc(sizeof(Color) * bitmapInfoHeader.biWidth);

	bitecolorcopy = (Color **)malloc(sizeof(Color*) * bitmapInfoHeader.biHeight);
	for (int j = 0; j < bitmapInfoHeader.biHeight; j++)
		bitecolorcopy[j] = (Color *)malloc(sizeof(Color) * bitmapInfoHeader.biWidth);
	buf = malloc(sizeof(char) * 4);
	for (int i = 0; i < bitmapInfoHeader.biHeight; i++)
	{
		for (int j = 0; j < bitmapInfoHeader.biWidth; j++)
		{
			fread(&(bitecolor[i][j]), sizeof(bitecolor[i][j]), 1, file);
			if (bitmapInfoHeader.biBitCount == 32) fread(&buf, 1, 1, file);
			bitecolorcopy[i][j] = bitecolor[i][j];
		}
		if (bitmapInfoHeader.biBitCount == 24) fread(buf, sizeof(BYTE), bitmapInfoHeader.biWidth % 4, file);
	}

	//createbmp(close, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	if (filters[0] == '4') grey(close, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	if (filters[0] == '0') median(close, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	if (filters[0] == '1') gauss(close, 10, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	if (filters[0] == '2') sobelx(close, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	if (filters[0] == '3') sobely(close, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	return 0;
}