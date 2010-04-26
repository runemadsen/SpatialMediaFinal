#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"

class BalloonControllerLetter : public BalloonController
{
	
public:
	
	BalloonControllerLetter(Balloon * model);
	
	void loadImage(string imgPath);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
	
	
private:
	
	ofImage _img;
	
};