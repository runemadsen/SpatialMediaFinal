#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Sensing.h"
#include "AnimationHeads.h"
#include "AnimationCircles.h"
#include "AnimationVideoHeads.h"
#include "AnimationStars.h"
#include "AnimationSingingHeads.h"
#include "ofxMidi.h"

class testApp : public ofSimpleApp, public ofxMidiListener
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
	
	int selectedAnimation;
	
	vector <Animation *> animations;
	
	ofxMidiIn midiIn;
	
	void newMidiMessage(ofxMidiEventArgs& eventArgs);
	
};



#endif
	
