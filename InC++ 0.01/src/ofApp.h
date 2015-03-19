/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp {

    public:

        void setup();
        void update();
        void draw();
        
        // Added functions
        void exit();    // For MIDI
        void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
        
        void keyPressed (int key);
        void keyReleased (int key);
        
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased();
        
    
    // MIDI stuff
	ofxMidiOut midiOut;
	int channel, note, velocity;
    unsigned int currentPgm;
    
    
    // Declare audio stuff used in audioRequested function and end of setup()
    int sampleRate;
    int initialBufferSize;
    
    // Counter stuff
    ofxMaxiOsc myCounter;
    float currentTime;
    float previousTime;
    bool timeCheck;
    
    // Pattern stuff
    int currentIndex;
    
    int arrayLength1 = 3;
    int pitch1[3] = {64, 65, 67};
    float times1[3] = {1, 2.5, 3};
    float beatsInBar[1] = {4};

};
