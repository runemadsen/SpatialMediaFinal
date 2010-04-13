#include "testApp.h"

void testApp::setup() 
{	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );
	
	sensing = new Sensing();
	
	displayMethod = 1;
	
	heads = new AnimationHeads();
}

void testApp::update() 
{	
	sensing->update();
	
	if(!sensing->disableAnimation())
	{
		heads->setPoints(sensing->getPointsSorted());
		heads->setPointScale(sensing->getPointScale());
		heads->update();
	}
}

void testApp::draw() 
{	
	if(!sensing->disableAnimation())
	{
		heads->draw();
	}
	
	sensing->draw();
}

void testApp::keyPressed( int key ) 
{
	sensing->keyPressed(key);
	
	if(key>='0' && key<='9') 
	{
		// change display method
	}
	else if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
}

void testApp::mouseMoved( int x, int y ) {}

void testApp::mouseDragged( int x, int y, int button ) {}

void testApp::mousePressed( int x, int y, int button ) 
{
	sensing->mousePressed(x, y, button);
}

void testApp::mouseReleased() {}


