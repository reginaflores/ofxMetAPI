#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
     //define the search term
     searchTerm = "blue";
    
     //define the number of images
     numResults = 350;
     
     myAPI.searchByTerm(searchTerm, numResults);
    
     myAPI.downloadImages();
    
     myInfo = myAPI.getSearchResults();
    
     index = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    myInfo[index]->assetImage.draw(0,0);
    
    ofDrawBitmapString(myInfo[index]->title, myInfo[index]->assetImage.width+10, 10);
    ofDrawBitmapString(myInfo[index]->medium, myInfo[index]->assetImage.width+10, 30);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key==OF_KEY_LEFT){
    
        index = ofClamp(index-1, 0, myInfo.size()-1);
    } else if(key==OF_KEY_RIGHT){
    
        index = ofClamp(index+1, 0, myInfo.size()-1);
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
