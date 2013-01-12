#pragma once
#include "ofThread.h"
#include "ofPixels.h"

namespace openni
{
	class Device;
	class VideoStream;
}

class ofxDepthStream : public ofThread
{

public:

	void setup(ofPtr<openni::Device> device = ofPtr<openni::Device>(), bool isVerbose = false);

	void exit();

	ofPtr<openni::Device> getDevice() const { return device; }
	ofPtr<openni::VideoStream> getStream() const { return stream; }

	ofPtr<ofShortPixels> getPixels() const { return pixels[0]; }

	ofVec3f cameraToWorld(ofVec2f p); //Depth Camera?

protected:
	ofPtr<ofShortPixels> pixels[2];

	virtual void threadedFunction();
	void allocateBuffers();

	ofPtr<openni::Device> device;
	ofPtr<openni::VideoStream> stream;
	
};
