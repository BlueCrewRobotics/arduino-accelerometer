#include <Wire.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
}

void loop()
{
  delay(100);
}


void requestEvent()
{
  //called when RoboRIO request a message from this device
  int output = 12;
  //writes data to the RoboRIO, converts it to string
  Wire.write(output); 
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent()
{
  String LED;
 
  while ( Wire.available() > 0 ){
    char n = (char)Wire.read();
    LED += n; 
  }
  
  if (LED == "start"){
    digitalWrite(LED_BUILTIN, HIGH);
    const char * stopCommand = "yes";
    delay(2000);
    Wire.write(stopCommand);
  }
  if (LED == "stop"){
    digitalWrite(LED_BUILTIN, LOW);
  }
}
