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
            
            animal = loadData.getImage( (int)ofRandom(animalNum.x) );
        }else{
            animal = loadData.getImage( (int)ofRandom(animalNum.y) );
        }
        position = p;
        size = ofRandom(.2, .5); //size
    }
    
    void draw(){
        
        update();
        animal.draw(position.x, position.y,
                    animal.getWidth()*size, animal.getHeight()*size);
        
    }
private:
    void update(){
    }
    LoadAnimalData loadData;
    ofImage animal;
    ofPoint position;
    float size;
    LoadAnimalData::ANIMAL _ANIMAL;
};

#endif /* AnimalMotionController_hpp */
