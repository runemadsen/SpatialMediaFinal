#include "AnimationLetters.h"

/* Constructor
 ___________________________________________________________ */

AnimationLetters::AnimationLetters()
{
	_usingControllers = true;
	
	// save image names
	_imgNames.push_back("letters/o.png");
	_imgNames.push_back("letters/h.png");
	_imgNames.push_back("letters/l.png");
	_imgNames.push_back("letters/a.png");
	_imgNames.push_back("letters/n.png");
	_imgNames.push_back("letters/d.png");
	_imgNames.push_back("letters/m.png");
	_imgNames.push_back("letters/u.png");
	_imgNames.push_back("letters/s.png");
	_imgNames.push_back("letters/i.png");
	_imgNames.push_back("letters/c.png");
	
	// first balloon gets 61, next 63, etc...
	_midiNotes.push_back(61);
	_midiNotes.push_back(63);
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
		b->loadImage(_imgNames[_controllers.size()]);
	}
	
	return b;
}



