#pragma once

#include "ofMain.h"
#include "BalloonController.h"
#include "Balloon.h"
#include "Constants.h"

class BalloonControllerHead : public BalloonController
{
	
public:
	
	BalloonControllerHead(Balloon * model);
	
	void update();
	void draw();
	
	void noteOn();
	void noteOff();
	
private:
	
	ofVideoPlayer head;
	
	int _headState; // 1 = blinking, 2 = opening, 3 = closing
	
	int _frameBlinkEnd;
	int _frameOpenEnd;
	int _frameCloseEnd;
	
};