HEADERS =
CFLAGS=`pkg-config --cflags gtk+-3.0 gtksourceview-3.0`
LIBS=`pkg-config --libs gtk+-3.0 gtksourceview-3.0`

default: dist/maia

build/maia.o: maia.c $(HEADERS)
	gcc $(CFLAGS) -c maia.c -o build/maia.o

dist/maia: build/maia.o
	gcc $(CFLAGS) build/maia.o $(LIBS) -o dist/maia

clean:
	-rm -f build/*
	-rm -f dist/maia
