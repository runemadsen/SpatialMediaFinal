#include "BalloonControllerTechno.h"

/* Constructor
 ___________________________________________________________ */

BalloonControllerTechno::BalloonControllerTechno(Balloon * model) : BalloonController(model)
{
	timer.setUpDown(true);
	timer.setState(1);
	timer.setDuration(200);
	
	_img.loadImage("balloon3.png");
}

void BalloonControllerTechno::setStartNum(int num)
{
	timer.setTime(num);
}

/* Update
 ___________________________________________________________ */

void BalloonControllerTechno::update()
{
	timer.tick();
}

/* Draw
 ___________________________________________________________ */

void BalloonControllerTechno::draw()
{
	ofRectangle bounds = _model->getBoundsFromSize(_img.getWidth(), _img.getHeight(), false);
	
	float alpha = Quad::easeIn(timer.getTime(), 0, 255, timer.getDuration());
	
	ofEnableAlphaBlending();
	
	ofSetColor(255, 255, 255, alpha);
	
	_img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
	
	ofDisableAlphaBlending();
}

/* Midi note on / off
 ___________________________________________________________ */

void BalloonControllerTechno::noteOn()
{
	//timer.setState(1);
}

void BalloonControllerTechno::noteOff()
{
	//timer.setState(-1);
}