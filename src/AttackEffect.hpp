#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>
#include "ofMain.h"

class AttackEffect{
public:
    AttackEffect(ofPoint p){
        CASE = 0;
        
        if(CASE == 0){
            NUM = ofRandom(25, 35);
            for(int i=0; i<NUM; i++){
                position.push_back(p);
                velocity.push_back(ofPoint(0, 0, 0));
                acceleration.push_back(ofPoint(ofRandom(-10, 10),
                                               ofRandom(-18, 0),0));
                resolution.push_back(ofRandom(3, 6));
                radius.push_back(ofRandom(1, 12));
            }
            friction = 0.01;
            
        }else{
            NUM = 14;
            alpha = 1;
            length = 100;
            nowLength = 0;
            resolution.push_back(ofRandom(3, 6));
            radius.push_back(12);
            position.push_back(p);
        }
        
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        if(CASE == 0){
            //update
            for(int i=0; i<NUM; i++){
                
                acceleration[i] += ofPoint(0, 1, 0);
                
                acceleration[i] -= velocity[i] * friction;
                velocity[i] += acceleration[i];
                position[i] += velocity[i];
                acceleration[i].set(0, 0, 0);
            }
            //draw
            for(int i=0; i<NUM;i++){
                ofSetColor(ofColor::fromHsb(ofRandom(255), ofRandom(100, 150), 255));
                ofSetCircleResolution(resolution[i]);
                ofSetLineWidth(2.5);
                if(i%2 == 0) ofNoFill();
                else ofFill();
                ofDrawCircle(position[i], radius[i]);
            }
        }else{
            //update
            nowLength += (length - nowLength)/4.5;
            alpha = pow( (length - nowLength)/length, .15);
            if(alpha < 0.25) alpha = 0;
            
            //draw
            ofTranslate(position[0].x, position[0].y);
            ofSetLineWidth(3);
            ofFill();
            for(int i=0; i<NUM; i++){
                ofPushMatrix();
                float theta = TWO_PI/NUM * i;
                ofTranslate(nowLength*cos(theta), nowLength*sin(theta));
                ofRotateZ(ofRadToDeg(theta+30));
                ofSetColor(ofColor::fromHsb(ofRandom(255), 125, 255), 255*alpha);
                
                ofSetCircleResolution(resolution[0]);
                ofDrawCircle(0, 0, radius[0]);
                
                ofTranslate(nowLength*.35*cos(0), nowLength*.35*sin(0));
                
                ofSetCircleResolution(60);
                ofDrawCircle(0, 0, radius[0]*0.35);
                
                ofPopMatrix();
            }
        }
        ofPopMatrix();
        ofPopStyle();
    }
private:
    int NUM;
    vector<ofPoint> position, velocity, acceleration;
    vector<int> resolution;
    vector<float> radius;
    vector<ofColor> color;
    float friction, alpha, length, nowLength;
    int CASE;
};

#endif /* Effect_hpp */
