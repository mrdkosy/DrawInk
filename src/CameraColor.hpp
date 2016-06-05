//
//  CameraColor.hpp
//  DrawInk
//
//  Created by 松田 勇磨 on 2016/06/02.
//
//

#ifndef CameraColor_hpp
#define CameraColor_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"

#define CAMERA_DEBUG	// デバッグ機能

class CameraColor{
public:
	void setup(int width, int height);
	
	void update();
	void draw();
	
	bool tryGetColor(int x, int y, ofColor& color);
	
	void startScreenAdjust(int x, int y);
	void setScreenAdjust(int x, int y);
	void endScreenAdjust(int x, int y);
	
	void changeDebugMode() { debugMode ^= true; }
	
private:
	int cameraWidth;
	int cameraHeight;
	
	ofVideoGrabber grabber;
	ofPixels persePixels;
	ofTexture videoTexture;
	ofxCvColorImage perseImage;
	ofPoint *cameraScreen_pt;
	
	// Debug用
	ofColor avgColor;		// 色の平均値
	ofColor resultColor;	// 判定結果の色
	ofPoint colorPoint;		// 色取得位置
	ofRectangle colorRect;	// 色取得範囲
	
	bool debugMode;
	
	bool adjustMode; // スクリーン補正座標調整モード
	int adjustIndex;
//	ofPoint adjustPoint;
	
	bool loadPersePoint();
	bool savePersePoint();
};;

#endif /* CameraColor_hpp */
