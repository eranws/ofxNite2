#include "ofxOniDevice.h"
#include "OpenNI.h"

void ofxOniDevice::setup(const char* uri)
{
	using namespace openni;

	openni::Status rc = openni::OpenNI::initialize();
	if (rc != ONI_STATUS_OK)
	{
		throw ("Initialize failed\n%s\n", openni::OpenNI::getExtendedError());
	}

	device = ofPtr<openni::Device>(new openni::Device);
	rc = device->open(uri);
	if (rc != ONI_STATUS_OK)
	{
		throw std::exception(OpenNI::getExtendedError());
	}

}

void ofxOniDevice::exit()
{
	device->close();
	openni::OpenNI::shutdown();
}

void ofxOniDevice::setRegistration( bool b )
{
	device->isImageRegistrationModeSupported(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	device->setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	
}

