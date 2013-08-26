Dependencies
------------
 * SDL2
 * SDL2_image
 * SDL2_ttf



Compiling in Visual Studio (2012)
---------------------------------
Is pretty straight forward. Edit the SDL2.props property
sheet and update the locations to point to your locations
for the includes and libraries.



Compiling on linux
------------------
As long as you have all the dependencies (and their development
packages) installed, it should be as easy as:

    cd LD27; make
