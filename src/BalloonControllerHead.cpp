#include "BalloonControllerHead.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerHead::BalloonControllerHead(Balloon * model) : BalloonController(model)
{
	_headState = 1;
	
	_frameBlinkEnd = 85;
	_frameCloseStart = 135;
	
	head.loadMovie("keying_tracking_resized4.mov");
	head.play();
}

/* Update
 ___________________________________________________________ */

void BalloonControllerHead::update()
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
		else if(head.getCurrentFrame() == _frameCloseStart - 1)
		{
			head.setPaused(true);
		}
	}
	else if(_headState == 3)
	{
		if(head.getCurrentFrame() == _frameCloseStart -1)
		{
			head.setPaused(false);
		}
		else if(head.getCurrentFrame() < _frameCloseStart)
		{
			head.setFrame(_frameCloseStart);
		}
		else if(head.getCurrentFrame() == head.getTotalNumFrames())
		{
			_headState = 1;
			head.firstFrame();
		}
	}
	
	head.idleMovie();
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerHead::draw()
{
	ofRectangle bounds = _model->getBoundsFromSize(head.getWidth(), head.getHeight());
	
	ofEnableAlphaBlending();
	
	head.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	ofDisableAlphaBlending();
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerHead::noteOn()
{
	_headState = 2;
}

void BalloonControllerHead::noteOff()
{
	_headState = 3;
}