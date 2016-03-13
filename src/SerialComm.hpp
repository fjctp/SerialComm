#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <Arduino.h>

#define SERIAL_TERMINATE_CHAR ';'
#define SERIAL_CALLBACK_SIGNATURE void (*callback)(char, byte*, unsigned int)

/*
 * Stanard APIs for serial communication
 *   - using a callback function (passed when initializing) to handle message received
 *     -- the callback function receives information (type, payload, length) about the message received
 *     -- the callback function does not return anything
 *   - call send() function to send a message over serial port
 *   
 *   Data types
 *     type (char):           used for message classification and filtering
 *     payload (byte*):       message or command
 *     length (unsigned int): length of the payload
 *
 *   Protocol
 *     # of byte, data type
 *     1,         topic
 *     2-(N-1),   payload
 *     N,         terminate character
 *     Note: length, N, includes terminate charater
 */
class SerialComm {
  public:
    SerialComm(HardwareSerial *serial, SERIAL_CALLBACK_SIGNATURE);
    void begin(const long baud);
    
    int send(const char type, const char payload);
    int send(const char type, const int payload);
    int send(const char type, const char* payload, const unsigned int length);
    int send(const char type, const byte* payload, const unsigned int length);
    
    void loop();
    
  private:
    HardwareSerial *_serial;
    SERIAL_CALLBACK_SIGNATURE;
};

#endif
