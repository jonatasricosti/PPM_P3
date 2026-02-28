#include <fstream> // pra usar ofstream
#include <sstream> // pra usar stringstream
#include <string> // pra usar string
#include <math.h> // pra usar abs
using namespace std;

string FileType = "P3";	
const int image_width = 640;
const int image_height = 480;
const int magic_number = 255;

//red        green     blue
//00000000 00000000  00000000
// use essa função pra ter uma cor no formato RGB24bits
unsigned long RGB24(int red, int green, int blue)
{   
    return ((red & 255) << 16) | ((green & 255) << 8) | (blue & 255);
}


// use essa função pra conveter uma cor em rgb24bits de hexadecimal pra decimal
string rgb24Todecimal(int color)
{
	int red = color >> 16 & 255;
	int green = color >> 8 & 255;
	int blue = color & 255;
	
	stringstream escreva;
	escreva << red << " " << green << " " << blue << endl;
	string texto = escreva.str();
	
	return texto;
}


// Esse array vai armazenar todas as nossas cores
// Esse array simula a memória de vídeo do game boy advance no mode 3
int vram[image_width*image_height];

// use essa função pra desenhar um pixel
void DrawPixel(int x, int y, int color)
{
	vram[x+y*image_width] = color;
}

// Bresenham's infamous line algorithm
// use essa função pra desenhar uma linha
void DrawLine(int x1, int y1, int x2, int y2, int color)
{
	int i, deltax, deltay, numpixels;
	int d, dinc1, dinc2;
	int x, xinc1, xinc2;
	int y, yinc1, yinc2;

	//calculate deltaX and deltaY
	deltax = abs(x2 - x1);
	deltay = abs(y2 - y1);

	//initialize
	if(deltax >= deltay)
	{
		//If x is independent variable
		numpixels = deltax + 1;
		d = (2 * deltay) - deltax;
		dinc1 = deltay << 1;
		dinc2 = (deltay - deltax) << 1;
		xinc1 = 1;
		xinc2 = 1;
		yinc1 = 0;
		yinc2 = 1;
	}
	else
	{
		//if y is independant variable
		numpixels = deltay + 1;
		d = (2 * deltax) - deltay;
		dinc1 = deltax << 1;
		dinc2 = (deltax - deltay) << 1;
		xinc1 = 0;
		xinc2 = 1;
		yinc1 = 1;
		yinc2 = 1;
	}

	//move the right direction
	if(x1 > x2)
	{
		xinc1 = -xinc1;
		xinc2 = -xinc2;
	}
	if(y1 > y2)
	{
		yinc1 = -yinc1;
		yinc2 = -yinc2;
	}

	x = x1;
	y = y1;

	//draw the pixels
	for(i = 1; i < numpixels; i++)
	{
		DrawPixel(x, y, color);

		if(d < 0)
		{
			d = d + dinc1;
			x = x + xinc1;
			y = y + yinc1;
		}
		else
		{
			d = d + dinc2;
			x = x + xinc2;
			y = y + yinc2;
		}
	}
}

// use essa função pra desenhar um triângulo
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,int color)
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

// use essa função pra desenhar um retângulo
void DrawRect(int x, int y, int width, int height, int color)
{
	int left = x;
	int right = x + width;
	int up = y;
	int down = y+height;
	
	for(int j = up; j < down; j++)
	{
		for(int i = left; i < right; i++)
		{
			DrawPixel(i,j,color);
		}
	}
}
// use essa função pra desenhar um retângulo vazio
void DrawEmptyRect(int x, int y, int width, int height, int color)
{
    DrawRect(x,y,width,1,color);
    DrawRect(x,y+height-1,width,1,color);
    DrawRect(x,y,1,height,color);
    DrawRect(x+width-1,y,1,height,color);
}


// Bresenham's infamous circle algorithm
// use essa função pra desenha um círculo
void DrawCircle(int xCenter, int yCenter, int radius, int color)
{
	int x = 0;
	int y = radius;
	int p = 3 - 2 * radius;
	while (x <= y)
	{
		DrawPixel(xCenter + x, yCenter + y, color);
		DrawPixel(xCenter - x, yCenter + y, color);
		DrawPixel(xCenter + x, yCenter - y, color);
		DrawPixel(xCenter - x, yCenter - y, color);
		DrawPixel(xCenter + y, yCenter + x, color);
		DrawPixel(xCenter - y, yCenter + x, color);
		DrawPixel(xCenter + y, yCenter - x, color);
		DrawPixel(xCenter - y, yCenter - x, color);

		if (p < 0)
			p += 4 * x++ + 6;
		else
			p += 4 * (x++ - y--) + 10;
	}
}


// use essa função pra colocar a cor de fundo da imagem
void BackgroundColor(int color)
{
	for(int i = 0; i < image_width*image_height; i++)
	{
		vram[i] = color; // cor de fundo
	}
}

// use essa função pra criar um arquivo de imagem ppm p3
void CreatImagePP3()
{
	ofstream escreva;
	escreva.open("text.ppm");
	
	escreva << FileType << endl;
	escreva << image_width << endl;
	escreva << image_height << endl;
	escreva << magic_number << endl;
	
	int whitecolor = RGB24(255,255,255);
	int yellowcolor = RGB24(255,255,0);
	int blackcolor = RGB24(0,0,0);
	
	BackgroundColor(whitecolor);
	DrawRect(50,50,100,150,RGB24(128,128,128));        // Retângulo superior esquerdo
	DrawEmptyRect(250,50,90,90,RGB24(90,128,255));     // Retângulo vazio superior direito
	DrawLine(50,250,200,350,0);                        // Linha parte inferior esquerda
	DrawTriangle(300,250,450,250,375,150,0xff);        // Triângulo parte inferior direita
	DrawCircle(540,200,80,0xff00ff);                   // Círculo mais à direita

	
	for(int i = 0; i < image_width*image_height; i++)
	{
		escreva << rgb24Todecimal(vram[i]);		
	}
	
	escreva.close();
}

int main()
{

CreatImagePP3();

return 0;
}
