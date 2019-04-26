/*
  Created by Tobias Zucali, May 2019.
  Released into the public domain.
*/

#include "NumberBuffer.h"
#include <LinkedList.h>


NumberBuffer::NumberBuffer(int maxSize = -1)
{
  _maxSize = maxSize;
  _buffer = LinkedList<int>();
}

void NumberBuffer::add(int value)
{
  _buffer.add(value);
  if (_maxSize > 0 && _buffer.size() > _maxSize) {
    _buffer.shift();
  }
}

int NumberBuffer::average()
{
  return this->sum() / _buffer.size();
}

int NumberBuffer::last()
{
  return _buffer.get(_buffer.size() - 1);
}

void NumberBuffer::setMaxSize(int maxSize)
{
  _maxSize = maxSize;
}

int NumberBuffer::sum()
{
  int size = _buffer.size();
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += _buffer.get(i);
  }
  return sum;
}

void NumberBuffer::clear()
{
  _buffer.clear();
}
