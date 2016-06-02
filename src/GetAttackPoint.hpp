#ifndef getAttackPoint_hpp
#define getAttackPoint_hpp

#include <stdio.h>
#include "ofMain.h"
#include <string>

class GetAttackPoint{
private:
    string getMsg, bytesReadString;
    ofSerial serial;
    ofPoint position;
    float power;
    
public:
    GetAttackPoint(){
        int baud = 9600;
        serial.setup(0, baud);
        getMsg = "";
        bytesReadString = "";
    }
    
    bool isAttack(){
        unsigned char bytesRead[1];
        memset(bytesRead, 0, 1);
        while( serial.readBytes( bytesRead, 1) > 0){
            if(bytesRead[0] == '\n'){
                getMsg = bytesReadString;
                bytesReadString = "";
                vector<string> split = ofSplitString(getMsg, ",");
                if(split.size() >= 3){
                    position = ofPoint(ofToFloat(split[0]), ofToFloat(split[1]), 0);
                    power = ofToFloat(split[2]);
                }
                return true;
            }else{
                bytesReadString += bytesRead[0];
            }
        }
        return false;
    }
    
    ofPoint getPosition(){
        return position;
    }
    float getPower(){
        return power;
    }
};

#endif /* getAttackPoint_hpp */
