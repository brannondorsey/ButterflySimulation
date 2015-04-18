#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    
    butterfly.setup(ofColor(255, 0, 0), ofColor(200, 0, 0), ofVec3f(83, 56));
    camera.lookAt(butterfly.getPosition());
}

//--------------------------------------------------------------
void ofApp::update(){
    butterfly.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    camera.begin();
    
    // don't render alpha pixels to depth buffer
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_ALPHA_TEST);
    
    butterfly.draw();
    camera.end();
    
    ofSetColor(0);
    ofVec3f pos = butterfly.getPosition();
    ofDrawSphere(pos.x, pos.y, 100);
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
    
    if (button == 2)
    {
        ofLogNotice("ofApp::mousePressed") << "Homing butterfly";
        butterfly.homeTo(camera.screenToWorld(ofVec3f(ofGetMouseX(), ofGetMouseY(), 0)));
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
