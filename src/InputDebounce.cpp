/*
This arduino library is for debouncing an input pin.
Why I wrote my own lib instad of using one of the readily available ones like
"bounce"? Well, practice my friend ;) i'm just learning C++ and riting your own
code makes you better, faster and more knowledgeable! So if you find errors:
please report them so i can learn even more!
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
  previousReading_    = !signalPolarity_;
  currentPinStatus_   = !signalPolarity_;
  previousPinStatus_  = !signalPolarity_;
  rose_               = false;
  fell_               = false;
  active_             = false;
}


void InputDebounce::begin ()
{
  // does nothing atm
} // end of InputDebounce::begin


bool InputDebounce::update ()
{
  // variable for storing if the status has changed
  bool changed = false;
  // constant for storing the current time
  const uint32_t now = millis();
  // constant for storing the current pin status
  const bool currentReading = digitalRead(pin_);

  // change detected between two readings
  if (currentReading != previousReading_)
  {
    // input has changed lets get to it!
    // send debug-message (if debugging is activated)
    #ifdef INPUTDEBOUNCE_DEBUG
    Serial.println("Readings differ");
    #endif
    // Set the active_ bit to indicate a debounce is in progress
    active_ = true;
    // reset startTime_
    startTime_ = now;
    // nothing has changed.. so lets set it:
    changed = false;
  }

  // if the active_ bit is set start the comparisons
  if (active_)
  {
    // wraparound detection
    if (now < startTime_)
    {
      // send debug-message (if debugging is activated)
      #ifdef INPUTDEBOUNCE_DEBUG
      Serial.println("Wraparound detected");
      #endif

      // if the current time is smaller than startTime we have millis()-counter
      // wraparound: reset startTime_ to current time
      startTime_ = now;
      // exit this iteration and return false
      changed = false;
    }

    // the debounceInterval_ has elapsed
    else if ((now - startTime_) >= debounceInterval_)
    {
      // the output has not changed for the debounceInterval => stable input
      // send debug-message (if debugging is activated)
      #ifdef INPUTDEBOUNCE_DEBUG
      Serial.println    ("Debounce interval elapsed");
      #endif
      // debounceing has finished reset the active_ flag
      active_ = false;

      // save the current pin status as old one
      previousPinStatus_ = currentPinStatus_;
      #ifdef INPUTDEBOUNCE_DEBUG
      Serial.print    ("previousPinStatus_ now is ");
      Serial.print    (previousPinStatus_);
      Serial.println  ("...");
      #endif

      // set the new pinStatus_
      currentPinStatus_ = currentReading;
      #ifdef INPUTDEBOUNCE_DEBUG
      Serial.print    ("currentPinStatus_ now is ");
      Serial.print    (currentPinStatus_);
      Serial.println  ("...");
      #endif

      // if the currentPinStatus_ DID NOT change (maybe due to noise...)
      if (currentPinStatus_ == previousPinStatus_)
      {
        // reset all output variables
        #ifdef INPUTDEBOUNCE_DEBUG
        Serial.print    ("pin ");
        Serial.print    (pin_);
        Serial.println  (" did not change");
        #endif
        rose_   = false;
        fell_   = false;
        changed = false;
      }

      // if the currentPinStatus_ DID change we detected an edge
      else
      {
        // if currentPinStatus_ is equal to signalPolarity_ => rising edge
        if (currentPinStatus_ == signalPolarity_)
        {
          // we detected a rising edge
          // send debug-message (if debugging is activated)
          #ifdef INPUTDEBOUNCE_DEBUG
          Serial.print    ("pin ");
          Serial.print    (pin_);
          Serial.println  (" rose");
          #endif
          // update the outputs
          rose_ = true;
          fell_ = false;
          // remember: this is only set for one loop cycle
          // after that it will be reset!! (see "else" below)

          // an output has changed... set returnValue to true
          changed = true;
        }

        // if currentPinStatus_ is NOT equal to signalPolarity_ => falling edge
        else
        {
          // we detected a falling edge
          // send debug-message (if debugging is activated)
          #ifdef INPUTDEBOUNCE_DEBUG
          Serial.print    ("pin ");
          Serial.print    (pin_);
          Serial.println  (" fell");
          #endif
          // update the outputs
          fell_ = true;
          rose_ = false;
          // remember: this is only set for one loop cycle
          // after that it will be reset!! (see "else" below)

          // an output has changed... set returnValue to true
          changed = true;
        }
      }


      // set the new currentPinStatus_ to the currentReading
    }

    // nothing happened lets clean up
    else
    {
      rose_   = false;
      fell_   = false;
      changed = false;
    }
  }

  // the following things will be executed every loop iteration:
  // save the currentReading into previousReading_ variable for next iteration
  previousReading_ = currentReading;
  // return if anything has changed
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
  return currentPinStatus_;
} // end of InputDebounce::pressed


bool InputDebounce::released ()
{
  return !currentPinStatus_;
} // end of InputDebounce::released
