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
    bool beatCheck;                         // Turns off when reach end of pitch array to stop
                                            // false triggering
    
    // Pattern stuff
    int currentBar;                         // Bar number
    int currentIndex;                       // Which pitch we are looking to play
    
    int arrayLength[53] = { 6, 4, 3, 3,     // How many pitches are in the bar
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
    
    float beatsInBar[53] = {3, 2, 2, 2,    // How many beats are in the bar

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
    
    int pitch[53][] = {                    // Pitches
    /*01*/        {60, 64, 60, 64, 60, 64},
    /*02*/        {60, 64, 65, 64},
    /*03*/        {64, 65, 64},
    /*04*/        {64, 65, 67},
    /*05*/        {64, 65, 67},
    /*06*/        {72},
    /*07*/        {60, 60, 60},
    /*08*/        {67, 65},
    /*09*/        {71, 67},
    /*10*/        {71, 67},
    /*11*/        {65, 67, 71, 67, 71, 67},
    /*12*/        {65, 67, 71, 72},
    /*13*/        {71, 67, 67, 65, 67, 67},
    /*14*/        {72, 71, 67, 66},
    /*15*/        {67},
    /*16*/        {67, 71, 72, 71},
    /*17*/        {71, 72, 71, 72, 71},
    /*18*/        {64, 66, 64, 66, 64, 64},
    /*19*/        {79},
    /*20*/        {64, 66, 64, 66, 55, 64, 66, 64, 66, 64},
    /*21*/        {66},
    /*22*/        {64, 64, 64, 64, 64, 66, 67, 69, 71},
    /*23*/        {64, 66, 66, 66, 66, 66, 67, 69, 71},
    /*24*/        {64, 66, 67, 67, 67, 67, 67, 69 ,71},
    /*25*/        {64, 66, 67, 69, 69, 69, 69, 69, 71},
    /*26*/        {64, 66, 67, 69, 71, 71, 71, 71, 71},
    /*27*/        {64, 66, 64, 66, 67, 64, 67, 66, 64, 66, 64},
    /*28*/        {64, 66, 64, 66, 64, 64},
    /*29*/        {64, 67, 72},
    /*30*/        {72},
    /*31*/        {67, 65, 67, 71, 67, 71},
    /*32*/        {65, 67, 65, 67, 71, 65, 67},
    /*33*/        {67, 65},
    /*34*/        {67, 65},
    /*35*/        {65, 67, 71, 67, 71, 67, 71, 67, 71, 67, 70,
                   79, 81, 79, 83, 81, 79, 76, 79, 78, 76, 77},
    /*36*/        {65, 67, 71, 67, 71, 67},
    /*37*/        {65, 67},
    /*38*/        {65, 67, 71},
    /*39*/        {71, 67, 65, 67, 71, 72},
    /*40*/        {71, 65},
    /*41*/        {71, 67},
    /*42*/        {72, 71, 68, 72},
    /*43*/        {77, 76, 77, 76, 76, 76, 76, 77, 76},
    /*44*/        {77, 76, 76, 72},
    /*45*/        {74, 74, 67},
    /*46*/        {67, 74, 76, 74, 67, 67, 67, 67, 74, 76, 74},
    /*47*/        {74, 76, 74},
    /*48*/        {67, 67, 65},
    /*49*/        {65, 67, 70, 67, 70, 67},
    /*50*/        {65, 67},
    /*51*/        {65, 67, 70},
    /*52*/        {67, 70},
    /*53*/        {70, 67},
                    };
    
    float times[53][] = {                  // Times at which pitches should play
    /*01*/        {1, 1.1, 2, 2.1, 3, 3.1},
    /*02*/        {1, 1.1, 1.6, 2.1},
    /*03*/        {1.5, 2, 2.5},
    /*04*/        {1.5, 2, 2.5},
    /*05*/        {1, 1.5, 2},
    /*06*/        {1},
    /*07*/        {4.5, 5, 5.5},
    /*08*/        {1, 7},
    /*09*/        {1, 1.5},
    /*10*/        {1, 1.5},
    /*11*/        {1, 1.25, 1.5, 1.75, 2, 2.25},
    /*12*/        {1, 1.5, 2, 6},
    /*13*/        {1, 1.25, 2, 2.25, 2.5, 3.75},
    /*14*/        {1, 5, 9, 13},
    /*15*/        {1},
    /*16*/        {1, 1.25, 1.5, 1.75},
    /*17*/        {1, 1.25, 1.5, 1.75, 2},
    /*18*/        {1, 1.25, 1.5, 1.75, 2, 2.75},
    /*19*/        {2.5},
    /*20*/        {1, 1.25, 1.5, 1.75, 2, 2.75, 3, 3.25, 3.5, 3.75},
    /*21*/        {1},
    /*22*/        {1, 2.5, 4, 5.5, 7, 8.5, 10, 11.5, 13},
    /*23*/        {1, 1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12},
    /*24*/        {1, 1.5, 2, 3.5, 5, 6.5, 8, 9.5, 11},
    /*25*/        {1, 1.5, 2, 2.5, 4, 5.5, 7, 8.5, 10},
    /*26*/        {1, 1.5, 2, 2.5, 3, 4.5, 6, 7.5, 9},
    /*27*/        {1, 1.25, 1.5, 1.75, 2, 2.25, 2.75, 3, 3.25, 3.5, 3.75},
    /*28*/        {1, 1.25, 1.5, 1.75, 2, 2.75},
    /*29*/        {1, 4, 7},
    /*30*/        {1},
    /*31*/        {1, 1.25, 1.5, 1.75, 2, 2.25},
    /*32*/        {1, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 5.5},
    /*33*/        {1, 1.25},
    /*34*/        {1, 1.25},
    /*35*/        {1, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 2.75, 3, 3.25, 7,
                   8, 11, 11.5, 12.5, 13, 14.5, 15, 18, 18.5, 24.5, 27},
    /*36*/        {1, 1.25, 1.5, 1.75, 2, 2.25},
    /*37*/        {1, 1.25},
    /*38*/        {1, 1.25, 1.5},
    /*39*/        {1, 1.25, 1.5, 1.75, 2, 2.25},
    /*40*/        {1, 1.25},
    /*41*/        {1, 1.25},
    /*42*/        {1, 5, 9, 13},
    /*43*/        {1, 1.25, 1.5, 1.75, 2, 2.5, 3, 3.35, 3.75},
    /*44*/        {1, 1.5, 2.5, 3},
    /*45*/        {1, 2, 3},
    /*46*/        {1, 1.25, 1.5, 1.75, 2.5, 3.5, 4.5, 5, 5.25, 5.5, 5.75},
    /*47*/        {1, 1.25, 1.5},
    /*48*/        {1, 7, 11},
    /*49*/        {1, 1.25, 1.5, 1.75, 2, 2.25},
    /*50*/        {1, 1.25},
    /*51*/        {1, .125, 1.5},
    /*52*/        {1, 1.25},
    /*53*/        {1, 1.25},
                        };

};