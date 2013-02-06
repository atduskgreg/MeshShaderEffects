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
    noiseShader.load("shaders/noise.vert", "shaders/noise.frag");
    shaderToApply = 2; // start with noise shader

    waveDirection = 0;
    waveFrequency = 1;
    noiseAmount = 5.0;

	cam.setDistance(500);
    
    glEnable(GL_DEPTH_TEST);
    
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
    
    if(shaderToApply == 1){
        sineShader.begin();
        sineShader.setUniform1f("time", ofGetElapsedTimef() );
        sineShader.setUniform1i("waveDirection", waveDirection );
        sineShader.setUniform1i("waveFrequency", waveFrequency );
    } else if(shaderToApply == 2){
        noiseShader.begin();
        noiseShader.setUniform1f("noiseAmount", noiseAmount);
        noiseShader.setUniform1f("time", ofGetElapsedTimef());
    }
    
    mesh.drawWireframe();
    
    if(shaderToApply == 1){
        sineShader.end();
    }else if(shaderToApply == 2){
        noiseShader.end();
    }
    
    cam.end();
    
    ofSetColor(255);

    stringstream s;
    s << "FPS: " << ofGetFrameRate() << "\n";
    if(shaderToApply == 1){
        s << "WAVE SHADER\n";
        s << "d   - toggle wave direction\n+/- - change wave frequency";
    } else if(shaderToApply == 2) {
        s << "NOISE SHADER\n";
        s << "+/- - change noise amount";
    } else {
        s << "NO SHADER";
    }
    
    s << "\ns - to toggle shaders";
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
    }
    
    if(key == 's'){
        shaderToApply++;
        if(shaderToApply > 2){
            shaderToApply = 0;
        }
    }
    
    if(key == '-'){
        if(shaderToApply == 1){
            waveFrequency--;
            if(waveFrequency < 1){
                waveFrequency = 1;
            }
        } else if(shaderToApply == 2){
            noiseAmount --;
            if(noiseAmount < 1){
                noiseAmount = 1;
            }
        }
    }
    
    if(key == '=' || key == '+'){
        if(shaderToApply == 1){
        waveFrequency++;
        } else if(shaderToApply == 2){
            noiseAmount ++;
        }
    }
    
    if(key == 'r'){
        if(shaderToApply == 1){
            sineShader.unload();
            sineShader.load("shaders/sine.vert", "shaders/sine.frag");
            cout << "sine shader reloaded" << endl;
        } else if(shaderToApply == 2){
            noiseShader.unload();
            noiseShader.load("shaders/noise.vert", "shaders/noise.frag");
            cout << "noise shader reloaded" << endl;
        }
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