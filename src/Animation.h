#pragma once

#include "ofMain.h"
#include "Balloon.h"

class Animation
{
	
public:
    
    Animation();
	
	void setPoints(vector <Balloon *> points);
	
protected:
	
	vector <Balloon *> _points;
};

