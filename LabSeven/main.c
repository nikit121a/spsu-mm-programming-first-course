#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>
#include <windows.h>
#include <math.h>

RGBQUAD **bitmapImage32;					//информация о цветах
RGBTRIPLE **bitmapImage24;
char *buf;
RGBQUAD **temp32;
RGBTRIPLE **temp24;


//fseek(FILE *stream, long int offset, int origin);
//устанавливает указатель текущей позиции файла, связанного с 
//потоком stream, в соответствии со значениями начала отсчета origin и смещения offset.

//fread(void *буфер, size_t колич_байт, size_t счетчик, FILE *уф);
//fwrite(const void *буфер, size_t колич_байт, size_t счетчик, FILE *уф);
//Значение счетчик определяет, сколько считывается или записывается элементов данных, причем
// длина каждого элемента в байтах равна колич_байт. (Вспомните, что тип size_t определяется как одна
// из разновидностей целого типа без знака.) И, наконец, уф — это указатель файла, то есть на уже открытый поток. 

//fopen(const char *fname, const char *mode);
//открывает файл, имя которого задается параметром fname, и возвращает указатель на поток, связанный с этим файлом.

int LoadBitmapFile(BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader, char argv)
{
	FILE *fileEnter;						//указатель на картинку						


											//октрываем нашу картинку
	fileEnter = fopen(argv, "rb");
	if (fileEnter == NULL)
	{
		return NULL;
	}
	//считываем иформацию заголовка
	fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fileEnter);
	//проверяем, бмп файл или нет

	//считываем информацию о файле
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fileEnter);

	if (bitmapInfoHeader->biBitCount == 32)
	{
		//выделяем память для переменной, содержащей основную информацию о цветах
		temp32 = (RGBQUAD **)malloc(sizeof(RGBQUAD*)* bitmapInfoHeader->biHeight);
		bitmapImage32 = (RGBQUAD **)malloc(sizeof(RGBQUAD*)* bitmapInfoHeader->biHeight);
		for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
		{
			bitmapImage32[i] = (RGBQUAD *)malloc(sizeof(RGBQUAD)* bitmapInfoHeader->biWidth + 4 - bitmapInfoHeader->biWidth % 4);
			temp32[i] = (RGBQUAD *)malloc(sizeof(RGBQUAD)* bitmapInfoHeader->biWidth);
		}
		//проверям, выделилась ли память
		if (!bitmapImage32)
		{
			free(bitmapImage32);
			fclose(fileEnter);
			return NULL;
		}
		//передвигаем указатель в нашем файле на начало информации о цветах
		fseek(fileEnter, bitmapFileHeader->bfOffBits, SEEK_SET);
		//считываем пиксели
		for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
		{
			for (int l = 0; l < bitmapInfoHeader->biWidth; l++)
			{
				fread(&bitmapImage32[i][l], sizeof(RGBQUAD), 1, fileEnter);
				memcpy(&temp32[i][l], &bitmapImage32[i][l], sizeof(RGBQUAD));
			}
		}
		fclose(fileEnter);
	}
	else
	{
		//выделяем память для переменной, содержащей основную информацию о цветах
		temp24 = (RGBTRIPLE **)malloc(sizeof(RGBTRIPLE*)* bitmapInfoHeader->biHeight);
		bitmapImage24 = (RGBTRIPLE **)malloc(sizeof(RGBTRIPLE*)* bitmapInfoHeader->biHeight);
		for (int i = 0; i <= bitmapInfoHeader->biHeight; i++)
		{
			temp24[i] = (RGBTRIPLE *)malloc(sizeof(RGBTRIPLE)* bitmapInfoHeader->biWidth);
			bitmapImage24[i] = (RGBTRIPLE *)malloc(sizeof(RGBTRIPLE)* bitmapInfoHeader->biWidth);
		}
		//проверям, выделилась ли память
		if (!bitmapImage24)
		{
			free(bitmapImage24);
			fclose(fileEnter);
			return NULL;
		}
		//передвигаем указатель в нашем файле на начало информации о цветах
		fseek(fileEnter, bitmapFileHeader->bfOffBits, SEEK_SET);

		buf = malloc(sizeof(char) * 4);

		int padding = (-((bitmapInfoHeader->biWidth * bitmapInfoHeader->biBitCount / 8) % 4) + 4) % 4;

		for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
		{
			for (int j = 0; j < bitmapInfoHeader->biWidth; j++)
			{
				fread(&bitmapImage24[i][j], sizeof(RGBTRIPLE), 1, fileEnter);
				memcpy(&temp24[i][j], &bitmapImage24[i][j], sizeof(RGBTRIPLE));
			}
			fread(buf, sizeof(BYTE), padding, fileEnter);
		}
	}
	//закрываем наш файл и возвращаем указатель на информацию о цветах
	fclose(fileEnter);
	return 1;
}

int ExitBitmapFile(BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader, char argv)
{
	FILE *fileExit;							//указатель на картинку						

	fileExit = fopen(argv, "wb");		//октрываем нашу картинку
	if (fileExit == NULL)
	{
		return NULL;
	}

	//вписываем иформацию заголовка
	fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fileExit);

	//вписываем информацию о файле
	fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fileExit);
	//передвигаем указатель в нашем файле на начало информации о цветах
	//fseek(fileExit, bitmapFileHeader->bfOffBits, SEEK_SET);

	if (bitmapInfoHeader->biBitCount == 32)
	{
		for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
		{
			for (int l = 0; l < bitmapInfoHeader->biWidth; l++)
			{
				fwrite(&(bitmapImage32[i][l]), sizeof(RGBQUAD), 1, fileExit);
			}
		}
	}
	else
	{
		int padding = (-((bitmapInfoHeader->biWidth * bitmapInfoHeader->biBitCount / 8) % 4) + 4) % 4;
		for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
		{
			for (int l = 0; l < bitmapInfoHeader->biWidth; l++)
			{
				fwrite(&(bitmapImage24[i][l]), sizeof(RGBTRIPLE), 1, fileExit);
			}
			fwrite(buf, sizeof(char), padding, fileExit);;
		}
	}
	//закрываем наш файл
	fclose(fileExit);
	return 0;
}

int gray(long W, long H, BITMAPINFOHEADER bih)
{
	if (bih.biBitCount == 32)
	{

		for (int i = 1; i < H - 1; i++)
		{
			for (int l = 1; l < W - 1; l++)
			{
				int b = bitmapImage32[i][l].rgbBlue;
				int g = bitmapImage32[i][l].rgbGreen;
				int r = bitmapImage32[i][l].rgbRed;
				int sum = (r + b + g) / 3;
				bitmapImage32[i][l].rgbBlue = sum;
				bitmapImage32[i][l].rgbGreen = sum;
				bitmapImage32[i][l].rgbRed = sum;
			}
		}
	}
	else
	{
		for (int i = 1; i < H - 1; i++)
		{
			for (int l = 1; l < W - 1; l++)
			{
				int b = bitmapImage24[i][l].rgbtBlue;
				int g = bitmapImage24[i][l].rgbtGreen;
				int r = bitmapImage24[i][l].rgbtRed;
				int sum = (r + b + g) / 3;
				bitmapImage24[i][l].rgbtBlue = sum;
				bitmapImage24[i][l].rgbtGreen = sum;
				bitmapImage24[i][l].rgbtRed = sum;
			}
		}
	}
	return 1;
}
int compare(const void *i, const void *j)
{
	return *(int *)i - *(int *)j;
}
int median(long W, long H, BITMAPINFOHEADER bih)
{

	if (bih.biBitCount == 32)
	{
		for (int x = 1; x < H - 1; x++)
		{
			for (int y = 1; y < W - 1; y++)
			{
				static int k = 0;
				int b[9], g[9], r[9];
				for (int i = -1; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						b[k] = temp32[x + i][y + j].rgbBlue;
						g[k] = temp32[x + i][y + j].rgbGreen;
						r[k] = temp32[x + i][y + j].rgbRed;
						k++;
					}
				}
				k = 0;
				qsort(b, 9, sizeof(int), compare);
				qsort(g, 9, sizeof(int), compare);
				qsort(r, 9, sizeof(int), compare);
				bitmapImage32[x][y].rgbBlue = b[7];
				bitmapImage32[x][y].rgbGreen = g[7];
				bitmapImage32[x][y].rgbRed = r[7];
			}
		}
	}
	else
	{
		for (int x = 1; x < H - 1; x++)
		{
			for (int y = 1; y < W - 1; y++)
			{
				static int k = 0;
				int b[9], g[9], r[9];
				for (int i = -1; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						b[k] = temp24[x + i][y + j].rgbtBlue;
						g[k] = temp24[x + i][y + j].rgbtGreen;
						r[k] = temp24[x + i][y + j].rgbtRed;
						k++;
					}
				}
				k = 0;
				qsort(b, 9, sizeof(int), compare);
				qsort(g, 9, sizeof(int), compare);
				qsort(r, 9, sizeof(int), compare);
				bitmapImage24[x][y].rgbtBlue = b[7];
				bitmapImage24[x][y].rgbtGreen = g[7];
				bitmapImage24[x][y].rgbtRed = r[7];
			}
		}
	}
	return 1;
}

int gauss(long W, long H, BITMAPINFOHEADER bih)
{
	int mask[3][3] = { { 1,2,1 } ,{ 2, 4, 2 } ,{ 1, 2, 1 } };
	int b = 0, g = 0, r = 0;
	if (bih.biBitCount == 32)
	{
		for (int x = 1; x < H - 1; x++)
		{
			for (int y = 1; y < W - 1; y++)
			{
				for (int i = -1; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						b += temp32[x + i][y + j].rgbBlue * mask[i + 1][j + 1];
						g += temp32[x + i][y + j].rgbGreen * mask[i + 1][j + 1];
						r += temp32[x + i][y + j].rgbRed * mask[i + 1][j + 1];
					}
				}
				bitmapImage32[x][y].rgbBlue = b / 16;
				bitmapImage32[x][y].rgbGreen = g / 16;
				bitmapImage32[x][y].rgbRed = r / 16;
				b = g = r = 0;
			}
		}
	}
	else
	{
		for (int x = 1; x < H - 1; x++)
		{
			for (int y = 1; y < W - 1; y++)
			{
				for (int i = -1; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						b += temp24[x + i][y + j].rgbtBlue * mask[i + 1][j + 1];
						g += temp24[x + i][y + j].rgbtGreen * mask[i + 1][j + 1];
						r += temp24[x + i][y + j].rgbtRed * mask[i + 1][j + 1];
					}
				}
				bitmapImage24[x][y].rgbtBlue = b / 16;
				bitmapImage24[x][y].rgbtGreen = g / 16;
				bitmapImage24[x][y].rgbtRed = r / 16;
				b = g = r = 0;
			}
		}
	}
	return 1;
}

int sobel(long W, long H, BITMAPINFOHEADER bih, char value)
{
	int maskX[3][3] = { { 3,10,3 } ,{ 0, 0, 0 } ,{ -3, -10, -3 } };
	int maskY[3][3] = { { 3, 0, -3 } ,{ 10, 0, -10 } ,{ 3, 0, -3 } };
	int limit = 101;
	if (bih.biBitCount == 32)
	{
		for (int x = 1; x < H - 1; x++)
		{
			for (int y = 1; y < W - 1; y++)
			{
				int bY = 0, gY = 0, rY = 0;
				int bX = 0, gX = 0, rX = 0;
				if (value == 'X')
				{
					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							bX += temp32[x + i][y + j].rgbBlue * maskX[i + 1][j + 1] / 3;
							gX += temp32[x + i][y + j].rgbGreen * maskX[i + 1][j + 1] / 3;
							rX += temp32[x + i][y + j].rgbRed * maskX[i + 1][j + 1] / 3;
						}
					}
				}
				else
				{
					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							bY += temp32[x + i][y + j].rgbBlue * maskY[i + 1][j + 1] / 3;
							gY += temp32[x + i][y + j].rgbGreen * maskY[i + 1][j + 1] / 3;
							rY += temp32[x + i][y + j].rgbRed * maskY[i + 1][j + 1] / 3;
						}
					}
				}
				int sumX = bX + rX + gX;
				int sumY = bY + rY + gY;
				int sum = sqrt(sumX * sumX + sumY * sumY);
				if (sum <= limit)
				{
					bitmapImage32[x][y].rgbBlue = 0;
					bitmapImage32[x][y].rgbGreen = 0;
					bitmapImage32[x][y].rgbRed = 0;
				}
				else
				{
					bitmapImage32[x][y].rgbBlue = 255;
					bitmapImage32[x][y].rgbGreen = 255;
					bitmapImage32[x][y].rgbRed = 255;
				}
			}
		}
	}
	else
	{
		for (int x = 1; x < H - 1; x++)
		{
			for (int y = 1; y < W - 1; y++)
			{
				int bX = 0, gX = 0, rX = 0;
				int bY = 0, gY = 0, rY = 0;
				if (value == 'X')
				{
					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							bX += temp24[x + i][y + j].rgbtBlue * maskX[i + 1][j + 1] / 3;
							gX += temp24[x + i][y + j].rgbtGreen * maskX[i + 1][j + 1] / 3;
							rX += temp24[x + i][y + j].rgbtRed * maskX[i + 1][j + 1] / 3;
						}
					}
				}
				else
				{
					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							bY += temp24[x + i][y + j].rgbtBlue * maskY[i + 1][j + 1] / 3;
							gY += temp24[x + i][y + j].rgbtGreen * maskY[i + 1][j + 1] / 3;
							rY += temp24[x + i][y + j].rgbtRed * maskY[i + 1][j + 1] / 3;
						}
					}
				}
				int sumX = bX + rX + gX;
				int sumY = bY + rY + gY;
				int sum = sqrt(sumX * sumX + sumY * sumY);
				if (sum <= limit)
				{
					bitmapImage24[x][y].rgbtBlue = 0;
					bitmapImage24[x][y].rgbtGreen = 0;
					bitmapImage24[x][y].rgbtRed = 0;
				}
				else
				{
					bitmapImage24[x][y].rgbtBlue = 255;
					bitmapImage24[x][y].rgbtGreen = 255;
					bitmapImage24[x][y].rgbtRed = 255;
				}
			}
		}
	}
	return 1;
}


int main(int argc, char *argv[])
{
	// Объявляем структуры
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	long weight, hight;

	LoadBitmapFile(&bih, &bfh, argv[1]);
	weight = bih.biWidth;
	hight = bih.biHeight;

	printf_s("Enter number of filter:\n 0-MEDIAN\n 1-GAUSS\n 2-SOBELX\n 3-SOBELY\n 4-GREY\n");
	int filter;
	scanf_s("%i", &filter);
	switch (filter)
	{
	case (0) :
		median(weight, hight, bih);
		break;
	case (1) :
		for (int l = 0; l < 10; l++)
		{
			gauss(weight, hight, bih);
			for (int i = 0; i < bih.biHeight; i++)
			{
				for (int j = 0; j < bih.biWidth; j++)
				{
					memcpy(&temp24[i][j], &bitmapImage24[i][j], sizeof(RGBTRIPLE));
				}
			}
		}
			 break;
	case (2) :
		sobel(weight, hight, bih, 'X');
		break;
	case (3) :
		sobel(weight, hight, bih, 'Y');
		break;
	case (4) :
		gray(weight, hight, bih);
		break;
	}
	ExitBitmapFile(&bih, &bfh, argv[2]);
	if (bih.biBitCount == 32)
	{
		free(bitmapImage32);
		free(temp32);
	}
	else
	{
		free(bitmapImage24);
		free(buf);
		free(temp24);
	}
	return 0;
}




