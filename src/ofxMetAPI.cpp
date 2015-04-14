#include "ofxMetAPI.h"

//--------------------------------------------------------------
void ofxMetAPI::searchByTerm(string searchTerm, int numberOfResults, bool randomize){

    int numPages;
    if (randomize) {
        string scrapiUrl = "http://scrapi.org/search/" + searchTerm;
        if (!response.open(scrapiUrl)) {
            ofLogNotice("ofApp::setup") << "Failed to parse JSON";
        }else{
            string lastPage = response["_links"]["last"]["href"].asString();
            cout << "last page " << lastPage << endl;
            vector<string> lastPageString = ofSplitString(lastPage, "page=");
            cout << ofToString(lastPageString) << endl;
            numPages = ofToInt(lastPageString[lastPageString.size()-1]);
            cout << "num pages " << numPages << endl;
        }
    }
    
    int pageNum = 1;
    searchItems.clear();
    
    while(searchItems.size() < numberOfResults){
        
        string scrapiUrl;
            if(randomize == true){
                
                 scrapiUrl = "http://scrapi.org/search/" + searchTerm + "?page=" + ofToString((int)ofRandom(numPages));
                
            }else{
                scrapiUrl = "http://scrapi.org/search/" + searchTerm + "?page=" + ofToString(pageNum);
            }
        
            cout << "Processing page " << pageNum << endl;
        
            if (!response.open(scrapiUrl)) {
                ofLogNotice("ofApp::setup") << "Failed to parse JSON";
            }else{
                
                try {
                    if(response.isNull() || response["collection"].isNull() || response["collection"]["items"].isNull()){
                        cout << "Response Failed" << endl;
                        return;
                    }
                }
                catch(runtime_error &e) {
                    cout << e.what() << endl;
                    cout << "Response Failed" << endl;
                    return;
                }
                
                
                for(int i=0; i < response["collection"]["items"].size(); i++){
                    
                    
                    
                    ofxMetAPIItem *temp = new ofxMetAPIItem();
                    searchItems.push_back(temp);
                    
                    temp->id = response["collection"]["items"][i]["id"].asInt();
                    temp->href = response["collection"]["items"][i]["href"].asString();
                    temp->website_href = response["collection"]["items"][i]["website_href"].asString();
                    temp->title = response["collection"]["items"][i]["title"].asString();
                    temp->image_thumb = response["collection"]["items"][i]["image_thumb"].asString();
                    temp->artist = response["collection"]["items"][i]["artist"].asString();
                    temp->date = response["collection"]["items"][i]["date"].asString();
                    temp->medium = response["collection"]["items"][i]["medium"].asString();
                    temp->gallery = response["collection"]["items"][i]["gallery"].asString();
                    
                    if(searchItems.size() >= numberOfResults){
                        return;
                    }

                }

            }
        
        pageNum++;
        
    }
    
    
}
//--------------------------------------------------------------
vector<ofxMetAPIItem*> & ofxMetAPI::getSearchResults(){


    return searchItems;


}
//--------------------------------------------------------------
void ofxMetAPI::downloadThumbs(){

    for(int i=0; i < searchItems.size(); i++){
        if(searchItems[i]->hasImage() == true){
            loader.loadFromURL(searchItems[i]->assetImageThumb, searchItems[i]->image_thumb);
        }
    }
    
}
//--------------------------------------------------------------
void ofxMetAPI::downloadImages(){
    
    for(int i=0; i < searchItems.size(); i++){
        if(searchItems[i]->hasImage() == true)
        {
            string image_large = searchItems[i]->image_thumb;
            ofStringReplace(image_large, "web-thumb","web-large");
            loader.loadFromURL(searchItems[i]->assetImage, image_large);
            
        }
    }
    
}
//--------------------------------------------------------------
bool ofxMetAPIItem::hasImage(){
    
    //LIMITING JSON CALLS BY DISREGARDING ITEMS W/ NO IMAGE
    if(image_thumb == "http://metmuseum.org/content/img/placeholders/NoImageAvailable_180x180_frame.png"){
    
        return false;
    }else{
    
        return true;
    }
       
}
//--------------------------------------------------------------
void ofxMetAPIItem::assetMetaDownload(){

    
    if (!assetResult.open(href) || assetResult.isNull()) {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON";
    }else{
    
        try {
        
            if(assetResult["imageUrl"].isNull() ||
               assetResult["publicAccess"].asBool() == 0 ||
               assetResult["isOasc"].asBool() == 0){
                cout << "No image available" << endl;
            }else{
                imageUrl = assetResult["currentImage"]["imageUrl"].asString();
            }
            
            if(assetResult["whoList"].isNull()){
                cout << "No who_List" << endl;
            }else{
                
                for(int i = 0; i < assetResult["whoList"].size(); i++){
                    whoList_name.push_back(assetResult["whoList"][i]["name"].asString());
                    cout << "added wholist"<< i << endl;
            
                }
            }
        
            if(assetResult["whatList"].isNull()){
                cout << "No what_List" << endl;
            }else{
                
                for(int i = 0; i < assetResult["whatList"].size(); i++){
                    whatList_name.push_back(assetResult["whatList"][i]["name"].asString());
                    cout << "added whatlist"<< i << endl;
                    
                }
            }

            if(assetResult["whereList"].isNull()){
                cout << "No where_List" << endl;
            }else{
                
                for(int i = 0; i < assetResult["whereList"].size(); i++){
                    whereList_name.push_back(assetResult["whereList"][i]["name"].asString());
                    cout << "added wherelist"<< i << endl;
                    
                }
            }

         
            if(assetResult["whenList"].isNull()){
                cout << "No when_List" << endl;
            }else{
                
                for(int i = 0; i < assetResult["whenList"].size(); i++){
                    whenList_name.push_back(assetResult["whenList"][i]["name"].asString());
                    cout << "added whenlist"<< i << endl;
                    
                }
            }


        }
        catch(runtime_error &e) {
            cout << "ERROR!! " <<e.what() << endl;
            ofSleepMillis(5000);
        }
        
    
    }

}
//--------------------------------------------------------------


