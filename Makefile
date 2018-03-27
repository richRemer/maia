HEADERS=
CFLAGS=`pkg-config --cflags gtk+-3.0 gtksourceview-3.0`
LIBS=`pkg-config --libs gtk+-3.0 gtksourceview-3.0`
BUILD=build
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, $(BUILD)/%.o, $(SRC))

default: dist/maia

build/%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< $(CFLAGS)

dist/maia: $(OBJ) dist/maia.css
	gcc $(CFLAGS) $(OBJ) $(LIBS) -o $@

dist/maia.css: style/maia.css
	cp $< $@

.PHONY: clean

clean:
	-rm -f build/*
	-rm -f dist/*
