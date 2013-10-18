/*
 * DisplayImage.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: dgyHome
 */

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

char key;

int main(int argc, char** argv)
{
	if (argc!=2)
	{
		cout << "Useage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}


	Mat image;
	image=imread(argv[1], IMREAD_COLOR);

	if (!image.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);

	waitKey(0);

	return 0;
}


