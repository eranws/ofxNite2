#pragma once
#include "ofThread.h"
#include "ofPixels.h"
#include <vector>

namespace openni
{
	class Device;
	class VideoStream;
	class Recorder;
}

class ofxRecorder : public ofThread
{

public:

	void setup(ofPtr<openni::VideoStream> stream = ofPtr<openni::VideoStream>());

	void addStream(ofPtr<openni::VideoStream> stream);
	void start(string filename);
	void stop();

	void exit();

	bool IsRecording() const {return _isRecording;}

	//ofPtr<openni::Recorder> getRecorder() const { return recorder; }
	
protected:
	
	std::vector<ofPtr<openni::VideoStream>> _streams; //make a list?
	ofPtr<openni::Recorder> recorder;

	bool _isRecording;

};
