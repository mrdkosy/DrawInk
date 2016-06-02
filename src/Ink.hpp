
#ifndef Ink_hpp
#define Ink_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Splash.hpp"

class Ink{
public:
    void dataSet(vector<ofPoint> _inkverts, vector<ofPoint> _splashverts){
        ink.addVertices(_inkverts);
        
        //splash setup
        for(int i=0; i<SplashNum; i++){
            Splash s(_splashverts);
            splash.push_back(s);
        }
    }
    
    void setup(ofPoint _position, ofColor _color, float _size){
        
        position = _position;
        color = _color;
        size = _size;
        rotate = ofRandom(360);
        dist = -1;
        nowPosition.clear();
        for(int i=0; i<ink.getVertices().size(); i++){
            nowPosition.push_back(ofPoint(0, 0, 0));
        }
        for(int i=0; i<SplashNum; i++){
            splash[i].setup();
        }
    };
    
    void draw(){
        //update
        for(int i=0; i<ink.getVertices().size(); i++){
            nowPosition[i] += (ink.getVertices()[i]-nowPosition[i])/late;
            if(i==0) dist = ofDist(nowPosition[i].x, nowPosition[i].y, ink.getVertices()[i].x, ink.getVertices()[i].y);
        }
        
        
        //draw
        ofPushMatrix();
        ofPushStyle();
        
        ofTranslate(position);
        ofRotateZ(rotate);
        ofScale(size, size);
        ofSetColor(color);
        
        ofBeginShape();
        for(int i=0; i<ink.getVertices().size(); i++){
            ofCurveVertex(nowPosition[i]);
        }
        ofEndShape();
        
        //splash
        for(int i=0; i<splash.size(); i++){
            splash[i].draw();
        }
        
        ofPopStyle();
        ofPopMatrix();
    };
    
    bool isDrawEnd(){
        if(dist != 0)return false;
        else return true;
    };
    
private:
    ofPolyline ink;
    ofPoint position;
    ofColor color;
    int rotate;
    float size;
    vector<ofPoint> nowPosition;
    constexpr static float late = 2;
    const int SplashNum = 7;
    vector<Splash> splash;
    float dist;
    
};

#endif /* Ink_hpp */
