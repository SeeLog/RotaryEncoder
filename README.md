# RotaryEncoder library
RotaryEncoder library for Arduino Uno etc...

Example program is [here](https://github.com/SeeLog/RotaryEncoder/blob/master/src/main.cpp)
日本語の説明はこちら

## Tutorial

### 1. Copy library files to your project
- RotaryEncoder.h
- RotaryEncoder.cpp

### 2. Include library
```cpp
#include "RotaryEncoder.h"
```

### 3. Set up
  
  1. define interruptable pin numbers
  ```cpp
  #define PIN_A 2
  #define PIN_B 3
  ```
  2. define and initialize RotaryEncoder object
  ```cpp
  RotaryEncoder encoder = RotaryEncoder(PIN_A, PIN_B);
  ```
  
### 4. Get encoded value
```cpp
int val = encoder.getRotationValue();
```

## Other
- Set max value and min value

```cpp
encoder.setMaxValue(255);
encoder.setMinValue(0);
```

- Set increase and decrese value

```cpp
encoder.skipValue = 4;
```

If set this, the value will increse 0, 4, 8, ... and decrese 0, -4, -8, ...
