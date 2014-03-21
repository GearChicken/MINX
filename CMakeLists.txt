cmake_minimum_required (VERSION 2.6)

project (MINX)

set(CMAKE_CXX_FLAGS "-g -Wall -fPIC -D LINUX -std=c++11 -shared")
find_package(GLFW3)
find_package(GLEW)
find_package(OpenGL)
find_package(Freetype)

include_directories(/usr/include/freetype2 /usr/include/MINX)

set(PROGRAMS ../src/Game.cpp ../src/GameComponent.cpp ../src/GameTime.cpp ../src/MathHelper.cpp ../src/Ray2.cpp ../src/Rectangle.cpp ../src/Thread.cpp ../src/Vector2.cpp ../src/Graphics/Color.cpp ../src/Graphics/Font.cpp ../src/Graphics/GameWindow.cpp ../src/Graphics/ShaderFactory.cpp ../src/Graphics/Texture2D.cpp ../src/Graphics/TextureBatch.cpp ../src/Input/Button.cpp ../src/Input/GamePad.cpp ../src/Input/IGenericHID.cpp ../src/Input/Keyboard.cpp ../src/Input/Mouse.cpp ../src/Media/SoundFile.cpp ../src/Media/SoundPlaylist.cpp)
add_library(MINX SHARED ${PROGRAMS})
