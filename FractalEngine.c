/*
Compile using
gcc FractalEngine.c -O3 -o FractalEngine.exe
*/

#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>
#include<time.h>

#define GRAYSCALE "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "
#define TERMINAL_WIDTH 236
#define TERMINAL_HEIGHT 59

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

int main(int argc, char* argv[]){
	unsigned int iter=150;
	register clock_t tstart;
	register clock_t tend;
	register float fps=0;
	register double frametime;
	register double complex inc = 0.0025;
	register double complex start;
	register double complex wt;
	if(argc == 2){
		iter = atoi(argv[1]);
	}
	while(1){
		wt += inc;
		start = ccos(wt)+csin(wt)*I;
		printf("\033[0;0H");
		tstart = clock();
		for(int y=0; y <=TERMINAL_HEIGHT;y++){
			for(int x=0; x <=TERMINAL_WIDTH;x++){
				printf("%c",GRAYSCALE[pixel(x,y,iter,start,TERMINAL_HEIGHT,TERMINAL_WIDTH)]);
			}
			printf("\n");
		}
		tend = clock();
		frametime = (double)tend-(double)tstart;
		fps = 1.0/((frametime)/1000.0);
		if(isfinite(fps)){
		printf("FPS: %f FRAMETIME: %f ms", fps, frametime);
		}

	}
	return 0;
}
