#pragma once

#include "Animation.h"

class AnimationCircles : public Animation
{
public:
    
	AnimationCircles();
	
    void update();
	void draw();
	
private:
	
	vector <int> _colors;
	
};


