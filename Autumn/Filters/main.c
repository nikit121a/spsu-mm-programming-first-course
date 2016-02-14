#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include < math.h >

BITMAPFILEHEADER bitmapFileHeader;
BITMAPINFOHEADER bitmapInfoHeader;
RGBQUAD **bitecolor;

//	printf("%d %d %d %d ", bitecolor[i][j].rgbBlue, bitecolor[i][j].rgbGreen, bitecolor[i][j].rgbRed, bitecolor[i][j].rgbReserved);

int comp(const void *i, const void *j)
{
	return *(int *)i - *(int *)j;
}

median(BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, RGBQUAD **bitecolor)
{
	int R[9], B[9], G[9];

	for (int a = 1; a < bitmapInfoHeader.biWidth - 1; a++)
		for (int b = 1; b < bitmapInfoHeader.biHeight - 1; b++)
		{
			int k = 0;
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
				{
					R[k] = bitecolor[i + a][j + b].rgbRed;
					G[k] = bitecolor[i + a][j + b].rgbGreen;
					B[k] = bitecolor[i + a][j + b].rgbBlue;
					k++;
				}
			qsort(R, 9, sizeof(int), comp);
			qsort(G, 9, sizeof(int), comp);
			qsort(B, 9, sizeof(int), comp);
			bitecolor[a][b].rgbBlue = B[4];
			bitecolor[a][b].rgbRed = R[4];
			bitecolor[a][b].rgbGreen = G[4];
		}


	createbmp(bitmapInfoHeader, bitmapFileHeader, bitecolor);

}

grey(BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, RGBQUAD **bitecolor)
{
	int R, G, B, Y;

	for (int i = 0; i < bitmapInfoHeader.biWidth; i++)
		for (int j = 0; j < bitmapInfoHeader.biHeight; j++)
		{
			R = bitecolor[i][j].rgbRed;
			G = bitecolor[i][j].rgbGreen;
			B = bitecolor[i][j].rgbBlue;
			Y = 0.299 * R + 0.587 * G + 0.114 * B;
			bitecolor[i][j].rgbRed = Y;
			bitecolor[i][j].rgbGreen = Y;
			bitecolor[i][j].rgbBlue = Y;
		}
	createbmp(bitmapInfoHeader, bitmapFileHeader, bitecolor);
}

RGBQUAD **newbitecolor;
gauss(int r, BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, RGBQUAD **bitecolor)
{

	newbitecolor = (RGBQUAD **)malloc(sizeof(RGBQUAD*) * bitmapInfoHeader.biWidth);
	for (int j = 0; j < bitmapInfoHeader.biWidth; j++)
		newbitecolor[j] = (RGBQUAD *)malloc(sizeof(RGBQUAD) * bitmapInfoHeader.biHeight);


	for (int i = 0; i < bitmapInfoHeader.biWidth; i++)
		for (int j = 0; j < bitmapInfoHeader.biHeight; j++)
		{
			newbitecolor[i][j].rgbRed = bitecolor[i][j].rgbRed;
			newbitecolor[i][j].rgbGreen = bitecolor[i][j].rgbGreen;
			newbitecolor[i][j].rgbBlue = bitecolor[i][j].rgbBlue;
		}


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

					byte red = newbitecolor[pixelPosY][pixelPosX].rgbRed;
					byte green = newbitecolor[pixelPosY][pixelPosX].rgbGreen;
					byte blue = newbitecolor[pixelPosY][pixelPosX].rgbBlue;

					double kernelVal = gaussArray[i][j];

					rSum += red * kernelVal;
					gSum += green * kernelVal;
					bSum += blue * kernelVal;

					kSum += kernelVal;
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

			newbitecolor[y][x].rgbRed = (byte)rSum;
			newbitecolor[y][x].rgbGreen = (byte)gSum;
			newbitecolor[y][x].rgbBlue = (byte)bSum;
		}

	createbmp(bitmapInfoHeader, bitmapFileHeader, newbitecolor);
}

createbmp(BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, RGBQUAD **bitecolor)
{
	FILE *newfile = fopen("a.bmp", "wb");

	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, newfile);
	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, newfile);
//	fseek(newfile, bitmapFileHeader.bfOffBits, SEEK_SET);
	//int padding = (-((bitmapInfoHeader.biWidth * bitmapInfoHeader.biBitCount / 8) % 4) + 4) % 4;
//	char *buf = malloc(sizeof(char) * 4);
	for (int i = 0; i < bitmapInfoHeader.biWidth; i++)
	{
	//	fwrite(buf, sizeof(char), padding, newfile);
		for (int j = 0; j < bitmapInfoHeader.biHeight; j++)
			fwrite(&(bitecolor[i][j]), sizeof(bitecolor[i][j]), 1, newfile);
	}

	fclose(newfile);
}

sobelx(BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, RGBQUAD **bitecolor)
{
	int g[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };

	int newr = 0, newg = 0, newb = 0;
	int rc, gc, bc;
	for (int i = 1; i < bitmapInfoHeader.biWidth - 1; i++)
		for (int j = 1; j < bitmapInfoHeader.biHeight - 1; j++)
		{

			newr = 0; newg = 0; newb = 0;
			rc = 0; gc = 0; bc = 0;

			for (int wi = -1; wi < 2; wi++)
				for (int hw = -1; hw < 2; hw++)
				{
					rc = bitecolor[i + hw][j + wi].rgbRed;
					newr += g[wi + 1][hw + 1] * rc;

					gc = bitecolor[i + hw][j + wi].rgbGreen;
					newg += g[wi + 1][hw + 1] * gc;

					bc = bitecolor[i + hw][j + wi].rgbBlue;
					newb += g[wi + 1][hw + 1] * bc;
				}

			bitecolor[i][j].rgbBlue = newb;
			bitecolor[i][j].rgbGreen = newg;
			bitecolor[i][j].rgbRed = newr;
		}

	createbmp(bitmapInfoHeader, bitmapFileHeader, bitecolor);
}

sobely(BITMAPINFOHEADER bitmapInfoHeader, BITMAPFILEHEADER bitmapFileHeader, RGBQUAD **bitecolor)
{
	int g[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };

	int newr = 0, newg = 0, newb = 0;
	int rc, gc, bc;
	for (int i = 1; i < bitmapInfoHeader.biWidth - 1; i++)
		for (int j = 1; j < bitmapInfoHeader.biHeight - 1; j++)
		{

			newr = 0; newg = 0; newb = 0;
			rc = 0; gc = 0; bc = 0;

			for (int wi = -1; wi < 2; wi++)
				for (int hw = -1; hw < 2; hw++)
				{
					rc = bitecolor[i + hw][j + wi].rgbRed;
					newr += g[wi + 1][hw + 1] * rc;

					gc = bitecolor[i + hw][j + wi].rgbGreen;
					newg += g[wi + 1][hw + 1] * gc;

					bc = bitecolor[i + hw][j + wi].rgbBlue;
					newb += g[wi + 1][hw + 1] * bc;
				}

			bitecolor[i][j].rgbBlue = newb;
			bitecolor[i][j].rgbGreen = newg;
			bitecolor[i][j].rgbRed = newr;
		}

	createbmp(bitmapInfoHeader, bitmapFileHeader, bitecolor);
}

int main()
{
	FILE *file;
	file = fopen("unicorn32.bmp", "r");

	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, file);

	bitecolor = (RGBQUAD **)malloc(sizeof(RGBQUAD*) * bitmapInfoHeader.biWidth);
	for (int j = 0; j < bitmapInfoHeader.biWidth; j++)
		bitecolor[j] = (RGBQUAD *)malloc(sizeof(RGBQUAD) * bitmapInfoHeader.biHeight);

	//fseek(file, bitmapFileHeader.bfOffBits, SEEK_SET);
	//int padding = (-((bitmapInfoHeader.biWidth * bitmapInfoHeader.biBitCount / 8) % 4) + 4) % 4;
//	char *buf = malloc(sizeof(char) * 4);
	for (int i = 0; i < bitmapInfoHeader.biWidth; i++)
	{
	//	fread(buf, sizeof(char), padding, file);
		for (int j = 0; j < bitmapInfoHeader.biHeight; j++)
			fread(&(bitecolor[i][j]), sizeof(bitecolor[i][j]), 1, file);
	}

	createbmp(bitmapInfoHeader, bitmapFileHeader, bitecolor);

	//grey(bitmapInfoHeader, bitmapFileHeader, bitecolor);

	//median(bitmapInfoHeader, bitmapFileHeader, bitecolor);

	//gauss(5, bitmapInfoHeader, bitmapFileHeader, bitecolor);

	//sobelx(bitmapInfoHeader, bitmapFileHeader, bitecolor);

	//sobely(bitmapInfoHeader, bitmapFileHeader, bitecolor);
	return 0;
}