/*
 *  ofxB.cpp
 *  emptyExample
 *
 *  Created by Yuki Takada on 4/20/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxB.h"


void ofxB::setup(float RX,float RY) {

	x = RX;
	y = RY;
	z = -1000;
	ax = ofRandom(-20, 20);
	ay = ofRandom(-20, 20);
	az = ofRandom(2, 5);
	r =  ofRandom(0, 255);
	g =  ofRandom(0, 255);
	b =  ofRandom(0, 255);
    angle = 0;
    angleX = ofRandom(-5, 5);
    
	
	
}
	

void ofxB::update() {
	
	x += ax;
	y += ay;
	z += az;
    angle += angleX;
	if (z > 0) {
		z = -1000;
		x = ofRandom(0, ofGetWidth());
		y = ofRandom(0, ofGetHeight());
	}

}