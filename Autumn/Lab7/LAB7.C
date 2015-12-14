/*Leonid Voroshilov, 143*/
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define X  0
#define Y  1
#define XY 2


void get_color(int x, int y, int *r, int *g, int *b, long W, long H, unsigned char* pic_in)
{
	static int mode;
	static int padding;
	int num;
	/*Setup*/
	if(x == -1)
	{
		if (y == 24)
			mode = 24;
		if (y == 32)
			mode = 32;
		return;
	}
	if (x == -2)
	{
		padding = y;
		return;
	}

	if(mode == 24)
	{
		num = 3 * W * (H - y - 1) + 3 * x + padding * max(0, H - y - 1);
		*b = pic_in[num + 0];
		*g = pic_in[num + 1];
		*r = pic_in[num + 2];
	}
	if(mode == 32)
	{
		num = 4 * W * (H - y - 1) + 4 * x;
		*b = pic_in[num + 1];
		*g = pic_in[num + 2];
		*r = pic_in[num + 3];
	}
}

void set_color(int x, int y, int r, int g, int b, long W, long H, unsigned char *pic_out)
{
	static int mode;
	static int padding;
	int num;
	if(x == -1)
	{
		if (y == 24)
			mode = 24;
		if (y == 32)
			mode = 32;
		return;
	}

	if (x == -2)
	{
		padding = y;
		return;
	}
	if(mode == 24)
	{
		num = 3 * W * (H - y - 1) + 3 * x + padding * max(0, H - y - 1);

		pic_out[num + 0] = b;
		pic_out[num + 1] = g;
		pic_out[num + 2] = r;
	}
	if(mode == 32)
	{
		num = 4 * W * (H - y - 1) + 4 * x;

		pic_out[num + 0] = 0;
		pic_out[num + 1] = b;
		pic_out[num + 2] = g;
		pic_out[num + 3] = r;

	}
}
/*Compàration function*/
int cmpfunc(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void gauss(long W, long H, unsigned char *pic_in, unsigned char *pic_out)
{
	int x, y, i, j;
	int mask[3][3] = { { 1, 2, 1 },{ 2, 4, 2 },{ 1, 2, 1 } };
	int resR, resG, resB;

	for (y = 1; y < H - 1; y++)
		for (x = 1; x < W - 1; x++)
		{
			resR = 0, resG = 0, resB = 0;
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
				{
					int r, g, b;
					get_color(x + j, y + i, &r, &g, &b, W, H, pic_in);
					resR += mask[i + 1][j + 1] * r ;
					resG += mask[i + 1][j + 1] * g;
					resB += mask[i + 1][j + 1] * b;
				}

			resR /= 16;
			resG /= 16;
			resB /= 16;
			set_color(x, y, resR, resG, resB, W, H, pic_out);
		}
}

void median(long W, long H, unsigned char *pic_in, unsigned char *pic_out)
{
	int x, y, i, j;
	int masR[9], masG[9], masB[9];

	for (y = 1; y < H - 1 ; y++)
		for (x = 1; x < W - 1; x++)
		{
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
				{
					int r, g, b;
					get_color(x + j, y + i, &r, &g, &b, W, H, pic_in);
					masR[(i + 1) * 3 + j + 1] = r;
					masG[(i + 1) * 3 + j + 1] = g;
					masB[(i + 1) * 3 + j + 1] = b;
				}
			qsort(masR, 9, sizeof(int), cmpfunc);
			qsort(masG, 9, sizeof(int), cmpfunc);
			qsort(masB, 9, sizeof(int), cmpfunc);

			set_color(x, y, masR[5], masG[5], masB[5], W, H, pic_out);
		}
}

int gray(long W, long H, unsigned char *pic_in, unsigned char *pic_out)
{
	int x, y;
	for (y = 1; y < H - 1; y++)
		for (x = 1; x < W - 1; x++)
		{
			int b, g, r, color;

			get_color(x, y, &r, &g, &b, W, H, pic_in);
			color = (r + g + b) / 3;
			set_color(x, y, color, color, color, W, H, pic_out);
		}
	return 1;
}

void sobel(int mode, long W, long H, unsigned char *pic_in, unsigned char *pic_out)
{
	int x, y, i, j;
	int maskX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int maskY[3][3] = {{-1,-2,-1}, {0 , 0 ,0}, {1, 2, 1 }};
	int resX, resY;
	int lim = 100;

	for (y = 1; y < H - 1; y++)
		for (x = 1; x < W - 1 ; x++)
		{
			resX = 0;
			resY = 0;

			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
				{
					int r, g, b;
					get_color(x + i, y + j, &r, &g, &b, W, H, pic_in);
					resX += (r + g + b) / 3 *  maskX[j + 1][i + 1]; 
					resY += (r + g + b) / 3 * maskY[j + 1][i + 1];
				}

			if (mode == X)
				resY = 0;
			else if (mode == Y)
				resX = 0;

			resX = (int)sqrt(resX * resX + resY * resY);
			if(resX > lim)
				set_color(x, y, 255,255,255, W, H, pic_out);
			else
				set_color(x, y, 0 ,0 ,0, W, H, pic_out);

		}
}


unsigned char * write_bmp(char *file_name, BITMAPFILEHEADER *BmpFileHeader, BITMAPINFOHEADER *BmpInfoHeader,
	           unsigned char *pic_in, unsigned char *pic_out, unsigned char *buf)
{
	FILE *bmp;
	int r;

	bmp = fopen(file_name, "wb");
	if(bmp == NULL)
	{
		printf("Can't open/create %s", file_name);
		free(buf);
		free(pic_in);
		free(pic_out);
		return NULL;
	}

	fwrite(BmpFileHeader,sizeof(BITMAPFILEHEADER),1,  bmp);
	fwrite(BmpInfoHeader,sizeof(BITMAPINFOHEADER),1, bmp);
	if(buf != NULL)
	  fwrite(buf, 1, BmpFileHeader->bfOffBits - (sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)), bmp);
	fseek(bmp, BmpFileHeader->bfOffBits, SEEK_SET);
	
	//r = BmpInfoHeader->biWidth * BmpInfoHeader->biHeight * BmpInfoHeader->biBitCount / 8;
 	r = BmpFileHeader->bfSize - BmpFileHeader->bfOffBits;

	fwrite(pic_out, 1, r, bmp); 
	fclose(bmp);
	free(buf);
	free(pic_in);
	//free(pic_out);
	
	return NULL;
}


unsigned char * open_bmp(char *file_name, BITMAPFILEHEADER *BmpFileHeader, BITMAPINFOHEADER *BmpInfoHeader, unsigned char **pic_in,
	                     unsigned char **pic_out, unsigned char **buf, long *W, long *H)
{
	FILE *bmp;

	int r, mode = 24;

	bmp = fopen(file_name, "rb");
	if(bmp == NULL)
	{
		printf("Can't open file\n");
		return NULL;
	}
	fread(BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, bmp);
	if(BmpFileHeader->bfType != 0x424D && BmpFileHeader->bfType != 0x4D42)
	{
		printf("It must be  '.bmp' file");
		fclose(bmp);
		return NULL;
	}

	fread(BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, bmp);

	*W = BmpInfoHeader->biWidth;
	*H = BmpInfoHeader->biHeight;
	
	if(BmpInfoHeader->biBitCount == 24)
	{
		set_color(-1, 24, 0, 0, 0, *W, *H, *pic_out);
		get_color(-1, 24, NULL, NULL, NULL, *W, *H, *pic_in);
	}
	else if(BmpInfoHeader->biBitCount == 32)
	{
		set_color(-1, 32, 0, 0, 0, *W, *H, *pic_out);
		get_color(-1, 32, NULL, NULL, NULL, *W, *H, *pic_in);
		mode = 32;
	}
	else
		printf("Incorrect format(must be 24 or 32)\n");

	int a = (BmpFileHeader->bfOffBits - (sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)) + 1);
	*buf = NULL;

	if(a > 1)
	{
		*buf = malloc(BmpFileHeader->bfOffBits - (sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)) + 1);
		fread(*buf, 1, BmpFileHeader->bfOffBits - (sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER)), bmp);
	}

	fseek(bmp, BmpFileHeader->bfOffBits, SEEK_SET);
    int r1 = *W * *H * mode / 8; 
	r = BmpFileHeader->bfSize - BmpFileHeader->bfOffBits;

	if (r1 != r)
	{
		set_color(-2, ((*W)) % 4, 0, 0, 0, *W, *H, *pic_out);
		get_color(-2, ((*W)) % 4,NULL,  NULL, NULL, *W, *H, *pic_in);
		
	}

	*pic_in = (unsigned char*)malloc(sizeof(unsigned char) * (r + 1));
	*pic_out = (unsigned char*)malloc(sizeof(unsigned char) * (r + 1));
	memset(*pic_out, 0, sizeof(unsigned char) * (r + 1));
	if(*pic_in == NULL)
		return NULL;
	fread(*pic_in, 1, r, bmp);
	fclose(bmp);
	
	return *pic_in;
}
 


int main(int argc, char *argv[])
{
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
	unsigned char *pic_in, *pic_out, *buf;
	long W, H;

	if(argc == 1 || argc > 4)
	{
		printf("Incorrect comand line arguments\n must be: \n input_file(at least) \nfilter( XSOBEL, YSOBEL, SOBEL(default), GAUSS, GRAY, MEDIAN) \n output file \n");
		return 0;
	}
	else if(argc == 2)
	{
		if(open_bmp(argv[1], &BmpFileHeader, &BmpInfoHeader, &pic_in, &pic_out, &buf, &W, &H) != NULL)
		{
			char *path;
			path = malloc(sizeof(char) * (strlen(argv[1]) + strlen("SOBEL_"))+ 1);
			memset(path, 0, sizeof(char) * (strlen(argv[1]) + strlen("SOBEL_") + 1));
			strcpy(path, "SOBEL_");
			strcat(path, argv[1]);
			sobel(XY, W, H, pic_in, pic_out);
			write_bmp(path, &BmpFileHeader, &BmpInfoHeader, pic_in, pic_out, buf);
			free(path);
		}
	}
	else
	{
		char* filters[] = { "GRAY", "XSOBEL", "YSOBEL", "SOBEL", "MEDIAN", "GAUSS" };
		int i;
		for(i = 0; i < 6; i++)
		{
			if(strcmp(filters[i], argv[2]) == 0)
			{
				char *pic = open_bmp(argv[1], &BmpFileHeader, &BmpInfoHeader, &pic_in, &pic_out, &buf, &W, &H);

				if(pic != NULL)
				{
					switch (i)
					{
					case 0:
						gray(W, H, pic_in, pic_out);
						break;
					case 1:
						sobel(X, W, H, pic_in, pic_out);
						break;
					case 2:
						sobel(Y, W, H, pic_in, pic_out);
						break;
					case 3:
						sobel(XY, W, H, pic_in, pic_out);
						break;
					case 4:
						median(W, H, pic_in, pic_out);
						break;
					case 5:
						gauss(W, H, pic_in, pic_out);
						break;
					}

					if(argc == 4)
						write_bmp(argv[3], &BmpFileHeader, &BmpInfoHeader, pic_in, pic_out, buf);

					else
					{
						char *path;
						path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + strlen(filters[i]) + 2));
						memset(path, 0, sizeof(char) * (strlen(argv[1]) + strlen(filters[i]) + 2));
						write_bmp(strcat(strcat(strcpy(path, filters[i]), "_"), argv[1]), &BmpFileHeader, &BmpInfoHeader, pic_in, pic_out, buf);
						free(path);
					}
					return 0;
				}
			}

		}
		printf("Incorrect comand line arguments\n must be: \n input_file(at least) \n filter( XSOBEL, YSOBEL, SOBEL(default), GAUSS, GRAY, MEDIAN) \n output file \n");
	}

	return 0;
}