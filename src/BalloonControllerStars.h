#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"

class BalloonControllerStars : public BalloonController
{
	
public:
	
	BalloonControllerStars(Balloon * model);
	
	void update();
	void draw();
	
private:
	
};