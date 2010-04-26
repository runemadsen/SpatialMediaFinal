#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"

class BalloonControllerCircle : public BalloonController
{
	
public:
	
	BalloonControllerCircle(Balloon * model);
	
	void setColor(int color);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
	
	
private:
	
	int _color;
	
};