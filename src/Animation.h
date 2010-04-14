#pragma once

#include "ofMain.h"
#include "Balloon.h"

class Animation
{
	
public:
    
    Animation();
	
	void setPoints(vector <Balloon *> points);
	
	virtual void update() {}
	virtual void draw() {}
	
protected:
	
	vector <Balloon *> _points;
};

