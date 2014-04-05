#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);
    
    //  BCM
    //
    int pinMax = 4;
    int pinMap[4] = {18,27,22,23};
    
#ifdef TARGET_OPENGLES
    consoleListener.setup(this);
    if(wiringPiSetupSys() == -1){
        printf("Error on wiringPi setup\n");
        return;
    }
#endif
	
	//this will let us just grab a video without recompiling
	ofDirectory currentVideoDirectory("videos");
    
	if (currentVideoDirectory.exists()) {
		currentVideoDirectory.listDir();
		vector<ofFile> files = currentVideoDirectory.getFiles();
		
		for (int i=0; i<files.size(); i++) {
            
            if(i>=pinMax)
                break;
            
            Channel newChannel;
            newChannel.pin = pinMap[i];
#ifdef TARGET_OPENGLES

            //  Pins
            pinMode(newChannel.pin, INPUT);
            
            //  Video Player
			ofxOMXPlayerSettings settings;
			settings.videoPath = files[i].path();
			settings.useHDMIForAudio = true;	//default true
			settings.enableTexture = true;		//default true
			settings.enableLooping = false;		//default true
			settings.enableAudio = false;		//default true, save resources by disabling
			ofxOMXPlayer* player = new ofxOMXPlayer();
			player->setup(settings);
#else
            ofVideoPlayer *player = new ofVideoPlayer();
            player->loadMovie(files[i].path());
#endif
            newChannel.video = player;
            newChannel.state = false;
			channels.push_back(newChannel);
		}
	}
    
    nActive = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    int nChange = -1;
    
    for (int i = 0; i < channels.size(); i++) {
        if((i==nKeyPressed)&&(!channels[i].state)){
            channels[i].state = true;
            nChange = i;
            nActive = i;
            nKeyPressed = -1;
            break;
        }
    }
    
    if(nChange!= -1){
        for (int i = 0; i < channels.size(); i++) {
            if (i==nChange) {
                channels[i].state = true;
#ifndef TARGET_OPENGLES
                channels[i].video->setPosition(0);
                channels[i].video->play();
#endif
            }else{
                channels[i].state = false;
#ifndef TARGET_OPENGLES
                channels[i].video->stop();
                channels[i].video->setPosition(0);
#endif
            }
            
#ifdef TARGET_OPENGLES
            channels[i]->video->setPaused(!channels[i].state);
#endif
        }
        
        cout << "Change to channel " << nChange << endl;
        for (int i = 0; i < channels.size(); i++) {
            cout << " " << channels[i].pin << ":" << channels[i].state;
        }
        cout << endl;

    }
    
    
	if(nActive!=-1){
#ifndef TARGET_OPENGLES
        channels[nActive].video->update();
#endif
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);
	if(nActive!=-1){
        channels[nActive].video->draw(0,0,
                                      channels[nActive].video->getWidth()*-0.5,
                                      channels[nActive].video->getHeight()*-0.5);
    }
    ofPopMatrix();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 15,15);
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------

#ifdef TARGET_OPENGLES
void ofApp::onCharacterReceived(SSHKeyListenerEventData& e){
	keyPressed((int)e.character);
}
#endif

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key > 47 ){
        nKeyPressed = key-48;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

