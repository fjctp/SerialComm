
#include <Arduino.h>
#include <stdlib.h>
#include "SerialComm.hpp"

SerialComm::SerialComm(HardwareSerial *serial, SERIAL_CALLBACK_SIGNATURE) {
  this->_serial = serial;
  this->callback = callback;
}

void SerialComm::begin(const long baud) {
  this->_serial->begin(baud);
}

int SerialComm::send(const char type, const char payload) {
  return this->send(type, &payload, sizeof(char));
}

int SerialComm::send(const char type, const int payload) {
  char buffer[64];
  itoa(payload, buffer, 10);
  return this->send(type, (byte*) buffer, strlen(buffer));
}

int SerialComm::send(const char type, const char* payload, const unsigned int length) {
  return this->send(type, (byte*) payload, length);
}

int SerialComm::send(const char type, const byte* payload, const unsigned int length) {
  unsigned int palength = length + 2;
  byte package[palength];
  package[0] = type;
  for(size_t i=0;i<length;i++)
    package[i+1]=payload[i];
  package[length+1]=SERIAL_TERMINATE_CHAR;
  return this->_serial->write(package, palength);
}

void SerialComm::loop() {
  int byte_count = this->_serial->available();
  if (byte_count>1) {
    unsigned int blength = 256;
    byte buffer[blength];
    
    int length = this->_serial->readBytesUntil(SERIAL_TERMINATE_CHAR, buffer, blength);
    
    if(length>1) {
      char type = (char) buffer[0];
      byte *payload = buffer+1;
      this->callback(type, payload, length-1);
    }
  }
}
