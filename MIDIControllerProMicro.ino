#include "frequencyToNote.h"
#include "MIDIUSB.h"
#include "MIDIUSB_Defs.h"
#include "pitchToFrequency.h"
#include "pitchToNote.h"



const int selectPins[3] = {A1, A2, A3}; // S0~2, S1~3, S2~4
const int zOutput = 5;
const int zInput = A0; // Connect common (Z) to A0 (analog input)

const int SW_Num = 12;
const byte s_pin[SW_Num] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16 }; // Connect switch to Digitalpins
const byte Notes[SW_Num] = { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 }; // MIDI notes

int State[SW_Num];
int State_old[SW_Num];

void setup()
{
  Serial.begin(115200); // Initialize the serial port
  // Set up the select pins as outputs:
  for (int i = 0; i < 3; i++) {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }

  pinMode(zInput, INPUT); // Set up Z as an input

  // Set up the s_pins as inputs:
  for (byte x = 0; x < SW_Num; x++) {
    pinMode(s_pin[x], INPUT_PULLUP);
  }
}

void loop()
{
  for (byte pin = 0; pin <= 5; pin++) {
    selectMuxPin(0);
    int faderval = (faderval * 0.9) + (analogRead(zInput) * 0.1);
    faderval = faderval / 1.68;
    faderval = constrain(faderval, 0, 127);

    int faderval_old;

    if (faderval != faderval_old) {
      Serial.println(String(faderval));
      controlChange(1, 1, faderval);
      MidiUSB.flush();
    }
    faderval_old = faderval;
  }

  for (byte pin = 0; pin <= 5; pin++) {
    selectMuxPin(1);
    int faderval = (faderval * 0.9) + (analogRead(zInput) * 0.1);
    faderval = faderval / 1.68;
    faderval = constrain(faderval, 0, 127);

    int faderval_old;

    if (faderval != faderval_old) {
      Serial.println(String(faderval));
      controlChange(1, 2, faderval);
      MidiUSB.flush();
    }
    faderval_old = faderval;
  }

  for (byte pin = 0; pin <= 5; pin++) {
    selectMuxPin(2);
    int faderval = (faderval * 0.9) + (analogRead(zInput) * 0.1);
    faderval = faderval / 1.68;
    faderval = constrain(faderval, 0, 127);

    int faderval_old;

    if (faderval != faderval_old) {
      Serial.println(String(faderval));
      controlChange(1, 3, faderval);
      MidiUSB.flush();
    }
    faderval_old = faderval;
  }

  for (byte pin = 0; pin <= 5; pin++) {
    selectMuxPin(3);
    int faderval = (faderval * 0.9) + (analogRead(zInput) * 0.1);
    faderval = faderval / 1.68;
    faderval = constrain(faderval, 0, 127);

    int faderval_old;

    if (faderval != faderval_old) {
      Serial.println(String(faderval));
      controlChange(1, 4, faderval);
      MidiUSB.flush();
    }
    faderval_old = faderval;
  }

  for (byte pin = 0; pin <= 5; pin++) {
    selectMuxPin(4);
    int faderval = (faderval * 0.9) + (analogRead(zInput) * 0.1);
    faderval = faderval / 1.68;
    faderval = constrain(faderval, 0, 127);

    int faderval_old;

    if (faderval != faderval_old) {
      Serial.println(String(faderval));
      controlChange(1, 5, faderval);
      MidiUSB.flush();
    }
    faderval_old = faderval;
  }

  for (byte pin = 0; pin <= 5; pin++) {
    selectMuxPin(5);
    int faderval = (faderval * 0.9) + (analogRead(zInput) * 0.1);
    faderval = faderval / 1.68;
    faderval = constrain(faderval, 0, 127);

    int faderval_old;

    if (faderval != faderval_old) {
      Serial.println(String(faderval));
      controlChange(1, 6, faderval);
      MidiUSB.flush();
    }
    faderval_old = faderval;
  }

  delay(5);

  for (byte x = 0; x < SW_Num; x++) {
    State[x] = digitalRead(s_pin[x]);

    if ( State[x] != State_old[x] ) {
      if ( State[x] == 0 ) {
        delay(5);
        noteOn(1, Notes[x], 127);
        MidiUSB.flush();
      } else {
        noteOff(1, Notes[x], 127);
        MidiUSB.flush();
      }
      State_old[x] = State[x];
    }
  }
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  for (int i = 0; i < 3; i++)
  {
    if (pin & (1 << i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
