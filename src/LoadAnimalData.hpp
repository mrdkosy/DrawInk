#ifndef LoadAnimalData_hpp
#define LoadAnimalData_hpp

#include <stdio.h>
#include "ofMain.h"

class LoadAnimalData{
public:
    enum ANIMAL{
        TENTOMUSHI=0,
        BIRD=1
    };
    enum TYPE{
        NORMAL=0,
        RARE
    };
    LoadAnimalData(){
        //normal
        ofImage img;
        vector<ofImage> _img;
        //------tentomushi------
        img.load("animal/normal/tentomushi1.png");
        _img.push_back(img);
        img.load("animal/normal/tentomushi2.png");
        _img.push_back(img);
        image.push_back(_img);
        //------bird------
        _img.clear();
        img.load("animal/normal/bird3.png");
        _img.push_back(img);
        image.push_back(_img);
        //rare
        
    }
    vector<ofImage>* getImage(ANIMAL _animal){
        return &image[_animal];
    }
    int getImageNum(ANIMAL _animal){
        return image[_animal].size();
    }
    ofVec2f getAnimalNum(){
        return ofVec2f(2, 0); //normal and rare animal image num
    }
    ANIMAL getAnimal(int i){
        if(i==0) return TENTOMUSHI;
        else if(i==1) return BIRD;
    }
private:
    vector<vector<ofImage>> image;
};

#endif /* LoadAnimalData_hpp */
