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
    
    camCol.setup(CAMERA_WIDTH, CAMERA_HEIGHT);
    
    data.loadData();
    ink.dataSet(data.getInkData(),data.getSplashData());
    
    for(int i=0; i<AnimalNum; i++){
        animal[i].setup(&fbo.getTexture(), LoadAnimalData::TYPE::SUPERARE);
    }
    
    shader.load("","shader.frag");
    vertex = ofVec2f(ofGetWidth(), ofGetHeight());
    animalCount = 0;
    
    isClear = false;
    preClear = isClear;
    rotate = 0;
    
    //sound
    pushSound[0].load("sound/Motion-Pop02-1.mp3");
    pushSound[1].load("sound/Motion-Pop19-1.mp3");
    rainSound.load("sound/rain.mp3");
    animalSound[0].load("sound/bird10.mp3");
    animalSound[1].load("sound/nyu1.mp3");
    volume = 1.;
    
}
//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    camCol.update();
    
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
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    fbo.end();
    
    
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
    
    
    if(ofGetFrameNum()!=0 && ofGetFrameNum()%3600 == 0){ //1分に一回画面をclearに
        isClear = true;
        rain.setup();
        rainSound.stop();
        rainSound.play();
    }
    
    if(rainSound.isPlaying()) volume *= .95;
    if(isClear){
        rain.draw();
        if( rain.getEnd() ){
            Clear();
            isClear = false;
        }
        volume = 1.;
    }
    if(rainSound.isPlaying()) rainSound.setVolume(volume);
    
    
    //update
    for(int i=0; i<AnimalNum; i++){
        if(!animal[i].getIsDraw()){
            if(animalCount%10 == 8){
                animal[i].setup(&fbo.getTexture(), LoadAnimalData::TYPE::RARE);
            }else{
                animal[i].setup(&fbo.getTexture(), LoadAnimalData::TYPE::NORMAL);
            }
            animalCount++;
        }
    }
    
    // 主にデバッグ表示用
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    camCol.draw();
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'i'){
        pushInk(ofPoint(ofRandomWidth(), ofRandomHeight(), 0),
                ofRandom(30, 150));
    }
    if(key == 'c'){ //clear
        Clear();
    }
    if(key == 'a'){
        for(int i=0; i<AnimalNum; i++){
            animal[i].setup(&fbo.getTexture(), LoadAnimalData::TYPE::NORMAL);
            
        }
    }
    
    if(key == '1')isClear = true;
    
    
    if(key == 'd'){	// Debug Mode
        camCol.changeDebugMode();
    }
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    // 色取得テスト
    ofColor color;
    if(camCol.tryGetColor(x - 320, y, color)) {
        
    }
    
    // スクリーン補正四隅座標調整開始
    camCol.startScreenAdjust(x, y);
    
    pushInk(ofPoint(x,y,0),
            ofRandom(50, 120));
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // スクリーン補正四隅座標移動
    camCol.setScreenAdjust(x, y);
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // スクリーン補正四隅座標調整終了
    camCol.endScreenAdjust(x, y);
}

//--------------------------------------------------------------
void ofApp::pushInk(ofPoint p, float size){ //draw ink
    
    if(!isClear){
        int s = ofRandom(2);
        pushSound[s].play();
        
        int n = ofRandom(3); //cyan, magenta , yellow
        ofColor c = color_list.color[n];
        size /= 100;
        ink.setup(p, //position
                  c, //color
                  size);//size
        
        for(int i=0; i<AnimalNum; i++){
            bool j = judge.InkAttackJudge(p, size,
                                          animal[i].getPosition());
            if(j == true){
                s = ofRandom(2);
                animalSound[s].play();
                animal[i].setDrawFalse();
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::Clear() {
    fbo.begin();
    ofBackground(255, 255, 255);
    fbo.end();
    ofBackground(255);
    for(int i=0; i<AnimalNum; i++){
        animal[i].setup(&fbo.getTexture(), LoadAnimalData::TYPE::SUPERARE);
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}