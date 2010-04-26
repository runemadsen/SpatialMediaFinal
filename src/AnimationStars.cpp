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
	
	// first balloon gets 61, next 63, etc...
	_midiNotes.push_back(61);
	_midiNotes.push_back(63);
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
	BalloonControllerStars * b = new BalloonControllerStars(model);
	b->setTexture(textures[0], 2, 2);
	return b;
}