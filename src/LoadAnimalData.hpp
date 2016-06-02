#ifndef LoadAnimalData_hpp
#define LoadAnimalData_hpp

#include <stdio.h>
#include "ofMain.h"

class LoadAnimalData{
public:
    enum ANIMAL{
        BIRD=0,
        TENTOMUSHI
    };
    enum TYPE{
        NORMAL=0,
        RARE
    };
    LoadAnimalData(){
        //normal
        image[BIRD].load("animal/normal/bird.png");
        image[TENTOMUSHI].load("animal/normal/tento.png");
        //rare
        
    }
    ofImage & getImage(int _animal){
        return image[_animal];
    }
    ofVec2f getAnimalNum(){
        return ofVec2f(2, 0); //normal and rare animal image num
    }
private:
    ofImage image[2];
};

#endif /* LoadAnimalData_hpp */
