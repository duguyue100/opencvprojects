/*
 * IOFunctions.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: dgyHome
 */

#include "TrackFaceLib.hpp"

void read_csv(const string & filename, vector<Mat> & images, vector<int> & labels)
{
	char separator= ';';
	ifstream file(filename.c_str(), ifstream::in);

	if (!file)
	{
		string error_message = "error";
		CV_Error(CV_StsBadArg, error_message);
	}

	string line, path, classlabel;

	while (getline(file, line))
	{
		stringstream liness(line);

		getline(liness, path, separator);
		getline(liness, classlabel);

		if (!path.empty() && !classlabel.empty())
		{
			images.push_back(imread(path,0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}


