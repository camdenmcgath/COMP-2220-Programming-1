# Speed and Distance
This program provides two menu options for different user calculations
1) Calculate the speed of sound through a medium
2) Calculate the distance between two pixels in an image

The following information may help explain the calculations used in the pixel distance code:
1) Get the pixel numbers in the image using a program like GIMP (Links to an external site.) (Note that the origin is in the upper-left corner).
2) Convert the pixel numbers to a coordinate system where the origin is in the middle of the picture (subtract half of the image's width from the user's horizontal coordinates & subtract half the image's height from the user's vertical coordinate)
3) Convert pixel coordinates to feet
4) Use the Pythagorean theorem to calculate the distance between the source and destination coordinates

## Menu Tree
```
Main Menu: Prompt asks which calculation user wants
  s) Calculate Speed of Sound Through A Medium
        Select A Material
        a) Air
        s) Steel
        w) Water
        Then Input the distance from the user
    d) Calculate Distance Between Two Pixels
       Input Height of Drone (Typically 300ft) 
       Input Drone's Field-of-View (Typically 94 degrees)
       Input Source X-pixel and Y-pixel (they will be seperated by a space)
       Input Destination X-pixel and Y-pixel (they will be seperated by a space)
```
