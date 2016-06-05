//
//  CameraColor.cpp
//  DrawInk
//
//  Created by 松田 勇磨 on 2016/06/02.
//
//

#include "CameraColor.hpp"

#define PERSE_FILENAME "perse.txt"
#define PERSE_POINT_SIZE (6)
#define BALL_SIZE (16)

//--------------------------------------------------------------
void CameraColor::setup(int width, int height) {
	cameraWidth = width;
	cameraHeight = height;
	
	cameraScreen_pt = new ofPoint[4];
	cameraScreen_pt[0] = ofPoint(0, 0);
	cameraScreen_pt[1] = ofPoint(cameraWidth, 0);
	cameraScreen_pt[2] = ofPoint(cameraWidth, cameraHeight);
	cameraScreen_pt[3] = ofPoint(0, cameraHeight);

	colorRect = ofRectangle(0,0, BALL_SIZE, BALL_SIZE);
	colorPoint = ofPoint(0,0);
	
	loadPersePoint();
	
	//we can now get back a list of devices.
	vector<ofVideoDevice> devices = grabber.listDevices();
	
	for(int i = 0; i < devices.size(); i++){
		if(devices[i].bAvailable){
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}else{
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}
	
	grabber.setDeviceID(0);
	grabber.setDesiredFrameRate(60);
	grabber.initGrabber(cameraWidth, cameraHeight);
	
	persePixels.allocate(cameraWidth, cameraHeight, OF_PIXELS_RGB);
	//videoTexture.allocate(persePixels);
	perseImage.allocate(cameraWidth, cameraHeight);
	
	debugMode = false;
	
}

//--------------------------------------------------------------
void CameraColor::update() {
	grabber.update();
	
	if(grabber.isFrameNew()){
		// コピー
		perseImage.setFromPixels(grabber.getPixelsRef(), cameraWidth, cameraHeight);
		// TODO: ホモグラフィ変換でまっすぐな画像にする
		perseImage.warpPerspective(cameraScreen_pt[0], cameraScreen_pt[1], cameraScreen_pt[2], cameraScreen_pt[3]);
		
		// 補正後の画像ピクセル取得
		persePixels = perseImage.getPixels();
		
		// 要る？
//		videoTexture.loadData(videoPixels);
	}

}

//--------------------------------------------------------------
void CameraColor::draw() {

	if(!debugMode) return;
	
	// Debug表示
	grabber.draw(0, 0, cameraWidth, cameraHeight);
	ofSetColor(255, 0, 0);
	for(int i = 0; i < 4; i++) {
		int j = (i+1) % 4;
		ofDrawLine(cameraScreen_pt[i].x, cameraScreen_pt[i].y, cameraScreen_pt[j].x, cameraScreen_pt[j].y);
		ofDrawCircle(cameraScreen_pt[i], PERSE_POINT_SIZE);
	}
	
	// 補正後の画像
	ofSetColor(255);
	perseImage.draw(0 + cameraWidth, 0);
	
	// 取得範囲
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofDrawRectangle(colorRect.getLeft() + cameraWidth, colorRect.getTop(), colorRect.width, colorRect.height);
	
	// 色の平均
	ofSetColor(avgColor);
	ofFill();
	ofDrawRectangle(cameraWidth + cameraWidth, 0, 16, 16);
	
	// 選択した色
	ofSetColor(resultColor);
	ofDrawRectangle(cameraWidth + cameraWidth + 16, 0, 16, 16);
	
}

//--------------------------------------------------------------
// 指定座標周辺の色取得
// x,y : 座標
// color : 戻り値の色
// return : 色の取得の成否
bool CameraColor::tryGetColor(int x, int y, ofColor& color) {
	
	// 範囲外
	if ((x < 0)||(x > cameraWidth)||(y < 0)||(y > cameraHeight)) {
		return false;
	}
	
	int rgbTotal[] = {0, 0, 0};
	int left = x - BALL_SIZE / 2;
	int right = x + BALL_SIZE / 2;
	int top = y - BALL_SIZE / 2;
	int bottom = y + BALL_SIZE / 2;
	if (left < 0) left = 0;
	if (right > cameraWidth) right = cameraWidth;
	if (top < 0) top = 0;
	if (bottom > cameraHeight) bottom = cameraHeight;

	colorRect = ofRectangle(left,top, right - left, bottom - top);
	colorPoint = ofPoint(x, y);
	
	colorPoint = ofPoint(0,0);
#ifdef CAMERA_DEBUG
	printf("X %d Y %d L %d R %d T %d B %d\n", x, y, left, right, top, bottom);
#endif
	
	int totalLoop = 0;
	for (int xx = left; xx < right; xx++){
		for (int yy = top; yy < bottom; yy++){
			ofColor col = persePixels.getColor(xx, yy);
			rgbTotal[0] += col.r;
			rgbTotal[1] += col.g;
			rgbTotal[2] += col.b;
			totalLoop++;
		}
	}
	
	// 色の平均
	if(totalLoop > 0 ) {
		rgbTotal[0] = rgbTotal[0] / totalLoop;
		rgbTotal[1] = rgbTotal[1] / totalLoop;
		rgbTotal[2] = rgbTotal[2] / totalLoop;
	}
	avgColor = ofColor(rgbTotal[0], rgbTotal[1], rgbTotal[2]);
	
	// 原色判定
	bool isHit = false;
	if((rgbTotal[0] > rgbTotal[1])&&(rgbTotal[0] > rgbTotal[2])) {
		// 赤が最も多い
		isHit = true;
		resultColor = ofColor(255, 0, 0);
	}else if((rgbTotal[2] > rgbTotal[0])&&(rgbTotal[2] > rgbTotal[1])) {
		// 青が最も多い
		isHit = true;
		resultColor = ofColor(0, 0, 255);
	}else if((rgbTotal[0] > rgbTotal[2])&&(rgbTotal[1] > rgbTotal[2])) {
		// 赤と緑が青より多い場合は黄色にする
		isHit = true;
		resultColor = ofColor(255, 255, 0);
	}
	if(isHit){
		color = resultColor;
	}
	
#ifdef CAMERA_DEBUG
	printf("tryGetColor XY(%d, %d) Avg(%x:%x:%x) Result(%x:%x:%x) isHit %s\n", x, y, avgColor.r, avgColor.g,avgColor.b, resultColor.r, resultColor.g, resultColor.b, (isHit ? "TRUE" : "FALSE"));
#endif	// CAMERA_DEBUG
	
	return isHit;
}

//--------------------------------------------------------------
bool CameraColor::loadPersePoint() {
	// 四隅座標読み込み
	ofBuffer buf = ofBufferFromFile( PERSE_FILENAME );
	if(buf.size() == 0) {
		// 読み込めないので新規作成
		cameraScreen_pt[0] = ofPoint(0, 0);
		cameraScreen_pt[1] = ofPoint(cameraWidth, 0);
		cameraScreen_pt[2] = ofPoint(cameraWidth, cameraHeight);
		cameraScreen_pt[3] = ofPoint(0, cameraHeight);
		savePersePoint();
		return true;
	}
	
	string str = string( buf );
	vector<string>str_points = ofSplitString(str, ",");
	for(int i = 0; i < 4; i++) {
		cameraScreen_pt[i] = ofPoint(ofToInt(str_points[i*2]), ofToInt(str_points[i*2+1]));
		printf("[%d] x: %f y: %f\n", i, cameraScreen_pt[i].x, cameraScreen_pt[i].y);
	}
	
	return true;

}

//--------------------------------------------------------------
bool CameraColor::savePersePoint() {
	// 四隅座標保存
	string str = "";
	
	int size = 4;
	for(int i = 0; i < size; i++) {
		str += ofToString(cameraScreen_pt[i].x) + "," + ofToString(cameraScreen_pt[i].y);
		if((i+1) < size) str += ",";
	}
	printf("size %d data %s\n", size, str.c_str());
	
	ofBuffer buffer = ofBuffer( str );
	ofBufferToFile( PERSE_FILENAME, buffer );
}

//--------------------------------------------------------------
void CameraColor::startScreenAdjust(int x, int y) {
	if(!debugMode) return;
	
	float rr = PERSE_POINT_SIZE * PERSE_POINT_SIZE;
	adjustIndex = -1;
	for(int i = 0; i < 4; i++) {
		float xx = cameraScreen_pt[i].x - x;
		float yy = cameraScreen_pt[i].y - y;
		float len = xx * xx + yy * yy;
		if(len <= rr) {
			adjustIndex = i;
			break;
		}
	}
	
	if(adjustIndex < 0) {
		adjustMode = false;
		return;
	}
	
	adjustMode = true;
}
//--------------------------------------------------------------
void CameraColor::setScreenAdjust(int x, int y){
	if(!debugMode) return;
	
	if(!adjustMode) return;
	
	cameraScreen_pt[adjustIndex].x = x;
	cameraScreen_pt[adjustIndex].y = y;
}
//--------------------------------------------------------------
void CameraColor::endScreenAdjust(int x, int y){
	if(!debugMode) return;
	
	if(!adjustMode) return;

	cameraScreen_pt[adjustIndex].x = x;
	cameraScreen_pt[adjustIndex].y = y;
	adjustMode = false;
	
	savePersePoint();
}

