/*
Debounces the input pin
*/

#include <InputDebounce.h>

/* constructors */

// constructor for pin, debounceInterval and signalPolarity
InputDebounce::InputDebounce (
  const uint8_t   pin,
  const uint32_t  debounceInterval,
  const bool      signalPolarity
)
{
  signalPolarity_     = signalPolarity;
  pin_                = pin;
  debounceInterval_   = debounceInterval;
  startTime_          = 0;
  currentReading_     = signalPolarity_;
  previousReading_    = signalPolarity_;
  pinStatus_          = signalPolarity_;
  rose_               = false;
  fell_               = false;
}


void InputDebounce::begin ()
{
  currentReading_ = digitalRead(pin_);
  previousReading_ = currentReading_;
} // end of InputDebounce::begin


bool InputDebounce::update ()
{
  // variable for storing if the status has changed
  bool changed = false;
  // constant for storing the current time
  const uint32_t now = millis();

  // get current pin status
  currentReading_ = digitalRead(pin_);

  // change detected
  if (currentReading_ != previousReading_)
  {
    // input has changed
    // reset startTime_
    startTime_ = now;
    // set previousReading_ for next loop iteration
    previousReading_ = currentReading_;
    // exit this iteration and return false, since nothing could have changed
    changed = false;
  }


  else
  {
    // wraparound detection
    if (now < startTime_)
    {
      // if the current time is smaller than startTime we have millis()-counter
      // wraparound: reset startTime_ to current time
      startTime_ = now;
      // exit this iteration and return false
      changed = false;
    }

    // the debounceInterval_ elapsed
    if ((now - startTime_) >= debounceInterval_)
    {
      // the output has not changed for the debounceInterval we have a
      // stable input so we update currentButtonState with the value of reading
      pinStatus_ = currentReading_;

      // if currentButtonState > lastButtonState
      if (currentReading_ > previousReading_)
      {
        // we detected a rising edge
        // update the outputs
        rose_ = true;
        fell_ = false;
        // remember: this is only set for one loop cycle
        // after that it will be reset!! (see "else" below)

        // an output has changed... set returnValue to true
        changed = true;
      }

      // if currentButtonState < lastButtonState
      else if (currentReading_ < previousReading_)
      {
        // we detected a falling edge
        // update the outputs
        fell_ = true;
        rose_ = false;
        // remember: this is only set for one loop cycle
        // after that it will be reset!! (see "else" below)

        // an output has changed... set returnValue to true
        changed = true;
      }

      // no rising edge was detected reset the values
      else {
        fell_ = false;
        rose_ = false;
        changed = false;
      }
    }

    // nothing happened lets clean up
    else
    {
      changed = false;
    }
  }
  previousReading_ = currentReading_;
  return changed;
} // end of InputDebounce::update


bool InputDebounce::rose ()
{
  return rose_;
} // end of InputDebounce::rose


bool InputDebounce::fell ()
{
  return fell_;
} // end of InputDebounce::fell


bool InputDebounce::pressed ()
{
  return pinStatus_;
} // end of InputDebounce::pressed


bool InputDebounce::released ()
{
  return !pinStatus_;
} // end of InputDebounce::released
