LDFLAGS=-L/Users/unibodydesignn/Desktop/lib -framework Cocoa -framework OpenGL  -framework GLUT  -lGLEW -lm
CC = g++
CFLAGS=-g -I/Users/unibodydesignn/Desktop/include
OBJFILES = *.o
TARGET = main

main: main.o
	$(CC) $@.o $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -w

clean:
	-rm -r example0 *.o core *.dSYM
