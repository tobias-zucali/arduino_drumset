/*
  Created by Tobias Zucali, May 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "tools.h"

#pragma GCC diagnostic ignored "-Wsizeof-array-argument"
int getSizeOf(const int someArray[]) {
  return sizeof(someArray) / sizeof(someArray[0]);
}

#pragma GCC diagnostic pop
