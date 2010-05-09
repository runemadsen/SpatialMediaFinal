#include "testApp.h"

void testApp::setup() 
{	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );
	ofEnableSmoothing();
	
	sensing = new Sensing();
	
	animations.push_back(new AnimationCircles());
	animations.push_back(new AnimationHeads());
	//animations.push_back(new AnimationVideoHeads());
	animations.push_back(new AnimationStars());
	animations.push_back(new AnimationSingingHeads());
	animations.push_back(new AnimationLetters());
	animations.push_back(new AnimationNew());
	animations.push_back(new AnimationDogs());
	
	selectedAnimation = 0;
	
	midiIn.setVerbose(false);
	midiIn.listPorts();
	midiIn.openPort(1);
	midiIn.addListener(this);
}

void testApp::update() 
{	
	sensing->update();
	
	if(!sensing->disableAnimation())
	{
		animations[selectedAnimation]->setBalloons(sensing->getBalloons());
		animations[selectedAnimation]->compareBalloonsToControllers();
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

void testApp::newMidiMessage(ofxMidiEventArgs& eventArgs)
{
	printf("<#message#>");
	
	animations[selectedAnimation]->newMidiMessage(eventArgs);
}

void testApp::keyPressed( int key ) 
{
	sensing->keyPressed(key);
	
	if(key > '0' && key <= '9')
	{
		int convert = key- '0';
		
		if (convert <= animations.size()) 
		{
			selectedAnimation = convert - 1;
		}
	}
	else if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
}

void testApp::mouseMoved( int x, int y ) {}

void testApp::mouseDragged( int x, int y, int button ) 
{
	sensing->mouseDragged(x, y, button);
}

void testApp::mousePressed( int x, int y, int button ) 
{
	sensing->mousePressed(x, y, button);
}

void testApp::mouseReleased() {}


