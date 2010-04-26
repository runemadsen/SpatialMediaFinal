#include "AnimationCircles.h"

/* Constructor
 ___________________________________________________________ */

AnimationCircles::AnimationCircles()
{
	_usingControllers = true;
	
	_colors.push_back(0x7eff00);
	_colors.push_back(0xf000ff);
	_colors.push_back(0x8a00ff);
	_colors.push_back(0x1800ff);
	_colors.push_back(0x0072ff);
	_colors.push_back(0x00ccff);
	_colors.push_back(0x00ffae);
	_colors.push_back(0x00ff1e);
	_colors.push_back(0x7eff00);
	_colors.push_back(0xfffc00);
	_colors.push_back(0xff8400);
	_colors.push_back(0xff0000);
	_colors.push_back(0xf000ff);
	_colors.push_back(0xf000ff);
	_colors.push_back(0xf000ff);
	_colors.push_back(0xf000ff);
}

/* Update
 ___________________________________________________________ */

void AnimationCircles::update()
{
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationCircles::draw()
{
	ofSetCircleResolution(40);
	
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
}

/* Midi
 ___________________________________________________________ */

void AnimationCircles::newMidiMessage(ofxMidiEventArgs& eventArgs)
{
	printf(">>>> New Midi Message \n");
	printf("channel: %d \n", eventArgs.channel);
	printf("status: %d \n", eventArgs.status);
	printf("byte one: %d \n", eventArgs.byteOne);
	printf("byte two: %d \n", eventArgs.byteTwo);
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationCircles::getNewController(Balloon * model)
{		
	BalloonControllerCircle * b = new BalloonControllerCircle(model);
	
	if(_controllers.size() < _colors.size())
	{
		b->setColor(_colors[_controllers.size()]);
	}
	else
	{
		b->setColor(0xFF0000);
	}
	
	return b;
}
