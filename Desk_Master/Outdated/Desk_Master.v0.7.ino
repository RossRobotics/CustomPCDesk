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
//      -Added Brightness & pattern Speed control (might be a minute, since it requires hardware revisions)
//  4-20-22
//      -Added Logo color control (Hue)
//  4-24-22
//      -Fixed bug - button for logo pattern held high allowed current to flow keeping the logo half on
//        +All the other pattern select buttons has been changed to active HIGH.
//  5-4-22
//      -Added Thunderstorm effect (untested)
//  6-1-22
//    -Added MP3 Trigger for thunderstorm audio (Audio tested 6-13-22!)
//  6-2-22
//    -Added Circuit color control (untested)
//    -Cleaned up unused code
//    -reorganized pins to tidy up wiring
//  6-4-22
//    -Added Glass Top control (untested)
//    -Cleaned up more code & GUI
//  6-10-22
//    -Added feature to adjust swipe speed of circuit pattern [circuit_SwipeSpeed] (untested)
//    -Added feature to adjust animation interval. [circuit_AnimationSpeed] (untested)
//  6-12-22
//    -Removed glass top code as it would not connect to bluetooth. Just going to add a dedicated
//     Arduino to run the code that will be triggered from Master.
//  6-13-22
//    -Tested thunderstorm audio, works!
//  6-15-22
//    -Re-assigned some pins due to hardware limitations.

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 1009 bytes
  { 255,27,0,6,0,234,3,16,25,4,130,0,30,23,36,34,2,180,130,0,
  0,23,30,34,2,180,130,1,23,6,24,11,0,25,130,0,0,0,100,22,
  0,29,130,0,22,0,55,22,0,30,130,0,0,23,57,34,1,29,130,0,
  39,1,22,20,0,164,1,1,4,7,15,10,0,48,31,32,32,80,87,82,
  32,32,0,1,1,80,7,15,10,0,77,31,32,32,82,83,84,32,32,0,
  130,0,57,23,43,34,1,30,72,140,41,2,18,18,0,24,26,188,25,0,
  0,0,0,0,0,200,66,0,0,0,0,135,0,0,240,65,0,0,200,66,
  94,0,0,160,65,0,0,240,65,63,0,0,32,65,0,0,160,65,48,0,
  0,0,0,0,0,32,65,129,0,13,23,34,4,1,26,68,101,115,107,32,
  76,69,68,32,67,111,110,116,114,111,108,0,69,1,39,4,3,3,0,10,
  53,24,3,12,6,0,4,34,31,70,32,70,97,110,115,32,79,110,0,31,
  70,32,70,97,110,115,32,79,102,102,0,10,53,24,13,12,6,0,4,34,
  31,82,32,70,97,110,115,32,79,110,0,31,82,32,70,97,110,115,32,79,
  102,102,0,10,53,63,3,11,6,0,4,34,31,80,117,109,112,32,79,110,
  0,31,80,117,109,112,32,79,102,102,0,10,53,63,13,11,6,0,4,34,
  31,77,101,116,101,114,32,79,110,0,31,77,101,116,101,114,32,79,102,102,
  0,70,32,43,4,14,14,0,164,37,135,2,10,117,2,29,13,6,1,4,
  34,31,32,32,32,76,111,103,111,32,32,32,0,31,10,117,2,36,13,6,
  1,4,34,31,32,32,32,32,32,77,66,32,32,32,32,32,0,31,10,117,
  2,43,13,6,1,4,34,31,32,32,87,97,116,101,114,32,32,0,31,10,
  117,2,50,13,6,1,4,34,31,32,32,87,104,105,116,101,32,32,0,31,
  10,117,30,29,13,6,1,4,34,31,32,73,110,102,105,110,105,116,121,32,
  0,31,129,0,44,19,11,2,0,25,32,87,97,116,101,114,32,70,108,111,
  119,0,1,1,18,30,8,4,1,28,192,226,150,186,0,129,0,18,28,8,
  2,1,26,80,97,116,116,101,114,110,115,0,1,1,18,37,8,4,1,28,
  136,226,150,186,0,1,1,18,44,8,4,1,28,66,226,150,186,0,1,1,
  18,51,8,4,1,26,31,88,0,1,1,46,30,8,4,1,28,163,226,150,
  186,0,129,0,80,1,14,3,0,26,32,80,67,32,82,101,115,101,116,0,
  129,0,82,19,11,2,0,26,80,114,101,115,115,32,52,32,115,101,99,0,
  129,0,4,1,15,3,0,26,32,80,67,32,80,111,119,101,114,0,131,1,
  20,58,19,4,1,14,24,77,97,105,110,0,131,0,42,58,18,4,2,166,
  24,69,102,102,101,99,116,115,0,10,117,30,36,13,6,1,4,34,31,32,
  32,32,67,97,115,101,32,32,32,0,31,129,0,37,23,23,3,2,26,67,
  105,114,99,117,105,116,32,86,97,114,105,97,98,108,101,115,0,130,0,66,
  23,34,34,2,180,1,1,46,37,8,4,1,28,227,226,150,186,0,10,117,
  68,30,21,4,1,4,34,31,32,32,32,32,32,32,32,83,116,111,114,109,
  32,32,32,32,32,32,32,0,31,129,0,63,23,29,4,1,26,83,112,101,
  99,105,97,108,32,69,102,102,101,99,116,115,0,129,0,5,23,21,3,2,
  26,76,111,103,111,32,86,97,114,105,97,98,108,101,115,0,129,0,10,55,
  5,2,2,26,67,111,108,111,114,0,4,0,10,25,5,29,2,27,25,10,
  117,30,43,13,6,1,4,34,31,32,32,67,105,114,99,117,105,116,32,32,
  0,31,1,1,46,44,8,4,1,28,9,226,150,186,0,4,0,33,24,5,
  29,2,27,25,130,0,57,41,43,16,1,30,1,1,61,50,13,5,1,48,
  31,32,32,32,226,134,145,32,32,85,112,32,32,226,134,145,32,32,32,0,
  1,1,84,50,13,5,1,48,31,32,226,134,147,32,68,111,119,110,32,226,
  134,147,32,0,129,0,67,41,20,4,1,26,32,71,108,97,115,115,32,84,
  111,112,0,70,17,64,47,6,2,1,26,37,0,70,17,87,47,6,2,1,
  26,37,0,129,0,40,54,10,2,0,26,32,65,110,105,109,97,116,105,111,
  110,0,129,0,33,54,5,2,2,26,67,111,108,111,114,0,4,0,43,24,
  5,29,2,27,25,4,0,53,24,5,29,2,27,25,129,0,52,54,6,2,
  0,26,32,83,119,105,112,101,0 }; 
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t sw_power;   
  uint8_t sw_reset;
  uint8_t pushSwitch_ForwardFans;
  uint8_t pushSwitch_RadFans;
  uint8_t pushSwitch_Pump;
  uint8_t pushSwitch_FlowMeter;  
  uint8_t pushSwitch_Logo;  
  uint8_t pushSwitch_mbLED;  
  uint8_t pushSwitch_Water;  
  uint8_t pushSwitch_White;  
  uint8_t pushSwitch_Infinity;  
  uint8_t logoPatternSelect;   
  uint8_t mbPatternSelect;   
  uint8_t waterPatternSelect;   
  uint8_t buttonNC;   
  uint8_t infinityPatternSelect;   
  uint8_t pushSwitch_CaseLED;  
  uint8_t casePatternSelect;   
  uint8_t pushSwitch_Storm;  
  int8_t logo_ColorHue; // =0..100 slider position 
  uint8_t pushSwitch_Circuit;  
  uint8_t circuitPatternSelect;   
  int8_t circuit_ColorHue; //slider
  uint8_t button_Up;   
  uint8_t button_Down;   
  int8_t circuit_AnimationSpeed; //slider
  int8_t circuit_SwipeSpeed; //slider

    // output variables
  int8_t circularbar_1;  // from 0 to 100 
  int16_t flowMeterAlarm; // =0 no sound, else ID of sound, =1001 for example, look sound list in app 
  uint8_t flowStatus; 
  uint8_t led_Up; 
  uint8_t led_Down;

    // other variable
  uint8_t connect_flag; 

} RemoteXY;
#pragma pack(pop)  
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

//#define PIN_SW_POWER 4
//#define PIN_SW_RESET 5
//#define PIN_PUSHSWITCH_FORWARDFANS 30
//#define PIN_PUSHSWITCH_RADFANS 23
//#define PIN_PUSHSWITCH_PUMP 24
//#define PIN_PUSHSWITCH_FLOWMETER 20
#define PIN_BUTTON_UP 13
#define PIN_BUTTON_DOWN 12
#define PIN_PUSHSWITCH_LOGO 46
#define PIN_PUSHSWITCH_MBLED 42
#define PIN_PUSHSWITCH_WATER 45
#define PIN_PUSHSWITCH_WHITE 22
#define PIN_PUSHSWITCH_INFINITY 43
#define PIN_LOGOPATTERNSELECT 21
#define PIN_MBPATTERNSELECT 33 //34,35
#define PIN_WATERPATTERNSELECT 38 
#define PIN_INFINITYPATTERNSELECT 30
#define PIN_PUSHSWITCH_CASELED 44
#define PIN_CASEPATTERNSELECT A0 //A1,A3
#define PIN_BUTTONNC 50  //not connected
#define LOGO_COLORHUE 2  //sliders need to be associated to a PWM pin
//CIRCUIT
#define CIRCUIT_COLORHUE 3
#define CIRCUIT_SWIPESPEED 7
#define CIRCUIT_ANIMATIONSPEED 8
#define PIN_PUSHSWITCH_CIRCUIT 41
#define PIN_CIRCUITPATTERNSELECT 11

//THUNDERSTORM EFFECT
int stormEnable[] = {15,16,17,18,19,20};
#define PIN_PUSHSWITCH_STORM 31
#define PIN_STORM_AUDIO 32
#define PIN_STOP_AUDIO 6

//int flowInput = A1;
//int flow;
//int flowOutput;

void setup(){
  RemoteXY_Init ();

    for (int stormpins=15; stormpins<20; stormpins++) {
    pinMode(stormpins, OUTPUT);
  }
//Serial.begin(9600);
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
  pinMode (LOGO_COLORHUE, OUTPUT);
    //STORM
  pinMode (PIN_STORM_AUDIO, OUTPUT);
  pinMode (PIN_STOP_AUDIO, OUTPUT);
    //CIRCUIT
  pinMode (PIN_PUSHSWITCH_CIRCUIT, OUTPUT);
  pinMode (PIN_CIRCUITPATTERNSELECT, OUTPUT);
  pinMode (CIRCUIT_COLORHUE, OUTPUT);
  pinMode (CIRCUIT_ANIMATIONSPEED, OUTPUT);
  pinMode (CIRCUIT_SWIPESPEED, OUTPUT);
  //GLASS ACTUATOR
  pinMode (PIN_BUTTON_UP, OUTPUT);
  pinMode (PIN_BUTTON_DOWN, OUTPUT);

  digitalWrite(PIN_STORM_AUDIO, HIGH);

}

void loop() {
  RemoteXY_Handler ();

  digitalWrite(PIN_PUSHSWITCH_STORM, (RemoteXY.pushSwitch_Storm==0)?LOW:HIGH);
   if (RemoteXY.pushSwitch_Storm!=0) {
    thunderstorm();
   }
  digitalWrite(PIN_PUSHSWITCH_CIRCUIT, (RemoteXY.pushSwitch_Circuit==0)?HIGH : LOW);
  digitalWrite(PIN_CIRCUITPATTERNSELECT, (RemoteXY.circuitPatternSelect==0)?LOW : HIGH);
   analogWrite(CIRCUIT_COLORHUE, RemoteXY.circuit_ColorHue * 2.55);
   analogWrite(CIRCUIT_ANIMATIONSPEED, RemoteXY.circuit_AnimationSpeed * 2.55);
   analogWrite(CIRCUIT_SWIPESPEED, RemoteXY.circuit_SwipeSpeed * 2.55);
   
  digitalWrite(PIN_PUSHSWITCH_LOGO, (RemoteXY.pushSwitch_Logo == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_MBLED, (RemoteXY.pushSwitch_mbLED == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_WATER, (RemoteXY.pushSwitch_Water == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_WHITE, (RemoteXY.pushSwitch_White == 0) ? HIGH : LOW);
  digitalWrite(PIN_PUSHSWITCH_INFINITY, (RemoteXY.pushSwitch_Infinity == 0) ? HIGH : LOW);

  digitalWrite(PIN_LOGOPATTERNSELECT, (RemoteXY.logoPatternSelect == 0) ? LOW : HIGH);
  analogWrite(LOGO_COLORHUE, RemoteXY.logo_ColorHue * 2.55); // sends voltage (0-5V) to the Logo controller to change color

  digitalWrite(PIN_MBPATTERNSELECT, (RemoteXY.mbPatternSelect == 0) ? LOW : HIGH);
  digitalWrite(PIN_WATERPATTERNSELECT, (RemoteXY.waterPatternSelect == 0) ? LOW : HIGH);
  digitalWrite(PIN_BUTTONNC, (RemoteXY.buttonNC == 0) ? HIGH : LOW);
  digitalWrite(PIN_INFINITYPATTERNSELECT, (RemoteXY.infinityPatternSelect == 0) ? LOW : HIGH);
  digitalWrite(PIN_PUSHSWITCH_CASELED, (RemoteXY.pushSwitch_CaseLED == 0) ? HIGH : LOW);
  digitalWrite(PIN_CASEPATTERNSELECT, (RemoteXY.casePatternSelect == 0) ? LOW : HIGH);
  analogWrite(CIRCUIT_COLORHUE, RemoteXY.circuit_ColorHue * 2.55);
  
  digitalWrite(PIN_BUTTON_UP, (RemoteXY.button_Up==0)?LOW:HIGH);
  digitalWrite(PIN_BUTTON_DOWN, (RemoteXY.button_Down==0)?LOW:HIGH);

  if (digitalRead(PIN_STOP_AUDIO) == HIGH){
    digitalWrite(TBD, LOW); //need to test trigger to see how it stops output
  }
  }
  //Reports Glass Top status to GUI
 // RemoteXY.led_Up = (digitalRead(stop_up)==HIGH)?255:0;
 // RemoteXY.led_Down = (digitalRead(stop_down)==HIGH)?255:0;
  
//  flow = analogRead(flowInput);
//  flowOutput = (int)(flow / 10.23);
//  RemoteXY.circularbar_1 = flowOutput;
//  if (flowOutput <= 10) {
//    RemoteXY.flowMeterAlarm = 16;
//  }
}

void thunderstorm() {
  digitalWrite(PIN_STORM_AUDIO, LOW); //mp3 trigger active LOW
    for (int stormpins=15; stormpins<20; stormpins++){
    digitalWrite(stormpins, HIGH);
    delay(10);
  }
      for (int stormpins=15; stormpins<20; stormpins++){
    digitalWrite(stormpins, LOW);
    delay(10);
  }
  digitalWrite(PIN_STORM_AUDIO, HIGH);  
  //mp3 trigger will loop a track if left LOW.  
  //This function is placed after to allow time for the mp3 trigger.
}
