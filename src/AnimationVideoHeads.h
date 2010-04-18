#pragma once

#include "Animation.h"

class AnimationVideoHeads : public Animation
{
public:
    
	AnimationVideoHeads();
	
    void update();
	void draw();
	
private:
	
	ofVideoPlayer head;
};


