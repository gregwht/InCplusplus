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
	
    
// MIDI stuff
    
	// print the available output ports to the console
	midiOut.listPorts(); // via instance
	//ofxMidiOut::listPorts(); // via static too
	
	// connect
	//midiOut.openPort(0); // by number
	//midiOut.openPort("IAC Driver Pure Data In"); // by name
	midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
	
    // Initialise MIDI values
	channel = 1;
	note = 0;
	velocity = 0;
    currentPgm = 0;
    
    // Initialise counter values
    currentTime = 0;
    previousTime = 0;
    beatCheck = true;
    
    // Initialise pattern values
    currentBar = 0;
    currentIndex = 0;
    
    
// Audio stuff
    
    sampleRate = 44100;
    initialBufferSize = 1024;
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    
    ofSoundStreamSetup(2,0, this, maxiSettings::sampleRate, initialBufferSize, 4);/* Call this last ! */


}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {

	// let's see something
	ofSetColor(0);
	stringstream text;
	text << "connected to port " << midiOut.getPort() 
		 << " \"" << midiOut.getName() << "\"" << endl
		 << "is virtual?: " << midiOut.isVirtual() << endl << endl
		 << "sending to channel " << channel << endl << endl
		 << "current program: " << currentPgm << endl << endl
         << "velocity: " << velocity << endl << endl
         << "bar: " << currentBar << endl
         << "note: " << note << endl
         << "current time: " << currentTime << endl
         << "current index: " << currentIndex << endl;
	ofDrawBitmapString(text.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiOut.closePort();
}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
//        currentBar = 0; // bar number we are playing
        
        currentTime = myCounter.phasor(1, 1, beatsInBar[currentBar]+1);
        
        
        // Check to see if phasor has restarted
        // If so, check again for beats
        if (currentTime < previousTime){
            beatCheck = true;
        }
        
        
        if (beatCheck == true){
            
            if (currentTime >= times[currentBar][currentIndex]){
                
                // Send MIDI notes
                velocity = 64;
                note = pitch[currentBar][currentIndex];
                
                midiOut.sendNoteOn(channel, note, velocity);
                
                
                // Incrememnt current index
                if (currentIndex < arrayLength[currentBar]){
                currentIndex++;
                    // Had to put inside an if statement, because when currentIndex went above arrayLength, it would send an extra MIDI note (value of 1)
                }
                
                // If current index is larger than array length, reset
                if (currentIndex >= arrayLength[currentBar]){
                    currentIndex = 0;
                    beatCheck = false;
                }
            }
            
        }
        
        // Set previousTime as the current time, so we can check at beginning of the loop
        previousTime = currentTime;
        
        //midiOut << NoteOff(channel, note, velocity);
    
        
    }

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// send a note on if the key is a letter or a number
	if(isalnum((unsigned char) key)) {
	
		// scale the ascii values to midi velocity range 0-127
		// see an ascii table: http://www.asciitable.com/
		note = ofMap(key, 48, 122, 0, 127);
		velocity = 64;
		midiOut.sendNoteOn(channel, note, velocity);
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
            
            currentBar++;
            
			break;
		case OF_KEY_DOWN:
//			currentPgm = (int) ofClamp(currentPgm-1, 0, 127);
//			midiOut << ProgramChange(channel, currentPgm); // stream interface
            
            currentBar--;
            
			break;
        
		// print the port list
		case '?':
			midiOut.listPorts();
			break;
		
		// note off using raw bytes
		case ' ':	
			// send with the byte stream interface, noteoff for note 60
			midiOut << StartMidi() << 0x80 << 0x3C << 0x40 << FinishMidi();
			break;

		default:
    
			// send a note off if the key is a letter or a number
			if(isalnum(key)) {
				note = ofMap(key, 48, 122, 0, 127);
				velocity = 0;
				midiOut << NoteOff(channel, note, velocity); // stream interface
			}
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {	
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
