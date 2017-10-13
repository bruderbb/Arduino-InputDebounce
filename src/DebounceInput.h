/*
Debounces the input pin
*/
#ifndef DEBOUNCEINPUT_H
#define DEBOUNCEINPUT_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class DebounceInput
{
  public:
    // constructors
    DebounceInput (
      const uint8_t   pin               // teh pin to use
    );

    DebounceInput (
      const uint8_t   pin,              // teh pin to use
      const uint32_t  debounceInterval  // the debounce interval lenth
    );

    DebounceInput (
      const uint8_t   pin,              // the pin to use
      const uint32_t  debounceInterval, // the debounce interval lenth
      const bool      polarity = true   // input polarity: true means HIGH = true
    );

    // methods
    void begin ();
    void update ();
    bool rose ();
    bool fell ();
    bool pressed ();
    bool released ();
    uint32_t pressedSince ();
    uint32_t releasedSince ();

  private:
    bool        polarity_;
    uint8_t     pin_;
    uint32_t    debounceInterval_;
    uint32_t    startTime_;
    bool        currentState_;
    bool        previousState_;
    bool        pinStatus_;
    bool        rose_;
    bool        fell_;

}; // end of class definition DebounceInput


#endif // end of include guard for DEBOUNCEINPUT_H
