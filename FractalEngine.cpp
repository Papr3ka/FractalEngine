#include<iostream>
#include<string>
#include<cmath>
#include<complex>
#include<chrono>
#include<ratio>

#define TERMINAL_WIDTH 208
#define TERMINAL_HEIGHT 50

const std::string grayscale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
const register double realStart = -2.0;
const register double realEnd = 1.0;
const register double imaginaryStart = -1.0;
const register double imaginaryEnd = 1.0;

short pixel(long double x, long double y, unsigned long iter, register std::complex<long double> z, int height, int width){
	std::complex<long double> c(realStart + (x / width) * (realEnd - realStart),imaginaryStart + (y / height) * (imaginaryEnd - imaginaryStart));
	register unsigned long n = 0;
	while(abs(z) < 2.0 && n < iter){
		z = z*z+c;
		n++;
	}
	return(short)(n*69)/iter;
}

static std::string trunc(std::string x, short prec){
	return x.substr(0, prec);
}

int main(int argc, char* argv[]){
	unsigned int iter=50;
	register short fps=0;
	std::complex<long double> start(0, 0);
	long double inc = 0.0025;
	long double wt = 0;
	while(1){
		wt += inc;
		start.real(cos(wt));
		start.imag(sin(wt));
		std::cout << "\033[0;0H";
		auto tstart = std::chrono::steady_clock::now();
		for(short y=0; y <=TERMINAL_HEIGHT;y++){
			for(short x=0; x <=TERMINAL_WIDTH;x++){
				std::cout << grayscale[pixel(x,y,iter,start,TERMINAL_HEIGHT,TERMINAL_WIDTH)];
			}
			std::cout << "\n";
		}
		auto tend = std::chrono::steady_clock::now();
		double frametime = std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(tend - tstart)).count();
		fps = (short)(1/(frametime));
		std::cout << "FPS: "<< trunc(std::to_string((double)fps),5) << "  FRAMETIME: " << std::to_string(()(frametime*1000)) << " ms";
	}
	return 0;
}
