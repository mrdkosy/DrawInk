#ifndef Rain_hpp
#define Rain_hpp

#include <stdio.h>
#include "ofMain.h"

class Rain{
public:
    Rain(){
        rain.load("rain.png");
    }
    void setup(){
        for(int i=0; i<NUM; i++){
            int x = ofRandomWidth();
            int y = -1*ofRandomHeight();
            position[i] = ofPoint(x, y, 0);
            velocity[i] = ofPoint(0, ofRandom(5, 10), 0);
            size[i] = ofRandom(0.01, 0.05);
        }
        alpha = 1;
        
    };
    void draw(){
        //update
        for(int i=0; i<NUM; i++){
            if(i == 0) latePos = position[i];
            if(position[i].y < latePos.y) latePos = position[i];
            position[i] += velocity[i];
        }
        alpha *= .95;
        
        
        //draw
        ofSetColor(255, 255-255*alpha);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        
        ofSetColor(255, 255);
        for(int i=0; i<NUM; i++){
            rain.draw(position[i].x, position[i].y,
                      rain.getWidth()*size[i], rain.getHeight()*size[i]);
        }
    };
    bool getEnd(){
        if(latePos.y > ofGetHeight()) return true;
        else return false;
    }
private:
    ofImage rain;
    static const int NUM = 100;
    ofPoint position[NUM], velocity[NUM], latePos;
    float size[NUM], alpha;
};
#endif /* Rain_hpp */
