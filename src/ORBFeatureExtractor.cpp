//
// ORBFeatureExtractor.cpp
//
// Extract ORB feature of each frame and feed 
// the extracted feature descriptor and position
// into the data manager.
//
// @Yu

#include "Common.h"
#include "ORBFeatureExtractor.h"

void ORBFeatureExtractor::process(DataManager& data, int frameIdx) {
	Frame &frame = data.frames[frameIdx];
	RawBuffer frameBuffer = frame.frameBuffer;
	std::vector<cv::KeyPoint> keypoints;
	detector.detect(frameBuffer, keypoints);
	Mat descriptor;
	extractor.compute(frameBuffer, keypoints, descriptor);
	for (int i=0; i<keypoints.size(); i++)
	{
		frame.features.positions.push_back(keypoints[i].pt);
		frame.features.descriptors = descriptor;
	}

	// Mat visualization;
	// drawKeypoints(frameBuffer, keypoints,visualization, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	// imshow("Keypoint", visualization);
	// waitKey(40);
}

bool ORBFeatureExtractor::validationCheck(DataManager& data, int frameIdx) {
	return true;
}

