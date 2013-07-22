##### Variables

INCDIR = -I/usr/include
CPPFLAGS = -g -Wall -W $(INCDIR) -fPIC -std=c++11
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
	OS=$(uname -s)
	#I don't know if uname -m for 32 bit will output i386 or x86 (i386 is needed for it to work correctly)
	rm -f /usr/lib/$(uname -m)-${OS,,}-gnu/libMINX.so
	cp bin/libMINX.so /usr/lib/$(uname -m)-${OS,,}-gnu/

##### End of Makefile
