#pragma once

#include "ofMain.h"
#include "ofxSimpleGuiToo.h"
#include "ofxFBOTexture.h"
#include "ofxXmlSettings.h"
#include "Constants.h"

#define VIDEO_WIDTH 320.0
#define VIDEO_HEIGHT 240.0
#define VIDEO_X 22.0
#define VIDEO_Y 133.0
#define VIDEO_SCALE 2.0
#define POINT_MARGIN 5
#define XML_FILE "points.xml"

class Sensing  
{
	
public:
	
	Sensing();
	
	struct ysorter
    {
        bool operator()(ofPoint * a, ofPoint * b) const
        {
            if(a->y < b->y)
			{
				return true;
			}
			
			return false;
        }
    };
	
	struct xsorter
    {
        bool operator()(ofPoint * a, ofPoint * b) const
        {
            if(a->x < b->x)
			{
				return true;
			}
			
			return false;
        }
    };
	
	void update();
	void draw();
	
	void mousePressed(int x, int y, int button);
	
	void toggleEnabled();
	void toggleMapFromScreen();
	void nextPage();
	void prevPage();
	
	void displace(string method, string value);
	
	vector <ofPoint *> getPoints();
	vector <ofPoint *> getPointsSorted();
	bool getEnabled();
	float getPointScale();
	int getPage();
	bool disableAnimation();
	
	void drawPoint(int xPos, int yPos, int color);
	
	void loadPoints();
	void savePoints();
	
	void keyPressed(int key);
	
private:
	
	void checkClick(int xPos, int yPos);
	int isClickWithinPoint(int xPos, int yPos);
	bool isClickWithinVideo(int xPos, int yPos);
	void setPointDataToGUI();

	
	ofImage _testImage;
	ofVideoGrabber  _camera;
	
	ofxFBOTexture _outputTexture;
	
	vector <ofPoint *> _points;
	
	float _xDisplace;
	float _yDisplace;
	float _scale;
	float _pointScale;
	float _selectedPointScale;
	bool _mapFromScreen;

	int _enabled;
	
	int _selectedPoint;
	float _selectedPointX;
	float _selectedPointY;
	
	ofxXmlSettings _xml;
};