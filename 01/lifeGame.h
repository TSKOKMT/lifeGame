#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"
#include "ofxTskokmtTranslator.h"
#include "ofxTskokmtTool.h"
#include "ofxTskokmtMotion.h"

class lifeGame {
    
public:
    void setup(int width_, int height_);
    void update();
    void draw();
    void createGlider(ofPoint p_);
    void set(ofPoint p_, bool b_);
    void random();
    ofPoint getCellPosition(int xIndex_, int yIndex_);
    void destroy(int xIndex_, int yIndex_);
    
//private:
    int width, height;
    
    int size;
    vector<vector<bool>> cells, _cells, __cells;
    vector<vector<bool>> bDestroys;
    
    vector<vector<ofSoundPlayer>> sounds;
    
    ofFbo fbo;
    
    ofRectangle boundingBox;
    ofRectangle safeBox;
    ofRectangle scaleBox;
    ofRectangle shootBox, _shootBox;
    ofPoint min, max;
    int sampleNumOfMean;
    float strongnessOfEase;
    
    bool glider[4][3][3] = {
        {
            {1, 1, 1},
            {1, 0, 0},
            {0, 1, 0}
        }, {
            {1, 0, 0},
            {1, 0, 1},
            {1, 1, 0}
        }, {
            {0, 1, 0},
            {0, 0, 1},
            {1, 1, 1}
        }, {
            {0, 1, 1},
            {1, 0, 1},
            {0, 0, 1}
        }
    };
    
    ofColor colors[3];
    
    ofxTskokmtMath math;
    ofxTskokmtTranslator translator;
    ofxTskokmtTool tool;
    vector<vector<ofxTskokmtMotion>> motions;
    ofxTskokmtMath maths[3];
};
