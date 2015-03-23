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
    ofxMaxiOsc myCounter;               // Phasor to count
    float currentTime;                  // The value used for time
    float previousTime;                 // Previous time - used to check when phasor resets
    bool beatCheck;                     // Turns off when reach end of pitch array to stop
                                        // false triggering
    
    // Pattern stuff
    int currentBar;                     // Bar number
    int currentIndex;                   // Which pitch we are looking to play
    
    int arrayLength[53] = {3, 3};               // How many pitches are in the bar
    float beatsInBar[53] = {4, 4};          // How many beats are in the bar
    int pitch[53][3] = {{64, 65, 67},   // Pitches
                        {67, 65, 64}
                                    };
    float times[53][3] = {{1, 2, 3},    // Times at which pitches should play
                          {1, 2.5, 3}
                                    };

};
