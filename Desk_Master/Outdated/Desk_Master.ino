//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 419 bytes
  { 255,11,0,4,0,156,1,16,24,0,130,1,58,26,38,26,29,130,1,23,
  6,24,11,25,130,1,1,2,98,20,29,130,1,22,2,55,20,30,130,1,
  1,26,55,33,29,130,1,39,2,22,20,162,1,1,4,7,15,10,48,31,
  32,32,80,87,82,32,32,0,1,1,80,7,15,10,77,31,32,32,82,83,
  84,32,32,0,130,1,3,27,50,31,30,72,140,41,3,18,18,24,26,188,
  30,0,0,0,0,0,0,200,66,0,0,0,0,135,0,0,240,65,0,0,
  200,66,94,0,0,160,65,0,0,240,65,63,0,0,32,65,0,0,160,65,
  48,0,0,0,0,0,0,32,65,129,0,20,28,14,3,25,68,101,115,107,
  32,76,69,68,0,69,1,39,4,3,3,10,53,24,4,12,6,4,34,31,
  70,32,70,97,110,115,32,79,110,0,31,70,32,70,97,110,115,32,79,102,
  102,0,10,53,24,13,12,6,4,34,31,82,32,70,97,110,115,32,79,110,
  0,31,82,32,70,97,110,115,32,79,102,102,0,10,53,63,4,11,6,4,
  34,31,80,117,109,112,32,79,110,0,31,80,117,109,112,32,79,102,102,0,
  10,53,63,13,11,6,4,34,31,77,101,116,101,114,32,79,110,0,31,77,
  101,116,101,114,32,79,102,102,0,70,32,44,6,12,12,162,37,135,2,10,
  117,10,33,11,4,4,34,31,32,32,76,111,103,111,32,32,0,31,10,117,
  10,39,11,4,4,34,31,32,32,32,32,77,66,32,32,32,32,0,31,10,
  117,10,45,11,4,4,34,31,32,32,87,97,116,101,114,32,32,0,31,10,
  117,10,51,11,4,4,34,31,32,32,87,104,105,116,101,32,32,0,31,10,
  117,35,33,11,4,4,34,31,32,73,110,102,105,110,105,116,121,32,0,31,
  129,0,44,20,11,2,25,32,87,97,116,101,114,32,70,108,111,119,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t sw_power; // =1 if button pressed, else =0 
  uint8_t sw_reset; // =1 if button pressed, else =0 
  uint8_t pushSwitch_ForwardFans; // =1 if state is ON, else =0 
  uint8_t pushSwitch_RadFans; // =1 if state is ON, else =0 
  uint8_t pushSwitch_Pump; // =1 if state is ON, else =0 
  uint8_t pushSwitch_FlowMeter; // =1 if state is ON, else =0 
  uint8_t pushSwitch_Logo; // =1 if state is ON, else =0 
  uint8_t pushSwitch_mbLED; // =1 if state is ON, else =0 
  uint8_t pushSwitch_Water; // =1 if state is ON, else =0 
  uint8_t pushSwitch_White; // =1 if state is ON, else =0 
  uint8_t pushSwitch_Infinity; // =1 if state is ON, else =0 

    // output variables
  int8_t circularbar_1;  // from 0 to 100 
  int16_t flowMeterAlarm; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  uint8_t flowStatus; // led state 0 .. 2 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SW_POWER 4
#define PIN_SW_RESET 5
#define PIN_PUSHSWITCH_FORWARDFANS 6
#define PIN_PUSHSWITCH_RADFANS 7
#define PIN_PUSHSWITCH_PUMP 8
#define PIN_PUSHSWITCH_FLOWMETER 9
#define PIN_PUSHSWITCH_LOGO 10
#define PIN_PUSHSWITCH_MBLED 11
#define PIN_PUSHSWITCH_WATER 13
#define PIN_PUSHSWITCH_WHITE 10
#define PIN_PUSHSWITCH_INFINITY A0


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SW_POWER, OUTPUT);
  pinMode (PIN_SW_RESET, OUTPUT);
  pinMode (PIN_PUSHSWITCH_FORWARDFANS, OUTPUT);
  pinMode (PIN_PUSHSWITCH_RADFANS, OUTPUT);
  pinMode (PIN_PUSHSWITCH_PUMP, OUTPUT);
  pinMode (PIN_PUSHSWITCH_FLOWMETER, OUTPUT);
  pinMode (PIN_PUSHSWITCH_LOGO, OUTPUT);
  pinMode (PIN_PUSHSWITCH_MBLED, OUTPUT);
  pinMode (PIN_PUSHSWITCH_WATER, OUTPUT);
  pinMode (PIN_PUSHSWITCH_WHITE, OUTPUT);
  pinMode (PIN_PUSHSWITCH_INFINITY, OUTPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_SW_POWER, (RemoteXY.sw_power==0)?LOW:HIGH);
  digitalWrite(PIN_SW_RESET, (RemoteXY.sw_reset==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_FORWARDFANS, (RemoteXY.pushSwitch_ForwardFans==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_RADFANS, (RemoteXY.pushSwitch_RadFans==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_PUMP, (RemoteXY.pushSwitch_Pump==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_FLOWMETER, (RemoteXY.pushSwitch_FlowMeter==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_LOGO, (RemoteXY.pushSwitch_Logo==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_MBLED, (RemoteXY.pushSwitch_mbLED==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_WATER, (RemoteXY.pushSwitch_Water==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_WHITE, (RemoteXY.pushSwitch_White==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_INFINITY, (RemoteXY.pushSwitch_Infinity==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
