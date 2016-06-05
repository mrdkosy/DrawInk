#ifndef AnimalHandler_hpp
#define AnimalHandler_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AnimalMotionController.hpp"
#include "AttackEffect.hpp"


class AnimalHandler{
public:
    
    void setup(ofTexture* texture, LoadAnimalData::TYPE type){
        //get color
        ofPixels pixels;
        texture->readToPixels(pixels);
        int count = 0;
        randomColor = false;
        isDraw = true;
        
        ofPoint p = ofPoint(ofRandom(100, ofGetWidth()-100), ofRandom(100, ofGetHeight()-100));
        ofColor c = pixels.getColor(p.x, p.y);
        
        if(type == LoadAnimalData::SUPERARE){ //super rare
            animal.setup(type, p, ofColor());
            
        }else if(type == LoadAnimalData::NORMAL){ //normal
            while( 1 ){
                color = c;
                if(c == color_list.color[3] ||
                   c == color_list.color[4] ||
                   c == color_list.color[5]){
                    color = c;
                    animal.setup(type, p, c);
                    break;
                }else if(count > 30){
                    isDraw = false;
                    break;
                }
                count++;
            }
        }else{
            while( 1 ){ //rare
                color = c;
                if(c == color_list.color[0] ||
                   c == color_list.color[1] ||
                   c == color_list.color[2]){
                    randomColor = true;
                    animal.setup(type, p, c);
                    break;
                }else if(count > 30){
                    isDraw = false;
                    break;
                }
                count++;
            }
        }
        preDraw = isDraw;
    }
    void draw(){
        update();
        
        ofPushStyle();
        if(randomColor){
            ofSetColor(ofColor::fromHsb(ofRandom(255),
                                        120, 255));
        }else{
            //ofSetColor(color, 255);
            ofSetColor(255, 255);
        }
        
        
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
    bool getIsDraw(){
        return isDraw;
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
    bool isDraw, preDraw, randomColor;
    COLOR_LIST color_list;
};

#endif /* AnimalHandler_hpp */
