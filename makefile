##### Variables
AT:=@
INCDIR = -I/usr/include/freetype2 -I./GL/x86/include
CPPFLAGS += -g -Wall -W $(INCDIR) -fPIC
LFLAGS = -lX11 -lglfw -lGL -lGLEW -lfreeimage -lsfml-audio
CXX = g++
INSTALLTARGET = /usr/lib/
RMCOMMAND = rm -f
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CPPFLAGS += -D LINUX -std=c++11
	LFLAGS += -shared
	EXTENSION = so
endif
ifeq ($(UNAME_S),Darwin)
	CPPFLAGS += -D OSX 
	LFLAGS += -dynamiclib
	EXTENSION = dylib
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
##### Files

SOURCES = $(wildcard src/*.cpp) $(wildcard src/Graphics/*.cpp) $(wildcard src/Input/*.cpp) $(wildcard src/Media/*.cpp)
HEADERS = $(wildcard src/*.hpp) $(wildcard src/Graphics/*.hpp) $(wildcard src/Input/*.hpp) $(wildcard src/Media/*.hpp)
OBJECTS = $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp)) $(patsubst src/Graphics/%.cpp,src/Graphics/%.o,$(wildcard src/Graphics/*.cpp)) $(patsubst src/Input/%.cpp,src/Input/%.o,$(wildcard src/Input/*.cpp)) $(patsubst src/Media/%.cpp,src/Media/%.o,$(wildcard src/Media/*.cpp))



##### Build rules

.PHONY: doxygen

all: $(OBJECTS)
	test -d bin/ || mkdir -p bin/
	$(CXX) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o bin/libMINX.$(EXTENSION)

x86: CPPFLAGS += -m32 -march=i686 -mtune=i686
x86 : all;

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/libMINX.$(EXTENSION)
	rm -rf doxygen
	
install:
	cp bin/libMINX.$(EXTENSION) $(INSTALLTARGET)
	test -d /usr/include/MINX || mkdir -p /usr/include/MINX
	test -d /usr/include/MINX/Input || mkdir -p /usr/include/MINX/Input
	test -d /usr/include/MINX/Graphics || mkdir -p /usr/include/MINX/Graphics
	test -d /usr/include/MINX/Media || mkdir -p /usr/include/MINX/Media
	cp -u -r src/*.h /usr/include/MINX/
	cp -u -r src/Input/*.h /usr/include/MINX/Input
	cp -u -r src/Graphics/*.h /usr/include/MINX/Graphics
	cp -u -r src/Media/*.h /usr/include/MINX/Media
doxygen:
	doxygen

doxygenupload:
	ncftpput -R -v -u minx$(AT)gearchicken.com gearchicken.com /docs/dev ./doxygen/html/*

##### End of Makefile
