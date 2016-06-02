#ifndef Splash_hpp
#define Splash_hpp

#include <stdio.h>
#include "ofMain.h"
class Splash{
public:
    Splash(vector<ofPoint> _splashverts){
        splash = _splashverts;
    }
    void setup(){
        rotate = ofRandom(360);
        radius = ofRandom(150, 200);
        position = ofPoint(radius*cos(ofDegToRad(rotate)),
                           radius*sin(ofDegToRad(rotate)),
                           0);
        scale = ofVec2f(ofRandom(.1, 1.2), ofRandom(.5, 4.));
        late = ofRandom(2, 4);
        nowPosition.clear();
        for(int i=0; i<splash.getVertices().size(); i++){
            nowPosition.push_back(ofPoint(0, 0, 0));
        }
    }
    void draw(){
        //update
        for(int i=0; i<splash.getVertices().size(); i++){
            nowPosition[i] += (splash.getVertices()[i]-nowPosition[i])/late;
        }
        
        //draw
        ofPushMatrix();
        
        ofTranslate(position);
        ofRotateZ(rotate+100);
        ofScale(scale.x, scale.y);
        ofBeginShape();
        for(int i=0; i<splash.getVertices().size(); i++){
            //            ofCurveVertex(splash.getVertices()[i]);
            ofCurveVertex(nowPosition[i]);
        }
        ofEndShape();
        
        ofPopMatrix();
    };
private:
    ofPoint position;
    int rotate;
    float size, late, radius;
    ofVec2f scale;
    ofPolyline splash;
    vector<ofPoint> nowPosition;
    
};
#endif /* Splash_hpp */
