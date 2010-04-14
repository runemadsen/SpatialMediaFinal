#include "testApp.h"

void testApp::setup() 
{	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );
	ofEnableSmoothing();
	
	sensing = new Sensing();
	
	displayMethod = 1;
	
	animations.push_back(new AnimationHeads());
	animations.push_back(new AnimationCircles());
	
	selectedAnimation = 0;
}

void testApp::update() 
{	
	sensing->update();
	
	if(!sensing->disableAnimation())
	{
		animations[selectedAnimation]->setPoints(sensing->getBalloonsSorted());
		animations[selectedAnimation]->update();
	}
}

void testApp::draw() 
{	
	if(!sensing->disableAnimation())
	{
		animations[selectedAnimation]->draw();
	}
	
	sensing->draw();
}

void testApp::keyPressed( int key ) 
{
	sensing->keyPressed(key);
	
	if(key == '1') 
	{
		selectedAnimation = 0;
	}
	else if(key == '2') 
	{
		selectedAnimation = 1;
	}
	else if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
}

void testApp::mouseMoved( int x, int y ) {}

void testApp::mouseDragged( int x, int y, int button ) 
{
	//sensing->mouseDragged(x, y, button);
}

void testApp::mousePressed( int x, int y, int button ) 
{
	sensing->mousePressed(x, y, button);
}

void testApp::mouseReleased() {}


