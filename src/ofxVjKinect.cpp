#include "ofxVjKinect.h"
#include <GLUT/GLUT.h>

float kinectDistance;
int delay_timer;
int delay_counter;
float hogeX[200][30000];
float hogeY[200][30000];
float hogeColor[200][30000];

int move_count;
int dotNum, frameNum;
ofImage TGS_image_r, TGS_image_b;
ofPath path;
float circleLimit;

void ofxVjKinect::setup(float k_distance) {	
	distLine.push_back(k_distance);	
	showCircleBool = true;
	kinectDistance = 1800;
    circleLimit = 100;
	dotNum = 30000;
	frameNum = 200;
}

void ofxVjKinect::delayReset() {

    
}

void ofxVjKinect::delay_update() {
	
}

void ofxVjKinect::draw() {
}

void ofxVjKinect::kinectCircleDraw(int color_select, bool _showCircleBool) {
	circleUpdate();
	colorGlobal = color_select;
	ofEnableAlphaBlending();
	if (_showCircleBool) {
		for (int i=0; i < circleX.size(); i++) {
			switch (circleRB[i]) {
				case 0:
                    ofSetColor(200, 0, 0, circleAlpha[i]);
                    ofSetColor(51,204,153, circleAlpha[i]);
					ofCircle(circleX[i], circleY[i], circleR[i]);
                    
                    ofSetColor(255,153,255, 200);
					//ofSetColor(0, 0, 0, circleAlpha[i] + 100);
					ofCircle(circleX[i], circleY[i], circleR[i] * 0.6);
					break;
				case 1:
                    ofSetColor(0, 0, 200, circleAlpha[i]);
                    ofSetColor(255,153,255, circleAlpha[i]);
					ofCircle(circleX[i], circleY[i], circleR[i]);
                    
                    ofSetColor(51,204,153 ,200);
					//ofSetColor(0, 0, 0, circleAlpha[i] + 100);
					ofCircle(circleX[i], circleY[i], circleR[i] * 0.6);
					break;
				default:
					break;
			}
		}
	}
	
}


//circleDraw's over load function
void ofxVjKinect::kinectCircleDraw(ofImage image, int color_select, bool _showCircleBool) {
	circleUpdate();
	colorGlobal = color_select;
	ofEnableAlphaBlending();
	if (_showCircleBool) {
		for (int i=0; i < circleX.size(); i++) {
			switch (circleRB[i]) {
				case 0:
                    //ofSetColor(255, 255, 255, circleAlpha[i]);
                    ofSetColor(51,204,153, circleAlpha[i]);
                    ofPushMatrix();
                    ofTranslate(circleX[i], circleY[i]);
                    if(circleX[i] > ofGetWidth()) {
                        ofRotateZ(ofGetFrameNum() * 30);
                    } else {
                        ofRotateZ(ofGetFrameNum() * -30);
                    }
                    image.draw(-image.width / 2, -image.height / 2, circleR[i]);
                    ofPopMatrix();
                    
					break;
				case 1:
                    
                    //ofSetColor(255, 255, 255, circleAlpha[i]);
                    ofSetColor(255,153,255, circleAlpha[i]);
                    ofPushMatrix();
                    ofTranslate(circleX[i], circleY[i]);
                    if(circleX[i] > ofGetWidth()) {
                        ofRotateZ(ofGetFrameNum() * 30);
                    } else {
                        ofRotateZ(ofGetFrameNum() * -30);
                    }
                    ofRotateZ(ofGetFrameNum() * 10);
                    image.draw(-image.width / 2, -image.height / 2, circleR[i]);
                    ofPopMatrix();
					break;
				default:
					break;
			}
		}
	}
	
}

void ofxVjKinect::showCircle() {
	showCircleBool = true;
	
}

void ofxVjKinect::hideCircle() {
	showCircleBool = false;
}

void ofxVjKinect::distanceUpdate(float distance) {
	kinectDistance = distance;
}

int ofxVjKinect::getMoveCount() {
	return move_count;
}

void ofxVjKinect::getMoveReset() {
	move_count = 0;
}


void ofxVjKinect::kinectDelayDraw() {
	
	for (int i=0; i < dotNum; i++) {
		ofSetColor(255, 255, 255);
		ofRect(hogeX[ofGetFrameNum() % frameNum][i], hogeY[ofGetFrameNum() % frameNum][i], 3, 3);
	}
	
}


void ofxVjKinect::kinectRectDraw(float now_distance, float x, float y, int _step, int frame,int count, bool delay) {
	
	delay_counter = ofGetWidth() * ofGetHeight();
	float circleMath_1 = distLine[ofGetWidth() * y + x];
	float circleMath_2 = now_distance;
	float circleMath_3 = distLine[ofGetWidth() * y + x] - now_distance;
	float axel = 10;
	int math_3_limit_max = 150;
	int math_3_limit_mini = 5;
	int circle_math_3_limit = 65;
    int yuuri = 1;

	if (circleMath_2 < kinectDistance) {				
		if (circleMath_1 > circleMath_2 &&
			circleMath_3 > math_3_limit_mini &&
			circleMath_3 < math_3_limit_max) {
            
            //色１
            ofSetColor(51,204,153);
			int random_size = ofRandom(1, 4);
			int map_size = ofMap(circleMath_3, math_3_limit_mini, math_3_limit_max, 0, 5);
            
            //usualy codes
			ofRect(x, y, _step, _step);
            
			if (delay) {
				hogeX[frame][count] = x;
				hogeY[frame][count] = y;
			}
			
			move_count++;
			
			
			if (circleMath_3 > circleLimit) {
				float hoge = ofMap(now_distance, 400, kinectDistance, 15, 5);
				circleMath(x, y, 1, hoge);
			}
			
		} else if (circleMath_1 < circleMath_2 &&
            circleMath_3 < -math_3_limit_mini &&
            circleMath_3 > -math_3_limit_max) {
            //色２
            ofSetColor(255,153,255);
			int random_size = ofRandom(0, 4);
			int map_size = ofMap(circleMath_3, math_3_limit_mini, math_3_limit_max, 0, 5);
            
			//usualy codes
			ofRect(x, y, _step, _step);
            
			
			if (delay) {
				hogeX[frame][count] = x;
				hogeY[frame][count] = y;
				//hogeColor[frame][count] = ofMap(ofGetFrameNum() % 200, 0, 200, 0, 255);
			}
			
			move_count++;
			if (circleMath_3 < -circleLimit) {
				float hoge = ofMap(now_distance, 400, kinectDistance, 15, 5);
				circleMath(x, y, 0, hoge);
			}
		}
		distLine[ofGetWidth() * y + x] = (circleMath_2);	
	}
	ofFill();

    //ofPopMatrix();
	
}


//ofImage plused kinectRectDraw function
void ofxVjKinect::kinectRectDraw(ofImage image, float now_distance, float x, float y, int _step, int frame,int count, bool delay) {
	
	delay_counter = ofGetWidth() * ofGetHeight();
	float circleMath_1 = distLine[ofGetWidth() * y + x];
	float circleMath_2 = now_distance;
	float circleMath_3 = distLine[ofGetWidth() * y + x] - now_distance;
	float axel = 10;
	int math_3_limit_max = 150;
	int math_3_limit_mini = 5;
	int circle_math_3_limit = 65;
    int yuuri = 1;
    
	if (circleMath_2 < kinectDistance) {
		if (circleMath_1 > circleMath_2 &&
			circleMath_3 > math_3_limit_mini &&
			circleMath_3 < math_3_limit_max) {
            ofSetColor(239, 139, 179);
			int random_size = ofRandom(1, 4);
			int map_size = ofMap(circleMath_3, math_3_limit_mini, math_3_limit_max, 0, 5);
            
            //usualy codes
			//ofRect(x, y, _step, _step);
            int rotation = 5;
            if ((int)x % rotation == 0 && (int)y % rotation == 0) {
                image.draw(x, y, _step, _step);
            }
            
            
			if (delay) {
				hogeX[frame][count] = x;
				hogeY[frame][count] = y;
			}
			
			move_count++;
			
			
			if (circleMath_3 > circleLimit) {
				float hoge = ofMap(now_distance, 400, kinectDistance, 15, 5);
				circleMath(x, y, 1, hoge);
			}
			
		} else if (circleMath_1 < circleMath_2 &&
                   circleMath_3 < -math_3_limit_mini &&
                   circleMath_3 > -math_3_limit_max) {
			//ofSetColor(112, 183, 186);
            ofSetColor(204, 0, 204);
			int random_size = ofRandom(0, 4);
			int map_size = ofMap(circleMath_3, math_3_limit_mini, math_3_limit_max, 0, 5);
            
			//usualy codes
			//ofRect(x, y, _step, _step);
            int rotation = 5;
            if ((int)x % rotation == 0 && (int)y % rotation == 0) {
                image.draw(x, y, _step, _step);
            }
			
			if (delay) {
				hogeX[frame][count] = x;
				hogeY[frame][count] = y;
				//hogeColor[frame][count] = ofMap(ofGetFrameNum() % 200, 0, 200, 0, 255);
			}
			
			move_count++;
			if (circleMath_3 < -circleLimit) {
				float hoge = ofMap(now_distance, 400, kinectDistance, 15, 5);
				circleMath(x, y, 0, hoge);
			}
		}
		distLine[ofGetWidth() * y + x] = (circleMath_2);
	}
	ofFill();
    
    //ofPopMatrix();
	
}


bool limit_over;
int limit_over_count;
void ofxVjKinect::circleMath(float x, float y, int RB, float _circleR) {
	int limit_num = 5000;
	if (circleX.size() > limit_num) {
		limit_over = true;
	} else {
		circleX.push_back(x);
		circleY.push_back(y);
		circleRB.push_back(RB);
		circleAx.push_back(ofRandom(-10, 10));
		circleAy.push_back(ofRandom(-5, 5));
		circleAlpha.push_back(170);
		circleR.push_back(_circleR);
	}
	
	
	if (limit_over) {
		circleX[limit_over_count] = x;
		circleY[limit_over_count] = y;
		circleRB[limit_over_count] = RB;
		circleAx[limit_over_count] = ofRandom(-10, 10);
		circleAy[limit_over_count] = ofRandom(-5, 5);
		circleAlpha[limit_over_count] = 170;
		circleR[limit_over_count] = _circleR;
		
		limit_over_count++;
		
		if (limit_over_count > limit_num ) {
			limit_over_count = 0;
		}
	}
	
}

void ofxVjKinect::circleUpdate() {
	for (int i=0; i < circleX.size(); i++) {
		circleX[i] += circleAx[i];
		circleY[i] += circleAy[i];
		circleAlpha[i] -= 10;
	}
	
}



/*#include "ofxVjKinect.h"

float kinectDistance;

void ofxVjKinect::setup(float k_distance) {	
	distLine.push_back(k_distance);	
	showCircleBool = true;
	kinectDistance = 1800;
	if (distLine.size() < 1) {
		
	}
}

void ofxVjKinect::update() {
}

void ofxVjKinect::draw() {
}

void ofxVjKinect::kinectCircleDraw(int color_select, bool _showCircleBool) {
	circleUpdate();
	colorGlobal = color_select;
	ofEnableAlphaBlending();
	if (_showCircleBool) {
	for (int i=0; i < circleX.size(); i++) {

		

		
		switch (circleRB[i]) {
			case 0:
				
				switch (color_select) {
					case 0:

						
						ofSetColor(255, 255, 255, circleAlpha[i]);
						ofCircle(circleX[i], circleY[i], circleR[i]);
						ofSetColor(61, 76, 83, circleAlpha[i] + 100);
						ofCircle(circleX[i], circleY[i], circleR[i] / 2);
						
						break;
					case 1:

						break;

					default:
						break;
				}
				
				break;
			case 1:
				
				switch (color_select) {
					case 0:

						
						ofSetColor(61, 76, 83, circleAlpha[i]);
						ofCircle(circleX[i], circleY[i], circleR[i]);
						ofSetColor(255, 255, 255, circleAlpha[i] + 100);
						ofCircle(circleX[i], circleY[i], circleR[i] / 2);
						break;
					case 1:

						break;
					default:
						break;
				}
				break;

			default:
				break;
		}
	}
	}
	
}

void ofxVjKinect::showCircle() {
	showCircleBool = true;
	
}

void ofxVjKinect::hideCircle() {
	showCircleBool = false;
}

void ofxVjKinect::distanceUpdate(float distance) {
	kinectDistance = distance;
}
	
//近づいてる　遠ざかってる　を判断して、パーティクルをはじけさせる。


void ofxVjKinect::kinectRectDraw(float now_distance, float x, float y, int _step) {
	//ofNoFill();
	float circleMath_1 = distLine[ofGetWidth() * y + x];
	float circleMath_2 = now_distance;
	float circleMath_3 = distLine[ofGetWidth() * y + x] - now_distance;
	//float rectWidth = ofGetWidth() / _step;
	
	float axel = 10;
	
	int math_3_limit_max = 150;
	int math_3_limit_mini = 5;
	int circle_math_3_limit = 65;


	
	if (circleMath_2 < kinectDistance) {				
		if (circleMath_1 > circleMath_2 &&
			circleMath_3 > math_3_limit_mini &&
			circleMath_3 < math_3_limit_max) {
			if (colorGlobal == 1) {
				ofSetColor(255, 215, 0, 150 );
			} else {
				ofSetColor(241, 67, 63);
			}
			
			int random_size = ofRandom(1, 4);
			int map_size = ofMap(circleMath_3, math_3_limit_mini, math_3_limit_max, 0, 5);


			
			ofRect(x, y, _step, _step);
			ofNoFill();
			ofSetColor(0, 0, 0);
			ofRect(x, y, _step, _step);
			ofFill();
			

			//red++;
			if (circleMath_3 > 80) {
				float hoge = ofMap(now_distance, 400, kinectDistance, 15, 5);
				circleMath(x, y, 1, hoge);
			}
		
		} else if (circleMath_1 < circleMath_2 &&
				   circleMath_3 < -math_3_limit_mini &&
				   circleMath_3 > -math_3_limit_max) {
			
			if (colorGlobal == 1) {
				ofSetColor(148, 0, 211, 150);
			} else {
				ofSetColor(112, 183, 186);
			}
			//ofRect(x, y, _step, _step);
			
			int random_size = ofRandom(0, 4);
			int map_size = ofMap(circleMath_3, math_3_limit_mini, math_3_limit_max, 0, 5);

			
			ofRect(x, y, _step, _step);
			ofNoFill();
			ofSetColor(0, 0, 0);
			ofRect(x, y, _step, _step);
			ofFill();
			
			//blue++;
			if (circleMath_3 < -80) {
				float hoge = ofMap(now_distance, 400, kinectDistance, 15, 5);
				circleMath(x, y, 0, hoge);
			}
		}
		distLine[ofGetWidth() * y + x] = (circleMath_2);	
	}
	ofFill();
	
}
bool limit_over;
int limit_over_count;
void ofxVjKinect::circleMath(float x, float y, int RB, float _circleR) {
	int limit_num = 2000;
	if (circleX.size() > limit_num) {
		limit_over = true;
	} else {
		circleX.push_back(x);
		circleY.push_back(y);
		circleRB.push_back(RB);
		circleAx.push_back(ofRandom(-10, 10));
		circleAy.push_back(ofRandom(-5, 5));
		circleAlpha.push_back(170);
		circleR.push_back(_circleR);
	}

	
	if (limit_over) {
		circleX[limit_over_count] = x;
		circleY[limit_over_count] = y;
		circleRB[limit_over_count] = RB;
		circleAx[limit_over_count] = ofRandom(-10, 10);
		circleAy[limit_over_count] = ofRandom(-5, 5);
		circleAlpha[limit_over_count] = 170;
		circleR[limit_over_count] = _circleR;
		
		limit_over_count++;
		
		if (limit_over_count > limit_num ) {
			limit_over_count = 0;
		}
	}
	
}

void ofxVjKinect::circleUpdate() {
	for (int i=0; i < circleX.size(); i++) {
		circleX[i] += circleAx[i];
		circleY[i] += circleAy[i];
		circleAlpha[i] -= 10;
	}
	
}
*/