#include <fstream> // pra usar ofstream
#include <sstream> // pra usar stringstream
#include <string> // pra usar string
using namespace std;

string FileType = "P3";	
const int image_width = 640;
const int image_height = 480;
const int magic_number = 255;


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

// use essa função pra desenhar pixel
void DrawPixel(int x, int y, int color)
{
	vram[x+y*image_width] = color;
}


// use essa função pra colocar a cor de fundo da imagem
void BackgroundColor(int color)
{
	for(int i = 0; i < image_width*image_height; i++)
	{
		vram[i] = color; // cor de fundo
	}
}

// Use essa função pra criar um arquivo de imagem ppm p3
void CreatImagePP3()
{
	ofstream escreva;
	escreva.open("text.ppm");
	
	escreva << FileType << endl;
	escreva << image_width << endl;
	escreva << image_height << endl;
	escreva << magic_number << endl;
	
	BackgroundColor(0xffff00);
	
	DrawPixel(100,200,0);
	
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
