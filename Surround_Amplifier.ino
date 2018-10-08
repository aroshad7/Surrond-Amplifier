#include <Wire.h>
#include <EEPROM.h>
#include <PT2322.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

#define HPF_LPF_PIN_A   7
#define HPF_LPF_PIN_B   8
#define HPF_PIN         9
#define RELAY_PIN       2
#define BUTTON_PIN      A2
#define IR_RECV_PIN     A3

#define CHH         0xFFE21D
#define CH          0xFF629D
#define CHL         0xFFA25D
#define PP          0xFFC23D
#define NEXT        0xFF02FD
#define PREV        0xFF22DD
#define INCREASE    0xFFA857
#define DECREASE    0xFFE01F
#define EQ          0xFF906F
#define _1          0xFF30CF
#define _2          0xFF18E7
#define _3          0xFF7A85
#define _4          0xFF10EF
#define _5          0xFF38C7
#define _6          0xFF5AA5
#define _7          0xFF42BD
#define _8          0xFF4AB5
#define _9          0xFF52AD
#define _0          0xFF6897
#define _+100       0xFF9867
#define _+200       0xFFB04F
#define CHH_2       0xEE886D7F
#define CH_2        0x511DBB
#define CHL_2       0xE318261B
#define NEXT_2      0xD7E84B1B
#define PREV_2      0x52A3D41F
#define INCREASE_2  0xA3C8EDDB
#define DECREASE_2  0xF076C13B
#define EQ_2        0xE5CFBD7F
#define _1_2        0x9716BE3F
#define _2_2        0x3D9AE3F7
#define _3_2        0x6182021B
#define _4_2        0x8C22657B
#define _5_2        0x488F3CBB
#define _6_2        0x449E79F
#define _7_2        0x32C6FDF7
#define _8_2        0x1BC0157B
#define _9_2        0x3EC3FC1B
#define _0_2        0xC101E57B
#define _+100_2     0x97483BFB
#define _+200_2     0xF0C41643

#define SELECT_6CH_INPUT    0b11000111
#define SELECT_2CH_INPUT_1  0b11001011
#define SELECT_2CH_INPUT_2  0b11001010
#define SELECT_2CH_INPUT_3  0b11001001
#define SELECT_2CH_INPUT_4  0b11001000
#define ENABLE_6dB_AMP      0b10010001
#define DISABLE_6dB_AMP     0b10010000
#define ENABLE_SURROUND     0b11010000
#define DISABLE_SURROUND    0b11010001
#define UNMUTE_ALL          0b11111110
#define MUTE_ALL            0b11111111

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
PT2322 audio;
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

bool mute_state = 0;
bool threeD_state = 0;
bool enhanced_surround_state = 0;
bool sixdB_amp_state = 0;
bool DBFB_state = 0;
bool DBFB_level_state = 0;
bool filter_state = 0;
uint8_t hpf_state, hlpf_state, input_source_state = 0;

bool relay_state = 0;
uint32_t powerButtonTime = 0;
int buttonValue = 0;
char itoaBuffer[4];

enum function {FDBFB, FFilter, FEnchancedSurround, F6dBAmp, F3D, FMasterVolume, FEq, FEnd, 
               FFrontLeftVolume, FFrontRightVolume, FCenterVolume, 
               FRearLeftVolume, FRearRightVolume, FSubVolume
              };
int currentFunction = FEnd;
int functionValues [] = {1, false, false, true, false, 20, 0, 0, 15, 15, 15, 15, 15, 15};
int minValues [] = {0, false, false, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int maxValues [] = {2, true, true, true, true, 40, 3, 0, 15, 15, 15, 15, 15, 15};


enum subFunction {FBass, FMiddle, FTreble};
int currentSubFunction = FTreble;
int subFunctionValues [] = {7, 7, 7};
int subMinValues [] = {-14, -14, -14};
int subMaxValues [] = {14, 14, 14}; 

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(HPF_PIN, OUTPUT);
  pinMode(HPF_LPF_PIN_A, OUTPUT);
  pinMode(HPF_LPF_PIN_B, OUTPUT);

  /*digitalWrite(RELAY_PIN, HIGH);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("     YAMAHA     ");
  lcd.setCursor(0, 1);
  lcd.print(" 6-CH AMPLIFIER ");
  delay(2000);

  lcd.setCursor(0, 0);
  lcd.print("   GOING INTO   ");
  lcd.setCursor(0, 1);
  lcd.print("   SLEEP MODE   ");
  delay(1500);
  lcd.noBacklight();
  lcd.clear();

  digitalWrite(RELAY_PIN, LOW);*/

  Serial.begin(115200);
  irrecv.enableIRIn();
}


void loop() {
  buttonValue = analogRead(BUTTON_PIN);

  if (buttonValue > 900) {
    while (buttonValue > 900) {
      buttonValue = analogRead(A2);
    }
    executeAction(2);
  }

  else if (buttonValue > 550) {
    while ((buttonValue > 600) & (buttonValue < 800)) {
      buttonValue = analogRead(A2);
    }
    executeAction(1);
  }

  else if (buttonValue > 200) {
    if (!relay_state) {
      switchPower(true);
    }
    powerButtonTime = millis();
    while ((buttonValue > 300) & (buttonValue < 500)) {
      buttonValue = analogRead(A2);
      if (((millis() - powerButtonTime) > 1500) && relay_state) {
        switchPower(false);
      }
    }
    executeAction(0);
  }
  
  handleRemote();

}
