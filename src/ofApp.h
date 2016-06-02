#pragma once

#include "ofMain.h"
#include <string>
#include "LoadData.hpp" //ink
#include "Ink.hpp" //ink
#include "GetAttackPoint.hpp" //arduino
#include "AnimalHandler.hpp" //animal

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
    AnimalHandler animal;
    void pushInk(ofPoint p, float size);
    ofFbo fbo;
    
    enum COLOR{
        CYAN = 0,
        MAGENTA,
        YELLOW,
        RED,
        GREEN,
        BLUE,
        BLACK
    };
    const ofColor color_list[7] = {
        ofColor(255, 0, 0), //cyan
        ofColor(0, 255, 0), //magenta
        ofColor(0, 0, 255), //yellow
        ofColor(255, 255, 0), //blue
        ofColor(0, 255, 255), //red
        ofColor(255, 0, 255), //green
        ofColor(255, 255, 255) //black
    };
    
};
