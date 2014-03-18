#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(false);
    
#ifdef TARGET_OPENGLES
    consoleListener.setup(this);
#endif
	
	//this will let us just grab a video without recompiling
	ofDirectory currentVideoDirectory("videos");
    
	if (currentVideoDirectory.exists()) {
		currentVideoDirectory.listDir();
		vector<ofFile> files = currentVideoDirectory.getFiles();
		
		for (int i=0; i<files.size(); i++) {
            
#ifdef TARGET_OPENGLES
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
			players.push_back(player);
            states.push_back(false);
		}
	}
    
    nActive = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    int nChange = -1;
    
    for (int i = 0; i < states.size(); i++) {
        if((i==nKeyPressed)&&(!states[i])){
            states[i] = true;
            nChange = i;
            nActive = i;
            nKeyPressed = -1;
            break;
        }
    }
    
    if(nChange!= -1){
        cout << "Something change" << endl;
        for (int i = 0; i < players.size(); i++) {
            if (i==nChange) {
                states[i] = true;
#ifndef TARGET_OPENGLES
                players[i]->setPosition(0);
                players[i]->play();
#endif
            }else{
                states[i] = false;
#ifndef TARGET_OPENGLES
                players[i]->stop();
                players[i]->setPosition(0);
#endif
            }
            
#ifdef TARGET_OPENGLES
            players[i]->setPaused(!states[i]);
#endif
        }
    }
    
    
	if(nActive!=-1){
        players[nActive]->update();
    }
    
//    cout << "Change: " << nChange << endl;
//    cout << "Active: " << nActive << endl;
//    for (int i = 0; i < states.size(); i++) {
//        cout << " " << i << ":" << states[i];
//    }
//    cout << endl;
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);
	if(nActive!=-1){
        players[nActive]->draw(0,0,players[nActive]->getWidth()*-0.5,players[nActive]->getHeight()*-0.5);
    }
    ofPopMatrix();
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
    cout << "Key press " << key << endl;
    
    if(key > 47 ){
        nKeyPressed = key-48;
        cout << "Register " << nKeyPressed << endl;
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

