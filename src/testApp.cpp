#include "testApp.h"



//kinectの変数
ofxKinect kinect;
float angle;
int step;

	
//kinectのエフェクトの変数宣言
ofxVjKinect kinectVJ;
//vector<ofxSoundBox> soundParticle;
int color_sec;
float _distance;


//BeatTrackingの変数
beatDetect bd;
int testApp_buffer_size = 1024;
int testApp_fft_size = 512;
int kick_timer;


//文字列の変数
ofxTrueTypeFontUC font_mid, font_small, font_big;
ofTrueTypeFont font_en;
vector<wstring> strline;
float alpha;
vector<ofxB> ofxBMath;
vector<float> str_alpha;


//検索文字表示の変数
wstring wSearch;
float searchX, searchY;


//twitterへのhttpRequest
ofxHttpUtils httpUtils;
int counter;
string action_url;
map<string, map<int, string> > tweets;
vector<wstring> wstr;
string searchName, hogehoge;
wstring whogehoge;


//各種切り替えのBool変数
bool kinectShow, stringShow,kinectCircle , stringWhite, showSearch, PoeOrTwi, hashTag, tweetInter, str_show;

//文字列の変数
float str_x, str_y;
float str_radius;
float str_angle;
ofxTrueTypeFontUC font_ja, font_title;//, font_small, font_mid, font_big;
ofTrueTypeFont yabai_font;
vector<wstring> wstr_1;
vector<float> vx, vy, vr, va, vax, VVX, VVY;
bool moveChangeBool;
//beatDetect bd;
vector<float> alpha_timer;
int str_kick_timer;
ofImage wings;
int alpha_timer_2;
int fade_str_num;
float fadeX, fadeY;
bool fade_str_show;
bool shadow_show;


//yabai_node
//ofxJSONElement result; //修正
float yabai_soku_flo;
int yabai_100;
vector<float> yabaX, yabaY, yabaAx;
ofImage yabai_over, yabai_def, yabai_on, arrow, arrow_2, yaba_gli_over, yaba_gli_def, yaba_gli_on, yaba_gli_on_1,yaba_gli_on_2;
ofImage arrow_big_off, arrow_big_on;

bool mouseOn;
bool debugOn;
bool json_parse;
bool yabai_node_bool;
bool parsingSuccessful;
bool glitch_on;
ofImage img;
ofImageQualityType quality;
ofImage preGlitch;
bool str_dance;
ofImage trans;
float audioInput;
ofImage fukidashi;

//lights
ofLight lights;

/*ーーーーーーーーーーーーーーーーーーーーディレイ！！ーーーーーーーーーーーーーーーーーー*/
 bool delay_move;
 int delay_counter_2;
 int delay_switch_time;
 vector< vector<int> > bool_count;
 wstring call_past[100];
 bool delay_on;
 bool delay_rec;
int preStep;
ofImage kCircleImage;
ofImage kRectImage;
float byWidth, byHeight;

//各種設定ファイルへディレクトリへのパス。
//char path_to_root = "/Users/Yuki/Desktop/ofxHuez/";

//--------------------------------------------------------------

wstring testApp::stringConvertToW(const char* c_buff) {
	const char*   c = c_buff;
	size_t     length = strlen( c );
	wchar_t*   wc = new wchar_t[ length + 1 ];
	length = mbstowcs( wc, c, length + 1);
	return wc;
}

void testApp::reset() {
	//元のファイルを読込み
	img.loadImage("preGlitch.jpg");
}

vector<ofImage> lights_image;
vector<string> three_lights;
int image_number;
int image_number_all;
bool disp_front;
bool mouse_bool;

void testApp::setup(){
    
	//openFrameworks各種初期設定
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofSetCircleResolution(128);
	setlocale( LC_ALL, "ja_JP.UTF-8" );
	ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();
    ofHideCursor();
	
	//フォントの読み込み
	font_mid.loadFont("やさしさゴシック.ttf", 64); //32 //twitter 用
    font_title.loadFont("やさしさゴシック.ttf", 108);
	
	//kinectのセットアップ
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	angle = 0;
	kinect.setCameraTiltAngle(angle);
    kinectShow = true;
	
	//kinectを使ったピクセルごとの距離のイニシャライズ
	for (int x=0; x < ofGetWidth(); x++) { 
		for (int y=0; y < ofGetHeight(); y++) {
			kinectVJ.setup(kinect.getDistanceAt(x,y));
			//cout << ofToString(kinect.getDistanceAt(x,y)) << endl;
		}
	}
	
	//各論理値と数値のイニシャライズ
	kinectShow = true;
	stringShow = FALSE;
	_distance = 1500;
	step = 6;
    
	
	//サウンドインプットのセットアップ
	ofSoundStreamSetup(0, 1, this, 44100, testApp_buffer_size, 4);
	
	//Jpeg圧縮の強度
	quality = OF_IMAGE_QUALITY_LOW;
	reset(); //リセット
	glitch_on = false;
	
	//モーションレック関連の変数の初期化
	color_sec = 0;
	kinectShow = true;
	fade_str_num = 0;
	alpha_timer_2 = 0;
	fadeX = ofRandom(200, 440);
	fadeY = ofRandom(ofGetHeight() / 2, ofGetHeight());
    
    //tweetのtxtファイルからの読み込み
    strline.clear();
    bNumReset();
    setlocale( LC_ALL, "ja_JP.UTF-8" );
    FILE * fp;
    if((fp=fopen("/Users/Yuki/work/ofxHuez/search_result.txt","r"))==NULL){
        cout << "no" << endl;
    }else{
        char buff[256]="";
        while(fgets(buff,256,fp)!=NULL){
            strline.push_back(stringConvertToW(buff));
        }
        fclose(fp);
    }
    
    //サーチワード関連の変数の初期化
    wSearch = L"searching for " + strline[0];
	ofRectangle searchRect = font_title.getStringBoundingBox(wSearch, 0,0);
	searchX = searchRect.width;
	searchY = ofGetHeight() / 2 + searchRect.height / 2;
	showSearch = false;
}

bool stop;

//--------------------------------------------------------------
void testApp::update(){
	kinect.update(); //kinectの更新
	bd.updateFFT(); //beatDetect の更新
	
    //kinectRectDraw における矩形の大きさ
	if (step < 1) {
		step = 1;
	}
	
    //tweetの毎フレームごとの更新
	for (int i = 0; i < ofxBMath.size(); i++) {
		ofxBMath[i].update();
	}

    //tweetの音と同期した更新
	if (bd.isKick() || bd.isSnare() || bd.isHat()) {
		for (int i = 0; i < ofxBMath.size(); i++) {
			ofxBMath[i].update();
		}
	}
	
	if (stringShow) {
		alpha += 3;
	} else {
		alpha = 0;
	}

	kinectVJ.distanceUpdate(_distance);
	kinectVJ.getMoveReset();

    //サーチワードの位置の計算
	ofRectangle searchRect = font_title.getStringBoundingBox(wSearch, 0,0);
	searchX -= 3;
	searchY = ofGetHeight() / 2 + searchRect.height / 2;
	if (searchX < 0 - searchRect.width) {
		searchX = searchRect.width;
	}
    
    //tweet表示のチックをなくす
	kick_timer++;

    //グリッチ処理
	if (glitch_on) {
		//Jpeg圧縮したデータの保存ファイル名
		string compressedFilename = "Glitch.jpg";
		
		//イメージデータをJpeg圧縮して保存
		img.saveImage(compressedFilename, quality);
		
		ofBuffer file = ofBufferFromFile(compressedFilename);
		int fileSize = file.size();
		char * buffer = file.getBinaryBuffer();
		
		//データを破壊する場所をランダムに決定
		int whichByte = (int) ofRandom(fileSize);
		int whichBit = ofRandom(8);
		char bitMask = 1 << whichBit;
		buffer[whichByte] |= bitMask;
		
		//glitchしたファイルをまた再度読込み
		ofBufferToFile(compressedFilename, file);
		img.loadImage(compressedFilename);
	}

}

//--------------------------------------------------------------

void testApp::draw(){ //どろーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

    float bxRandom = ofRandom(0, ofGetWidth());
	float byRandom = ofRandom(0, ofGetHeight());
    
    //キック音を取得後、twitterインスタンスを一つ追加する
	if(bd.isKick() && kick_timer > 5){
		ofxB new_instance;
		new_instance.setup(bxRandom, byRandom);
		ofxBMath.push_back(new_instance);
		kick_timer = 0;
	}
    
    //影を残す処理
	if (shadow_show || bd.isKick() || bd.isSnare() || bd.isHat()) {
      ofFill();
    } else {
        //背景黒塗り
        ofSetColor(0, 0, 0);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    //謎の変数たち
	int hogehogecounter = 0;
    int count_delay = 0;
    
    //モーションレックの描画
    if (delay_move) kinectVJ.kinectDelayDraw();
    
    //kinectの実写映像の描画 現在は、kinectDelayDraw を描画するためにコメントアウト中
    //kinect.draw(0, 0, 640, 480);
    
    //kinectの円形のエフェクトの描画
    kinectVJ.kinectCircleDraw(color_sec, kinectCircle);

    //kinectの矩形のエフェクトの描画と変数をofxVJKinectクラスへ投げる
	for (int x=0; x < ofGetWidth(); x+=step) {
		for (int y=0; y < ofGetHeight(); y+=step) {
			hogehogecounter++;
			count_delay++;
			if (kinectShow) kinectVJ.kinectRectDraw(kinect.getDistanceAt(x,y), x, y, step, ofGetFrameNum() % 200, hogehogecounter, delay_rec);
		} 
	}

    //モーションレックのプログレスバー描画 //現在されてない
	if (delay_move) {
		ofSetColor(255, 0, 0, 100);	
	} else {
		ofSetColor(0, 0, 255, 100);
	}
	
	if (delay_rec) {
		ofSetColor(0, 255, 0, 100);
	}
	
	if (delay_move && delay_rec) {
		ofSetHexColor(0x9400D3);
	}
	float delay_frame = ofMap(ofGetFrameNum() % 200, 0, 200, 0, ofGetWidth());
	ofFill();

    //なにここ？
	for (int i=0; i < str_alpha.size(); i++) {
		str_alpha[i] -= 10;
		if (str_alpha[i] < 0) {
			str_alpha[i] = 255;
		}
	}
	
    //twitter timeline の描画
	for (int i=0; i < ofxBMath.size(); i++) {
		ofPushMatrix();
        
		ofTranslate(ofxBMath[i].x, ofxBMath[i].y, ofxBMath[i].z);
        ofRotateZ(ofxBMath[i].angle);
		float hogeAngle = ofMap(ofGetFrameNum() % 360, 0, 10, 0, 180);
		if (stringShow) {
            stringDrawPoetry(i);
		}
		ofPopMatrix();
	}
    
    //ランダムな走査線の描画
	for (int i=0; i < 4; i++) {
		float hogeY = ofRandom(0, ofGetHeight());
		ofLine(0, hogeY, ofGetWidth(), hogeY);
	}
	
    //サーチワードの描画
    if (strline.size() != 0) {
        ofSetColor(255,255,255, 150);
        if (showSearch) {
            font_title.drawString(wSearch, searchX, searchY);
        }
    }

    //デバッグページの描画
	if (debugOn) {
		debug_page();
	}
	
    //グリッチの描画
	if (glitch_on) {
		ofSetColor(255);
		img.draw(0, 0, ofGetWidth(), ofGetHeight());
	}   
}

void testApp::stringDrawPoetry(int num) {
    
	if (num + 1 < strline.size()) {
		ofRectangle rect = font_mid.getStringBoundingBox(strline[num], 0,0);
		ofSetColor(ofxBMath[num].r, ofxBMath[num].g, ofxBMath[num].b, alpha);
		font_mid.drawString(strline[num], -rect.width / 2, -rect.height / 2);
	}
    
    if (ofxBMath.size() > strline.size() || strline.size() > 30) {
		bNumReset();
		strline.clear();
        bNumReset();
        setlocale( LC_ALL, "ja_JP.UTF-8" );
        FILE * fp;
        if((fp=fopen("/Users/Yuki/work/ofxHuez/search_result.txt","r"))==NULL){
            cout << "no" << endl;
        }else{
            char buff[256]="";
            while(fgets(buff,256,fp)!=NULL){
                strline.push_back(stringConvertToW(buff));
            }
            fclose(fp);
        }
	}
	
}


void testApp::debug_page() {
	ofSetColor(255, 255, 255, 100);
	ofRect(5, 5, 230, 400);
	
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("dot mesh +( + )", 10, 15);
	ofDrawBitmapString("dot mesh -( - )", 10, 30);
	ofDrawBitmapString("load Petry( c )", 10, 45);
	ofDrawBitmapString("kinect angle up(up)", 10, 60);
	ofDrawBitmapString("kinect angle down(down)", 10, 75);
	ofDrawBitmapString("kinect distance + ( q )", 10, 90);
	ofDrawBitmapString("kinect distance - ( w )", 10, 105);
	
	if (kinectCircle) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetColor(0, 0, 255);
	}
	ofDrawBitmapString("kinectCircle( s )", 10, 135);
	
	if (kinectShow) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetColor(0, 0, 255);
	}
	ofDrawBitmapString("kinectShow( u )", 10, 150);
	
	if (stringShow) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetColor(0, 0, 255);
	}
	ofDrawBitmapString("stringShow( i )", 10, 165);
	
	if (stringWhite) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetColor(0, 0, 255);
	}
	ofDrawBitmapString("string color change( a )", 10, 180);
	
	if (showSearch) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetColor(0, 0, 255);
	}
	ofDrawBitmapString("twitter search word( e )", 10, 195);
	if (yabai_node_bool) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetColor(0, 0, 255);
	}
	ofDrawBitmapString("yabai_node_bool ( y )", 10, 210);
}






//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) {
        case '*':
            if (disp_front) {
				disp_front = false;
			} else {
				disp_front = true;
			}
            break;
        case '@':
            if (mouse_bool) {
				mouse_bool = false;
			} else {
				mouse_bool = true;
			}
            break;
		case '-':
            if(step < 2) step = 3;
			step--;
			break;
			
		case '+':
			step++;
			break;
			
		case 's':
			if (kinectCircle) {
				
				kinectCircle = false;
			} else {
				
				kinectCircle = true;
			}
			break;

		case 'u':
			if (kinectShow) {
				kinectShow = false;
			} else {
				kinectShow = true;
			}
			break;
		case 'i':
			if (stringShow) {
				stringShow = false;
			} else {
				stringShow = true;
			}
			break;
		case 'q':
			_distance += 20;
			break;
		case 'w':
			_distance -= 20;
			break;
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
		case 'e':
			if (showSearch) {
				showSearch = false;
			} else {
				showSearch = true;
			}
			break;
		case '6':
			shadow_show = true;
			break;
		case 'p':
			if (debugOn) {
				debugOn = false;
			} else {
				debugOn = true;
			}
			break;
		case 'g':
            kinectVJ.delayReset();
			break;
		case ' ':
            if (glitch_on) {
				glitch_on = false;
			} else {
				glitch_on = true;
			}
			preGlitch.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
			preGlitch.saveImage("preGlitch.jpg");
			reset();
			break;
		case 'd':
			if (delay_move) {
				delay_move = false;
			} else {
				delay_move = true;
				
			}
			break;
			
		case '0':
            if(delay_rec == false) preStep = step;
            step = 6;
			delay_rec = true;
			break;

		default:
			break;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){	
	switch (key) {
		case '6':
			shadow_show = false;
			break;
		case '0':
            step = preStep;
			delay_rec = false;
			break;
        case OF_KEY_RETURN:
            stop = false;
		default:
			break;
	}

}
void testApp::bNumReset() {
	ofxBMath.clear();
}

void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
}

void testApp::audioReceived(float* input, int bufferSize, int nChannels) {
    bd.audioReceived(input, bufferSize);
    audioInput = input[0];
}





//************************************************************************************

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
}
