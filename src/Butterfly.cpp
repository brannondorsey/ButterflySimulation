//
//  Butterfly.cpp
//  ButterflyTest
//
//  Created by bdorse on 4/16/15.
//
//

#include "Butterfly.h"

Butterfly::Butterfly():
_maxWingSpread(120),
_maxFlapSpeed(2),
_wingFlapDir(1),
_curWingTilt(-180),
_bHoming(false),
_bInAir(true),
_maxSpeed(2.0),
_maxForce(0.1),
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
    
    // face wings towards _body's orientation
    _wing1.rotate(-90, ofVec3f(0, 1, 0));
    _wing2.rotate(-90, ofVec3f(0, 1, 0));
    
    _wing1.setParent(_body);
    _wing2.setParent(_body);
    
    _wing1.tilt(_curWingTilt);
    _wing2.tilt(_curWingTilt);
}
    
void Butterfly::update()
{
    if (_bInAir)
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
    
    if (_bHoming)
    {
        // apply homing force
        _steer();
        
        // apply acceleration to velocity
        // and update position by velocity
        _velocity += _acceleration;
        _velocity.limit(_maxSpeed);
        ofVec3f pos = _body.getPosition();
        pos += _velocity;
        _body.setPosition(pos);
        _acceleration.set(ofVec3f::zero());
    }
}

void Butterfly::draw()
{
    _body.ofNode::draw();
    _image.getTextureReference().bind();
    ofSetColor(_color);
    _wing1.draw();
    ofSetColor(_shadowColor);
    _wing2.draw();
}

void Butterfly::homeTo(const ofVec3f& position)
{
    _bHoming = true;
    _destination = position;
}

void Butterfly::setPosition(const ofVec3f& position)
{
    _body.setPosition(position);
}

void Butterfly::applyForce(const ofVec3f& force)
{
    // We could add mass here if we want A = F / M
    _acceleration += force;
}

ofVec3f Butterfly::getPosition()
{
    return _body.getPosition();
}

bool Butterfly::isHoming()
{
    return _bHoming;
}

bool Butterfly::isInAir()
{
    return _bInAir;
}

void Butterfly::_steer()
{
    // A vector pointing from the location to the target
    ofVec3f desired = _destination - _body.getPosition();
    
    float d = desired.length();
    
    // Scale with arbitrary damping within 100 pixels
    if (d < 100)
    {
        float m = ofMap(d, 0, 100, 0, _maxSpeed);
        desired.scale(m);
    } else
    {
        desired.scale(_maxSpeed);
    }
    
    // Steering = Desired minus Velocity
    ofVec3f steer = desired - _velocity;
    steer.limit(_maxForce);  // Limit to maximum steering force
    
    if (d > 1)
    {
        applyForce(steer);
    }
    else
    {
        // destination reached
        desired.set(ofVec3f::zero());
        _bHoming = false;
        _destination.set(ofVec3f::zero());
    }
}