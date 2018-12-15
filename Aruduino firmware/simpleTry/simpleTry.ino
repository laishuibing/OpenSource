/**
************************************************************
* @file         Gizwits + ArduinoUnoR3 Library 
* @brief        Datapoints handle , Gizwits Process
* @author       Gizwits
* @date         2017-08-01
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include <Gizwits.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A2, A3); // A2 -> RX, A3 -> TX

Gizwits myGizwits;
int ledPin = 13;
/**
* Serial Init , Gizwits Init  
* @param none
* @return none
*/
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  mySerial.begin(115200);

  myGizwits.begin();

  mySerial.println("GoKit init  OK \n");
  myGizwits.setBindMode(0x02);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
}

/**
* Arduino loop 
* @param none
* @return none
*/

bool varW_led = 0;//Add Sensor Data Collection
unsigned long varW_ADC = 0;//Add Sensor Data Collection
void loop() {  
  
  //Configure network
  //if(XXX) //Trigger Condition
  //myGizwits.setBindMode(0x02);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
    


  varW_led= digitalRead(ledPin); 
  myGizwits.write(VALUE_led, varW_led);
  varW_ADC= analogRead(A0);
  myGizwits.write(VALUE_ADC, varW_ADC);


  bool varR_key = 0;
  if(myGizwits.hasBeenSet(EVENT_key))
  {
    myGizwits.read(EVENT_key,&varR_key);//Address for storing data
    mySerial.println(F("EVENT_key"));
    mySerial.println(varR_key,DEC);
    digitalWrite(ledPin,varR_key);
  }


  //binary datapoint handle
  

  myGizwits.process();
}
