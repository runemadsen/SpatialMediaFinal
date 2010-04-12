#include "testApp.h"

void testApp::setup() 
{	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );
	
	sensing = new Sensing();
	
	displayMethod = 1;
}

void testApp::update() 
{	
	sensing->update();
}

void testApp::draw() 
{	
	sensing->draw();
	
	if(!sensing->disableAnimation())
	{
		vector <ofPoint *> points = sensing->getPointsSorted();
		
		ofEnableAlphaBlending();
		
		ofSetColor(255, 255, 255, 100);
		
		for(int i = 0; i < points.size(); i++)
		{
			ofCircle(points[i]->x, points[i]->y, sensing->getRadius());
		}	
	
		ofDisableAlphaBlending();
	}
}

void testApp::keyPressed( int key ) 
{
	if(key>='0' && key<='9') 
	{
		// change display method
	}
	else if (key =='f' || key=='F') 
	{
		ofToggleFullscreen();
	} 
	else if (key == 358) 
	{
		sensing->nextPage();
	}
	else if (key == 356) 
	{
		sensing->prevPage();
	}
	else if (key == 'S') 
	{
		sensing->displace(ADD, DISPLACE_SCALE);
	}
	else if (key == 's') 
	{
		sensing->displace(SUB, DISPLACE_SCALE);
	}
	else if (key == 'X') 
	{
		sensing->displace(ADD, DISPLACE_X);
	}
	else if (key == 'x') 
	{
		sensing->displace(SUB, DISPLACE_X);
	}
	else if (key == 'Y') 
	{
		sensing->displace(ADD, DISPLACE_Y);
	}
	else if (key == 'y') 
	{
		sensing->displace(SUB, DISPLACE_Y);
	}
	else if (key == 'R') 
	{
		sensing->displace(ADD, DISPLACE_RADIUS);
	}
	else if (key == 'r') 
	{
		sensing->displace(SUB, DISPLACE_RADIUS);
	}
	else if (key == 'l') 
	{
		sensing->loadPoints();
	}
	else if (key == 'L') 
	{
		sensing->savePoints();
	}
	else if (key ==' ') 
	{
		sensing->toggleEnabled();
	}
	else if (key == 'm') 
	{
		sensing->toggleMapFromScreen();
	}
}

void testApp::mouseMoved( int x, int y ) {}

void testApp::mouseDragged( int x, int y, int button ) {}

void testApp::mousePressed( int x, int y, int button ) 
{
	sensing->mousePressed(x, y, button);
}

void testApp::mouseReleased() {}


