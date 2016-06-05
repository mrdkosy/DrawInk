#ifndef AnimalMotionController_hpp
#define AnimalMotionController_hpp

#include <stdio.h>
#include "ofMain.h"
#include "LoadAnimalData.hpp"
class COLOR_LIST{
public:
    ofColor color[7] = {
        ofColor(255, 0, 0), //cyan
        ofColor(0, 255, 0), //magenta
        ofColor(0, 0, 255), //yellow
        ofColor(255, 255, 0), //blue
        ofColor(0, 255, 255), //red
        ofColor(255, 0, 255), //green
        ofColor(255, 255, 255) //black
    };
    
};

class AnimalMotionController{
public:
    void setup(LoadAnimalData::TYPE type, ofPoint p, ofColor color){ //set position, image
        ofVec3f animalNum = loadData.getAnimalNum();
        if(type == LoadAnimalData::TYPE::NORMAL){
            
            if(color == color_list.color[4]) _ANIMAL = LoadAnimalData::BIRD;
            else if(color == color_list.color[5]) _ANIMAL = LoadAnimalData::TENTOMUSHI;
            else if(color == color_list.color[3]) _ANIMAL = LoadAnimalData::BUTTERFLY;
            
            //_ANIMAL = loadData.getAnimal( 0, (int)ofRandom(animalNum.x) );
            loadData.setType(LoadAnimalData::TYPE::NORMAL);
            
        }else if(type == LoadAnimalData::TYPE::RARE){
            _ANIMAL = loadData.getAnimal( 1, (int)ofRandom(animalNum.y) );
            loadData.setType(LoadAnimalData::TYPE::RARE);
        }else{ //super rare
            _ANIMAL = loadData.getAnimal( 2, (int)ofRandom(animalNum.z) );
            loadData.setType(LoadAnimalData::TYPE::SUPERARE);
        }
        loadData.setAnimal(_ANIMAL);
        
        //load image
        nowImage = 0;
        imageNum = loadData.getImageNum();
        animal = *loadData.getImage();
        
        
        position = p; //first position
        if(p.x < ofGetWidth()/2) direct = -1;
        else direct = 1;
        velocity = ofPoint( -1*direct*ofRandom(2,6), -1*ofRandom(1,2), 0 ); //first velocity
        size = ofRandom(.1, .2); //size
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
            case LoadAnimalData::BUTTERFLY:
            case LoadAnimalData::EGG:{
                
                if(_ANIMAL == LoadAnimalData::EGG){
                    if(position.x > ofGetWidth()) position.x = 0;
                    else if(position.x < -100) position.x = ofGetWidth();
                    else if(position.y > ofGetHeight()) position.y = 0;
                    else if(position.y < -100) position.y = ofGetHeight();
                }
                
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
                
                prePos = position;
                position = c.getGlobalPosition();
            }
                break;
                /*------------------------------------*/
            case LoadAnimalData::DRAGON:{
                position.y += sin(ofDegToRad(ofGetFrameNum()));
            }
                break;
                /*------------------------------------*/
            case LoadAnimalData::HUMAN:{
                float x = sin(ofDegToRad(ofGetFrameNum()*5));
                position.x += x;
                x = x/.5*5;
                position.y += x;
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
    int imageNum, nowImage, direct, jump;
    COLOR_LIST color_list;
};

#endif /* AnimalMotionController_hpp */
