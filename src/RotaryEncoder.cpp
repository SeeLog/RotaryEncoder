#include "RotaryEncoder.h"

static RotaryEncoder *_instance;

/*
    pin1: encoder pin A
    pin2: encoder pin B

    Arduino Uno Example:
    pin1 = 2, pin2 = 3
*/
RotaryEncoder::RotaryEncoder(uint8_t pin1, uint8_t pin2)
{
    _instance = this;
    /*
        Initialize pins
    */
    m_pin1 = pin1;
    m_pin2 = pin2;

    m_maxval = INT16_MAX;
    m_minval = INT16_MIN;

    pinMode(m_pin1, INPUT_PULLUP);
    pinMode(m_pin2, INPUT_PULLUP);

    reset();
    attachPins();
}

/*
    Reset values
*/
void RotaryEncoder::reset()
{
    pos = 0;
    enc_count = 0;
}

/*
    Set maximum value
*/
void RotaryEncoder::setMaxValue(int maxval)
{
    m_maxval = maxval;
    enc_count = min(enc_count, m_maxval);
}

/*
    Set minimum value
*/
void RotaryEncoder::setMinValue(int minval)
{
    m_minval = minval;
    enc_count = max(enc_count, m_minval);
}

/*
    NOT for calling
*/
static void attachedInterrupt_RotaryEncoder()
{
    if (_instance != NULL)
    {
        _instance->updateValue();
    }
}

/*
    Attach interruptions
*/
void RotaryEncoder::attachPins()
{
    attachInterrupt(digitalPinToInterrupt(m_pin1), attachedInterrupt_RotaryEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(m_pin2), attachedInterrupt_RotaryEncoder, CHANGE);
}

/*
    Detach interruptions
*/
void RotaryEncoder::detachPins()
{
    detachInterrupt(digitalPinToInterrupt(m_pin1));
    detachInterrupt(digitalPinToInterrupt(m_pin2));
}

/*
    Finish process
*/
void RotaryEncoder::finish()
{
    detachPins();
}


/*
    Get rotation value
*/
int RotaryEncoder::getRotationValue()
{
    return enc_count;
}

/*
    This method is public, but
    NOT for call by main loop

    https://jumbleat.com/2016/12/17/encoder_1/
*/
void RotaryEncoder::updateValue()
{
    uint8_t cur = (!digitalRead(m_pin2) << 1) | !digitalRead(m_pin1);
    uint8_t old = pos & B00000011;
    uint8_t dir = (pos & B00110000) >> 4;

    if (cur == 3)
    {
        cur = 2;
    }
    else if (cur == 2)
    {
        cur = 3;
    }

    if (cur != old)
    {
        if (dir == 0)
        {
            if (cur == 1 || cur == 3)
            {
                dir = cur;
            }
        }
        else
        {
            if (cur == 0)
            {
                int skip = skipValue;
                if (skipValue < 0)
                {
                    skip = -skip;
                    /* swap by xor swap algorithm */
                    dir = dir ^ old;
                    old = dir ^ old;
                    dir = dir ^ old;
                }

                if (dir == 1 && old == 3)
                {
                    if (!isRotateValue)
                    {
                        enc_count = min(enc_count + skip, m_maxval);
                    }
                    else
                    {
                        if (enc_count + skip > m_maxval)
                        {
                            enc_count = m_minval + (enc_count + skip - m_maxval) - 1;
                        }
                        else
                        {
                            enc_count = enc_count + skip;
                        }
                    }
                }
                else if (dir == 3 && old == 1)
                {
                    if (!isRotateValue)
                    {
                        enc_count = max(enc_count - skip, m_minval);
                    }
                    else
                    {
                        if (enc_count - skip < m_minval)
                        {
                            enc_count = m_maxval + enc_count - skip + 1;
                        }
                        else
                        {
                            enc_count = enc_count - skip;
                        }
                    }
                }

                if (skipValue < 0)
                {
                    skip = -skip;
                    /* swap by xor swap algorithm */
                    dir = dir ^ old;
                    old = dir ^ old;
                    dir = dir ^ old;
                }

                dir = 0;
            }
        }

        pos = (dir << 4) + (old << 2) + cur;
    }
}


