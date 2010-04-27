#include "AnimationNew.h"

/* Constructor
 ___________________________________________________________ */

AnimationNew::AnimationNew()
{
	_usingControllers = true;
	
	// save image names
	_imgNames.push_back("o");
	_imgNames.push_back("h");
	_imgNames.push_back("l");
	_imgNames.push_back("a");
	_imgNames.push_back("n");
	_imgNames.push_back("d");
	_imgNames.push_back("m");
	_imgNames.push_back("u");
	_imgNames.push_back("s");
	_imgNames.push_back("i");
	_imgNames.push_back("c");;
}

/* Update
 ___________________________________________________________ */

void AnimationNew::update()
{	
	for(int i = 0; i < _controllers.size(); i++)
	{
		_controllers[i]->update();
	}
}

/* Draw
 ___________________________________________________________ */

void AnimationNew::draw()
{
	ofSetColor(255, 255, 255);
	
	ofEnableAlphaBlending();
	
	for(int i = 0; i < _controllers.size(); i++)
	{ 
		_controllers[i]->draw();
	}
	
	ofDisableAlphaBlending();
}

/* Overrides
 ___________________________________________________________ */

BalloonController * AnimationNew::getNewController(Balloon * model)
{		
	BalloonControllerNew * b = new BalloonControllerNew(model);
	
	string imgName1 = "letters/" + _imgNames[_controllers.size()] + ".png";
	string imgname2 = "letters/" + _imgNames[_controllers.size()] + "_over.png";
	
	if(_controllers.size() < _imgNames.size())
	{
		b->loadImage(imgName1, imgName2);
	}
	
	return b;
}



