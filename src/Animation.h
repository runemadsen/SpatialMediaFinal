#pragma once

#include "ofMain.h"
#include "Balloon.h"
#include "BalloonController.h"

class Animation
{
	
public:
    
    Animation();
	
	void setBalloons(vector <Balloon *> points);
	void compareBalloonsToControllers();
	
	virtual void update() {}
	virtual void draw() {}
	
protected:
	
	virtual BalloonController * getNewController(Balloon * model) { printf("wrong"); }
	
	vector <Balloon *> _points;
	vector <BalloonController *> _controllers;
	
	bool _usingControllers;
};