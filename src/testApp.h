#pragma once
#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxB.h"
#include "ofxKinect.h"
#include "ofxVjKinect.h"
#include "beatDetect.h"
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
    
    //kinectの変数
    ofxKinect kinect;
    float angle;
    int step;
    
    //kinectのエフェクトの変数宣言
    ofxVjKinect kinectVJ;
    int color_sec;
    float _distance;
    
    //BeatTrackingの変数
    beatDetect bd;
    int testApp_buffer_size = 1024;
    int testApp_fft_size = 512;
    int kick_timer;
    
    //文字列の変数
    ofxTrueTypeFontUC font_mid;
    vector<wstring> strline;
    float alpha;
    vector<ofxB> ofxBMath;
    vector<float> str_alpha;
    
    
    //検索文字表示の変数
    wstring wSearch;
    float searchX, searchY;
    
    //各種切り替えのBool変数
    bool kinectShow, stringShow,kinectCircle , showSearch;
    
    //文字列の変数
    ofxTrueTypeFontUC font_ja, font_title;
    int str_kick_timer;
    
    bool shadow_show;
    
    //グリッチ関連の変数
    bool debugOn;
    bool glitch_on;
    ofImage img;
    ofImageQualityType quality;
    ofImage preGlitch;
    ofImage trans;
    
    //beat detect
    float audioInput;
    
    //motion rec
    bool delay_move;
    bool delay_rec;
    int preStep;
    float fadeX, fadeY;
    int fade_str_num;
    int alpha_timer_2;
};
