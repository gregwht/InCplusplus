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


// Special thanks to Rebecca Fiebrink for showing me how to make this project in a much simpler and cleverer way, and the general openFrameworks knowledge.
// Special thanks also to Kiona H. Niehaus, for helping me when my brain wouldn't math so good.
// Finally, thanks to the MA/MFA Computational Arts cohort at Goldsmiths for the continued support, ideas, critiques, and inspiration.

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
    ofxMaxiOsc metronome;                   // Phasor to count beats
    float currentTime;                      // The value used for time
    float previousTime;                     // Previous time - used to check when phasor resets
    bool beatCheck;                         // Turns off when reach end of pitch array to stop false triggering
    
    int tempo;                              // Beats per minute
    float freq;                             // Phasor frequency
    
    float progress;                         // Increases at the end of each bar
    float factor;                           // Factor by which progress increases
    
    float threshold;                        // When progress >= threshold, progress to next bar
    float margin;                           // random (per bar) +/- number added to threshold
    float margMin;                          // for ofRandom( );
    float margMax;                          // for ofRandom( );
    
    int previousBar;                        // Store previous bar to compare to currentBar, to check if bar has changed and progress counter needs resetting
   
    bool finished;                          // Flag when performer finishes last bar and is just repeating
    
    
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
 - (Sends weird MIDI note when changing bars)
 - (Sometimes when changing bars, currentIndex gets stuck and notes won't play)
 - When changing bar in the middle of a bar, the next bar doesn't start until phasor has returned to 1? (Drops not _necessarily_ a bad thing, as the score dictates that performers are allowed to drop out if they wish. But here, this is not determined by choice).
 - Sometimes when changing bars, you get two notes triggered at once
 - Bar 32: Think last note isn't there
 - Bar 47: Think missing note

 
 FEATURES:
 - Add functionality so that you can enter a time, and the program will play the piece over that amount of time
 - Have a counter, up to say 50 +/- a margin. After the bar has been played, add the vector.size(); to that counter. After it passes the threshold, move on to next bar
 - Next bar 9/10 the next bar, 1/10 C pulse. If C pulse, save currentBar as savedBar, then after performer is finished with C pulse, play savedBar + 1. 
 = Classes: Give performers a loadBars function that loads the pitch and time data vectors. Then stick it at the bottom of the screen.
   - For (i = 1; i < performerNum+1; i++)
    - performer[i].setup()
    - performer[i].loadBars()
    - performer[i].play()
 - Pulse player

 
 
 */
