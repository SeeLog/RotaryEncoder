# RotaryEncoder library
RotaryEncoder library for Arduino Uno etc...

I checked the operation with [EC12PLRGBSDVBF-D-25K-24-24C-61](http://akizukidenshi.com/catalog/g/gP-05773/)

Example program is [here](https://github.com/SeeLog/RotaryEncoder/blob/master/src/main.cpp)

日本語の説明は[こちら](https://github.com/SeeLog/RotaryEncoder/blob/master/README.jp.md)

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

- Set increase and decrease value

```cpp
encoder.skipValue = 4;
```

If set this, the value will increase to `0, 4, 8, ...` and decrease to `0, -4, -8, ...`

- Value rotation
```cpp
encoder.isRotateValue = true;
```

If the max value is 10 and the min value is 0, the value will increase to `...,9,10,0,1,...` and decrease to `...,1,0,10,9,...`
