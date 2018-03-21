HEADERS =
CFLAGS=`pkg-config --cflags gtk+-3.0 gtksourceview-3.0`
LIBS=`pkg-config --libs gtk+-3.0 gtksourceview-3.0`

default: dist/maia

build/%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< $(CFLAGS)

dist/maia: build/maia.o build/mime.o
	gcc $(CFLAGS) build/maia.o build/mime.o $(LIBS) -o dist/maia

clean:
	-rm -f build/*
	-rm -f dist/maia
