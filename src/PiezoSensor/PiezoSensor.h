/*
  Connect a piezo to an analog input with 1 mega ohm resistor with ground.
  Created by Tobias Zucali, May 2019.
  Released into the public domain.
*/

#ifndef PiezoSensor_h
#define PiezoSensor_h

#include "Arduino.h"
#include "../NumberBuffer/NumberBuffer.h"


class PiezoSensor
{
  public:
    PiezoSensor(int pin, bool isReversed = true, int tolerance = 1);
    void loop();
    int state = NOT_INITIALIZED;
    int value;

    static const int NOT_INITIALIZED = -1;
    static const int OFF = 0;
    static const int TURNING_ON = 1;
    static const int ON = 2;
    static const int TURNING_OFF = 3;
  private:
    int _getMovement();
    int _rawValue;
    int _reverseMultiplier;
    const int _pin;
    const int _tolerance;
    int _staleRawValue;
    int _minRawValue;
    int _previousRawValue;
    NumberBuffer _rawValueBuffer = NumberBuffer(3);
    NumberBuffer _movementBuffer = NumberBuffer(3);
    NumberBuffer _maxRawValueBuffer = NumberBuffer(10);
};

#endif
