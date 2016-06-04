#ifndef AnimalHandler_hpp
#define AnimalHandler_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AnimalMotionController.hpp"
#include "AttackEffect.hpp"

class AnimalHandler{
public:
    void setup(ofTexture* texture){
        ofPixels pixels;
        texture->readToPixels(pixels);
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
            preDraw = isDraw;
        }
    }
    void draw(){
        update();
        
        ofPushStyle();
        
        ofSetColor(color, 255);
        if(isDraw) animal.draw();
        
        for(int i=0; i<effect.size(); i++){
            effect[i].draw();
        }
        
        ofPopStyle();
    }
    ofPoint getPosition(){
        return animal.getPosition();
    }
    void setDrawFalse(){
        isDraw = false;
    }
private:
    void update(){
        
        
        if( !isDraw && preDraw){ //ink attack to animal
            if(effect.size() > 10) effect.erase(effect.begin());
            AttackEffect e(animal.getPosition());
            effect.push_back(e);
        }
        
        ofPoint p = animal.getPosition();
        int range = 100;
        if(p.x < -range || p.x > ofGetWidth()+range ||
           p.y < -range || p.y > ofGetHeight()+range){
            isDraw = false; //not draw over screen
        }
        
        
        preDraw = isDraw;
        
    }
    AnimalMotionController animal;
    vector<AttackEffect> effect;
    ofColor color;
    bool isDraw, preDraw;
};

#endif /* AnimalHandler_hpp */
