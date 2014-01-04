##### Variables
AT:=@
INCDIR = -I./GamePad/include
CPPFLAGS += -g -Wall -W $(INCDIR) -fPIC
LFLAGS = -L./GamePad/library/debug-linux64 -lstem_gamepad -lX11 -lglfw -lGL -lGLEW -lfreeimage
CXX = g++
    INSTALLTARGET = /usr/lib/
    RMCOMMAND = rm -f
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CPPFLAGS += -D LINUX -std=c++11
        LFLAGS += -shared
        TARGET = bin/libMINX.so
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

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/libMINX.so
	rm -rf doxygen
	
install:
	cp bin/libMINX.so $(INSTALLTARGET)

doxygen:
	doxygen

doxygenupload:
	ncftpput -R -v -u minx$(AT)gearchicken.com gearchicken.com / ./doxygen/html/

##### End of Makefile
