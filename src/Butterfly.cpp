//
//  Butterfly.cpp
//  ButterflyTest
//
//  Created by bdorse on 4/16/15.
//
//

#include "Butterfly.h"

Butterfly::Butterfly():
_maxWingSpread(55),
_maxFlapSpeed(2),
_wingFlapDir(1),
_curWingTilt(-180),
_homing(false),
_inAir(true),
_maxSpeed(2.0),
_velocity(0.0),
_acceleration(0.0),
_destination(ofVec3f::zero())
{
    
}

Butterfly::~Butterfly()
{
    
}

void Butterfly::setup(const ofColor& color, const ofColor& shadowColor, const ofVec2f& size)
{
    _color = color;
    _shadowColor = shadowColor;
    _size = size;
    _size.y *= 2.0;
    _image.loadImage(ofToDataPath("wing_empty_space.png"));
    _image.resize(_size.x, _size.y);
    
    _wing1.resizeToTexture(_image.getTextureReference());
    _wing2.resizeToTexture(_image.getTextureReference());
    
    _wing1.tilt(_curWingTilt);
    _wing2.tilt(_curWingTilt);
}
    
void Butterfly::update()
{

    if (_inAir)
    {
        if (_curWingTilt < -180 || _curWingTilt > -180 + _maxWingSpread)
        {
            _wingFlapDir = -_wingFlapDir;
        }
        
        float step = _maxFlapSpeed * _wingFlapDir;
        _wing1.tilt(step);
        _wing2.tilt(-step);
        
        _curWingTilt = _wing1.getPitch();
    }
    
    if (_homing)
    {
        
    }
}

void Butterfly::draw()
{
    ofSetColor(_color);
    _image.getTextureReference().bind();
    _wing1.draw();
    ofSetColor(_shadowColor);
    _wing2.draw();
}

void Butterfly::homeTo(const ofVec3f& position)
{
    _destination = position;
    _homeTween.setParameters(1, _easingLinear, ofxTween::easeInOut, getPosition(), <#float to#>, <#unsigned int duration#>, <#unsigned int delay#>)
}

void Butterfly::setPosition(const ofVec3f& position)
{
    _wing1.setPosition(position);
    _wing2.setPosition(position);
}

ofVec3f Butterfly::getPosition()
{
    return _wing1.getPosition();
}