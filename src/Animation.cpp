#include "Animation.h"

/* Constructor
___________________________________________________________ */

Animation::Animation()
{
	_usingControllers = false;
	
	// first balloon gets 61, next 63, etc...
	_midiNotes.push_back(61);
	_midiNotes.push_back(62);
	_midiNotes.push_back(63);
	_midiNotes.push_back(64);
	_midiNotes.push_back(67);
}

/* add / update / delete controllers with models
___________________________________________________________ */

void Animation::compareBalloonsToControllers()
{
	if(_usingControllers)
	{
		// first delete controllers with missing point
		for (int i = _controllers.size() - 1; i >= 0; i--) 
		{
			bool found = false;
			
			for (int j = 0; j < _points.size(); j++) 
			{
				if(_controllers[i]->getModel()->getID() == _points[j]->getID())
				{
					found = true;
					
					break;
				}
			}
			
			if(!found)
			{
				_controllers.erase(_controllers.begin() + i);
			}
		}
		
		// then update or create new controller
		for(int i = 0; i < _points.size(); i++)
		{
			bool found = false;
			
			for (int j = 0; j < _controllers.size(); j++) 
			{
				if(_points[i]->getID() == _controllers[j]->getModel()->getID())
				{
					_controllers[j]->setModel(_points[i]);
					
					found = true;
					
					break;
				}
			}
			
			if(!found)
			{				
				_controllers.push_back(getNewController(_points[i]));
				
				// automatically assign midi note
				if(_midiNotes.size() >= _controllers.size())
				{
					_controllers[_controllers.size() - 1]->setMidiNote(_midiNotes[_controllers.size() - 1]);
				}
			}
		}
	}
}

/* MIDI
 ___________________________________________________________ */

void Animation::newMidiMessage(ofxMidiEventArgs& eventArgs)
{
	if(_usingControllers)
	{
		BalloonController * b;
		
		for(int i = 0; i < _controllers.size(); i++)
		{
			if(_controllers[i]->getMidiNote() == eventArgs.byteOne)
			{
				if(eventArgs.status == MIDI_NOTE_ON)
				{
					_controllers[i]->noteOn();
				}
				else if(eventArgs.status == MIDI_NOTE_OFF)
				{
					_controllers[i]->noteOff();
				}
				else 
				{
					printf("ERROR: Midi message neither on or off");
				}

				
				break;
			}
		}
	}
}

/* Getter / Setter
___________________________________________________________ */

void Animation::setBalloons(vector <Balloon *> points)
{
	_points = points;
}
