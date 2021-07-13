#include "lifeGame.h"

//--------------------------------------------------------------
void lifeGame::setup(int width_, int height_) {
    
    width = width_, height = height_;
    
    fbo.allocate(width * 2, height * 2);
    boundingBox = ofRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    safeBox = ofRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    shootBox = ofRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    _shootBox = shootBox;
    size = 30;
    for (int y = 0; y < fbo.getHeight(); y += size) {
        cells.push_back(vector<bool>());
        motions.push_back(vector<ofxTskokmtMotion>());
        //sounds.push_back(vector<ofSoundPlayer>());
        for (int x = 0; x < fbo.getWidth(); x += size) {
            cells.back().push_back(bool());
            //cells.back().back() = int(ofRandom(7)) == 0;
            motions.back().push_back(ofxTskokmtMotion());
            /*sounds.back().push_back(ofSoundPlayer());
            sounds.back().back().load(ofToString(int(ofRandom(9))) + ".mp3");
            sounds.back().back().setLoop(false);*/
        }
    }
    __cells = _cells = cells;
    sampleNumOfMean = 120;
    strongnessOfEase = 0.1;

    colors[0].setHex(0xff0049);
    colors[1].setHex(0x000000);
    colors[2].setHex(0x0000ff);
}

//--------------------------------------------------------------
void lifeGame::update() {
    
    //update cells
    /*vector<vector<bool>> memoOfCells = cells;
    for (int y = 0; y < cells.size(); y++) {
        for (int x = 0; x < cells[y].size(); x++) {
            int numOfNeighbors = 0;
            for (int j = y - 1; j <= y + 1; j++) {
                for (int i = x - 1; i <= x + 1; i++) {
                    if (i == x && j == y) continue;
                    int memoOfI = i, memoOfJ = j;
                    memoOfI = (memoOfI + cells.front().size()) % cells.front().size();
                    memoOfJ = (memoOfJ + cells.size()) % cells.size();
                    if (cells[memoOfJ][memoOfI]) numOfNeighbors++;
                }
            }
            if (!cells[y][x] && numOfNeighbors == 3) memoOfCells[y][x] = true;
            if (cells[y][x] && numOfNeighbors != 2 && numOfNeighbors != 3) memoOfCells[y][x] = false;
        }
    }
    cells = memoOfCells;*/
    
    //update shootBox
    int numOfBirth = 0;
    for (int y = 0; y < cells.size(); y++) {
        for (int x = 0; x < cells[y].size(); x++) {
            if (cells[y][x] && !_cells[y][x] && !__cells[y][x]) numOfBirth++;
        }
    }
    if (numOfBirth > 0) {
        min = ofPoint(INT_MAX, INT_MAX), max = ofPoint(INT_MIN, INT_MIN);
        for (int y = 0; y < cells.size(); y++) {
            for (int x = 0; x < cells[y].size(); x++) {
                if (cells[y][x] && !_cells[y][x] && !__cells[y][x]) {
                    int memoOfX = x * size, memoOfY = y * size;
                    memoOfX = math.loop(memoOfX, safeBox.getLeft(), safeBox.getRight());
                    memoOfY = math.loop(memoOfY, safeBox.getTop(), safeBox.getBottom());
                    if (memoOfX < min.x) min.x = memoOfX;
                    if (memoOfY < min.y) min.y = memoOfY;
                    if (memoOfX > max.x) max.x = memoOfX;
                    if (memoOfY > max.y) max.y = memoOfY;
                }
            }
        }
    }
    boundingBox = ofRectangle(min, max.x - min.x, max.y - min.y);
    safeBox = tool.getCenteredRect(boundingBox.getCenter(), fbo.getWidth(), fbo.getHeight());
    safeBox.position = math.loop(safeBox.position, ofPoint(0, 0), ofPoint(fbo.getWidth() , fbo.getHeight()));
    boundingBox = tool.getCenteredRect(safeBox.getCenter(), boundingBox.width, boundingBox.height);
    scaleBox = translator.getSmartFilledRectangle(ofRectangle(0, 0, fbo.getWidth(), fbo.getHeight()), boundingBox);
    scaleBox = tool.getCenteredRect(scaleBox.getCenter(), ofClamp(scaleBox.width * (18 / 16.), fbo.getWidth() / 2., fbo.getWidth()), ofClamp(scaleBox.height * (18 / 16.), fbo.getHeight() / 2., fbo.getHeight()));
    if (maths[0].stackedPoints.size() > 0) {
        ofPoint diff = ofPoint(0, 0);
        if (scaleBox.x - maths[0].stackedPoints.front().x > fbo.getWidth() / 2.) diff += ofPoint(fbo.getWidth(), 0);
        if (scaleBox.y - maths[0].stackedPoints.front().y > fbo.getHeight() / 2.) diff += ofPoint(0, fbo.getHeight());
        if (maths[0].stackedPoints.front().x - scaleBox.x > fbo.getWidth() / 2.) diff -= ofPoint(fbo.getWidth(), 0);
        if (maths[0].stackedPoints.front().y - scaleBox.y > fbo.getHeight() / 2.) diff -= ofPoint(0, fbo.getHeight());
        for (int i = 0; i < maths[0].stackedPoints.size(); i++) {
            maths[0].stackedPoints[i] += diff;
        }
    }
    shootBox = ofRectangle(maths[0].meanFilter(scaleBox.position, sampleNumOfMean), maths[1].meanFilter(scaleBox.width, sampleNumOfMean), maths[2].meanFilter(scaleBox.height, sampleNumOfMean));
    if (shootBox.x - _shootBox.x > fbo.getWidth() / 2.) _shootBox.x += fbo.getWidth();
    if (shootBox.y - _shootBox.y > fbo.getHeight() / 2.) _shootBox.y += fbo.getHeight();
    if (_shootBox.x - shootBox.x > fbo.getWidth() / 2.) _shootBox.x -= fbo.getWidth();
    if (_shootBox.y - shootBox.y > fbo.getHeight() / 2.) _shootBox.y -= fbo.getHeight();
    shootBox = ofRectangle(_shootBox.position + (shootBox.position - _shootBox.position) * strongnessOfEase, _shootBox.getWidth() + (shootBox.getWidth() - _shootBox.getWidth()) * strongnessOfEase, _shootBox.getHeight() + (shootBox.getHeight() - _shootBox.getHeight()) * strongnessOfEase);
    shootBox.position = math.loop(shootBox.position, ofPoint(0, 0), ofPoint(fbo.getWidth() , fbo.getHeight()));
    _shootBox = shootBox;

    //update sounds
    /*for (int y = 0; y < sounds.size(); y++) {
        for (int x = 0; x < sounds[y].size(); x++) {
            if (cells[y][x] && !_cells[y][x] && !__cells[y][x] && !sounds[y][x].isPlaying()) {
                ofPoint positionInShootBox = math.loop((ofPoint(x, y) + .5) * size, shootBox.getCenter() - ofPoint(fbo.getWidth(), fbo.getHeight()) / 2., shootBox.getCenter() + ofPoint(fbo.getWidth(), fbo.getHeight()) / 2.);
                sounds[y][x].setVolume(ofMap(ofDist(positionInShootBox, shootBox.getCenter()), 0, sqrt(fbo.getWidth() * fbo.getHeight()) / 2., 1, .2));
                sounds[y][x].setPan(ofMap(positionInShootBox.x, shootBox.getLeft(), shootBox.getRight(), -1, 1));
                sounds[y][x].play();
            }
        }
    }*/

    //update fbo
    fbo.begin();
    ofClear(0);
    ofSetColor(colors[0]);
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    if (fbo.getWidth() / size != 0) ofScale(fbo.getWidth() / ((cells[0].size() - 1) * size), 1);
    for (int y = 0; y < cells.size(); y++) {
        for (int x = 0; x < cells[y].size(); x++) {
            if (cells[y][x]/* && !_cells[y][x] && !__cells[y][x]*/) motions[y][x].begin(1000, true, true, 0);
            if (motions[y][x].isFinished() || !motions[y][x].isBegun()) continue;
            float ratio = motions[y][x].power(2);
            ofSetColor(tool.gradientColor(colors[2], colors[1], ratio, 1));
            ofDrawCircle((x + .5) * size + size / 2. * sin(ofGetElapsedTimef() * PI + x + y) * pow(1 - ratio, 2), (y + .5) * size - size / 2. * pow(1 - ratio, 3), size / 2. * ratio);
        }
    }
    fbo.end();
    
    //update cells history
    __cells = _cells;
    _cells = cells;
}

//--------------------------------------------------------------
void lifeGame::draw() {
    
    //draw fbo
    ofPushMatrix();
    translator.disSmartFill(ofRectangle(0, 0, width, height), shootBox);
    ofSetColor(255);
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            fbo.draw(fbo.getWidth() * i, fbo.getHeight() * j);
        }
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void lifeGame::createGlider(ofPoint p_) {
    
    //create glider
    translator.reset();
    translator.disSmartFill(ofRectangle(0, 0, width, height), shootBox);
    ofPoint pressedPosition = translator.getDisTranslatedPosition(p_) / (float)size;
    int k = ofRandom(4);
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            int memoOfX = pressedPosition.x + (i - 1), memoOfY = pressedPosition.y + (j - 1);
            memoOfX = (memoOfX + cells.front().size()) % cells.front().size();
            memoOfY = (memoOfY + cells.size()) % cells.size();
            cells[memoOfY][memoOfX] = glider[k][j][i];
        }
    }
}

//--------------------------------------------------------------
void lifeGame::set(ofPoint p_, bool b_) {
    
    translator.reset();
    translator.disSmartFill(ofRectangle(0, 0, width, height), shootBox);
    ofPoint pressedPosition = translator.getDisTranslatedPosition(p_) / (float)size;
    cells[(int)pressedPosition.y % cells.size()][(int)pressedPosition.x % cells.front().size()] = b_;
}

//--------------------------------------------------------------
void lifeGame::random() {
    
    vector<ofPoint> points;
    for (int i = 0; i < 100; i++) {
        int y = ofRandom(cells.size() - 1);
        int x = ofRandom(cells[0].size() - 1);
        /*for (int j = -1; j <= 1; j++) {
            cells[y + j][x] = true;
        }*/
        cells[y][x] = true;
        cells[y + 1][x] = true;
        cells[y][x + 1] = true;
        cells[y + 1][x + 1] = true;
    }
 
    /*for (int y = 0; y < cells.size(); y++) {
        for (int x = 0; x < cells[y].size(); x++) {
            cells[y][x] = (int)ofRandom(2);
        }
    }*/
}
