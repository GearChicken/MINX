##### Variables

INCDIR = -I/usr/include
CPPFLAGS = -g -Wall -W $(INCDIR) -fPIC -std=c++11 -O3
LFLAGS = -lSDL_gfx -lX11 -lSDL -lSDL_image -lSDL_mixer
CC = g++
ifeq ($(OS),Windows_NT)
    CPPFLAGS += -D WIN32 -mdll -mwindows
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
        CPPFLAGS += -D LINUX
        LFLAGS += -shared
        TARGET = bin/libMINX.so
    endif
    ifeq ($(UNAME_S),Darwin)
        CPPFLAGS += -D OSX -fno_commons
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

SOURCES = $(wildcard src/*.cpp) $(wildcard src/Graphics/*.cpp) $(wildcard src/Input/*.cpp)
OBJECTS = $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp)) $(patsubst src/Graphics/%.cpp,src/Graphics/%.o,$(wildcard src/Graphics/*.cpp)) $(patsubst src/Input/%.cpp,src/Input/%.o,$(wildcard src/Input/*.cpp))



##### Build rules

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/libMINX.so
	
install:
	cp bin/libMINX.so $(INSTALLTARGET)

##### End of Makefile
