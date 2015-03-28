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
    ofxMaxiOsc myCounter;                   // Phasor to count
    float currentTime;                      // The value used for time
    float previousTime;                     // Previous time - used to check when phasor resets
    bool beatCheck;                         // Turns off when reach end of pitch array to stop false triggering
    
    int tempo;
    float duration;                         // How long, in seconds, each bar lasts
    float freq;                             // Phasor frequency
    
    // Pattern stuff
    int currentBar;                         // Bar number
    int currentIndex;                       // Which pitch we are looking to play
    
    int arrayLength[54] = {1, 6, 4, 3, 3,     // How many pitches are in the bar
                            3, 1, 3, 2,
                            2, 2, 6, 4,
                            6, 4, 1, 4,
                            5, 6, 1, 10,
                            1, 9, 9, 9,
                            9, 9, 11, 6,
                            3, 1, 6, 7,
                            2, 2, 22, 6,
                            2, 3, 6, 2,
                            2, 4, 9, 4,
                            3, 11, 3, 3,
                            6, 2, 3, 2,
                            2 };
    
    float beatsInBar[54] = {1, 3, 2, 2, 2,    // How many beats are in the bar

                            2, 8, 9.5, 14,
                            4.5, 1, 1.5, 6,
                            6, 16, 4, 1,
                            1.5, 2, 3, 3,
                            3, 12.5, 12, 10.5,
                            10.5, 9.5, 3, 2,
                            9, 6, 1.5, 6,
                            0.75, 0.5, 29, 1.5,
                            0.5, 0.75, 1.5, 0.5,
                            0.5, 16, 3, 3,
                            3, 5, 0.5, 15,
                            1.5, 0.5, 0.75, 0.5,
                            0.5};
    
    vector< vector<int> > pitch;
    vector< vector<float> > time;
    

};

/* BUGS:
 - Sends weird MIDI note when changing bars
 
 
 
 
 
 */
