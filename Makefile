CFLAGS=`pkg-config --cflags gtk+-3.0 gtksourceview-3.0`
LIBS=`pkg-config --libs gtk+-3.0 gtksourceview-3.0`
BUILD=build
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, $(BUILD)/%.o, $(SRC))
ASSETS=$(patsubst style/%, dist/%, $(wildcard style/*))

default: dist/maia

build/%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< $(CFLAGS)

dist/%.css: style/%.css
	cp $< $@

dist/%.svg: style/%.svg
	cp $< $@

dist/maia: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LIBS) -o $@

.PHONY: all
.PHONY: clean

all: dist/maia $(ASSETS)

clean:
	-rm -f build/*
	-rm -f dist/*
