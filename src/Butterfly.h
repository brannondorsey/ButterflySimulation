//
//  Butterfly.h
//  ButterflyTest
//
//  Created by bdorse on 4/16/15.
//
//

#ifndef __ButterflyTest__Butterfly__
#define __ButterflyTest__Butterfly__

#include "ofMain.h"
#include "ofxTween.h"

class Butterfly{
    
public:
    
    Butterfly();
    ~Butterfly();
    
    void setup(const ofColor& color, const ofColor& shadowColor, const ofVec2f& size);
    void update();
    void draw();
    void homeTo(const ofVec3f& position);
    void setPosition(const ofVec3f& position);
    
    ofVec3f getPosition();
    
protected:
    
    bool _homing;
    bool _inAir;
    
    float _maxWingSpread;
    float _maxFlapSpeed;
    float _wingFlapDir;
    float _curWingTilt;
    float _maxSpeed;
    
    ofVec2f _size;
    ofVec3f _destination;
    ofVec3f _velocity;
    ofVec3f _acceleration;
    ofColor _color;
    ofColor _shadowColor;
    ofImage _image;
    ofPlanePrimitive _wing1;
    ofPlanePrimitive _wing2;
    
    ofxTween _homeTween;
    ofxEasingLinear _easingLinear;
};

#endif /* defined(__ButterflyTest__Butterfly__) */
