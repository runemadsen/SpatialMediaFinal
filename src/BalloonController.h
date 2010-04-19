#pragma once

#include "ofMain.h"
#include "Balloon.h"

class BalloonController
{
	
public:
	
	BalloonController(Balloon * model) 
	{ 
		_model = model;
	}
	
	void setModel(Balloon * model) { _model = model; }
	
	virtual void update() {}
	virtual void draw() {}
	
	Balloon * getModel() { return _model; }
	
protected:
	
	Balloon * _model;
};