#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <Arduino.h>

class SequenceArray {
  private:
    String colors[4] = {"RED", "GREEN", "YELLOW", "BLUE"};
    String* _array;
    int _size;
  public:
    SequenceArray();
    
    void addToSequence();
    String getLastElement();
};

#endif