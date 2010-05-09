#include "AnimationLetters.h"

/* Constructor
 ___________________________________________________________ */

AnimationLetters::AnimationLetters()
{
	_usingControllers = true;
	
	// save image names
	_imgNames.push_back("empty");
	_imgNames.push_back("i");
	_imgNames.push_back("t");
	_imgNames.push_back("p");
	_imgNames.push_back("s");
	_imgNames.push_back("h");
	_imgNames.push_back("o");
	_imgNames.push_back("w");
	_imgNames.push_back("2");
	_imgNames.push_back("0");
	_imgNames.push_back("1");
	_imgNames.push_back("0");
	_imgNames.push_back("empty");
}

/* Update
 ___________________________________________________________ */

void AnimationLetters::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationLetters::draw()
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

BalloonController * AnimationLetters::getNewController(Balloon * model)
{		
	BalloonControllerLetter * b = new BalloonControllerLetter(model);
	
	if(_controllers.size() < _imgNames.size())
	{
		b->loadImage("letters/" + _imgNames[_controllers.size()] + ".png", "letters/" + _imgNames[_controllers.size()] + "_over.png");
	}
	
	return b;
}



