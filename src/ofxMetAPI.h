#pragma once
#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxThreadedImageLoader.h"

class ofxMetAPIItem{
public:
    
    void assetMetaDownload();
    bool hasImage();
    
    int id;
    string href;
    string website_href;
    string title;
    string image_thumb;
    string artist;
    string date;
    string medium;
    string gallery;


    ofxJSONElement assetResult;
    
    string imageUrl;
    vector<string> whoList_name;
    vector<string> whatList_name;
    vector<string> whereList_name;
    vector<string> whenList_name;
    
    
    ofImage assetImageThumb;
    ofImage assetImage;
};


class ofxMetAPI {
public:
    void searchByTerm(string _searchTerm, int numberOfResults, bool randomize=false );
    void downloadThumbs();
    void downloadImages();
    
    vector<ofxMetAPIItem*> & getSearchResults();

    ofxJSONElement response;

    vector<ofxMetAPIItem*> searchItems;
    
    ofxThreadedImageLoader loader;


};
