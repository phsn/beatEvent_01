#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "beatThread.h"

#define PORT 8000
#define HOST "192.168.178.73"

#define BEAT_BUFFER 131072

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    beatThread beatSyncThread;

    
    int BPM;
    float bTime;
    float tickTime;
    float beatStart;
    bool tickSent;
};
