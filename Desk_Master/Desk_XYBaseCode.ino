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
uint8_t RemoteXY_CONF[] =   // 518 bytes
  { 255,16,0,4,0,255,1,16,24,0,130,0,33,23,67,40,29,130,1,23,
  6,24,11,25,130,1,0,0,100,22,29,130,1,22,0,55,22,30,130,1,
  0,23,31,40,29,130,1,39,1,22,20,164,1,1,4,7,15,10,48,31,
  32,32,80,87,82,32,32,0,1,1,80,7,15,10,77,31,32,32,82,83,
  84,32,32,0,130,0,1,28,29,33,30,72,140,41,2,18,18,24,26,188,
  25,0,0,0,0,0,0,200,66,0,0,0,0,135,0,0,240,65,0,0,
  200,66,94,0,0,160,65,0,0,240,65,63,0,0,32,65,0,0,160,65,
  48,0,0,0,0,0,0,32,65,129,0,6,24,19,4,25,68,101,115,107,
  32,76,69,68,0,69,1,39,4,3,3,10,53,24,3,12,6,4,34,31,
  70,32,70,97,110,115,32,79,110,0,31,70,32,70,97,110,115,32,79,102,
  102,0,10,53,24,13,12,6,4,34,31,82,32,70,97,110,115,32,79,110,
  0,31,82,32,70,97,110,115,32,79,102,102,0,10,53,63,3,11,6,4,
  34,31,80,117,109,112,32,79,110,0,31,80,117,109,112,32,79,102,102,0,
  10,53,63,13,11,6,4,34,31,77,101,116,101,114,32,79,110,0,31,77,
  101,116,101,114,32,79,102,102,0,70,32,43,4,14,14,164,37,135,2,10,
  53,4,31,12,5,4,34,31,32,32,32,76,111,103,111,32,32,32,0,31,
  32,32,76,111,103,111,32,32,0,10,53,4,37,12,5,4,34,31,32,32,
  32,32,32,77,66,32,32,32,32,32,0,31,32,32,32,32,77,66,32,32,
  32,32,0,10,117,4,43,12,5,4,34,31,32,32,87,97,116,101,114,32,
  32,0,31,10,117,4,49,12,5,4,34,31,32,32,87,104,105,116,101,32,
  32,0,31,10,117,4,55,12,5,4,34,31,32,73,110,102,105,110,105,116,
  121,32,0,31,129,0,44,19,11,2,25,32,87,97,116,101,114,32,70,108,
  111,119,0,1,1,19,32,7,3,28,31,226,150,186,0,129,0,18,29,8,
  2,26,32,80,97,116,116,101,114,110,115,0,1,1,19,38,7,3,28,31,
  226,150,186,0,1,1,19,44,7,3,28,31,226,150,186,0,1,1,19,50,
  7,3,26,31,88,0,1,1,19,56,7,3,28,31,226,150,186,0 };
  
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
  uint8_t logoPatternSelect; // =1 if button pressed, else =0 
  uint8_t mbPatternSelect; // =1 if button pressed, else =0 
  uint8_t waterPatternSelect; // =1 if button pressed, else =0 
  uint8_t buttonNC; // =1 if button pressed, else =0 
  uint8_t button_1; // =1 if button pressed, else =0 

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
#define PIN_LOGOPATTERNSELECT A4
#define PIN_MBPATTERNSELECT A3
#define PIN_WATERPATTERNSELECT A2


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
  pinMode (PIN_LOGOPATTERNSELECT, OUTPUT);
  pinMode (PIN_MBPATTERNSELECT, OUTPUT);
  pinMode (PIN_WATERPATTERNSELECT, OUTPUT);
  
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
  digitalWrite(PIN_LOGOPATTERNSELECT, (RemoteXY.logoPatternSelect==0)?LOW:HIGH);
  digitalWrite(PIN_MBPATTERNSELECT, (RemoteXY.mbPatternSelect==0)?LOW:HIGH);
  digitalWrite(PIN_WATERPATTERNSELECT, (RemoteXY.waterPatternSelect==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
