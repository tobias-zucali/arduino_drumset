/*
  Created by Tobias Zucali, May 2019.
  Released into the public domain.
*/

#ifndef NumberBuffer_h
#define NumberBuffer_h

#include "Arduino.h"
#include <LinkedList.h>


class NumberBuffer
{
  public:
    NumberBuffer(int maxSize);
    void add(int value);
    int average();
    int last();
    void setMaxSize(int maxSize);
    int sum();
    void clear();
  private:
    LinkedList<int> _buffer;
    int _maxSize;
};

#endif
