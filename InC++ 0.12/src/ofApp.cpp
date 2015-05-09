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
    
    port.openVirtualPort("Port");


    //c.openVirtualPort("Pulse");
    //c.openPort(0);
    //c.setup(1);
    //c.exit();
    //c.loadBars();

    
    for (int i = 1; i < PERFORMER_NUM+1; i++){
        
        performer[i].openVirtualPort("Performer");
        performer[i].setup(i);
        performer[i].exit();
        performer[i].loadBars();
    }

    
    // Audio stuff

    sampleRate = 44100;
    initialBufferSize = 1024;

    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);

    ofSoundStreamSetup(2,0, this, maxiSettings::sampleRate, initialBufferSize, 4);/* Call this last ! */


}


//--------------------------------------------------------------
void ofApp::audioRequested  	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){

        c.play();
        
        for (int i = 1; i < PERFORMER_NUM+1; i++){
            performer[i].play();
            
            // Check to see that performers are within 3 bars of each other
            for (int j = 1; j < PERFORMER_NUM+1; j++){

                // If the distance between performers is 4 bars or greater...
                if (performer[i].currentBar - performer[j].currentBar >= 4){

                    //...when the lagging performer finishes their bar, progress to the next one
                    if (performer[j].currentTime < performer[j].previousTime) {

                        performer[j].currentBar++;
                    }
                }
            }
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {

	// let's see something
    for (int i = 1; i < PERFORMER_NUM+1; i++){

        if (performer[i].finished == false){ofSetColor(0);}
        else {ofSetColor(255, 0, 0);}
        
        stringstream text;
        text << "connected to port " << performer[i].midiOut.getPort()
             << " \"" << performer[i].midiOut.getName() << "\"" << endl
             << "is virtual?: " << performer[i].midiOut.isVirtual() << endl << endl
             << "sending to channel " << performer[i].channel << endl << endl
             << "threshold: " << performer[i].threshold << endl
             << "margin: " << performer[i].margin << endl << endl
             << "velocity: " << performer[i].velocity << endl << endl
             << "tempo: " << performer[i].tempo << endl
             << "freq: " << performer[i].freq << endl << endl
             << "bar: " << performer[i].currentBar << endl
             << "pitches in bar: " << performer[i].arrayLength[performer[i].currentBar] << endl
             << "beats in bar: " << performer[i].beatsInBar[performer[i].currentBar] << endl << endl
             << "note: " << performer[i].note << endl
             << "current time: " << performer[i].currentTime << endl
             << "current index: " << performer[i].currentIndex << endl
             << "factor: " << performer[i].factor << endl
             << "progress: " << performer[i].progress << endl << endl
             << "finished: " << performer[i].finished << endl;
        ofDrawBitmapString(text.str(), 20 + (200 * (i-1)), 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    // send a note on if the key is a letter or a number
    if(isalnum((unsigned char) key)) {
        
        // scale the ascii values to midi velocity range 0-127
        // see an ascii table: http://www.asciitable.com/
//        performer.note = ofMap(key, 48, 122, 0, 127);
//        performer.velocity = 64;
//        performer.midiOut.sendNoteOn(performer.channel, performer.note, performer.velocity);
    }
    
    if(key == 'l') {
        ofxMidiOut::listPorts();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
    
    for (int i = 1; i < PERFORMER_NUM+1; i++){
        
        switch(key) {
                
            
            case OF_KEY_UP:
        
                performer[i].currentBar++;
                
                break;
            case OF_KEY_DOWN:
                
                performer[i].currentBar--;
                
                break;
            case '-':
                performer[i].factor *= 0.9;
                
                break;
            case '=':
                performer[i].factor *= 1.1;
                
        }
    }
}