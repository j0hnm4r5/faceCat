#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
	cam.initGrabber(500, 375);
	tracker.setup();
	ofBackground(10, 15, 15);
	
	bDrawFeatures = true;
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
	findCat();
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
	leftEye.set(tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D()[0], tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D()[1]);
	rightEye.set(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D()[0], tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D()[1]);
	mouth.set(tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH).getCentroid2D()[0], tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH).getCentroid2D()[1]);
	
	if (bDrawFeatures) {
		ofPushStyle();
			ofNoFill();
			ofSetLineWidth(2);
			ofSetColor(255, 0, 255);
			
			ofCircle(leftEye, 5);
			ofCircle(rightEye, 5);
			ofCircle(mouth, 5);
		ofPopStyle();
	}
	
	if (leftEye.x != 0 && leftEye.y != 0) {
		cat.draw(500, 0);
	}
	
}

void testApp::findCat() {

	float closestCatDist = 99999.;
	string closestCatName = "";
	
	string path = "/Users/johnmars/Desktop/CAT_DATASET/CAT_00";
	ofDirectory dir(path);
	dir.allowExt("cat");
	dir.listDir();
	
	for(int i = 0; i < dir.numFiles(); i++){
		string fileContents(ofBufferFromFile(dir.getPath(i)));
		vector<string> split = ofSplitString(fileContents, " ");

		ofPoint leftEyeCat;
		ofPoint rightEyeCat;
		ofPoint mouthCat;
		
		leftEyeCat.set(ofToInt(split[1]), ofToInt(split[2]));
		rightEyeCat.set(ofToInt(split[3]), ofToInt(split[4]));
		mouthCat.set(ofToInt(split[5]), ofToInt(split[6]));
		
		float currentDist = mouth.distance(mouthCat) + leftEye.distance(leftEyeCat) + rightEye.distance(rightEyeCat);
		
		if (currentDist < closestCatDist) {
				closestCatDist = currentDist;
				closestCatName = dir.getPath(i);
			
		}
		
	}
	
	ofStringReplace(closestCatName, ".cat", "");
	cat.loadImage(closestCatName);
	
//	ofLog() << closestCatDist <<  " " << closestCatName;
	
}

void testApp::keyPressed(int key) {
	switch (key) {
		case 'r':
			tracker.reset();
			break;
		case ' ':
			bDrawFeatures = !bDrawFeatures;
			break;
	}
}