/*******************************************************************************
Debounces the input pin

*******************************************************************************/
#ifndef InputDebounce_H
  #define InputDebounce_H
  #if ARDUINO >= 100
    #include <Arduino.h>
    #else
    #include <WProgram.h>
  #endif // end of if ARDUINO


  #ifndef INPUTDEBOUNCE_DEBUG
    // uncomment the following line to enable debug messages
    //#define INPUTDEBOUNCE_DEBUG
  #endif

  class InputDebounce
  {
    public:
      /** constructors **/
      // constructor for pin, debounceInterval and signalPolarity
      InputDebounce (
        const uint8_t   pin,                    // the pin to use
        const uint32_t  debounceInterval = 25,  // the debounce interval lenth
        const bool      signalPolarity = true   // true means HIGH on pin is ON
      );

      /** methods **/
      // begin: starts the debouncing of the input pin
      void begin ();

      // update: checks the status of the input pin
      // run as often as possible (everey loop iteration)
      // returns true if status changed
      bool update ();

      // returns true if input just activated
      bool rose ();

      // returns true if input just deactivated
      bool fell ();

      // returns true if input is activated at the moment
      bool pressed ();

      // returns true if input is deactivated at the moment
      bool released ();


    private:
      bool        signalPolarity_;    // input polaarity
      uint8_t     pin_;               // pin number
      uint32_t    debounceInterval_;  // the debounce interval
      uint32_t    startTime_;         // the debounce start time
      bool        active_;            // if true there is a debounce in progress
      bool        previousReading_;   // the previously read pin value
      bool        currentPinStatus_;  // the calculated (debounced) state of the pin
      bool        previousPinStatus_; // the calculated (debounced) state of the pin last iteration
      bool        rose_;              // if the pin-level rose
      bool        fell_;              // if the pin level fell

  }; // end of class definition InputDebounce

#endif // end of include guard for InputDebounce_H
