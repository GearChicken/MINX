Hello MINX
==========

Introductory Tutorial to Using MINX

# Setting Up Your Development Enviornment

## For Windows ( Visual Studio )
  1. Launch Visual Studio

  2. Install NuGet Package Manager

  3. Install MINX with the instructions on this page [MINX NuGet Package Link](http://google.com)

## For GNU/Linux
  1. Download the source for the release of MINX that you wish to use
[Source Listing](https://github.com/GearChicken/MINX/releases)

  2. Check that the proper dependencies are installed `./configure.sh`
  
  3. Compile and Install MINX `make` `sudo make install`

# Basic Overview of The MINX::Game Class
  Everything in MINX is centered around the MINX::Game class
When your program is launched these MINX::Game functions
will be called in the following order.

  1. MINX::Game::Game();

  2. MINX::Game::Initialize();

  3. MINX::Game::LoadContent();

  4. MINX::Game::Update();

  5. MINX::Game::Draw(); // Go back to #4 unless the game is told to exit

  6. MINX::Game::UnloadContent();

# Your First MINX Project

## On GNU/Linux

  The following instructions will be created at a later time

## On Windows

  The following instructions will be created at a later time
