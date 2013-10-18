OpenCV Projects
==============

This repository includes all the practices I wrote and projects I did in OpenCV.

##SOME NEW FACTS (OCT 2013)###

* By this date (Oct 18th, 2013), in order to install OpenCV on Mac OS, it's still better to use version 2.4.3 instead of latest release since some compatible problems (not confirmed actually, but happened to my machine).
* Hebrew is an awesome tool for completing Mac OS.
* The process to install OpenCV in mac is like this:
    + First, download OpenCV and uncompress it locally, I recommend that you move it to home folder.
    + Second, install `cmake`, apparently, it's very important. You can in fact install it using Hebrew by using `ruby -e "$(curl -fsSL https://raw.github.com/mxcl/homebrew/go)"`. And then use `brew install cmake` to install `cmake`
    + Third, `cd` to your opencv folder and execute following commands: `mkdir build`, `cd build`, `cmake -G "Unix Makefiles"`, `make -j8`, `sudo make install`, and yes, you do need administrator access.
    + If everything moves correctly, now you can enjoy your fresh OpenCV installation.
    + If you want to remove it, go to `build` folder and run `sudo make uninstall`. This command will clear everything for you.
* Eclipse+OpenCV is still my best choice
    + Sadly, you need to configure C++ build properties every time (as I know).
    + In MacOS C++ Linker/Libraries: include `/usr/local/lib/` in _Library search path (-L)_, include `opencv_core`, `opencv_imgproc`, `opencv_highgui`, `opencv_ml`, `opencv_video`, `opencv_features2d`, `opencv_calib3d`, `opencv_objdetect`, `opencv_contrib`, `opencv_legacy`, `opencv_flann` in _Libraries (-L)_
    + In GCC C++ Compiler/Includes: include `/usr/local/include/` in _Include paths (-I)_
* Of course, system library are still working.
* When you include a library from OpenCV, better use like `#include<opencv2/core/core.hpp>`
* Read Image: `imread("argument", OPTION)`
* Image type: `Mat` (not like old days)
* Create a window object: `namedWindow("name", WINDOW_AUTOSIZE)`, if you are not using Qt, `WINDOW_AUTOSIZE` is the only option.
* Show image: `imshow("window's name", image)`.
* Waiting for key stroke: `waitKey(0)`.
* Seems like you don't have to destroy and release resource anymore.
* `cvtColor` is able to perform colour transformation, in this case, `CV_BGR2GRAY` specify that image is changed from BGR format to Grayscale format. And if you look at it, there are many of them.
* Write image: `imwrite("address",image)` is the corresponding function for writing image to disk.
* The function and data type mentioned above can be found in `cv` class.
* Some interesting facts about `Mat` class
    + If you perform something like `A=C` or `Mat B(A)`, different `Mat` object will have certainly the different headers, but they are all pointing to the same data matrix.
    + Use `A.clone()` or `A.copyTo(B)` instead.
    + You don't need to worry about memory management.
    + Supporting storage format: RGB, HSV & HLS, YCrCb (JPEG) and CIE L*a*b*
    + There are some Matlab style function available to use `Mat::eye`, `Mat::ones`, `Mat::zeros`
    + Output formatting is pretty interesting.
    + Can format a vector to matrix


###Contacts###

Name: Hu Yuhuang (duguyue100)

Email: duguyue100@gmail.com

Address: _No. 42, North, Flatland_
