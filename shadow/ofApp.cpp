#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //setup app
    app.setup("lifeGame", 50006, true, true, true);
    
    lifeGame.setup(app.frame.width, app.frame.height);
    lifeGame.random();
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle("lifeGame | " + ofToString(round(ofGetFrameRate())));
    
    //update app
    app.update();
    
    if (!app.bActive) return;
    
    //create gliders
    for (int i = 0; i < app.touches.size(); i++) {
        if (app.touches[i].bPressing) lifeGame.createGlider(app.touches[i].position);
    }
    if (ofGetMousePressed()) lifeGame.createGlider(app.getDisTranslatedPosition(ofPoint(mouseX, mouseY)));
    
    /*for (int i = 0; i < app.people.size(); i++) {
        for (float y = 0; y < ofMap(abs(app.getPeopleSpeedZ()[i]), 0, 30, 0, app.frame.height); y += lifeGame.size) {
            lifeGame.set(ofPoint(app.getPeopleL()[i], y), true);
            lifeGame.set(ofPoint(app.getPeopleR()[i], y), true);
        }
    }*/
    for (int i = 0; i < lifeGame.cells.size(); i++) {
        for (int j = 0; j < lifeGame.cells[i].size(); j++) {
            lifeGame.cells[i][j] = false;
        }
    }
    for (int i = 0; i < app.silhouettes.size(); i++) {
        for (int j = 0; j < app.silhouettes[i].polyline.getVertices().size(); j++) {
            lifeGame.set(app.silhouettes[i].polyline.getVertices()[j] + app.frameL.getTopRight(), true);
        }
    }

    //update lifeGame
    lifeGame.update();
    
    //draw
    app.begin();
    
    lifeGame.draw();
    ofSetColor(255, 0, 0);
    
    app.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw app
    app.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    
    //exit app
    app.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
