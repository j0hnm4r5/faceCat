#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "ofxFaceTracker.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	void findCat();
	
	ofImage cat;
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	
	ofPoint leftEye;
	ofPoint rightEye;
	ofPoint mouth;
	
	bool bDrawFeatures;

};
