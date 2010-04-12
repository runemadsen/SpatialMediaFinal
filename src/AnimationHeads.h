#pragma once

#include "Animation.h"

class AnimationHeads : public Animation
{
public:
    
	AnimationHeads();
	
    void update();
	void draw();
	
private:
	
	ofImage img;
	ofImage orgImg;
};

 
