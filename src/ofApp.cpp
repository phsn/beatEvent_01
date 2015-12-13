#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(PORT);
    sender.setup(HOST, PORT);
    
    ofAddListener(beatSyncThread.tickEvent, this, &ofApp::onTick);
    ofAddListener(beatSyncThread.barEvent, this, &ofApp::onBar);
    beatSyncThread.start();
    
    BPM = 124;
    beatStart = ofGetElapsedTimef();
    tickTime = 60.0f/BPM;
    tickSent = false;
    syncDelay = tickTime;
    
    ofSetCircleResolution(64);
    circleColor = ofColor(ofRandom(255.0f),ofRandom(255.0f),ofRandom(255.0f),255.0);
    circleSize = ofGetHeight()/2-20;
}

//--------------------------------------------------------------
void ofApp::update(){
    bTime = ofGetElapsedTimef() - beatStart;
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        //cout << m.getAddress() << "\t\t" << ofToString(m.getArgAsFloat(0)) << endl;
        
        if(ofGetElapsedTimef()-lastSync >= syncDelay) {
            if(m.getAddress() == "/Sync/x" && m.getArgAsFloat(0) == 1) {
                beatSyncThread.syncBeat();
                lastSync = ofGetElapsedTimef();
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(circleColor);
    ofCircle(ofGetWidth()/2, ofGetHeight()/2,circleSize);
}

//--------------------------------------------------------------
void ofApp::onTick(ofVec2f &tObj) {
    circleColor = ofColor(ofRandom(255.0f),ofRandom(255.0f),ofRandom(255.0f),255.0);
    
    ofxOscMessage m;
    m.setAddress("/BeatState/x");
    m.addFloatArg((tObj.y)/3.0f);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::onBar(ofVec2f &bObj) {
    //circleColor = ofColor(ofRandom(255.0f),ofRandom(255.0f),ofRandom(255.0f),255.0);
    circleSize = ofRandom(ofGetHeight()/2-20);

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
    beatSyncThread.setBPM(x/4);
    cout << x/4 << endl;
    beatSyncThread.setBPM(124);

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
