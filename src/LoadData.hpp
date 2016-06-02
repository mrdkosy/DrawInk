
#ifndef LoadData_hpp
#define LoadData_hpp

#include <stdio.h>
class LoadData{
public:
    void loadData(){
        
        string text = string(ofBufferFromFile("path/ink.txt"));
        vector<string>path = ofSplitString(text, ",");
        
        int rough = 45;
        for(int i=0; i<path.size()/2/rough; i++){
            ofPoint p;
            p.set(ofToInt(path[rough*2*i]), ofToInt(path[rough*2*i+1]));
            ink.push_back(p);
        }

        string text2 = string(ofBufferFromFile("path/ink2.txt"));
        vector<string>path2 = ofSplitString(text2, ",");
        
        rough = 15;
        for(int i=0; i<path2.size()/2/rough; i++){
            ofPoint p;
            p.set(ofToInt(path2[rough*2*i]), ofToInt(path2[rough*2*i+1]));
            splash.push_back(p);
        }

    };
    vector<ofPoint> getInkData(){
        return ink;
    };
    vector<ofPoint> getSplashData(){
        return splash;
    };
private:
    vector<ofPoint> ink;
    vector<ofPoint> splash;
};
#endif /* LoadData_hpp */
