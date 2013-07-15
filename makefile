LIBS := -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer

libMINX.so: build/*.o
	g++ $(LIBS) -shared $(inputs) -o $(output)

build/%.o: %.cpp
	g++ -fPIC -c $(input) -o $(output)
