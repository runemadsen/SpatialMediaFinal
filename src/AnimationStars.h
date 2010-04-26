#pragma once

#include "Animation.h"
#include "BalloonControllerStars.h"
#include "Constants.h"

#define NUM_TEXTURES 3
#define NUM_ROWS 2
#define NUM_COLS 2

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


