/*
Compile using
gcc FractalEngine.c -O3 -o FractalEngine.exe
*/

#include<stdio.h>
#include<stdlib.h>
#include<complex.h>

#define GRAYSCALE "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "

int pixel(double x, double y, int iter, int height, int width){
	register double realStart = -2.0;
	register double realEnd = 1.0;
	register double imaginaryStart = -1.0;
	register double imaginaryEnd = 1.0;
	int n = 0;
	register double complex z=0;
	register double complex c = (realStart + (x / width) * (realEnd - realStart)) + (imaginaryStart + (y / height) * (imaginaryEnd - imaginaryStart))*I;
	while(abs(z) < 2.0 && n < iter){
		z = (z*z) + c;
		n++;
	}
	return (int)(n*69)/iter;
}

int main(){
	for(int y=0; y<=60;y++){
		for(int x=0;x<=236;x++){
			printf("%c", GRAYSCALE[pixel(x,y,85,60,236)]);
		}
		printf("\n");
	}

	return 0;
}