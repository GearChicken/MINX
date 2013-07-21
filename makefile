##### Variables

INCDIR = -I/usr/include
CPPFLAGS = -g -Wall -W $(INCDIR) -fPIC
LFLAGS = -shared -lSDL_gfx -lX11 -lSDL -lSDL_image -lSDL_mixer
CC = g++

##### Files

SOURCES = $(wildcard src/*.cpp) $(wildcard src/Graphics/*.cpp) $(wildcard src/Input/*.cpp)
OBJECTS = $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp)) $(patsubst src/Graphics/%.cpp,src/Graphics/%.o,$(wildcard src/Graphics/*.cpp)) # $(patsubst src/Input/%.cpp,src/Input/%.o,$(wildcard src/Input/*.cpp))
TARGET = bin/libMINX.so

##### Build rules

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

clean:
	@for dir in src; do find $$dir -name \*.o -exec rm -f {} \; ; done
	rm -f bin/libMINX.so

install:
	cp bin/libMINX.so /usr/lib/libMINX.so
##### End of Makefile
