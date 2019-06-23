#include "ForceSensor.h"

void ForceSensor::service(int rotation) {
    this->val = map(analogRead(this->pin), 0, 1023, 0, 10);

    if (this->val != 2) {
        if (this->val <= 1 && this->correctionVal >= 0) 
            this->correctionVal -=5;
        else if (this->correctionVal <= rotation) {
            if (this->val < 4) 
                this->correctionVal += 2;
            else if (this->val < 8)
                this->correctionVal += 6;
            else if (this->val <= 10) 
                this->correctionVal += 12;    
        }
    }

    if (this->correctionVal <= 0) 
        this->correctionVal = 0;
    else if (this->correctionVal > rotation)
        this->correctionVal = rotation;
}