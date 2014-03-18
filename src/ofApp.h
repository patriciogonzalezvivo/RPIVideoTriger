#pragma once

#include "ofMain.h"

struct Channel{
#ifdef TARGET_OPENGLES
    ofxOMXPlayer *  video;
#else
    ofVideoPlayer*  video;
#endif
    int             pin;
    bool            state;
};

#ifdef TARGET_OPENGLES
#include "ofAppEGLWindow.h"
#include "wiringPi.h"
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
#endif

    vector<Channel> channels;
    
    int nActive;
    int nKeyPressed;
};

