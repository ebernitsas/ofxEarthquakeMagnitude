#include "ofApp.h"

struct circle{
    int x;
    int y;
    int r;
    int transp;
};

bool activateSize;

vector <circle> circles;
circle temp;
int activateEarthquake;
int currentIndex;

vector <float> magnitudes;

vector <int> buckets;

vector <int> radiiClicked;



int o;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    temp.y = 400;
    temp.r = 40;
    for (int i = 0; i < 9; i++){
        temp.x = 110 * (i+1) - 40;
        temp.transp = 70 + (((255-70)/9)*(i+1));
        circles.push_back(temp);
        
//        if (i == 0) circle.red, circle.green, circle.blue = 0xFD, 0x78, 0x7B;
//        if (i == 1) circle.red, circle.green, circle.blue = 0xE0, 0x5E, 0x61;
        
        
    }
    
    ofBackground(255, 255, 255);
    activateEarthquake = 0;
    activateSize = false;
    
    //CSV parse
    currentIndex = 0;
    
    //Path to the comma delimited file
    string filePath = "earthquakes.csv";
    
    //Load file placed in bin/data
    ofFile file(filePath);
    
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    ofBuffer buffer(file);
    
    //Read file line by line
    
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        //Split line into strings
        vector<string> words = ofSplitString(line, ",");
        
        magnitudes.push_back(ofToFloat(words[4]));
    }
    
    for (int i = 0; i < 9; i ++ ){
        buckets.push_back(0);
        radiiClicked.push_back(0);
    }
    
    for (int i = 0; i < magnitudes.size(); i++){
        if (magnitudes[i] < 2) buckets[0] += 1;
        else if (magnitudes[i] < 3) buckets[1] += 1;
        else if (magnitudes[i] < 4) buckets[2] += 1;
        else if (magnitudes[i] < 5) buckets[3] += 1;
        else if (magnitudes[i] < 6) buckets[4] += 1;
        else if (magnitudes[i] < 7) buckets[5] += 1;
        else if (magnitudes[i] < 8) buckets[6] += 1;
        else if (magnitudes[i] < 9) buckets[7] += 1;
        else if (magnitudes[i] >= 9) buckets[8] += 1;
    }
        

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < 9; i++){
        circles[i].x =110 * (i+1) - 40;
        circles[i].y = 400;
        //circles[i].r = 40;
        
    }
    //cout << "   "<< activateEarthquake << endl;
    int strength, strength2;
    if (activateEarthquake != 0){
        //cout << "activated" <<endl;
        for (int i = 0; i < 9; i++){
            strength = ofRandom(1,3*(i+1)); //1 or 2
            strength2 = ofRandom(1,3*(i+1));
            circles[i].x += strength;
            circles[i].y += strength2;
            if (radiiClicked[i] == 0) circles[i].r = 40;
        }
    }
    else
        for (int i = 0; i < 9; i++){
            circles[i].r = 40;
        }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetCircleResolution(100);
    //ofSetHexColor(A8383B);
    //ofSetColor(0,100,100);
    ofSetColor(168,56,59);
    
    if (activateSize == true) {
        for (int i = 0; i < 9; i++){
            circles[i].x += 60*(i+1);
            circles[i].r = buckets[i]/50;
            cout << buckets[i] <<endl;
        }
    }
    
    
    
    o = 20;
    
    for (int i = 0; i < 9; i++){
        ofSetColor(168,56,59,circles[i].transp);
        ofDrawCircle(circles[i].x, circles[i].y, circles[i].r);
        if (i == 0) ofDrawBitmapString("Micro", circles[i].x - o, circles[i].y + 150);
        else if (i == 1) ofDrawBitmapString("Minor", circles[i].x - o, circles[i].y + 150);
        else if (i == 2) ofDrawBitmapString("MinorII", circles[i].x - o, circles[i].y + 150);
        else if (i == 3) ofDrawBitmapString("Light", circles[i].x - o, circles[i].y + 150);
        else if (i == 4) ofDrawBitmapString("Moderate", circles[i].x - o, circles[i].y + 150);
        else if (i == 5) ofDrawBitmapString("Strong", circles[i].x - o, circles[i].y + 150);
        else if (i == 6) ofDrawBitmapString("Major", circles[i].x - o, circles[i].y + 150);
        else if (i == 7) ofDrawBitmapString("Great", circles[i].x - o, circles[i].y + 150);
        else if (i == 8) ofDrawBitmapString("GreatII", circles[i].x - o, circles[i].y + 150);
    }
    
    
    stringstream ss;
    ss << "(m) activate magnitude" << "\n";
    ss << "(b): back" << "\n";
    ss << "(s): stop vibrations" << "\n";
    ss << "click on dots to activate" << endl << "\n" << "\n" << "\n";
    ss << "2016 Earthquakes on Richter Magnitude Scale" << endl;
    ofDrawBitmapString(ss.str().c_str(), 20, 20);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case('m'): //make all of the dots relative size to the number of earthquakes
            activateSize = true;
            break;
        case('b'):
            //back to normal view
            activateSize = false;
            break;
        case('s'):
            activateEarthquake = 0;
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < 9; i ++){
        if (( circles[i].x - 40 <= x && x <= circles[i].x + 40) && (
            400-40 <=y && y <= 400+40)){
            circles[i].r += 30;
            
            activateEarthquake = i+1;
            
            cout << "clicked in circle" << "   "<< activateEarthquake << endl;
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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