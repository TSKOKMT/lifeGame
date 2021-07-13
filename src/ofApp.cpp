#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //setup app
    app.setup("lifeGame", 50006, true, true, true);
    
    lifeGame.setup(app.frame.width, app.frame.height);
    //lifeGame.random();
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
    
    for (int i = 0; i < app.people.size(); i++) {
        for (float y = 0; y < ofMap(abs(app.getPeopleSpeedZ()[i]), 0, 20, 0, app.frame.height); y += lifeGame.size) {
            if (app.people[i].x < .25) lifeGame.set(ofPoint(app.getPeopleL()[i], y), true);
            if (app.people[i].x > .75) lifeGame.set(ofPoint(app.getPeopleR()[i], y), true);
        }
    }
    /*for (int i = 0; i < app.silhouettes.size(); i++) {
        for (int j = 0; j < app.silhouettes[i].polyline.getVertices().size(); j++) {
            lifeGame.set(app.silhouettes[i].polyline.getVertices()[j], true);
        }
    }*/
    for (int i = 0; i < lifeGame.cells.size(); i++) {
        for (int j = 0; j < lifeGame.cells[i].size(); j++) {
            for (int k = 0; k < app.silhouettes.size(); k++) {
                ofPoint p = lifeGame.getCellPosition(j, i);
                if (app.silhouettes[k].polyline.inside(p.x, p.y)) lifeGame.destroy(j, i);
            }
        }
    }
    
    //update colors
    float hue = 244;
    if (app.people.size() > 0) hue = app.people[(int)(app.time / 60) % (int)app.people.size()].y * 256;
    float saturation = ofGetMousePressed() ? 0 : 255;
    if (app.people.size() > 0) saturation = ofClamp(ofMap(app.people[(int)(app.time / 60) % (int)app.people.size()].x, 0, .5, 0, 256), 0, 256);
    float brightness = 255;
    if (app.people.size() > 0) brightness = ofClamp(ofMap(app.people[(int)(app.time / 60) % (int)app.people.size()].x, .5, 1, 256, 0), 0, 256);
    lifeGame.colors[0].setHsb(math[0].easeFilter(hue, .1), math[1].easeFilter(saturation, ofGetMousePressed() ? 1 : .1), math[2].easeFilter(brightness, .1));
    
    brightness = 0;
    if (app.people.size() > 0) {
        if (app.people[(int)(app.time / 60) % (int)app.people.size()].x > .5) brightness = 255;
    }
    lifeGame.colors[1].setHsb(0, 0, math[3].easeFilter(brightness, .1));
    
    hue = 0;
    if (app.people.size() > 0) {
        hue = app.people[(int)(app.time / 60) % (int)app.people.size()].y * 256;
        hue = fmod(hue + 128, 256);
    }
    saturation = 0;
    if (app.people.size() > 0) {
        float seed = app.people[(int)(app.time / 60) % (int)app.people.size()].x;
        if (seed < .5) saturation = 255;
        else saturation = ofClamp(ofMap(seed, .5, .75, 0, 256), 0, 256);
    }
    brightness = 0;
    if (app.people.size() > 0) {
        float seed = app.people[(int)(app.time / 60) % (int)app.people.size()].x;
        if (seed > .5) brightness = 255;
        else brightness = ofClamp(ofMap(seed, .25, .5, 256, 0), 0, 256);
    }
    lifeGame.colors[2].setHsb(math[6].easeFilter(hue, .1), math[7].easeFilter(saturation, .1), math[8].easeFilter(brightness, .1));
    
    //explosion
    if (ofGetMousePressed()) lifeGame.random();

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
