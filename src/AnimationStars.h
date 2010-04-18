#pragma once

#include "Animation.h"
#include "BalloonControllerStars.h"
#include "Constants.h"

class AnimationStars : public Animation
{
public:
    
	AnimationStars();
	
    void update();
	void draw();
	
protected:
	
	BalloonController * getNewController(Balloon * model);
	
	ofImage textures[NUM_TEXTURES];
	
	int curTexture;
};


