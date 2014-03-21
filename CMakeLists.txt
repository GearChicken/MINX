cmake_minimum_required (VERSION 2.6)

project (MINX)

set(CMAKE_CXX_FLAGS "-g -Wall -fPIC -D LINUX -std=c++11 -shared")
find_package(GLFW3)
find_package(GLEW)
find_package(OpenGL)
find_package(Freetype)

include_directories(/usr/include/freetype2 /usr/include/MINX)

set(PROGRAMS Game GameComponent GameTime MathHelper Ray2 Rectangle Thread Vector2 Graphics/Color Graphics/Font Graphics/GameWindow Graphics/ShaderFactory Graphics/Texture2D Graphics/TextureBatch Input/Button Input/GamePad Input/IGenericHID Input/Keyboard Input/Mouse Media/SoundFile Media/SoundPlaylist)

foreach(program ${PROGRAMS})
	add_executable(objects/${program} ../src/${program}.cpp)
endforeach(program) 
