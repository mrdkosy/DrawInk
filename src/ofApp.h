#pragma once

#include "ofMain.h"
#include <string>
#include "LoadData.hpp" //ink
#include "Ink.hpp" //ink
#include "GetAttackPoint.hpp" //arduino
#include "AnimalHandler.hpp" //animal
#include "Judge.hpp" //attack judges
#include "Rain.hpp"

#include "CameraColor.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    LoadData data;
    Ink ink;
    GetAttackPoint getAttackPoint;
    static const int AnimalNum = 3;
    AnimalHandler animal[AnimalNum];
    void pushInk(ofPoint p, float size);
    void Clear();
    Judge judge;
    ofFbo fbo;
    ofShader shader;
    ofVec2f vertex;
    ofSoundPlayer pushSound[2], rainSound, animalSound[2];
    COLOR_LIST color_list;
    int animalCount, rotate;
    bool isClear, preClear;
    float volume;
    Rain rain;
    
	CameraColor camCol;
	
	// cameraの解像度
#define CAMERA_WIDTH	(320)
#define CAMERA_HEIGHT	(240)

};
