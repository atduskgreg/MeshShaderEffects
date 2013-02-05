#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    int grid = 25;
    int spacing = 25;
    
    for(int row = 0; row < grid; row++){
        for(int col = 0; col < grid; col++){
            ofVec3f v = ofVec3f(col*spacing, row*spacing, 0);
            mesh.addVertex(v);
            center.x += v.x;
            center.y += v.y;
            center.z += v.z;

            
            if(row < grid -1  && col < grid -1){
                int i = col + row*grid;
                mesh.addIndex(i);
                mesh.addIndex(i+1);
                mesh.addIndex(i+1+grid);
                
                mesh.addIndex(i);
                mesh.addIndex(i+1+grid);
                mesh.addIndex(i+grid);

            }
            
        }
    }
    
    center.x /= (float)(grid*grid);
    center.y /= (float)(grid*grid);
    center.z /= (float)(grid*grid);
    
    sineShader.load("shaders/sine.vert", "shaders/sine.frag");
    waveDirection = 0;
    waveFrequency = 1;

	cam.setDistance(500);

        
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(125);
    ofSetColor(0);
    cam.lookAt(center);

    cam.begin();
    
    
    sineShader.begin();
    sineShader.setUniform1f("time", ofGetElapsedTimef() );
    sineShader.setUniform1i("waveDirection", waveDirection );
    sineShader.setUniform1i("waveFrequency", waveFrequency );

    mesh.drawWireframe();
    sineShader.end();

    cam.end();
    
    ofSetColor(255);
    stringstream s;
    s << "FPS: " << ofGetFrameRate() << "\n";
    s << "d   - toggle wave direction\n+/- - change wave frequency";
    ofDrawBitmapString(s.str(), ofPoint(25,25));
    
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'd'){
        if(waveDirection == 0){
            waveDirection = 1;
        } else {
            waveDirection = 0;
        }
        cout << "waveDirection: " << waveDirection << endl;
    }
    
    if(key == '-'){
        waveFrequency--;
        if(waveFrequency < 1){
            waveFrequency = 1;
        }
    }
    
    if(key == '=' || key == '+'){
        waveFrequency++;
    }
    
    if(key == 'r'){
        sineShader.unload();
        sineShader.load("shaders/sine.vert", "shaders/sine.frag");
        cout << "sine shader reloaded" << endl;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

void testApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}