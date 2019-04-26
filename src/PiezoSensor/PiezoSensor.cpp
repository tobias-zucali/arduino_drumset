/*
  Connect a piezo to an analog input with 1 mega ohm resistor with ground.
  Created by Tobias Zucali, May 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "PiezoSensor.h"


const int NO_MOVEMENT = 0;
const int UP_MOVEMENT = 1;
const int DOWN_MOVEMENT = -1;

PiezoSensor::PiezoSensor(
  int pin,
  bool isReversed,
  int tolerance
) :
  _pin(pin),
  _tolerance(tolerance),
  _reverseMultiplier(isReversed ? -1 : 1)
{
  _maxRawValueBuffer.add(isReversed ? 0 : 1023);
}

void PiezoSensor::loop()
{
  _rawValueBuffer.add(analogRead(_pin));
  _rawValue = _rawValueBuffer.average() * _reverseMultiplier;
  int movement = this->_getMovement();

  switch (state) {
    case NOT_INITIALIZED:
      state = OFF;
      break;
    case OFF:
      if (movement == UP_MOVEMENT) {
        state = TURNING_ON;
        _minRawValue = _rawValue;
      }
      break;
    case TURNING_ON:
      if (movement == NO_MOVEMENT || _rawValue <= _minRawValue) {
        state = ON;
        _maxRawValueBuffer.add(_rawValue);
      }
      break;
    case ON:
      if (movement == DOWN_MOVEMENT || _rawValue <= _minRawValue) {
        state = TURNING_OFF;
      }
      break;
    case TURNING_OFF:
      if (movement == NO_MOVEMENT || _rawValue <= _minRawValue) {
        state = OFF;
      }
      break;
  }

  if (state == OFF) {
    value = 0;
  } else {
    value = constrain(
      map(
        _rawValue,
        _minRawValue,
        _maxRawValueBuffer.average(),
        0,
        255
      ),
      0,
      255
    );
  }
}

int PiezoSensor::_getMovement()
{
  int movement = NO_MOVEMENT;
  if ((_rawValue - _previousRawValue) > _tolerance) {
    movement = UP_MOVEMENT;
  }
  if ((_rawValue - _previousRawValue) < _tolerance * -1) {
    movement = DOWN_MOVEMENT;
  }
  _movementBuffer.add(movement);
  _previousRawValue = _rawValue;

  int isMovingSum = _movementBuffer.sum();
  if (isMovingSum > UP_MOVEMENT) {
    return UP_MOVEMENT;
  } else if (isMovingSum < DOWN_MOVEMENT) {
    return DOWN_MOVEMENT;
  } else {
    return NO_MOVEMENT;
  }
}
