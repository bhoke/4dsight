
# Running the Code

OpenCV libraries must have been installed beforehand.

Then, you should compile the code in Linux as follows:

**For OpenCV Version < 4**
>g++ -o 4dsight main.cpp `pkg-config --libs --cflags opencv`

**For OpenCV Version 4**
>g++ -o 4dsight main.cpp `pkg-config --libs --cflags opencv4`

**Final step to run the code**:

>./4dsight Small_area.png StarMap.png 

or
> ./4dsight Small_area_rotated.png StarMap.png 
