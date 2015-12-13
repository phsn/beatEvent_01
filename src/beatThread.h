#pragma once

#include "ofThread.h"

/// This is a simple example of a ThreadedObject created by extending ofThread.
/// It contains data (count) that will be accessed from within and outside the
/// thread and demonstrates several of the data protection mechanisms (aka
/// mutexes).

class beatThread: public ofThread
{
public:
    /// Create a ThreadedObject and initialize the member
    /// variable in an initialization list.
    beatThread(){
    }
    
    ofEvent<ofVec2f> tickEvent;
    ofEvent<ofVec2f> barEvent;

    /// Start the thread.
    void start()
    {
        SYNC = false;
        beatStart = ofGetElapsedTimef();
        barStart = beatStart;
        tickTime = 60.0f/BPM;
        tickSent = false;
        // Mutex blocking is set to true by default
        // It is rare that one would want to use startThread(false).
        startThread();
    }
    
    /// Signal the thread to stop.  After calling this method,
    /// isThreadRunning() will return false and the while loop will stop
    /// next time it has the chance to.
    void stop()
    {
        stopThread();
    }
    
    void syncBeat() {
        SYNC = true;
    }
    
    void setBPM(int beats) {
        BPM = beats;
        tickTime = 60.0f/BPM;
    }
    
    /// Our implementation of threadedFunction.
    void threadedFunction()
    {
        while(isThreadRunning())
        {
            // Attempt to lock the mutex.  If blocking is turned on,
            if(lock())
            {
                if(SYNC) {
                    beatStart = ofGetElapsedTimef()-tickTime-0.07;
                    barStart = beatStart;
                    tickStart = beatStart;
                    beatState = 0;
                    SYNC = false;
                }

                if(ofGetElapsedTimef()-tickStart >= tickTime) {
                    this->tick();
                }
                sleep(10);
                unlock();
            }
            else
            {
                // If we reach this else statement, it means that we could not
                // lock our mutex, and so we do not need to call unlock().
                // Calling unlock without locking will lead to problems.
                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
            }
        }
    }
    
    void tick() {
        
        ofVec2f tData = ofVec2f(tickStart, beatState);
        ofNotifyEvent(tickEvent, tData, this);
        if(beatState == 0) {
            ofVec2f bData = ofVec2f(tickStart, beatState);
            ofNotifyEvent(barEvent, bData, this);
        }
        
        //cout << "TICK " << beatState+1 << endl;
        beatState = (beatState+1)%4;
        tickStart += tickTime;
        if(beatState == 0) barStart = tickStart;
    }
    
protected:

    int BPM=1;
    int beatState;
    
    float bTime;
    float tickTime;
    float beatStart;
    float barStart;
    float tickStart;
    bool tickSent;
    
    bool SYNC;
    
};
