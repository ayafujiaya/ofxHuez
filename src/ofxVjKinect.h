
#include "ofMain.h"

class ofxVjKinect  : public ofBaseApp {
	
public:	
	void setup(float k_distance);
	void delay_update();
	void draw();	
	void kinectRectDraw(float now_distance, float x, float y, int _step, int frame, int count, bool delay);
    void kinectRectDraw(ofImage image, float now_distance, float x, float y, int _step, int frame, int count, bool delay);
	void kinectCircleDraw(int color_select, bool _showCircleBool);
    void kinectCircleDraw(ofImage image, int color_select, bool _showCircleBool);
	void showCircle();
	void hideCircle();
	void colorChanger(int num);
	void distanceUpdate(float distance);
	void kinectDelayDraw();
	int getMoveCount();
	void getMoveReset();
    void delayReset();
	
private:
	void circleMath(float x, float y,int RB, float _circleR);
	void circleUpdate();
	vector<float> distLine;
	vector<float> circleX, circleY, circleAx, circleAy, circleAlpha, circleR;
	vector<int> circleRB;
	bool showCircleBool;	
	int colorGlobal;
};