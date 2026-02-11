#include "sequence.h"
#include <Arduino.h>

SequenceArray::SequenceArray() {
    _array = nullptr;
    _size = 0;
}   

void SequenceArray::addToSequence(byte element) {
    byte* newArray = new byte[_size + 1];
    
    for (int i = 0; i < _size; i++) {
        newArray[i] = _array[i];
    }
    
    newArray[_size] = element;
    
    delete[] _array;
    _array = newArray;
    _size++;
}

byte SequenceArray::getLastElement() {
    if (_size > 0) {
        return _array[_size - 1];
    }
    return byte(-1); // Return -1 if the sequence is empty
}