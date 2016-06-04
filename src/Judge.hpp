#ifndef Judge_hpp
#define Judge_hpp

#include <stdio.h>
#include "ofMain.h"

class Judge{
public:
    bool InkAttackJudge(ofPoint inkPos, float inkScale, ofPoint animalPos){
        float dist = ofDist(inkPos.x, inkPos.y,
                            animalPos.x, animalPos.y);
        if(dist < 130*inkScale){
            return true;
        }
        return false;
    }
    
};

#endif /* Judge_hpp */
