#pragma once

#include "ofMain.h"

class Animation
{
	
public:
    
    Animation();
	
	void setPoints(vector <Balloon *> points);
	void setPointScale(float pointScale);
	
protected:
	
	vector <Balloon *> _points;
	
	float _pointScale;
	float _oldPointScale;
	
	bool newPointScale();
};

