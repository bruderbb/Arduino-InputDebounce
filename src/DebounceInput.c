/*
Debounces the input pin
*/

#include <DebounceInput.h>

// constructors
// constructor for just the pin
DebounceInput::DebounceInput (
  const uint8_t   pin
)
{
  polarity_           = true;
  pin_                = pin;
  debounceInterval_   = 25;
  startTime_          = 0;
  currentState_       = polarity_;
  previousState_      = polarity_;
  pinStatus_          = polarity_;
  rose_               = false;
  fell_               = false;
}

DebounceInput::DebounceInput (
  const uint8_t   pin,
  const uint32_t  debounceInterval
)
{
  polarity_           = true;
  pin_                = pin;
  debounceInterval_   = debounceInterval;
  startTime_          = 0;
  currentState_       = polarity_;
  previousState_      = polarity_;
  pinStatus_          = polarity_;
  rose_               = false;
  fell_               = false;
}

DebounceInput::DebounceInput (
  const uint8_t   pin,
  const uint32_t  debounceInterval,
  const bool      polarity
)
{
  polarity_           = polarity;
  pin_                = pin;
  debounceInterval_   = debounceInterval;
  startTime_          = 0;
  currentState_       = polarity_;
  previousState_      = polarity_;
  pinStatus_          = polarity_;
  rose_               = false;
  fell_               = false;
}
