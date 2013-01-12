#include "ofxUserTracker.h"

#include "Nite.h"

void ofxUserTracker::setup(ofPtr<openni::Device> device)
{
	nite::Status niteRc;
	niteRc = nite::NiTE::initialize();
	if (niteRc != nite::STATUS_OK)
	{
		throw ("NiTE initialization failed\n");
	}
	this->device = device;

	startThread(false, true);
}

void ofxUserTracker::exit()
{
	stopThread();
	waitForThread();
}

void ofxUserTracker::threadedFunction()
{

	nite::UserTracker userTracker;		
	nite::UserTrackerFrameRef userTrackerFrame;	
	nite::Status niteRc;

	niteRc = userTracker.create(device.get());
	if (niteRc != nite::STATUS_OK)
	{
		throw ("Couldn't create user tracker\n");
	}


	while (isThreadRunning())
	{
		niteRc = userTracker.readFrame(&userTrackerFrame);
		if (niteRc != nite::STATUS_OK)
		{
			printf("Get next frame failed\n");
			continue;
		}


		const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
		for (int i = 0; i < users.getSize(); ++i)
		{
			const nite::UserData& user = users[i];
			if (user.isVisible())
			{
				ofPoint userCoM = *(ofPoint*)&user.getCenterOfMass();
				printf("user #%d. (%5.2f, %5.2f, %5.2f)\n", user.getId(), userCoM.x);
			}
		}
	}

	nite::NiTE::shutdown();
}



