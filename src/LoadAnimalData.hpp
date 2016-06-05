#ifndef LoadAnimalData_hpp
#define LoadAnimalData_hpp

#include <stdio.h>
#include "ofMain.h"

class LoadAnimalData{
public:
    enum ANIMAL{
        BIRD=0,
        TENTOMUSHI,
        BUTTERFLY,

        DRAGON,
        HUMAN,
        
        EGG
    };
    enum TYPE{
        NORMAL=0,
        RARE,
        SUPERARE
    };
    LoadAnimalData(){
        
        //normal
        ofImage img;
        vector<ofImage> _img;
        
        //------bird------
        _img.clear();
        img.load("animal/normal/bird.png");
        _img.push_back(img);
        img.load("animal/normal/bird2.png");
        _img.push_back(img);
        img.load("animal/normal/bird.png");
        _img.push_back(img);
        img.load("animal/normal/bird3.png");
        _img.push_back(img);
        image.push_back(_img);
        
        //------tentomushi------
        _img.clear();
        //        img.load("animal/normal/tento.png");
        //        _img.push_back(img);
        //        img.load("animal/normal/tento2.png");
        //        _img.push_back(img);
        img.load("animal/normal/tento3.png");
        _img.push_back(img);
        image.push_back(_img);
        
        
        //------butterfly------
        _img.clear();
        img.load("animal/normal/butterfly2.png");
        _img.push_back(img);
        img.load("animal/normal/butterfly.png");
        _img.push_back(img);
        img.load("animal/normal/butterfly3.png");
        _img.push_back(img);
        img.load("animal/normal/butterfly.png");
        _img.push_back(img);
        image.push_back(_img);
        
        
        //rare
        _img.clear();
        img.load("animal/rare/doragon2.png");
        _img.push_back(img);
        img.load("animal/rare/doragon2.png");
        _img.push_back(img);
        img.load("animal/rare/doragon3.png");
        _img.push_back(img);
        img.load("animal/rare/doragon3.png");
        _img.push_back(img);
        image.push_back(_img);
        
        //------human------
        _img.clear();
        img.load("animal/rare/human.png");
        _img.push_back(img);
        img.load("animal/rare/human2.png");
        _img.push_back(img);
        img.load("animal/rare/human3.png");
        _img.push_back(img);
        img.load("animal/rare/human2.png");
        _img.push_back(img);
        image.push_back(_img);
        
        
        //super rare
        _img.clear();
        img.load("animal/rare/egg.png");
        _img.push_back(img);
        img.load("animal/rare/egg.png");
        _img.push_back(img);
        img.load("animal/rare/egg2.png");
        _img.push_back(img);
        img.load("animal/rare/egg2.png");
        _img.push_back(img);
        img.load("animal/rare/egg.png");
        _img.push_back(img);
        img.load("animal/rare/egg.png");
        _img.push_back(img);
        img.load("animal/rare/egg3.png");
        _img.push_back(img);
        img.load("animal/rare/egg3.png");
        _img.push_back(img);

        image.push_back(_img);
        
        
        //sound
        rareSound.load("sound/sound04.mp3");
    }
    vector<ofImage>* getImage(){
        return &image[_ANIMAL];
    }
    int getImageNum(){
        return image[_ANIMAL].size();
    }
    ofVec3f getAnimalNum(){
        return v; //normal and rare animal image num
    }
    ANIMAL getAnimal(int type, int i){
        if(type == 0){
            if(i==0) return BIRD;
            else if(i==1) return TENTOMUSHI;
            else if(i==2) return BUTTERFLY;
        }else if(type == 1){
            rareSound.play();
            if(i==0) return DRAGON;
            else if(i==1) return HUMAN;
        }else if(type == 2){
            if(i == 0) return EGG;
        }
    }
    void setAnimal(ANIMAL a){
        _ANIMAL = a;
    }
    void setType(TYPE t){
        _TYPE = t;
    }
private:
    vector< vector<ofImage >> image;
    ANIMAL _ANIMAL;
    TYPE _TYPE;
    ofVec3f v = ofVec3f(3, 2, 1);
    ofSoundPlayer rareSound;
};

#endif /* LoadAnimalData_hpp */
