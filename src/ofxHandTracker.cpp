#include "ofxHandTracker.h"

#include "Nite.h"

void ofxHandTracker::setup(ofPtr<openni::Device> device)
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

void ofxHandTracker::exit()
{
	stopThread();
	waitForThread();
}

void ofxHandTracker::threadedFunction()
{
	
		nite::HandTracker handTracker;		
		nite::HandTrackerFrameRef handTrackerFrame;	
		nite::Status niteRc;

		niteRc = handTracker.create(device.get());
		if (niteRc != nite::STATUS_OK)
		{
			throw ("Couldn't create user tracker\n");
		}

		handTracker.startGestureDetection(nite::GESTURE_WAVE);
		handTracker.startGestureDetection(nite::GESTURE_CLICK);


		//if using nite thread (unsupported for now)
		//handTracker.addListener(this);	


		while (isThreadRunning())
		{
			niteRc = handTracker.readFrame(&handTrackerFrame);
			if (niteRc != nite::STATUS_OK)
			{
				printf("Get next frame failed\n");
				continue;
			}

			const nite::Array<nite::GestureData>& gestures = handTrackerFrame.getGestures();
			for (int i = 0; i < gestures.getSize(); ++i)
			{
				if (gestures[i].isComplete())
				{
					nite::HandId newId;
					handTracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
				}
			}

			const nite::Array<nite::HandData>& hands = handTrackerFrame.getHands();
			for (int i = 0; i < hands.getSize(); ++i)
			{
				const nite::HandData& hand = hands[i];
				if (hand.isTracking())
				{
					printf("%d. (%5.2f, %5.2f, %5.2f)\n", hand.getId(), hand.getPosition().x, hand.getPosition().y, hand.getPosition().z);
				}
			}
		}

		nite::NiTE::shutdown();
}



