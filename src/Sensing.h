#pragma once

#include "ofMain.h"
#include "ofxSimpleGuiToo.h"
#include "ofxFBOTexture.h"
#include "ofxXmlSettings.h"
#include "Constants.h"
#include "Balloon.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"
#include "ofxFBOTexture.h"


#define VIDEO_WIDTH 320.0
#define VIDEO_HEIGHT 240.0
#define VIDEO_X 22.0
#define VIDEO_Y 133.0
#define VIDEO_SCALE 2.0
#define POINT_MARGIN 5
#define NORMALIZED_SELECT 0.004
#define XML_FILE "points.xml"

class Sensing  
{
	
public:
	
	Sensing();
	
	struct xsorter
    {
        bool operator()(Balloon * a, Balloon * b) const
        {
            if(a->getCenterX() < b->getCenterX())
			{
				return true;
			}
			
			return false;
        }
    };
	
	struct ysorter
    {
        bool operator()(Balloon * a, Balloon * b) const
        {
            if(a->getCenterY() < b->getCenterY())
			{
				return true;
			}
			
			return false;
        }
    };
	
	void update();
	void draw();
	
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	
	void toggleEnabled();
	void toggleMapFromScreen();
	void nextPage();
	void prevPage();
	
	vector <Balloon *> getBalloons();
	vector <Balloon *> getBalloonsSorted();
	bool getEnabled();
	int getPage();
	bool disableAnimation();
	
	void drawBalloon(float xPos, float yPos, int color);
	void loadBalloons();
	void saveBalloons();
	
	void keyPressed(int key);
	
private:
	
	void checkClick(float xPos, float yPos);
	int isClickWithinBalloon(float xPos, float yPos);
	bool isClickWithinVideo(float xPos, float yPos);
	void setBalloonDataToGUI();
	void deleteSelectedBalloon();
	
	
	float mapScreenXToVideoX(float xPos);
	float mapScreenYToVideoY(float yPos);
	float mapVideoXToScreenX(float xPos);
	float mapVideoYToScreenY(float yPos);
	float cleanMapVideoXToScreenX(float xPos);
	float cleanMapVideoYToScreenY(float yPos);
	
	ofImage _testImage;
	ofVideoGrabber  _camera;
	
	vector <Balloon *> _balloons;
	int _selectedBalloon;
	
	float _scalePosAll;
	float _xDisplaceAll;
	float _yDisplaceAll;
	float _scaleSizeAll;
	
	float _blobCalibrate;
	
	bool _blobMode;
	
	bool _constrainRatio;
	float _scaleWidthSelected;
	float _scaleHeightSelected;
	
	float _oldScaleWidthSelected;
	float _oldScaleHeightSelected;
	
	bool _mapFromScreen;

	int _enabled;
	int _idcount;
	
	ofxXmlSettings _xml;
	
	int _threshold;
	int _blurAmount;
	int _area;
	bool _showMask;
	
	ofxCvColorImage  _colorImg;
    ofxCvGrayscaleImage  _grayImg;
    ofxCvContourFinder  _contourFinder;
    ofxCvBlobTracker  _blobTracker;	
	ofxFBOTexture _outputTexture;
	ofImage _mask;
	unsigned char * _maskPixels;
	unsigned char * _grayPixels;
};