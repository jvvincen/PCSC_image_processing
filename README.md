# Readme



## RUNNING THE PROGRAM

Warning: In order to run the program with google tests, googletest has to be downloaded from
https://github.com/google/googletest. The folder should be placed next to the build folder and
the source files.

STEP 1: Build the program from a build folder
-Open a terminal and go to the desired location, next to the source files

--&gt;mkdir build

--&gt;cd build

--&gt;cmake &lt;Path to the src folder&gt;

--&gt;make

STEP 2: Execute the program

From the build folder

Main program  --&gt; ./image_process

tests --&gt; ./runTests


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   ## PROCEDURE: Running ./image_process
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -



When you start the main program, you will be prompted with a display of the chosen picture.

You will have to press space in order to display the  Fourier transformation of the image.



The image of Lena is displayed is in color.



<img src="/pics/lena.png" alt="Lena color" width="400"/>

After pressing a key, four histograms are displayed showing the intensity distribution of the pixels for the image in gray and the three channels separately, Red, Green and Blue. The range of intensity values goes from 0 being black to 255, the brightest.

The histogram is plotted with Python, but the histogram data comes from the c++ code and is stored in the histogram.txt file.


<img src="/pics/gray.png" alt="Gray histogram" width="400"/>

There are pics of intensity around the low values (50) and medium (150).


<img src="/pics/red.png" alt="Lena red" width="400"/>

For the red, the peak is located around 225, showing high values of intensity for the red distribution.
It can be explained by the pinky/red bakground.


<img src="/pics/blue.png" alt="Lena blue" width="400"/>

The repartition of the blue intensities is well distributed across all values from 0 to 220.

<img src="/pics/green.png" alt="Lena green" width="400"/>

Concerning the green pixels, there are no low intensities. They are all belonging to a medium value range between 50 and 200.

After the histogram, each keystroke will display the image of Lena with the following filter apply by convolution.
By using the convolution, it was requiered to implement a zero padding, that consists in a boolean
For the convolution, we emulate a zero padding with the use of a boolean function that returns false, and assigned the value 0 if the selected coordonates are out the bounds of the image, and true otherwise.
The image of Lena appears in succession, first Prewitt horizontal then vertical, third the high pass filter of the original image and at last the median filter on the former high pass filter of the image.


**Prewitt for horizontal edge detection**



<img src="/pics/prewitt_h.png" alt=" prewitt horizontal" width="200"/>





<img src="/pics/horizontal.png" alt="Lena prewitt horizontal" width="400"/>



**Prewitt for vertical edge detection**

<img src="/pics/prewitt_v.png" alt=" prewitt vertical" width="200"/>


<img src="/pics/vertical.png" alt="Lena prewitt vertical" width="400"/>


**High Pass**


<img src="/pics/high_pass.png" alt="high pass" width="200"/>



<img src="/pics/highpass.png" alt="Lena high" width="400"/>


The high pass filter accentuates the bright features of the image.
As you can see on the image, several bright spots have appeared which can be likened to salt and pepper noise.
The perfect opportunity to test our median filter for noise removal!

**Median filter**

By applying the median filter, each pixel takes the median value for the surrounding pixels.
We can see that, compared to the high pass filter Lena, the noise is reduced.


<img src="/pics/median_filter.png" alt="Lena median" width="400"/>

**Edge detection**

We also tried to apply the edge detection with horizontal prewitt on the image of hand shadows.


<img src="/pics/hand_shadows.png" alt="Hand shadows" width="400"/>


<img src="/pics/hand_shadows_contour.png" alt="Hand shadows" width="400"/>

We can see that it detects the edges.



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   ## TEST: Running ./runTests
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

We implemented the following tests.
**image_convolution**
We tested the function convolve a 3x3 filter on a 3x3 image and by calculation by the hand the expected result and comparing it to the output.
**is_In_Bounds**
We tested if the function isInBounds was able to recognize if some coordonates were in bounds or not for the zero padding.

**get_Intensity**
We created an image with our image class, modified the pixel (10,10) with the function set_pixel_intensity and used the function get_intensity to see if we obtain the modified intensity value of the same pixel.
By this test, we tried both set_pixel_intensity and get_intensity.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   ## To Do's and perspective
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
- Use a tclap implementation in order to allow the use of user defined options.

- Check if the filter applied by fourier and by convolution produce the same result.

- Generalize the function of convolution for different sizes of filter (in this project, it is always a 3x3 filter).

- Unify our two classes.
