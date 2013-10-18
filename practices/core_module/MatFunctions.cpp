/*
 * MatFunctions.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: dgyHome
 */

#include<iostream>
#include<vector>
#include<opencv/cv.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat M(2,2,CV_8UC3, Scalar(0,0,255));

	cout << "M =" << endl << M << endl;

	// create a header for an already existing IplImage pointer

	IplImage* img=cvLoadImage(argv[1],1);
	Mat mtx(img);

	namedWindow("Display",cv::WINDOW_AUTOSIZE);
	imshow("Display", mtx);

	// very nice function

	vector<float> v;
	v.push_back((float)CV_PI);
	v.push_back(2);
	v.push_back(3.01f);

	cout << Mat(v) << endl;

	vector<Point2f> vPoints(20);
	for (size_t i = 0; i < vPoints.size(); ++i)
	    vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));

	cout << vPoints << endl;

	waitKey(0);

	return 0;
}


