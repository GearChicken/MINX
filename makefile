##### Variables
AT:=@
INCDIR = -I./GamePad/include -I/usr/include/freetype2 -I./GL/x86/include
CPPFLAGS += -g -Wall -W $(INCDIR) -fPIC
LFLAGS = -lX11 -lglfw -lGL -lGLEW -lfreeimage -lgorilla
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
        CPPFLAGS += -D OSX 
        LFLAGS += -dynamiclib
        TARGET = bin/libMINX.dylib
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CPPFLAGS += -D AMD64
		LFLAGS += -L./GamePad/library/debug-linux64 -lstem_gamepad
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CPPFLAGS += -D IA32
		LFLAGS += -L./GamePad/library/debug-linux32 -lstem_gamepad
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CPPFLAGS += -D ARM
    endif
endif
##### Files

SOURCES = $(wildcard src/*.cpp) $(wildcard src/Graphics/*.cpp) $(wildcard src/Input/*.cpp) $(wildcard src/Audio/*.cpp)
HEADERS = $(wildcard src/*.h) $(wildcard src/Graphics/*.h) $(wildcard src/Input/*.h) $(wildcard src/Audio/*.h)
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
windows: LFLAGS = 
windows: TARGET = bin/MINX.dll
windows: all;

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/libMINX.so
	rm -rf doxygen
	
install:
	cp bin/libMINX.so $(INSTALLTARGET)

headers:
	test -d /usr/include/MINX || mkdir -p /usr/include/MINX
	test -d /usr/include/MINX/Input || mkdir -p /usr/include/MINX/Input
	test -d /usr/include/MINX/Graphics || mkdir -p /usr/include/MINX/Graphics
	test -d /usr/include/MINX/Media || mkdir -p /usr/include/MINX/Media
	cp -u -r src/*.h /usr/include/MINX/
	cp -u -r src/Input/*.h /usr/include/MINX/Input
	cp -u -r src/Graphics/*.h /usr/include/MINX/Graphics
	cp -u -r src/Media/*.h /usr/include/MINX/Media
	cp -u -r GamePad/include/* /usr/include/MINX
	cp -u -r GL/x86/include/* /usr/include/MINX
doxygen:
	doxygen

doxygenupload:
	ncftpput -R -v -u minx$(AT)gearchicken.com gearchicken.com /docs ./doxygen/html/*

##### End of Makefile
