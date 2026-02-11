#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <Arduino.h>

class SequenceArray {
  private:
    byte* _array;
    int _size;
  public:
    SequenceArray();
    
    void addToSequence(byte);
    byte getLastElement();
};

#endif