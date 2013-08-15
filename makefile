##### Variables

INCDIR = -I/usr/include -I/usr/include/SDL
CPPFLAGS += -g -Wall -W $(INCDIR) -fPIC -O3
LFLAGS = -lSDL_gfx -lX11 -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
CXX = g++
ifeq ($(OS),Windows_NT)
    CPPFLAGS += -D _WIN32 -mdll -mwindows
    TARGET = bin/MINX.dll
    INSTALLTARGET = C:\\windows\\system32
    RMCOMMAND = del
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CPPFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CPPFLAGS += -D IA32
    endif
else
    INSTALLTARGET = /usr/lib/
    RMCOMMAND = rm -f
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CPPFLAGS += -D LINUX -std=c++11
        LFLAGS += -shared
        TARGET = bin/libMINX.so
    endif
    ifeq ($(UNAME_S),Darwin)
        CPPFLAGS += -D OSX -I/usr/include/SDL_mixer -I/usr/include/SDL_image -I/usr/include/SDL_ttf
        LFLAGS += -dynamiclib
        TARGET = bin/libMINX.dylib
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CPPFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CPPFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CPPFLAGS += -D ARM
    endif
endif
##### Files

SOURCES = $(wildcard src/*.cpp) $(wildcard src/Graphics/*.cpp) $(wildcard src/Input/*.cpp) $(wildcard src/Audio/*.cpp)
OBJECTS = $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp)) $(patsubst src/Graphics/%.cpp,src/Graphics/%.o,$(wildcard src/Graphics/*.cpp)) $(patsubst src/Input/%.cpp,src/Input/%.o,$(wildcard src/Input/*.cpp)) $(patsubst src/Audio/%.cpp,src/Audio/%.o,$(wildcard src/Audio/*.cpp))



##### Build rules

.PHONY: doxygen

all: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)
	
raspi: CPPFLAGS += -mtune=arm1176jzf-s
raspi : all;

x86: CPPFLAGS += -m32 -march=i686 -mtune=i686
x86 : all;

windows: CXX = i686-w64-mingw32-g++
windows: CPPFLAGS = -mdll -I/usr/i686-w64-mingw32/include/ -I/usr/i686-w64-mingw32/include/SDL/ -D IA32 -std=c++0x
windows: LFLAGS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
windows: TARGET = bin/MINX.dll
windows: all;

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/libMINX.so
	rm -rf doxygen
	
install:
	cp bin/libMINX.so $(INSTALLTARGET)

doxygen:
	doxygen

doxygenupload:
	ncftpput -R -v -u MINX gearchicken.com / ./doxygen/html/

##### End of Makefile
