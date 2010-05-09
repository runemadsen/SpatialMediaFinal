#include "AnimationDogs.h"

/* Constructor
 ___________________________________________________________ */

AnimationDogs::AnimationDogs()
{
	_usingControllers = true;
	
	// save image names
	_imgNames.push_back("dog1");
	_imgNames.push_back("dog2");
	_imgNames.push_back("dog3");
	_imgNames.push_back("dog9");
	_imgNames.push_back("dog5");
	_imgNames.push_back("dog6");
	_imgNames.push_back("dog7");
	_imgNames.push_back("dog8");
	_imgNames.push_back("dog4");
}

/* Update
 ___________________________________________________________ */

void AnimationDogs::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationDogs::draw()
{
	ofSetColor(255, 255, 255);
	
	ofEnableAlphaBlending();
	
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
	
	ofDisableAlphaBlending();
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationDogs::getNewController(Balloon * model)
{		
	BalloonControllerDog * b = new BalloonControllerDog(model);
	
	if(_controllers.size() < _imgNames.size())
	{
		b->loadImage("dogs/" + _imgNames[_controllers.size()] + ".png");
	}
	
	return b;
}



