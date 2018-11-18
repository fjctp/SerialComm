#include "SerialComm.hpp"
#include <string.h>

SerialComm comm(&Serial, callback);
long now = 0;
long last = 0;

void callback(char type, byte* payload, unsigned int length) {
/*
  char msg[length+1+12];
  strcat(msg, "Received: " + type);
  strcat(msg, (char*) payload);
  comm.send('i', msg, sizeof(msg));
*/
  comm.send('a', type);
  comm.send('b', payload, length-1);
  comm.send('c', '\n');
  comm.send('c', (int) length);
  comm.send('c', '\n');
}

void setup() {
  comm.begin(115200);
}

void loop() {
  comm.loop();
  
  now = millis();
  const char *msg = "Function Send Test\0";
  if (now - last > 2000) {
    comm.send('i', msg, strlen(msg));
    comm.send('a', 123);
    comm.send('c', '\n');
    last = now;
  }
}
