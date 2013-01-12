#pragma once

#include "ofThread.h"

namespace openni
{
	class Device;
}

class ofxHandTracker : public ofThread
{
public:
	void setup(ofPtr<openni::Device> device = ofPtr<openni::Device>());
	void exit();

protected:
	virtual void threadedFunction();

private:
	ofPtr<openni::Device> device;
};


