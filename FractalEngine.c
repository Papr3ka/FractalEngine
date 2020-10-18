/*
Compile using
gcc FractalEngine.c -O3 -o FractalEngine.exe
*/

#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

#define GRAYSCALE "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "

int pixel(double x, double y, unsigned long iter, register double complex z,int height, int width){
	register double realStart = -2.0;
	register double realEnd = 1.0;
	register double imaginaryStart = -1.0;
	register double imaginaryEnd = 1.0;
	unsigned long n = 0;
	register double complex c = (realStart + (x / width) * (realEnd - realStart)) + (imaginaryStart + (y / height) * (imaginaryEnd - imaginaryStart))*I;
	while(abs(z) < 2.0 && n < iter){
		z = z*z+c;
		n++;
	}
	return (int)(n*69)/iter;
}

int main(){
	unsigned long count=1;
	double inc = 0.01;
	register double start;
	while(1==1){
		start += inc;
		printf("\033[0;0H");
		for(int y=0; y<=60;y++){
			for(int x=0;x<=236;x++){
				printf("%c", GRAYSCALE[pixel(x,y,150,start,60,236)]);
			}
			printf("\n");
		}
		if(start >= (2-abs(inc))){
			inc *= -1;
		}
		if(start <= abs(inc)){
			inc *= -1;
		}
	}
	return 0;
}
