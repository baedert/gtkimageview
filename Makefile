

CFLAGS=`pkg-config --cflags gtk+-3.0`
LDFLAGS=`pkg-config --libs gtk+-3.0` -lm



all: demo.o gtkimageview.o
	$(CC) $(LDFLAGS) demo.o gtkimageview.o -o demo


gtkimageview.o: gtkimageview.c gtkimageview.h
	$(CC) $(CFLAGS) -c gtkimageview.c

demo.o: demo.c
	$(CC) $(CFLAGS) -c demo.c
