#pragma once

#include "ofMain.h"

class Animation
{
	
public:
    
    Animation();
	
	void setPoints(vector <ofPoint *> points);
	void setPointScale(float pointScale);
	
protected:
	
	vector <ofPoint *> _points;
	
	float _pointScale;
	float _oldPointScale;
	
	bool newPointScale();
};

