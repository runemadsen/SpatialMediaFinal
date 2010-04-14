#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Sensing.h"
#include "AnimationHeads.h"
#include "AnimationCircles.h"

class testApp : public ofSimpleApp
{
public:
    
	void setup();
    void update();
    void draw();
	
    void keyPressed( int key );
    void mouseMoved( int x, int y );
    void mouseDragged( int x, int y, int button );
    void mousePressed( int x, int y, int button );
    void mouseReleased();
	
    void blobOn( int x, int y, int id, int order );
    void blobMoved( int x, int y, int id, int order );
    void blobOff( int x, int y, int id, int order );
	
	Sensing * sensing;
	
	int displayMethod;
	int selectedAnimation;
	
	vector <Animation *> animations;
	
};



#endif
	
