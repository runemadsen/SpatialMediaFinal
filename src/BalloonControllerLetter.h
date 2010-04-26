#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"
#include "Tools.h"
#include "Expo.h"

class BalloonControllerLetter : public BalloonController
{
	
public:
	
	BalloonControllerLetter(Balloon * model);
	
	void loadImage(string imgPath, string imgPath2);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
	
	
private:
	
	ofImage _img;
	ofImage _img2;
	
	PTimer timer;
	
};