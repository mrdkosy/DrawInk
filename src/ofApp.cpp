#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
    //    ofToggleFullscreen();
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo.begin();
    ofClear(255);
    fbo.end();
    
    data.loadData();
    ink.dataSet(data.getInkData(),data.getSplashData());
    
    shader.load("","shader.frag");
    vertex = ofVec2f(ofGetWidth(), ofGetHeight());
    
    //sound
    pushSound[0].load("sound/Motion-Pop02-1.mp3");
    pushSound[1].load("sound/Motion-Pop19-1.mp3");
    pushSound[2].load("sound/Motion-Pop23-1.mp3");
    attackSound.load("sound/ata_a26.mp3");
    
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
    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    if( !ink.isDrawEnd() ) ink.draw();
    ofDisableBlendMode();
    fbo.end();
    fbo.draw(0, 0);
    
    shader.begin();
    
    shader.setUniformTexture("tex", fbo.getTexture(), 1);
    ofColor c = ofColor::fromHsb(ofGetFrameNum()%255, 110, 200);
    ofVec3f v = ofVec3f(c.r, c.g, c.b);
    shader.setUniform3f("color", v/255);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex2d(0, 0);
    
    glTexCoord2d(vertex.x, 0);
    glVertex2d(vertex.x, 0);
    
    glTexCoord2d(0, vertex.y);
    glVertex2d(0, vertex.y);
    
    glTexCoord2d(vertex.x, vertex.y);
    glVertex2d(vertex.x, vertex.y);
    glEnd();
    
    shader.end();
    
    ofSetColor(255);
    for(int i=0; i<AnimalNum; i++){
        animal[i].draw();
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'i'){
        pushInk(ofPoint(ofRandomWidth(), ofRandomHeight(), 0),
                ofRandom(30, 150));
    }
    if(key == 'c'){ //clear
        fbo.begin();
        ofBackground(255, 255, 255);
        fbo.end();
        ofBackground(255);
    }
    if(key == 'a'){
        for(int i=0; i<AnimalNum; i++){
            animal[i].setup(&fbo.getTexture());
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pushInk(ofPoint(x,y,0),
            ofRandom(30, 150));
}
//--------------------------------------------------------------
void ofApp::pushInk(ofPoint p, float size){ //draw ink
    
    int s = ofRandom(3);
    pushSound[s].play();
    
    int n = ofRandom(3); //cyan, magenta , yellow
    ofColor c = color_list[n];
    size /= 100;
    ink.setup(p, //position
              c, //color
              size);//size
    
    for(int i=0; i<AnimalNum; i++){
        bool j = judge.InkAttackJudge(p, size,
                                      animal[i].getPosition());
        if(j == true){
            animal[i].setDrawFalse();
            attackSound.play();
        }
    }
    
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