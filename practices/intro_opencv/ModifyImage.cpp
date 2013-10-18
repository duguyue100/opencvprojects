/*
 * ModifyImage.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: dgyHome
 */

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc!=2)
	{
		cout << "Useage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	char* imageName=argv[1];


	Mat image;
	image=imread(imageName, IMREAD_COLOR);

	if (!image.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat gray_image;

	cvtColor(image,gray_image,COLOR_BGR2GRAY);

	imwrite("../Gray_image.jpg", gray_image);

	namedWindow(imageName, WINDOW_AUTOSIZE);
	namedWindow("Gray Image", WINDOW_AUTOSIZE);

	imshow(imageName, image);
	imshow("Gray Image", gray_image);

	waitKey(0);

	return 0;
}


