#include "AnimationSingingHeads.h"

/* Constructor
 ___________________________________________________________ */

AnimationSingingHeads::AnimationSingingHeads()
{
	_headState = 1;
	
	_frameBlinkEnd = 73;
	_frameOpenEnd = 93;
	_frameCloseEnd = 105;
	
	head.loadMovie("blinksequence.mov");
	head.play();
}

/* Update
 ___________________________________________________________ */

void AnimationSingingHeads::update()
{	
	if(_headState == 1)
	{
		if (head.getCurrentFrame() > _frameBlinkEnd) 
		{
			head.firstFrame();
		}
	}
	else if(_headState == 2)
	{
		if(head.getCurrentFrame() < _frameBlinkEnd)
		{
			head.setFrame(_frameBlinkEnd);
		}
		else if(head.getCurrentFrame() == _frameOpenEnd)
		{
			head.setPaused(true);
		}
	}
	else if(_headState == 3)
	{
		if(head.getCurrentFrame() == _frameOpenEnd)
		{
			head.setPaused(false);
		}
		else if(head.getCurrentFrame() > _frameCloseEnd)
		{
			_headState = 1;
			head.firstFrame();
		}
	}
	
	head.idleMovie();
}

/* Draw
 ___________________________________________________________ */

void AnimationSingingHeads::draw()
{
	ofSetColor(255, 255, 255);
	
	ofRectangle bounds;
	
	for(int i = 0; i < _points.size(); i++) 
	{
		bounds = _points[i]->getBoundsFromSize(head.getWidth(), head.getHeight());
		
		head.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	}
}

/* Midi
 ___________________________________________________________ */

void AnimationSingingHeads::newMidiMessage(ofxMidiEventArgs& eventArgs)
{
	if(eventArgs.byteTwo == 127)
	{
		// note on
		_headState = 2;
	}
	else if(eventArgs.byteTwo == 0)
	{
		// note off
		_headState = 3;
	}
}

