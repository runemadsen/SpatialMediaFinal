#include "AnimationStars.h"

/* Constructor
 ___________________________________________________________ */

AnimationStars::AnimationStars()
{
	_usingControllers = true;
	
	for(int i = 0; i < NUM_TEXTURES; i++)
	{
		textures[i].loadImage("particleGrid" + ofToString(i, 0) + ".png");
	}
}

/* Update
 ___________________________________________________________ */

void AnimationStars::update()
{
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationStars::draw()
{
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationStars::getNewController(Balloon * model)
{		
	return new BalloonControllerStars(model);
}