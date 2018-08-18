#ifndef ROTARYENCODER_H_INCLUDE
#define ROTARYENCODER_H_INCLUDE

#include <Arduino.h>

class RotaryEncoder
{
    public:
        RotaryEncoder(uint8_t, uint8_t);
        void reset();
        int getRotationValue();
        void setMaxValue(int);
        void setMinValue(int);
        void updateValue();
        void finish();

        bool isRotateValue = false;
        int skipValue = 1;


    private:
        void attachPins();
        void detachPins();

        uint8_t m_pin1;
        uint8_t m_pin2;

        volatile uint8_t pos;
        volatile int enc_count;

        int m_maxval;
        int m_minval;
};

#endif