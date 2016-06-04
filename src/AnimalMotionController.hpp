#ifndef AnimalMotionController_hpp
#define AnimalMotionController_hpp

#include <stdio.h>
#include "ofMain.h"
#include "LoadAnimalData.hpp"

class AnimalMotionController{
public:
    void setup(LoadAnimalData::TYPE type, ofPoint p){ //set position, image
        ofVec2f animalNum = loadData.getAnimalNum();
        if(type == LoadAnimalData::TYPE::NORMAL){
            _ANIMAL = loadData.getAnimal( (int)ofRandom(animalNum.x) );
        }else{
            _ANIMAL = loadData.getAnimal( (int)ofRandom(animalNum.y) );
        }
        
        //load image
        nowImage = 0;
        imageNum = loadData.getImageNum(_ANIMAL);
        animal = *loadData.getImage( _ANIMAL );
        
        position = p; //first position
        if(p.x < ofGetWidth()/2) direct = -1;
        else direct = 1;
        velocity = ofPoint( -1*direct*ofRandom(4,6), -1*ofRandom(1,2), 0 ); //first velocity
        size = ofRandom(.3, .4); //size
        nowSize = 0;
        rotate =  180;
        
        
        //motion
        a.setPosition(ofGetWidth()/2,ofGetHeight()/2,0);
        b.setParent(a);
        b.setPosition(0,ofRandom(250, 300),0);
        c.setParent(b);
        c.setPosition(position.x-a.getPosition().x,
                      position.y-a.getPosition().y-b.getPosition().y,
                      0);
        aEnergy = 1;
        bEnergy = 1;
        aEnergySmth = 1;
        bEnergySmth = 1;
        
        
    }
    
    void draw(){
        ofPushMatrix();
        
        float w = animal[nowImage].getWidth()*nowSize*direct;
        float h = animal[nowImage].getHeight()*nowSize;
        ofTranslate(position.x, position.y);
        
        
        update();
        
        animal[nowImage].draw(-w/2, -h/2, w, h);
        ofPopMatrix();
        
    }
    ofPoint getPosition(){
        return position;
    }
    
private:
    void update(){
        
        if(ofGetFrameNum()%10 == 0) nowImage = (nowImage+1)%imageNum;
        
        
        //size
        nowSize += (size-nowSize)/10;
        
        //motion
        switch (_ANIMAL) {
                /*------------------------------------*/
            case LoadAnimalData::BIRD:{
                position += velocity;
            }
                break;
                /*------------------------------------*/
            case LoadAnimalData::TENTOMUSHI:{
                float r = 0.97;
                aEnergySmth = r * aEnergySmth + (1-r) *aEnergy;
                bEnergySmth = r * bEnergySmth + (1-r) *bEnergy;
                
                float s = .05;
                a.roll(aEnergySmth*s);
                b.roll(bEnergySmth*s);
                
                if ( ofRandom(0,1) > 0.95 ){
                    aEnergy = 0.4 * ofRandom(4, 8) * (ofRandom(0,1) > 0.5 ? 1 : -1);
                }
                
                if (ofRandom(0,1) > 0.95){
                    bEnergy = ofRandom(4,8) * (ofRandom(0,1) > 0.5 ? 1 : -1);
                }
                
                if(ofGetFrameNum()%30 == 0){
                    float t = atan2(position.y-prePos.y, position.x-prePos.x);
                    rotate += t;
                }
                ofRotateZ(ofRadToDeg(rotate));
                
                
                prePos = position;
                position = c.getGlobalPosition();
            }
                break;
                
                /*------------------------------------*/
            default:{
                position += velocity;
            }
        }
        
        
    }
    LoadAnimalData loadData;
    vector<ofImage> animal;
    ofPoint position, velocity, prePos;
    float size, nowSize;
    LoadAnimalData::ANIMAL _ANIMAL;
    ofNode a, b, c;
    float aEnergy, bEnergy, aEnergySmth, bEnergySmth, time, rotate;
    int imageNum, nowImage, direct;
};

#endif /* AnimalMotionController_hpp */
