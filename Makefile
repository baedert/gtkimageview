

CFLAGS=`pkg-config --cflags gtk+-3.0`
LDFLAGS=`pkg-config --libs gtk+-3.0` -lm



all: demo.o gtkimageview.o vala_demo.o
	$(CC) $(LDFLAGS) demo.o gtkimageview.o -o demo
	$(CC) $(LDFLAGS) vala_demo.o gtkimageview.o -o vala_demo


vala_demo.o: vala_demo.c gtkimageview.vapi
	$(CC) $(CFLAGS) -c vala_demo.c

vala_demo.c: vala_demo.vala
	valac --pkg gtk+-3.0 gtkimageview.vapi vala_demo.vala -C


gtkimageview.o: gtkimageview.c gtkimageview.h
	$(CC) $(CFLAGS) -c gtkimageview.c

demo.o: demo.c
	$(CC) $(CFLAGS) -c demo.c
