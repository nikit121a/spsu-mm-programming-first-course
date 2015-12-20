#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable: 4996)
#define word unsigned __int16
#define dword unsigned int

typedef struct 
{
	word code;
	dword size;
	word res1;
	word res2;
	dword offset;
} HEADER;

typedef struct
{
	dword header;
	dword width;
	dword height;
	word num;
	word Bit_Per_Pixel;
	dword type;
	dword comp;
	dword hres;
	dword vres;
	dword count;
	dword colors;
} BITMAP;

typedef struct
{
	dword height;
	dword width;
	dword offset;
	dword type;
} Image;

int read_header(Image *image, char *filename, char* new_file, HEADER *header_origin, BITMAP *bitmap_origin)
{
	FILE *f, *f1;
	HEADER header;
	BITMAP bitmap;
	f = fopen(filename, "rb");
	if(f == NULL)
	{
		return 0;
	}
	fopen_s(&f1, new_file, "wb");
	fread_s(&header.code, sizeof(word), 2, 1, f);
	fread_s(&header.size, sizeof(dword), 4, 1, f);
	fread_s(&header.res1, sizeof(word), 2, 1, f);
	fread_s(&header.res2, sizeof(word), 2, 1, f);
	fread_s(&header.offset, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.header, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.width, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.height, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.num, sizeof(word), 2, 1, f);
	fread_s(&bitmap.Bit_Per_Pixel, sizeof(word), 2, 1, f);
	fread_s(&bitmap.type, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.comp, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.hres, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.vres, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.count, sizeof(dword), 4, 1, f);
	fread_s(&bitmap.colors, sizeof(dword), 4, 1, f);
	fclose(f);
	fwrite(&header.code, 2, 1, f1);
	fwrite(&header.size, 4, 1, f1);
	fwrite(&header.res1, 2, 1, f1);
	fwrite(&header.res2, 2, 1, f1);
	fwrite(&header.offset, 4, 1, f1);
	fwrite(&bitmap.header, 4, 1, f1);
	fwrite(&bitmap.width, 4, 1, f1);
	fwrite(&bitmap.height, 4, 1, f1);
	fwrite(&bitmap.num, 2, 1, f1);
	fwrite(&bitmap.Bit_Per_Pixel, 2, 1, f1);
	fwrite(&bitmap.type, 4, 1, f1);
	fwrite(&bitmap.comp, 4, 1, f1);
	fwrite(&bitmap.hres, 4, 1, f1);
	fwrite(&bitmap.vres, 4, 1, f1);
	fwrite(&bitmap.count, 4, 1, f1);
	fwrite(&bitmap.colors, 4, 1, f1);
	fclose(f1); 
	image->height = bitmap.height;
	image->width = bitmap.width;
	image->offset = header.offset;
	image->type = bitmap.Bit_Per_Pixel;
	*header_origin = header;
	*bitmap_origin = bitmap;
	return 1;
}

typedef struct
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} PIXEL;

unsigned int value(PIXEL x)
{
	return x.blue + x.green << 8 + x.red << 16;
}

void greyscale(PIXEL **pic, Image image)
{
	int width = image.width;
	int height = image.height;
	int i, j;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			pic[i][j].blue = floor(0.114 * pic[i][j].blue) + floor(0.299 * pic[i][j].red) + floor(0.587 * pic[i][j].green);
			if(pic[i][j].blue > 255)
			{
				pic[i][j].blue = 255;
			}
			pic[i][j].green = pic[i][j].red = pic[i][j].blue;
		}
	}
	return;
}

int get_median(int a, int b, int c)
{
	if((a - b) * (a - c) < 0)
	{
		return a;
	}
	if((b - a) * (b - c) < 0)
	{
		return b;
	}
	if((c - a) * (c - b) < 0)
	{
		return c;
	}
}

void strange_filter(PIXEL **pic, Image image)
{
	int width = image.width;
	int height = image.height;
	int i, j;
	int a, b, c, res;
	for(i = 1; i < height - 1; i++)
	{
		for(j = 1; j < width - 1; j++)
		{
			a = get_median(pic[i - 1][j - 1].blue, pic[i - 1][j].blue, pic[i - 1][j + 1].blue);
			b = get_median(pic[i][j - 1].blue, pic[i][j].blue, pic[i][j + 1].blue);
			c = get_median(pic[i + 1][j - 1].blue, pic[i + 1][j].blue, pic[i + 1][j + 1].blue);
			res = get_median(a, b, c);
			pic[i][j].blue = res;
			a = get_median(pic[i - 1][j - 1].green, pic[i - 1][j].green, pic[i - 1][j + 1].green);
			b = get_median(pic[i][j - 1].green, pic[i][j].green, pic[i][j + 1].green);
			c = get_median(pic[i + 1][j - 1].green, pic[i + 1][j].green, pic[i + 1][j + 1].green);
			res = get_median(a, b, c);
			pic[i][j].green = res;
			a = get_median(pic[i - 1][j - 1].red, pic[i - 1][j].red, pic[i - 1][j + 1].red);
			b = get_median(pic[i][j - 1].red, pic[i][j].red, pic[i][j + 1].red);
			c = get_median(pic[i + 1][j - 1].red, pic[i + 1][j].red, pic[i + 1][j + 1].red);
			res = get_median(a, b, c);
			pic[i][j].red = res;
		}
	}
	return;
}

int median(int *a)
{
	int i, j, temp, length = 9;
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < length - i - 1; j++)
		{
			if(a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	return a[4];
}

void get_value(PIXEL **pic, int i, int j)
{
	int arr[9];
	arr[0] = pic[i - 1][j - 1].blue;
	arr[1] = pic[i - 1][j].blue;
	arr[2] = pic[i - 1][j + 1].blue;
	arr[3] = pic[i][j - 1].blue;
	arr[4] = pic[i][j].blue;
	arr[5] = pic[i][j + 1].blue;
	arr[6] = pic[i + 1][j - 1].blue;
	arr[7] = pic[i + 1][j].blue;
	arr[8] = pic[i + 1][j + 1].blue;
	pic[i][j].blue = median(arr);
	arr[0] = pic[i - 1][j - 1].red;
	arr[1] = pic[i - 1][j].red;
	arr[2] = pic[i - 1][j + 1].red;
	arr[3] = pic[i][j - 1].red;
	arr[4] = pic[i][j].red;
	arr[5] = pic[i][j + 1].red;
	arr[6] = pic[i + 1][j - 1].red;
	arr[7] = pic[i + 1][j].red;
	arr[8] = pic[i + 1][j + 1].red;
	pic[i][j].red = median(arr);
	arr[0] = pic[i - 1][j - 1].green;
	arr[1] = pic[i - 1][j].green;
	arr[2] = pic[i - 1][j + 1].green;
	arr[3] = pic[i][j - 1].green;
	arr[4] = pic[i][j].green;
	arr[5] = pic[i][j + 1].green;
	arr[6] = pic[i + 1][j - 1].green;
	arr[7] = pic[i + 1][j].green;
	arr[8] = pic[i + 1][j + 1].green;
	pic[i][j].green = median(arr);
}

void median_filter(PIXEL **pic, Image image)
{
	int width = image.width;
	int height = image.height;
	int i, j, res;
	for(i = 1; i < height - 1; i++)
	{
		for(j = 1; j < width - 1; j++)
		{
			get_value(pic, i, j);
		}
	}
	return;
}

int sum(int *a)
{
	int val = 0, i, length = 9;
	for(i = 0; i < length; i++)
	{
		val += a[i];
	}
	return val;
}

void gaussian(PIXEL **pic, int i, int j)
{
	int arr[9];
	arr[0] = floor(pic[i - 1][j - 1].blue * 0.0625);
	arr[1] = floor(pic[i - 1][j].blue * 0.125);
	arr[2] = floor(pic[i - 1][j + 1].blue * 0.0625);
	arr[3] = floor(pic[i][j - 1].blue * 0.125);
	arr[4] = floor(pic[i][j].blue * 0.25);
	arr[5] = floor(pic[i][j + 1].blue * 0.125);
	arr[6] = floor(pic[i + 1][j - 1].blue * 0.0625);
	arr[7] = floor(pic[i + 1][j].blue * 0.125);
	arr[8] = floor(pic[i + 1][j + 1].blue * 0.0625);
	pic[i][j].blue = sum(arr);
	arr[0] = floor(pic[i - 1][j - 1].red * 0.0625);
	arr[1] = floor(pic[i - 1][j].red * 0.125);
	arr[2] = floor(pic[i - 1][j + 1].red * 0.0625);
	arr[3] = floor(pic[i][j - 1].red * 0.125);
	arr[4] = floor(pic[i][j].red * 0.25);
	arr[5] = floor(pic[i][j + 1].red * 0.125);
	arr[6] = floor(pic[i + 1][j - 1].red * 0.0625);
	arr[7] = floor(pic[i + 1][j].red * 0.125);
	arr[8] = floor(pic[i + 1][j + 1].red * 0.0625);
	pic[i][j].red = sum(arr);
	arr[0] = floor(pic[i - 1][j - 1].green * 0.0625);
	arr[1] = floor(pic[i - 1][j].green * 0.125);
	arr[2] = floor(pic[i - 1][j + 1].green * 0.0625);
	arr[3] = floor(pic[i][j - 1].green * 0.125);
	arr[4] = floor(pic[i][j].green * 0.25);
	arr[5] = floor(pic[i][j + 1].green * 0.125);
	arr[6] = floor(pic[i + 1][j - 1].green * 0.0625);
	arr[7] = floor(pic[i + 1][j].green * 0.125);
	arr[8] = floor(pic[i + 1][j + 1].green * 0.0625);
	pic[i][j].green = sum(arr);
}

void gaussian_blur(PIXEL **pic, Image image)
{
	int width = image.width;
	int height = image.height;
	int i, j, res;
	for(i = 1; i < height - 1; i++)
	{
		for(j = 1; j < width - 1; j++)
		{
			gaussian(pic, i, j);
		}
	}
	return;
}

void Sobel_X_Table(PIXEL **pic, int i, int j)
{
	int arr[9], edge = 125;
	arr[0] = pic[i - 1][j - 1].blue * -1;
	arr[1] = pic[i - 1][j].blue * -2;
	arr[2] = pic[i - 1][j + 1].blue * -1;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 0;
	arr[6] = pic[i + 1][j - 1].blue * 1;
	arr[7] = pic[i + 1][j].blue * 2;
	arr[8] = pic[i + 1][j + 1].blue * 1;
	pic[i][j].blue = sum(arr);
	arr[0] = pic[i - 1][j - 1].red * -1;
	arr[1] = pic[i - 1][j].red * -2;
	arr[2] = pic[i - 1][j + 1].red * -1;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 0;
	arr[6] = pic[i + 1][j - 1].red * 1;
	arr[7] = pic[i + 1][j].red * 2;
	arr[8] = pic[i + 1][j + 1].red * 1;
	pic[i][j].red = sum(arr);
	arr[0] = pic[i - 1][j - 1].green * -1;
	arr[1] = pic[i - 1][j].green * -2;
	arr[2] = pic[i - 1][j + 1].green * -1;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 0;
	arr[6] = pic[i + 1][j - 1].green * 1;
	arr[7] = pic[i + 1][j].green * 2;
	arr[8] = pic[i + 1][j + 1].green * 1;
	pic[i][j].green = sum(arr);
	if((pic[i][j].green + pic[i][j].blue + pic[i][j].red) / 3 < edge)
	{
		pic[i][j].green = pic[i][j].blue = pic[i][j].red = 0;
	}
	else
	{
		pic[i][j].green = pic[i][j].blue = pic[i][j].red = 255;
	}
}

void Sobel_Y_Table(PIXEL **pic, int i, int j)
{
	int arr[9], edge = 100;
	arr[0] = pic[i - 1][j - 1].blue * -1;
	arr[1] = 0;
	arr[2] = pic[i - 1][j + 1].blue * 1;
	arr[3] = pic[i][j - 1].blue * -2;
	arr[4] = 0;
	arr[5] = pic[i][j + 1].blue * 2;
	arr[6] = pic[i + 1][j - 1].blue * -1;
	arr[7] = 0;
	arr[8] = pic[i + 1][j + 1].blue * 1;
	pic[i][j].blue = sum(arr);
	arr[0] = pic[i - 1][j - 1].red * -1;
	arr[1] = 0;
	arr[2] = pic[i - 1][j + 1].red * 1;
	arr[3] = pic[i][j - 1].red * -2;
	arr[4] = 0;
	arr[5] = pic[i][j + 1].red * 2;
	arr[6] = pic[i + 1][j - 1].red * -1;
	arr[7] = 0;
	arr[8] = pic[i + 1][j + 1].red * 1;
	pic[i][j].red = sum(arr);
	arr[0] = pic[i - 1][j - 1].green * -1;
	arr[1] = 0;
	arr[2] = pic[i - 1][j + 1].green * 1;
	arr[3] = pic[i][j - 1].green * -2;
	arr[4] = 0;
	arr[5] = pic[i][j + 1].green * 2;
	arr[6] = pic[i + 1][j - 1].green * -1;
	arr[7] = 0;
	arr[8] = pic[i + 1][j + 1].green * 1;
	pic[i][j].green = sum(arr);
	if((pic[i][j].green + pic[i][j].blue + pic[i][j].red) / 3 < edge)
	{
		pic[i][j].green = pic[i][j].blue = pic[i][j].red = 0;
	}
	else
	{
		pic[i][j].green = pic[i][j].blue = pic[i][j].red = 255;
	}
}

void Sobel_X(PIXEL **pic, Image image)
{
	int width = image.width;
	int height = image.height;
	int i, j, res;
	for (i = 1; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			Sobel_X_Table(pic, i, j);
		}
	}
	return;
}

void Sobel_Y(PIXEL **pic, Image image)
{
	int width = image.width;
	int height = image.height;
	int i, j, res;
	for(i = 1; i < height - 1; i++)
	{
		for(j = 1; j < width - 1; j++)
		{
			Sobel_Y_Table(pic, i, j);
		}
	}
	return;
}

int strcomp(char *str, char *str_new)
{
	int i;
	for(i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != str_new[i])
		{
			return 0;
		}
	}
	if(str[i] == '\0' && str_new[i] != '\0')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main(int argc, char *argv[])
{
	FILE *f;
	char *filename = "C://C++ projects/111.bmp", *filename_new = "C://C++ projects/new.bmp", *buff, *choice, **alpha;
	Image pic;
	PIXEL **str;
	int i, j;
	HEADER header;
	BITMAP bitmap;

	printf("\tGUIDE\nThis is the filter application.\nInput your parametrs in this format:\n\"source_file_name\" \"filter_name\" \"destination_file_name\"\nChoose the filter from:\nmedian\ngaussian\ngreyscales\nSobelX\nSobelY\n\n");

	if(argc != 4)
	{
		printf("Wrong format. Expected source_file_name type_of_filter destination_file_name.\n");
		getchar();
		return 0;
	}

	filename = argv[1];
	choice = argv[2];
	filename_new = argv[3];

	if(!read_header(&pic, filename, filename_new, &header, &bitmap))
	{
		printf("This file doesn't exist");
		getchar();
		return 0;
	}

	buff = (char*)malloc(pic.offset);
	str = (PIXEL**)malloc(sizeof(PIXEL*) * pic.height);
	alpha = (char**)malloc(sizeof(char*) * pic.height);

	f = fopen(filename, "rb");
	fread_s(buff, pic.offset, 1, pic.offset, f);

	if(pic.type == 24)
	{
		for(i = 0; i < pic.height; i++)
		{
			str[i] = (PIXEL*)malloc(sizeof(PIXEL) * pic.width);
			fread_s(str[i], pic.width * 3, 3, pic.width, f);
			fread_s(buff, 5, pic.width % 4, 1, f);
		}
	}
	if(pic.type == 32)
	{
		for(i = 0; i < pic.height; i++)
		{
			str[i] = (PIXEL*)malloc(sizeof(PIXEL) * pic.width);
			alpha[i] = (char*)malloc(sizeof(char) * pic.width);
			for(j = 0; j < pic.width; j++)
			{
				fread_s(&str[i][j], pic.width * 3, 3, 1, f);
				fread_s(&alpha[i][j], pic.width, 1, 1, f);
			}
		}
	}
	fclose(f);

	if(strcomp(choice, "greyscales"))
	{
		greyscale(str, pic);
	}
	else if(strcomp(choice, "gaussian"))
	{
		gaussian_blur(str, pic);
	}
	else if(strcomp(choice, "median"))
	{
		median_filter(str, pic);
	}
	else if(strcomp(choice, "SobelX"))
	{
		Sobel_X(str, pic);
	}
	else if(strcomp(choice, "SobelY"))
	{
		Sobel_Y(str, pic);
	}
	else
	{
		printf("Uncorrect filter name. Choose from\ngaussian\nmedian\ngreyscales\nSobelX\nSobelY\n");
		getchar();
	}

	fopen_s(&f, filename_new, "ab");
	memset(buff, 0, pic.offset);

	if(pic.type == 24)
	{
		for(i = 0; i < pic.height; i++)
		{
			fwrite(str[i], 3, pic.width, f);
			fwrite(buff, pic.width % 4, 1, f);
		}
	}
	if(pic.type == 32)
	{
		for(i = 0; i < pic.height; i++)
		{
			for(j = 0; j < pic.width; j++)
			{
				fwrite(&str[i][j], 3, 1, f);
				fwrite(&alpha[i][j], 1, 1, f);
			}
		}
	}

	fclose(f);

	printf("Ready!");
	getchar();
	return 0;
}