#include "AnimationSingingHeads.h"

/* Constructor
 ___________________________________________________________ */

AnimationSingingHeads::AnimationSingingHeads()
{
	_usingControllers = true;
}

/* Update
 ___________________________________________________________ */

void AnimationSingingHeads::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationSingingHeads::draw()
{
	ofSetColor(255, 255, 255);
	
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationSingingHeads::getNewController(Balloon * model)
{		
	BalloonControllerHead * b = new BalloonControllerHead(model);
	return b;
}

/* Midi
 ___________________________________________________________ */

void AnimationSingingHeads::newMidiMessage(ofxMidiEventArgs& eventArgs)
{
	BalloonControllerHead * b;
	
	switch (eventArgs.byteOne) 
	{
		case 61:
			b = dynamic_cast<BalloonControllerHead *>(_controllers[0]);
			break;
		case 63:
			b = dynamic_cast<BalloonControllerHead *>(_controllers[1]);
			break;
		default:
			break;
	}
	
	if(eventArgs.byteTwo > 0)	b->noteOn();
	else						b->noteOff();
}



