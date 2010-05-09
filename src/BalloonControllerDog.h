#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"
#include "Tools.h"
#include "Expo.h"

class BalloonControllerDog : public BalloonController
{
	
public:
	
	BalloonControllerDog(Balloon * model);
	
	void loadImage(string imgPath);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
	
	
private:
	
	ofImage _img;
	
	PTimer timer;
	
};