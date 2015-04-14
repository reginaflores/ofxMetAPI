#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofSetFullscreen(true);
    
     //define the search term
     searchTerm = "blue";
     
     //define number of cols in the grid
     gridSize = 10;
    
     thumbSize = 100;
    
     //define the number of images
     numResults = 350;
     
     myAPI.searchByTerm(searchTerm, numResults);
    
     myAPI.downloadThumbs();
    
     myInfo = myAPI.getSearchResults();

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //scrolling
    
    float maxHeight = (float) myInfo.size() * thumbSize / gridSize - ofGetHeight();
    float ty = ofClamp(ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, -maxHeight), -maxHeight, 0);
    ofTranslate(0, ty);
    
    int index = 0;
    for(int i = 0; i<myInfo.size(); i++){
        
            
        int x = (index%gridSize)*thumbSize;
        int y = floor((float) index/gridSize)*thumbSize;
        
        if(myInfo[i]->hasImage()){
           myInfo[i]->assetImageThumb.draw(x,y,thumbSize,thumbSize);
            
           ofDrawBitmapString(myInfo[i]->medium.substr(0,10), x, y+20);
           
           index++;
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
