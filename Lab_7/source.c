#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void print_info(BITMAPFILEHEADER bfh, BITMAPINFOHEADER bih)
{
	printf("bfh.bfType ----- %x\n", bfh.bfType);
	printf("bfh.bfSize ----- %d\n", bfh.bfSize);
	printf("bfh.bfOffBits -- %d (=size of headers)\n", bfh.bfOffBits);
	printf("bih.biSize ----- %d\n", bih.biSize);
	printf("bih.biWidth ---- %d\n", bih.biWidth);
	printf("bih.biHeight --- %d\n", bih.biHeight);
	printf("bih.biPlanes --- %d\n", bih.biPlanes);
	printf("bih.biBitCount - %d\n", bih.biBitCount);
	printf("bih.biClrUsed -- %d\n", bih.biClrUsed);
	printf("padding = %d\n", -((bih.biWidth * bih.biBitCount / 8) % 4) + 4);
	printf("size of headers = %d\n", (int)((sizeof(bfh) + sizeof(bih))));
}

void GRAY(RGBTRIPLE* pic, int W, int H)
{
	for (int i = 0; i < W * H; i++)
		pic[i].rgbtBlue  = 
		pic[i].rgbtGreen = 
		pic[i].rgbtRed   = (pic[i].rgbtRed + pic[i].rgbtGreen + pic[i].rgbtBlue) / 3;
}

void GAUSS(RGBTRIPLE* pic, RGBTRIPLE* pic_copy, int W, int H)
{
	int mask[3][3] = { { 1, 2, 1 },
					   { 2, 4, 2 },
					   { 1, 2, 1 } };
	for (int i = 1; i < H - 1; i++)
		for (int j = 1; j < W - 1; j++)
		{
			pic[i * W + j].rgbtBlue = ( pic_copy[(i - 1) * W + j - 1].rgbtBlue *  mask[0][0] +
								  	    pic_copy[(i - 1) * W + j    ].rgbtBlue *  mask[0][1] +
									    pic_copy[(i - 1) * W + j + 1].rgbtBlue *  mask[0][2] +
									    pic_copy[(i    ) * W + j - 1].rgbtBlue *  mask[1][0] +
									    pic_copy[(i    ) * W + j    ].rgbtBlue *  mask[1][1] +
									    pic_copy[(i    ) * W + j + 1].rgbtBlue *  mask[1][2] +
									    pic_copy[(i + 1) * W + j - 1].rgbtBlue *  mask[2][0] +
									    pic_copy[(i + 1) * W + j    ].rgbtBlue *  mask[2][1] +
									    pic_copy[(i + 1) * W + j + 1].rgbtBlue *  mask[2][2] ) / 16;

			pic[i * W + j].rgbtRed =  ( pic_copy[(i - 1) * W + j - 1].rgbtRed  *  mask[0][0] +
								  	    pic_copy[(i - 1) * W + j    ].rgbtRed  *  mask[0][1] +
									    pic_copy[(i - 1) * W + j + 1].rgbtRed  *  mask[0][2] +
									    pic_copy[(i    ) * W + j - 1].rgbtRed  *  mask[1][0] +
									    pic_copy[(i    ) * W + j    ].rgbtRed  *  mask[1][1] +
									    pic_copy[(i    ) * W + j + 1].rgbtRed  *  mask[1][2] +
									    pic_copy[(i + 1) * W + j - 1].rgbtRed  *  mask[2][0] +
									    pic_copy[(i + 1) * W + j    ].rgbtRed  *  mask[2][1] +
									    pic_copy[(i + 1) * W + j + 1].rgbtRed  *  mask[2][2] ) / 16;

			pic[i * W + j].rgbtGreen = (pic_copy[(i - 1) * W + j - 1].rgbtGreen * mask[0][0] +
								  	    pic_copy[(i - 1) * W + j    ].rgbtGreen * mask[0][1] +
									    pic_copy[(i - 1) * W + j + 1].rgbtGreen * mask[0][2] +
									    pic_copy[(i    ) * W + j - 1].rgbtGreen * mask[1][0] +
									    pic_copy[(i    ) * W + j    ].rgbtGreen * mask[1][1] +
									    pic_copy[(i    ) * W + j + 1].rgbtGreen * mask[1][2] +
									    pic_copy[(i + 1) * W + j - 1].rgbtGreen * mask[2][0] +
									    pic_copy[(i + 1) * W + j    ].rgbtGreen * mask[2][1] +
									    pic_copy[(i + 1) * W + j + 1].rgbtGreen * mask[2][2] ) / 16;
		}
}

void SOBEL(int mode, RGBTRIPLE* pic, RGBTRIPLE* pic_copy, int W, int H)
{
	int soft_border = 20;
	int medium_border = 65;
	int hard_border = 110;
	int resX, resY;
	int maskX[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
	int maskY[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
	
	for (int i = 1; i < H - 1; i++)
		for (int j = 1; j < W - 1; j++)
		{ 
			resX =                     
				( pic_copy[(i - 1) * W + j - 1].rgbtBlue *  maskX[0][0] +
				  pic_copy[(i - 1) * W + j - 1].rgbtRed  *  maskX[0][0] +
				  pic_copy[(i - 1) * W + j - 1].rgbtGreen * maskX[0][0] ) / 3 +
				( pic_copy[(i - 1) * W + j    ].rgbtBlue *  maskX[0][1] +
				  pic_copy[(i - 1) * W + j    ].rgbtRed  *  maskX[0][1] +
				  pic_copy[(i - 1) * W + j    ].rgbtGreen * maskX[0][1] ) / 3 +
				( pic_copy[(i - 1) * W + j + 1].rgbtBlue *  maskX[0][2] +
				  pic_copy[(i - 1) * W + j + 1].rgbtRed  *  maskX[0][2] +
				  pic_copy[(i - 1) * W + j + 1].rgbtGreen * maskX[0][2] ) / 3 +
				( pic_copy[(i    ) * W + j - 1].rgbtBlue *  maskX[1][0] +
				  pic_copy[(i    ) * W + j - 1].rgbtRed  *  maskX[1][0] +
				  pic_copy[(i    ) * W + j - 1].rgbtGreen * maskX[1][0] ) / 3 +
				( pic_copy[(i    ) * W + j    ].rgbtBlue *  maskX[1][1] +
				  pic_copy[(i    ) * W + j    ].rgbtRed  *  maskX[1][1] +
				  pic_copy[(i    ) * W + j    ].rgbtGreen * maskX[1][1] ) / 3 +
				( pic_copy[(i    ) * W + j + 1].rgbtBlue *  maskX[1][2] +
				  pic_copy[(i    ) * W + j + 1].rgbtRed  *  maskX[1][2] +
				  pic_copy[(i    ) * W + j + 1].rgbtGreen * maskX[1][2] ) / 3 +
				( pic_copy[(i + 1) * W + j - 1].rgbtBlue *  maskX[2][0] +
				  pic_copy[(i + 1) * W + j - 1].rgbtRed  *  maskX[2][0] +
				  pic_copy[(i + 1) * W + j - 1].rgbtGreen * maskX[2][0] ) / 3 +
				( pic_copy[(i + 1) * W + j    ].rgbtBlue *  maskX[2][1] +
				  pic_copy[(i + 1) * W + j    ].rgbtRed  *  maskX[2][1] +
				  pic_copy[(i + 1) * W + j    ].rgbtGreen * maskX[2][1] ) / 3 +
				( pic_copy[(i + 1) * W + j + 1].rgbtBlue *  maskX[2][2] +
				  pic_copy[(i + 1) * W + j + 1].rgbtRed  *  maskX[2][2] +
				  pic_copy[(i + 1) * W + j + 1].rgbtGreen * maskX[2][2] ) / 3 ;

			resY =                     
				( pic_copy[(i - 1) * W + j - 1].rgbtBlue *  maskY[0][0] +
				  pic_copy[(i - 1) * W + j - 1].rgbtRed  *  maskY[0][0] +
				  pic_copy[(i - 1) * W + j - 1].rgbtGreen * maskY[0][0] ) / 3 +
				( pic_copy[(i - 1) * W + j    ].rgbtBlue *  maskY[0][1] +
				  pic_copy[(i - 1) * W + j    ].rgbtRed  *  maskY[0][1] +
				  pic_copy[(i - 1) * W + j    ].rgbtGreen * maskY[0][1] ) / 3 +
				( pic_copy[(i - 1) * W + j + 1].rgbtBlue *  maskY[0][2] +
				  pic_copy[(i - 1) * W + j + 1].rgbtRed  *  maskY[0][2] +
				  pic_copy[(i - 1) * W + j + 1].rgbtGreen * maskY[0][2] ) / 3 +
				( pic_copy[(i    ) * W + j - 1].rgbtBlue *  maskY[1][0] +
				  pic_copy[(i    ) * W + j - 1].rgbtRed  *  maskY[1][0] +
				  pic_copy[(i    ) * W + j - 1].rgbtGreen * maskY[1][0] ) / 3 +
				( pic_copy[(i    ) * W + j    ].rgbtBlue *  maskY[1][1] +
				  pic_copy[(i    ) * W + j    ].rgbtRed  *  maskY[1][1] +
				  pic_copy[(i    ) * W + j    ].rgbtGreen * maskY[1][1] ) / 3 +
				( pic_copy[(i    ) * W + j + 1].rgbtBlue *  maskY[1][2] +
				  pic_copy[(i    ) * W + j + 1].rgbtRed  *  maskY[1][2] +
				  pic_copy[(i    ) * W + j + 1].rgbtGreen * maskY[1][2] ) / 3 +
				( pic_copy[(i + 1) * W + j - 1].rgbtBlue *  maskY[2][0] +
				  pic_copy[(i + 1) * W + j - 1].rgbtRed  *  maskY[2][0] +
				  pic_copy[(i + 1) * W + j - 1].rgbtGreen * maskY[2][0] ) / 3 +
				( pic_copy[(i + 1) * W + j    ].rgbtBlue *  maskY[2][1] +
				  pic_copy[(i + 1) * W + j    ].rgbtRed  *  maskY[2][1] +
				  pic_copy[(i + 1) * W + j    ].rgbtGreen * maskY[2][1] ) / 3 +
				( pic_copy[(i + 1) * W + j + 1].rgbtBlue *  maskY[2][2] +
				  pic_copy[(i + 1) * W + j + 1].rgbtRed  *  maskY[2][2] +
				  pic_copy[(i + 1) * W + j + 1].rgbtGreen * maskY[2][2] ) / 3 ;

			if (mode == 2)
				resX = 0;
			if (mode == 1)
				resY = 0;

			resX = (int)sqrt(resX * resX + resY * resY);

			if ( resX <= soft_border)
			{
				pic[i * W + j].rgbtBlue =
				pic[i * W + j].rgbtRed =
				pic[i * W + j].rgbtGreen = 120;
			}
			if (resX > soft_border)
			{
				pic[i * W + j].rgbtBlue =
				pic[i * W + j].rgbtRed =
				pic[i * W + j].rgbtGreen = 105;
			}
			if (resX > medium_border)
			{
				pic[i * W + j].rgbtBlue =
				pic[i * W + j].rgbtRed =
				pic[i * W + j].rgbtGreen = 90;
			}
			if (resX > hard_border)
			{
				pic[i * W + j].rgbtBlue =
				pic[i * W + j].rgbtRed =
				pic[i * W + j].rgbtGreen = 80;
			}
		}
}

int cmpfunc(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void MEDIAN(RGBTRIPLE* pic, RGBTRIPLE* pic_copy, int W, int H)
{
	int tempR[9];
	int tempG[9];
	int tempB[9];
	for (int i = 1; i < H - 1; i++)
		for (int j = 1; j < W - 1; j++)
		{			
			tempB[0] = pic_copy[(i - 1) * W + j - 1].rgbtBlue;
			tempB[1] = pic_copy[(i - 1) * W + j    ].rgbtBlue;
			tempB[2] = pic_copy[(i - 1) * W + j + 1].rgbtBlue;
			tempB[3] = pic_copy[(i    ) * W + j - 1].rgbtBlue; 
			tempB[4] = pic_copy[(i    ) * W + j    ].rgbtBlue;
			tempB[5] = pic_copy[(i    ) * W + j + 1].rgbtBlue; 
			tempB[6] = pic_copy[(i + 1) * W + j - 1].rgbtBlue;
			tempB[7] = pic_copy[(i + 1) * W + j    ].rgbtBlue;
			tempB[8] = pic_copy[(i + 1) * W + j + 1].rgbtBlue;

			tempG[0] = pic_copy[(i - 1) * W + j - 1].rgbtGreen;
			tempG[1] = pic_copy[(i - 1) * W + j    ].rgbtGreen;
			tempG[2] = pic_copy[(i - 1) * W + j + 1].rgbtGreen;
			tempG[3] = pic_copy[(i    ) * W + j - 1].rgbtGreen; 
			tempG[4] = pic_copy[(i    ) * W + j    ].rgbtGreen;
			tempG[5] = pic_copy[(i    ) * W + j + 1].rgbtGreen; 
			tempG[6] = pic_copy[(i + 1) * W + j - 1].rgbtGreen;
			tempG[7] = pic_copy[(i + 1) * W + j    ].rgbtGreen;
			tempG[8] = pic_copy[(i + 1) * W + j + 1].rgbtGreen;

			tempR[0] = pic_copy[(i - 1) * W + j - 1].rgbtRed;
			tempR[1] = pic_copy[(i - 1) * W + j    ].rgbtRed;
			tempR[2] = pic_copy[(i - 1) * W + j + 1].rgbtRed;
			tempR[3] = pic_copy[(i    ) * W + j - 1].rgbtRed; 
			tempR[4] = pic_copy[(i    ) * W + j    ].rgbtRed;
			tempR[5] = pic_copy[(i    ) * W + j + 1].rgbtRed; 
			tempR[6] = pic_copy[(i + 1) * W + j - 1].rgbtRed;
			tempR[7] = pic_copy[(i + 1) * W + j    ].rgbtRed;
			tempR[8] = pic_copy[(i + 1) * W + j + 1].rgbtRed;

			qsort(tempR, 9, sizeof(int), cmpfunc);
			qsort(tempG, 9, sizeof(int), cmpfunc);
			qsort(tempB, 9, sizeof(int), cmpfunc);
			pic[i* W + j].rgbtRed = tempR[8];
			pic[i* W + j].rgbtGreen = tempG[8];
			pic[i* W + j].rgbtBlue = tempB[8];
		}
}

int main(int argc, char *argv[])
{
	//if (argc < 2 || argc > 4)
	//{
	//	printf("Incorrect comand line arguments\n must be: \n input_file(at least) \nfilter( XSOBEL, YSOBEL, SOBEL(default), GAUSS, GRAY, MEDIAN) \n output file \n");
	//	return 0;
	//}

	FILE * bmp;

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	const char *file_name = "1.bmp";

	bmp = fopen(file_name, "rb");
	if (bmp == NULL)
	{
		printf("Error: Cannot open file\n");
		fclose(bmp);
		return 0;
	}

	//char* filters[6] = { "GRAY", "GAUSS", "SOBELX", "SOBELY", "SOBELXY", "MEDIAN"};
	//int filter = 0;
	//for (filter = 0; filter <= 6; filter++)
	//{
	//	if (filter == 6)
	//		break;
	//	if (strcmp(filters[filter], argv[2]) == 0)
	//		break;
	//}

	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, bmp);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, bmp);
	fseek(bmp, bfh.bfOffBits, SEEK_SET);

	if (bfh.bfType != 0x4d42 && bfh.bfType != 0x4349 && bfh.bfType != 0x5450)
	{
		fclose(bmp);
		printf("Error: file is not bmp\n");
		return 0;
	}

	RGBTRIPLE *pic;
	RGBTRIPLE *pic_copy;
	char *trash;
	char *alpha;
	alpha = NULL;
	trash = malloc(sizeof(char) * 4);

	int padding = -((bih.biWidth * bih.biBitCount / 8) % 4) + 4;
	pic = malloc(bih.biWidth * bih.biHeight * sizeof(RGBTRIPLE));

	if (bih.biBitCount == 24)
	{
		for (int i = 0; i < bih.biHeight; i++)
		{
			for (int j = 0; j < bih.biWidth; j++)
			{
				fread(&pic[i * bih.biWidth + j], sizeof(RGBTRIPLE), 1, bmp);
			}
			fread(trash, sizeof(BYTE), padding, bmp);
		}
	}
	else if (bih.biBitCount == 32)
	{
		alpha = malloc(bih.biWidth * bih.biHeight * sizeof(BYTE));
		for (int i = 0; i < bih.biHeight; i++)
		{
			for (int j = 0; j < bih.biWidth; j++)
			{
				fread(&pic[i * bih.biWidth + j], sizeof(RGBTRIPLE), 1, bmp);
				fread(&alpha[i * bih.biWidth + j], sizeof(BYTE), 1, bmp);
			}
			fread(trash, sizeof(BYTE), padding, bmp);
		}
	}
	pic_copy = malloc(bih.biWidth * bih.biHeight * sizeof(RGBTRIPLE));
	memcpy(pic_copy, pic, bih.biWidth * bih.biHeight * sizeof(RGBTRIPLE));
	fclose (bmp);

	print_info(bfh, bih);

	int input = 9;
	printf("0 - gray\n");
	printf("1 - gauss\n");
	printf("2 - sobel x\n");
	printf("3 - sobel y\n");
	printf("4 - sobel xy\n");
	printf("5 - median\n");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		GRAY(pic, bih.biWidth, bih.biHeight);
		break;
	case 1:
		for (int i = 1; i <= 15; i++)
		{
			GAUSS(pic, pic_copy, bih.biWidth, bih.biHeight);
			memcpy(pic_copy, pic, bih.biWidth * bih.biHeight * sizeof(RGBTRIPLE));
			printf("gauss x %d\n", i);
		   }
		break;
	case 2:
		SOBEL(1, pic, pic_copy, bih.biWidth, bih.biHeight);
		break;
	case 3:
		SOBEL(2, pic, pic_copy, bih.biWidth, bih.biHeight);
		break;
	case 4:
		SOBEL(3, pic, pic_copy, bih.biWidth, bih.biHeight);
		break;
	case 5:
		MEDIAN(pic, pic_copy, bih.biWidth, bih.biHeight);
		break;
	default:
		printf("Incorrect name of filter\n");
		return 0;
		break;
	}

	FILE *new_bmp;

	new_bmp = fopen("new_.bmp", "wb");
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, new_bmp);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, new_bmp);
	for (int i = 0; i < bih.biHeight; i++)
	{
		for (int j = 0; j < bih.biWidth; j++)
		{
			fwrite(&pic[i * bih.biWidth + j], sizeof(RGBTRIPLE), 1, new_bmp);
		}
		fwrite(trash, sizeof(char), padding, new_bmp);
	}

	fclose(new_bmp);
	free(pic);
	free(pic_copy);
	free(trash);
	free(alpha);

	_getch();
}
