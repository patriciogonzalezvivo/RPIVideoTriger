#pragma once

#include "ofMain.h"

#ifdef TARGET_OPENGLES
#include "ofAppEGLWindow.h"
#include "ConsoleListener.h"

#include "ofxOMXPlayer.h"
#include "ConsoleListener.h"

class ofApp : public ofBaseApp, public SSHKeyListener{
#else
class ofApp : public ofBaseApp{
#endif
    
public:
    void setup();
    void update();
    void draw();
    void exit();
	
	
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
	
#ifdef TARGET_OPENGLES
    void onCharacterReceived(SSHKeyListenerEventData& e);
	ConsoleListener consoleListener;
	
    vector<ofxOMXPlayer*> players;
#else
    vector<ofVideoPlayer*> players;
#endif

    vector<bool>    states;
    
    int nActive;
    int nKeyPressed;
};

