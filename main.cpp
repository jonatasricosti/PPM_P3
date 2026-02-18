#include <fstream>
using namespace std;


void CreatImage()
{
	ofstream escreva;
	escreva.open("text.ppm");
	
	const int image_width = 640;
	const int image_height = 480;
	const int magic_number = 255;
	
	int red = 0;
	int green = 0;
	int blue = 255;
		
	escreva << "P3" << endl;
	escreva << image_width << endl;
	escreva << image_height << endl;
	escreva << magic_number << endl;
	
	for(int i = 0; i < image_width*image_height; i++)
	{
		escreva << red << " " << green << " " << blue << " " << endl;
	}
	
	escreva.close();
}

int main()
{

CreatImage();

return 0;
}
