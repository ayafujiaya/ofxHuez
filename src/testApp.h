#pragma once
#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxB.h"
#include "ofxKinect.h"
#include "ofxVjKinect.h"
#include "beatDetect.h"
#include "ofxHttpUtils.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void audioReceived(float* input, int bufferSize, int nChannels);
	
	
	void stringDrawTwitter(int num);
	void stringDrawPoetry(int num);
	void bNumReset();
	wstring stringConvertToW(const char* c_buff);
	void debug_page();
	void reset();

		
};
