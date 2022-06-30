//    RossRobotics.com
//  4-6-22
//     -Initial Base Code from RemoteXY
//  4-9-22
//      -Added flowmeter logic
//      -Lots of GUI tweaks
//  4-18-22
//      -Added PC Fan control
//      -Added PWM feature for PC fans
//  4-19-22
//      -Added Brightness & pattern Speed control (might be a min, since it requires hardware revisions)
//  4-20-22
//      -Added color control (Hue)
//  4-24-22
//      -Fixed bug - button for logo pattern held high allowed current to flow keeping the logo half on
//        +All the other pattern select buttons has been changed to active HIGH.

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
uint8_t RemoteXY_CONF[] =   // 1132 bytes
  { 255,34,0,4,0,101,4,16,25,4,130,1,1,23,36,34,3,137,130,1,
  30,23,36,34,2,180,130,1,0,23,30,34,2,180,130,1,23,6,24,11,
  0,25,130,0,0,0,100,22,0,29,130,0,22,0,55,22,0,30,130,0,
  0,23,57,34,1,29,130,0,39,1,22,20,0,164,1,1,4,7,15,10,
  0,48,31,32,32,80,87,82,32,32,0,1,1,80,7,15,10,0,77,31,
  32,32,82,83,84,32,32,0,130,0,57,23,43,34,1,30,72,140,41,2,
  18,18,0,24,26,188,25,0,0,0,0,0,0,200,66,0,0,0,0,135,
  0,0,240,65,0,0,200,66,94,0,0,160,65,0,0,240,65,63,0,0,
  32,65,0,0,160,65,48,0,0,0,0,0,0,32,65,129,0,17,24,25,
  3,1,26,68,101,115,107,32,76,69,68,32,67,111,110,116,114,111,108,0,
  69,1,39,4,3,3,0,10,53,24,3,12,6,0,4,34,31,70,32,70,
  97,110,115,32,79,110,0,31,70,32,70,97,110,115,32,79,102,102,0,10,
  53,24,13,12,6,0,4,34,31,82,32,70,97,110,115,32,79,110,0,31,
  82,32,70,97,110,115,32,79,102,102,0,10,53,63,3,11,6,0,4,34,
  31,80,117,109,112,32,79,110,0,31,80,117,109,112,32,79,102,102,0,10,
  53,63,13,11,6,0,4,34,31,77,101,116,101,114,32,79,110,0,31,77,
  101,116,101,114,32,79,102,102,0,70,32,43,4,14,14,0,164,37,135,2,
  10,117,2,29,13,6,1,4,34,31,32,32,32,76,111,103,111,32,32,32,
  0,31,10,117,2,36,13,6,1,4,34,31,32,32,32,32,32,77,66,32,
  32,32,32,32,0,31,10,117,2,43,13,6,1,4,34,31,32,32,87,97,
  116,101,114,32,32,0,31,10,117,2,50,13,6,1,4,34,31,32,32,87,
  104,105,116,101,32,32,0,31,10,117,30,29,13,6,1,4,34,31,32,73,
  110,102,105,110,105,116,121,32,0,31,129,0,44,19,11,2,0,25,32,87,
  97,116,101,114,32,70,108,111,119,0,1,1,18,30,8,4,1,28,192,226,
  150,186,0,129,0,18,28,8,2,1,26,80,97,116,116,101,114,110,115,0,
  1,1,18,37,8,4,1,28,136,226,150,186,0,1,1,18,44,8,4,1,
  28,66,226,150,186,0,1,1,18,51,8,4,1,26,31,88,0,1,1,46,
  30,8,4,1,28,163,226,150,186,0,129,0,80,1,14,3,0,26,32,80,
  67,32,82,101,115,101,116,0,129,0,82,19,11,2,0,26,80,114,101,115,
  115,32,52,32,115,101,99,0,129,0,4,1,15,3,0,26,32,80,67,32,
  80,111,119,101,114,0,129,0,7,23,15,3,2,26,70,97,110,32,83,112,
  101,101,100,0,131,1,20,58,19,4,1,14,24,77,97,105,110,0,131,0,
  42,58,18,4,2,166,24,69,102,102,101,99,116,115,0,4,0,2,27,5,
  29,2,185,25,4,0,9,27,5,29,2,185,25,4,0,16,27,5,29,2,
  185,25,10,53,30,36,13,6,1,4,34,31,32,32,32,76,111,103,111,32,
  32,32,0,31,32,32,32,67,97,115,101,32,32,32,0,4,0,35,27,5,
  29,2,27,25,4,0,42,27,5,29,2,27,25,4,0,49,27,5,29,2,
  27,25,129,0,9,26,4,2,2,26,32,82,97,100,0,129,0,2,26,4,
  2,2,26,70,119,100,0,129,0,16,26,4,2,2,26,32,88,116,114,97,
  0,129,0,41,23,16,3,2,26,66,114,105,103,104,116,110,101,115,115,0,
  4,0,56,27,5,29,2,27,25,129,0,35,26,5,2,2,26,76,111,103,
  111,0,129,0,42,26,6,2,2,26,87,97,116,101,114,0,129,0,50,26,
  4,2,2,26,73,110,102,121,0,129,0,57,26,3,2,2,26,77,66,0,
  130,1,66,23,34,34,2,180,129,0,75,23,18,3,2,26,69,102,102,101,
  99,116,32,83,112,101,101,100,0,4,0,70,27,5,29,2,87,25,4,0,
  77,27,5,29,2,87,25,4,0,84,27,5,29,2,87,25,129,0,71,26,
  3,2,2,26,77,66,0,129,0,77,26,5,2,2,26,76,111,103,111,0,
  129,0,84,26,6,2,2,26,87,97,116,101,114,0,4,0,91,27,5,29,
  2,87,25,4,0,23,27,5,29,2,185,25,129,0,92,26,4,2,2,26,
  88,116,114,97,0,129,0,23,26,4,2,2,26,32,72,68,68,0,1,1,
  46,37,8,4,1,28,227,226,150,186,0,131,0,62,58,18,4,3,137,24,
  67,111,108,111,114,115,0,129,0,11,23,15,3,3,26,67,111,108,111,114,
  32,72,117,101,0,4,0,6,27,5,29,3,158,25,4,0,13,27,5,29,
  3,158,25,4,0,20,27,5,29,3,158,25,129,0,14,26,3,2,3,26,
  77,66,0,129,0,6,26,4,2,3,26,76,111,103,111,0,129,0,20,26,
  4,2,3,26,87,97,116,101,114,0,4,0,27,27,5,29,3,158,25,129,
  0,27,26,4,2,3,26,67,97,115,101,0 }; 
  
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
  uint8_t infinityPatternSelect; // =1 if button pressed, else =0 
  int8_t forwardFanSpeed; // =0..100 slider position 
  int8_t rearFanSpeed; // =0..100 slider position 
  int8_t extraFanSpeed; // =0..100 slider position 
  uint8_t pushSwitch_CaseLED; // =1 if state is ON, else =0 
  int8_t logo_Bright; // =0..100 slider position 
  int8_t water_Bright; // =0..100 slider position 
  int8_t infinity_Bright; // =0..100 slider position 
  int8_t MB_Bright; // =0..100 slider position 
  int8_t MB_Speed; // =0..100 slider position 
  int8_t water_Speed; // =0..100 slider position 
  int8_t infinity_Speed; // =0..100 slider position 
  int8_t xtra_Speed; // =0..100 slider position 
  int8_t HDDFanSpeed; // =0..100 slider position 
  uint8_t casePatternSelect; // =1 if button pressed, else =0 
  int8_t logo_ColorHue; // =0..100 slider position 
  int8_t MB_ColorHue; // =0..100 slider position 
  int8_t water_ColorHue; // =0..100 slider position 
  int8_t case_ColorHue; // =0..100 slider position 

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
#define PIN_PUSHSWITCH_FORWARDFANS 30
#define PIN_PUSHSWITCH_RADFANS 23
#define PIN_PUSHSWITCH_PUMP 24
#define PIN_PUSHSWITCH_FLOWMETER 20
#define PIN_PUSHSWITCH_LOGO 18
#define PIN_PUSHSWITCH_MBLED 26
#define PIN_PUSHSWITCH_WATER 28
#define PIN_PUSHSWITCH_WHITE 22
#define PIN_PUSHSWITCH_INFINITY 30
#define PIN_LOGOPATTERNSELECT 40
#define PIN_MBPATTERNSELECT 46
#define PIN_WATERPATTERNSELECT 42
#define PIN_INFINITYPATTERNSELECT 38
#define PIN_PUSHSWITCH_CASELED 32
#define PIN_CASEPATTERNSELECT 36
#define PIN_BUTTONNC 50

#define PWM_REAR_FANS 6
#define PWM_FWD_FANS 7
#define PWM_XTRA_FANS 8
#define LOGO_COLORHUE 9

int flowInput;
int flow;
int flowOutput;

void setup(){
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
  pinMode (PIN_BUTTONNC, OUTPUT);
  pinMode (PIN_INFINITYPATTERNSELECT, OUTPUT);
  pinMode (PIN_PUSHSWITCH_CASELED, OUTPUT);
  pinMode (PIN_CASEPATTERNSELECT, OUTPUT);
  pinMode (PWM_XTRA_FANS, OUTPUT);
  pinMode (PWM_FWD_FANS, OUTPUT);
  pinMode (PWM_REAR_FANS, OUTPUT);
  pinMode (LOGO_COLORHUE, OUTPUT);
}

void loop() {
  RemoteXY_Handler ();

  digitalWrite(PIN_SW_POWER, (RemoteXY.sw_power == 0) ? HIGH : LOW);
  digitalWrite(PIN_SW_RESET, (RemoteXY.sw_reset == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_FORWARDFANS, (RemoteXY.pushSwitch_ForwardFans == 0) ? HIGH : LOW);
  int FWDFANS_SPEED = RemoteXY.forwardFanSpeed * 2.5 ;
  analogWrite(PWM_FWD_FANS, FWDFANS_SPEED);

  digitalWrite(PIN_PUSHSWITCH_RADFANS, (RemoteXY.pushSwitch_RadFans == 0) ? HIGH : LOW);
  int RADFANS_SPEED = RemoteXY.rearFanSpeed * 2.5 ;
  analogWrite(PWM_REAR_FANS, RADFANS_SPEED);
  int XTRAFANS_SPEED = RemoteXY.extraFanSpeed * 2.5 ;
  analogWrite(PWM_XTRA_FANS, XTRAFANS_SPEED);

  digitalWrite(PIN_PUSHSWITCH_PUMP, (RemoteXY.pushSwitch_Pump == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_FLOWMETER, (RemoteXY.pushSwitch_FlowMeter == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_LOGO, (RemoteXY.pushSwitch_Logo == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_MBLED, (RemoteXY.pushSwitch_mbLED == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_WATER, (RemoteXY.pushSwitch_Water == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_WHITE, (RemoteXY.pushSwitch_White == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_INFINITY, (RemoteXY.pushSwitch_Infinity == 0) ? HIGH : LOW);
  // Needs pull-down resistor\/
  digitalWrite(PIN_LOGOPATTERNSELECT, (RemoteXY.logoPatternSelect == 0) ? LOW : HIGH);
  analogWrite(LOGO_COLORHUE, RemoteXY.logo_ColorHue * 2.55);
  
  digitalWrite(PIN_MBPATTERNSELECT, (RemoteXY.mbPatternSelect == 0) ? LOW : HIGH);
  digitalWrite(PIN_WATERPATTERNSELECT, (RemoteXY.waterPatternSelect == 0) ? LOW : HIGH);
  digitalWrite(PIN_BUTTONNC, (RemoteXY.buttonNC == 0) ? HIGH : LOW);
  digitalWrite(PIN_INFINITYPATTERNSELECT, (RemoteXY.infinityPatternSelect == 0) ? LOW : HIGH);
  digitalWrite(PIN_PUSHSWITCH_CASELED, (RemoteXY.pushSwitch_CaseLED == 0) ? LOW : HIGH);
  digitalWrite(PIN_CASEPATTERNSELECT, (RemoteXY.casePatternSelect == 0) ? LOW : HIGH);

  flow = analogRead(flowInput);
  flowOutput = (int)(flow / 10.23);
  RemoteXY.circularbar_1 = flowOutput;
  if (flowOutput <= 10) {
    RemoteXY.flowMeterAlarm = 16;
  }
}
