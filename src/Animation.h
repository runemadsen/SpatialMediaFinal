#pragma once

#include "ofMain.h"
#include "Balloon.h"
#include "BalloonController.h"
#include "ofxMidi.h"

class Animation
{
	
public:
    
    Animation();
	
	void setBalloons(vector <Balloon *> points);
	void compareBalloonsToControllers();
	void allNodesOff();
	
	virtual void update() {}
	virtual void draw() {}
	virtual void newMidiMessage(ofxMidiEventArgs& eventArgs);
	
	
protected:
	
	virtual BalloonController * getNewController(Balloon * model) { }
	
	vector <Balloon *> _points;
	vector <BalloonController *> _controllers;
	
	bool _usingControllers;
	
	vector <int> _midiNotes;
};