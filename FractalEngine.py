import multiprocessing, os, sys, time, math
from multiprocessing import Pool, Queue, Process
try:
	import msvcrt
except ImportError:
	print("MSVCRT module not found")
	input()
	sys.exit(0)
os.system('')
def clear():
    if os.name == None:
        print('\x1b[2J\x1b[H')
    try:
        if os.name == "nt":
            os.system('cls')
        elif os.name == "posix" or os.name == "java":
            os.system('clear')
        else:
            print('\x1b[2J\x1b[H')
    except Exception:
        pass
GREYSCALE = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. "
def render(column, line, column_offset, render_set):
	print(f"\033[{line};{column}H")
	for pos, setchar in enumerate(render_set):
		print(setchar, end="")
		if pos % column_offset == 0:
			print(f"\033[{line+pos//column_offset};{column}H")
def mandelbrot(c, iterations):
	z = 0
	n = 0
	while abs(z) <= 2 and n < iterations:
		z = z*z+c
		n += 1
	return n
def np_mandelbrot(coord, offset, realStart, realEnd, imaginaryStart, imaginaryEnd, width, height, iterations, zoom):
	x, y = coord
	xoffset, yoffset = offset
	try:
		c = complex((realStart + (x / width) * (realEnd - realStart))/zoom - xoffset*1.5, (imaginaryStart + (y / height) * (imaginaryEnd - imaginaryStart))/zoom - yoffset*1.5)
		color = int(mandelbrot(c, iterations) * 69 / iterations)
	except ZeroDivisionError: return 1
	return color
def main():
	iterations = 80
	realStart = -2
	realEnd = 1
	imaginaryStart = -1
	imaginaryEnd = 1
	zoom = 1
	xoffset = 0
	yoffset = 0
	while True:
		RenderList = []
		width = int(os.get_terminal_size()[0])
		height = int(os.get_terminal_size()[1])
		xratio = abs(realEnd - realStart) / width
		yratio = abs(imaginaryEnd - imaginaryStart) / height
		for y in range(height):
			for x in range(width):
				RenderList.append(np_mandelbrot((x,y), (xoffset,yoffset), realStart, realEnd, imaginaryStart, imaginaryEnd, width, height, iterations, zoom))
		render(0, 0, width, list(map(lambda k: GREYSCALE[int(k)], RenderList)))
		key = msvcrt.getch()
		if key == b"+": 
			zoom += zoom/2
		elif key == b"-": 
			zoom -= zoom/2
		elif key == b"a":
			xoffset += 0.25*zoom**-1
		elif key == b"d":
			xoffset -= 0.25*zoom**-1
		elif key == b"w":
			yoffset += 0.25*zoom**-1
		elif key == b"s":
			yoffset -= 0.25*zoom**-1
		elif key == b"r":
			realStart = -2
			realEnd = 1
			imaginaryStart = -1
			imaginaryEnd = 1
			zoom = 1
			xoffset = 0
			yoffset = 0
			iterations = 80
		elif key == b"z":
			iterations -= 10
		elif key == b"x":
			iterations +=10
		elif key== b"\x03": 
			sys.exit(0)
		else:
			pass
if __name__ == "__main__": main()
