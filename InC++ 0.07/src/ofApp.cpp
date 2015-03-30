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
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    performerNum = 2;
    
    performer.setup();
    performer.exit();
    performer.loadBars();
    performer.audioRequested (* output, initialBufferSize, 2);
    
    
//    // Audio stuff
//
//    sampleRate = 44100;
//    initialBufferSize = 1024;
//
//    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
//
//    ofSoundStreamSetup(2,0, this, maxiSettings::sampleRate, initialBufferSize, 4);/* Call this last ! */


}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {

	// let's see something

        if (performer.finished == false){ofSetColor(0);}
        else {ofSetColor(255, 0, 0);}
        
        stringstream text;
        text << "connected to port " << performer.midiOut.getPort()
             << " \"" << performer.midiOut.getName() << "\"" << endl
             << "is virtual?: " << performer.midiOut.isVirtual() << endl << endl
             << "sending to channel " << performer.channel << endl << endl
             << "current program: " << performer.currentPgm << endl << endl
             << "threshold: " << performer.threshold << endl << endl
             << "velocity: " << performer.velocity << endl << endl
             << "tempo: " << performer.tempo << endl
             << "freq: " << performer.freq << endl << endl
             << "bar: " << performer.currentBar << endl
             << "pitches in bar: " << performer.arrayLength[performer.currentBar] << endl
             << "beats in bar: " << performer.beatsInBar[performer.currentBar] << endl << endl
             << "note: " << performer.note << endl
             << "current time: " << performer.currentTime << endl
             << "current index: " << performer.currentIndex << endl
             << "progress: " << performer.progress << endl << endl
             << "finished: " << performer.finished << endl;
        ofDrawBitmapString(text.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    // send a note on if the key is a letter or a number
    if(isalnum((unsigned char) key)) {
        
        // scale the ascii values to midi velocity range 0-127
        // see an ascii table: http://www.asciitable.com/
        performer.note = ofMap(key, 48, 122, 0, 127);
        performer.velocity = 64;
        performer.midiOut.sendNoteOn(performer.channel, performer.note, performer.velocity);
    }
    
    if(key == 'l') {
        ofxMidiOut::listPorts();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
    switch(key) {
            
            // send pgm change on arrow keys
        case OF_KEY_UP:
            //			currentPgm = (int) ofClamp(currentPgm+1, 0, 127);
            //			midiOut.sendProgramChange(channel, currentPgm);
            
            performer.currentBar++;
            
            break;
        case OF_KEY_DOWN:
            //			currentPgm = (int) ofClamp(currentPgm-1, 0, 127);
            //			midiOut << ProgramChange(channel, currentPgm); // stream interface
            
            performer.currentBar--;
            
            break;
            
            // print the port list
        case '?':
           performer.midiOut.listPorts();
            break;
            
            // note off using raw bytes
        case ' ':
            // send with the byte stream interface, noteoff for note 60
            performer.midiOut << StartMidi() << 0x80 << 0x3C << 0x40 << FinishMidi();
            break;
            
            //		default:
            //
            //			// send a note off if the key is a letter or a number
            //			if(isalnum(key)) {
            //				note = ofMap(key, 48, 122, 0, 127);
            //				velocity = 0;
            //				midiOut << NoteOff(channel, note, velocity); // stream interface
            //			}
            //			break;
    }
}