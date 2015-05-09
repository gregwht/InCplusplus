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
#include "Performer.h"
#include "Pulse.h"
#include "maximilian.h"

#define PERFORMER_NUM 10

class ofApp : public ofBaseApp {

    public:

        void setup();
        void update();
        void draw();
        void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    
        void keyPressed (int key);
        void keyReleased (int key);

    // Declare audio stuff used in audioRequested function and end of setup()
    int sampleRate;
    int initialBufferSize;
    
    
    Performer performer[PERFORMER_NUM];
    Performer port;
    int tempo;                              // Beats per minute
    Pulse c;

};

/* BUGS:
 - CHECK ALL BARS ARE CORRECT
 - (Sends weird MIDI note when changing bars)
 - (Sometimes when changing bars, currentIndex gets stuck and notes won't play)
 - When changing bar in the middle of a bar, the next bar doesn't start until phasor has returned to 1? (Drops not _necessarily_ a bad thing, as the score dictates that performers are allowed to drop out if they wish. But here, this is not determined by choice).
 - Sometimes when changing bars, you get two notes triggered at once
 - Bar 32: Think last note isn't there
 - Bar 47: Think missing note

 
 FEATURES:
 - Add functionality so that you can enter a time, and the program will play the piece over that amount of time
 - Next bar 9/10 the next bar, 1/10 C pulse. If C pulse, save currentBar as savedBar, then after performer is finished with C pulse, play savedBar + 1.
 - Pulse player
 - Performers don't all start at once - delay a random amount of beats before coming in
 - Performers keep within 3 bars (see score to confirm 3 bars)
 - Separate Performer's process into more functions

 
 
 */
