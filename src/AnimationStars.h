#pragma once

#include "Animation.h"
#include "BalloonControllerStars.h"

class AnimationStars : public Animation
{
public:
    
	AnimationStars();
	
    void update();
	void draw();
	
protected:
	
	BalloonController * getNewController(Balloon * model);
};


