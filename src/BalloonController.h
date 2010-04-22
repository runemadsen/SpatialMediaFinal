#pragma once

#include "ofMain.h"
#include "Balloon.h"

class BalloonController
{
	
public:
	
	BalloonController(Balloon * model);
	
	virtual void update() {}
	virtual void draw() {}
	virtual void noteOn() {}
	virtual void noteOff() {}
	
	void setModel(Balloon * model);
	void setMidiNote(int midiNote);
	
	Balloon * getModel();
	int getMidiNote();
	
protected:
	
	Balloon * _model;
	int _midiNote;
};