#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"
#include "Tools.h"
#include "Expo.h"

class BalloonControllerNew : public BalloonController
{
	
public:
	
	BalloonControllerNew(Balloon * model);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
	
	
private:
	
	ofImage img;
};