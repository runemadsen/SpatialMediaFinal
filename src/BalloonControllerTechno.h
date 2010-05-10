#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"
#include "Tools.h"
#include "Quad.h"

class BalloonControllerTechno : public BalloonController
{
	
public:
	
	BalloonControllerTechno(Balloon * model);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
	void setStartNum(int num);
	
private:
	
	ofImage _img;
	
	PTimer timer;
};