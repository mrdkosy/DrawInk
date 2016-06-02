#ifndef AnimalHandler_hpp
#define AnimalHandler_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AnimalMotionController.hpp"

class AnimalHandler{
public:
    void setup(){
        screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        ofPixels pixels = screen.getPixels();
        int count = 0;
        while( 1 ){
            ofPoint p = ofPoint(ofRandomWidth(), ofRandomHeight());
            ofColor c = pixels.getColor(p.x, p.y);
            if( c != ofGetBackgroundColor() ){
                color = c;
                isDraw = true;
                
                //-------------must change--------------
                animal.setup(LoadAnimalData::TYPE::NORMAL, p);
                
                
                break;
            }else if(count > 30){
                isDraw = false;
                break;
            }
            count++;
        }
    }
    void draw(){
        ofPushStyle();
        
        ofSetColor(color);
        if(isDraw)animal.draw();
        
        ofPopStyle();
    }
private:
    AnimalMotionController animal;
    ofColor color;
    ofImage screen;
    bool isDraw;
};

#endif /* AnimalHandler_hpp */
