/*
 * TrackFaceMain.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: dgyHome
 */


// Included Libraries

#include "TrackFaceLib.hpp"

// name spaces

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	// Learning faces

	string fn_csv="resources/train_image.in";
	string fn_haar="resources/haarcascade_frontalface_default.xml";

	vector<Mat> images;
	vector<int> labels;

	try
	{
		read_csv(fn_csv, images, labels);
	}
	catch (cv::Exception & e)
	{
		cout << "Error" << endl;
		exit(1);
	}

	int im_width=images[0].cols;
	int im_height=images[0].rows;


	Ptr<FaceRecognizer> model=createFisherFaceRecognizer();
	model->train(images, labels);

	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);

	// Camera
	CvCapture* capture=0;
	Mat frame;

	capture=cvCaptureFromCAM(0);

	if (!capture) cout << "No camera detected" << endl;

	cvNamedWindow("Track Face", cv::WINDOW_AUTOSIZE);

	if (capture)
	{
		while (true)
		{
			frame=cvQueryFrame(capture);

			if (frame.empty()) break;

			// processing
			Mat original=frame.clone();

			Mat gray;
			cvtColor(original, gray, CV_BGR2GRAY);

			vector<Rect_<int> > faces;

			haar_cascade.detectMultiScale(gray, faces);

			for (size_t i=0;i<faces.size();i++)
			{
				Rect face_i = faces[i];

				Mat face=gray(face_i);

				Mat face_resized;

				cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

				int prediction = model->predict(face_resized);

				rectangle(original, face_i, CV_RGB(0,255,0),1);

				string box_text=format("Prediction = %d", prediction);

				int pos_x=std::max(face_i.tl().x-10, 0);
				int pos_y=std::max(face_i.tl().y-10, 0);

				putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0),2.0);
			}

			imshow("Track Face",original);

			if (waitKey(1)>=0)
				cvReleaseCapture(&capture);
		}

		waitKey(0);

		cvDestroyWindow("Track Face");
	}

	return 0;
}
