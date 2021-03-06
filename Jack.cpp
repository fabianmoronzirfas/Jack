/**
 * Copyright 2017 Fabian Morón Zirfas
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to  permit persons to
 * whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTIO
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * see also http://www.opensource.org/licenses/mit-license.php
 */
#include "Arduino.h"
#include "Jack.h"

// Jack::Jack(int inpin, int outpin) {
//   Serial.begin(9600);
//   pinMode(inpin, INPUT);
//   pinMode(outpin, OUTPUT);
//   _inpin = inpin;
//   _outpin = outpin;
// }

// Jack::Jack(int inpin, int outpin, boolean pullup) {

//   if (pullup == true) {
//     pinMode(inpin, INPUT_PULLUP);
//   } else {
//     pinMode(inpin, INPUT);
//   }
//   pinMode(outpin, OUTPUT);
//   _inpin = inpin;
//   _outpin = outpin;
//   _pullup = pullup;
// }

Jack::Jack(int inpin, int outpin, boolean pullup, boolean log) {
  if (pullup == true) {
    pinMode(inpin, INPUT_PULLUP);
  } else {
    pinMode(inpin, INPUT);
  }
  pinMode(outpin, OUTPUT);
  _inpin = inpin;
  _outpin = outpin;
  _pullup = pullup;
  _log = log;
}

Jack::~Jack() {}

boolean Jack::listen() {

  int in = digitalRead(_inpin);

  if (_pullup == true) {
    if (in == LOW) {
  if(_log) Serial.println("Jack got a signal");
      return true;
    } else {
      return false;
    }
  } else {
    if (in == HIGH) {
      return false;
    } else {
      // Serial.println("Got a low signal (I'm pull up)");
      return true;
    }
  }
}
void Jack::setInterval(long interval) {
  _interval = interval;
  if(_log) {
    Serial.print("Jack changed interval to ");
    Serial.println(_interval);
  }

}
void Jack::send() {
  // Serial.println("Sending a message in Jack::send()");
  if(_pullup == true){
    digitalWrite(_outpin, LOW);
  }else{
    digitalWrite(_outpin, HIGH);
  }
  Serial.print("Jack is seding a signal and will wait for ");
  Serial.print(_interval);
  Serial.println(" milliseconds!");
  delay(_interval);
  if(_pullup == true){
    digitalWrite(_outpin, HIGH);
  } else {
    digitalWrite(_outpin, LOW);

  }
  // Serial.println("Wait period is over ready to send again");
}

