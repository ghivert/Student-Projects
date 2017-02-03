CC = clang
AR = ar
FLAGS = -Wall -std=c11
CFLAGS = -fPIC
ARFLAGS = -shared
LIBS_DIR = ../lib

SOURCES = display_tools.c display.c
OBJECTS = $(SOURCES:%.c=%.o)

-include configure.in

all: configure.in libdisplay.so

%.o : %.c
	$(CC) $(FLAGS) $(CFLAGS) $(SDLFLAGS) $(LIBS) -o $@ -c $<

libdisplay.so : $(OBJECTS)
	mkdir -p $(LIBS_DIR)
	$(CC) $(FLAGS) $(CFLAGS) $(ARFLAGS) -L/usr/lib64 -lSDL2 -lpthread -o $(LIBS_DIR)/$@ $^

configure.in : configure
	./configure

clean:
	$(RM) $(OBJECTS)
	$(RM) libdisplay.a
	$(RM) configure.in
