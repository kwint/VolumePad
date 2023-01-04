#ifndef ORDER_H
#define ORDER_H

// Define the orders that can be sent and received
enum Order {
  HELLO = 0,
  ERROR = 1,
  ALREADY_CONNECTED = 2,
  RECEIVED = 3,
  STOP = 4,
  FADER0 = 5,
  FADER1 = 6,
  BUTTON_PRESSED = 7,
};

typedef enum Order Order;

#endif
