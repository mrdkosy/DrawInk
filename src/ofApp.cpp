#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
    //    ofSetBackgroundAuto(false);
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(255);
    fbo.end();
    
    data.loadData();
    ink.dataSet(data.getInkData(),data.getSplashData());
    animal.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if( getAttackPoint.isAttack() ){
        pushInk(getAttackPoint.getPosition(),
                getAttackPoint.getPower());
    }
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    ofBackground(255);
    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    if( !ink.isDrawEnd() ) ink.draw();
    ofDisableBlendMode();
    fbo.end();
    fbo.draw(0, 0);
    
    ofSetColor(255);
    animal.draw();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'i'){
        pushInk(ofPoint(ofRandomWidth(), ofRandomHeight(), 0),
                ofRandom(30, 150));
    }
    if(key == 'c'){ //clear
        ofClear(ofGetBackgroundColor());
    }
    
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pushInk(ofPoint(x,y,0),
            ofRandom(30, 150));
    
    animal.setup();
}
//--------------------------------------------------------------
void ofApp::pushInk(ofPoint p, float size){ //draw ink
    
    int n = ofRandom(3); //cyan, magenta , yellow
    ofColor c = color_list[n];
    ink.setup(p, //position
              c, //color
              size/100);//size
    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}