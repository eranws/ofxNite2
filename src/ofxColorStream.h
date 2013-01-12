#pragma once
#include "ofThread.h"
#include "ofPixels.h"

namespace openni
{
	class Device;
	class VideoStream;
}

class ofxColorStream : public ofThread
{

public:

	void setup(ofPtr<openni::Device> device = ofPtr<openni::Device>(), bool isVerbose = false);
	void exit();

	ofPtr<openni::Device> getDevice() const { return device; }
	ofPtr<openni::VideoStream> getStream() const { return stream; }

	ofPixels& getPixels() const { return *pixels[0]; }

protected:
	ofPtr<ofPixels> pixels[2];
	
	virtual void threadedFunction();
	void allocateBuffers();

	ofPtr<openni::Device> device;
	ofPtr<openni::VideoStream> stream;

};
