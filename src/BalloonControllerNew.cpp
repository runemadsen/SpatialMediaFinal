#include "BalloonControllerNew.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerNew::BalloonControllerNew(Balloon * model) : BalloonController(model)
{
	timer.setDuration(50);
}

void BalloonControllerNew::loadImage(string imgPath, string imgPath2)
{
	_img.loadImage(imgPath);
	_img2.loadImage(imgPath2);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerNew::update()
{
	timer.tick();
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerNew::draw()
{
	ofSetColor(255, 255, 255, 255);
	
	ofRectangle bounds = _model->getBoundsFromSize(_img.getWidth(), _img.getHeight());
	
	_img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	
	float alpha = Expo::easeOut(timer.getTime(), 0, 255, timer.getDuration());
	
	ofSetColor(255, 255, 255, alpha);
	
	_img2.draw(bounds.x, bounds.y, bounds.width, bounds.height);
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerNew::noteOn()
{
	timer.setState(1);
}

void BalloonControllerNew::noteOff()
{
	timer.setState(-1);
}