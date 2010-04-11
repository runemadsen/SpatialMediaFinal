#include "testApp.h"

void testApp::setup() 
{
	name = "OHLAND";
	
	ofSetFrameRate(60);
	ofBackground( 0, 0, 0 );
	
	sensing = new Sensing();
}

void testApp::update() 
{	
	sensing->update();
}

void testApp::draw() 
{	
	sensing->draw();
	
	if(sensing->getPage() != 1 || !sensing->getEnabled())
	{
		vector <ofPoint *> points = sensing->getPointsSorted();
		
		ofEnableAlphaBlending();
		
		ofSetColor(255, 255, 255, 100);
		
		for(int i = 0; i < points.size(); i++)
		{
			if(i < name.length())
			{
				ofDrawBitmapString(name.substr(i, 1), points[i]->x, points[i]->y);
				ofCircle(points[i]->x, points[i]->y, sensing->getRadius());
			}
		}	
	
		ofDisableAlphaBlending();
	}
}

void testApp::keyPressed( int key ) 
{
	if (key =='f' || key=='F') 
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
	else if (key ==' ') 
	{
		sensing->toggleEnabled();
	}
}

void testApp::mouseMoved( int x, int y ) {}

void testApp::mouseDragged( int x, int y, int button ) {}

void testApp::mousePressed( int x, int y, int button ) 
{
	sensing->mousePressed(x, y, button);
}

void testApp::mouseReleased() {}


