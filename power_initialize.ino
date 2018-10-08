void switchPower(bool powerState) {

  relay_state = powerState;

  if (!powerState) {
    audio.muteOff();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      BYE!      ");
    delay(1500);
    lcd.clear();
    lcd.noBacklight();
    digitalWrite(RELAY_PIN, LOW);
  }
  else {
    digitalWrite(RELAY_PIN, HIGH);
    initialize();
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("    WELCOME!    ");
    delay(1500);
    lcd.clear();
  }
}

void initialize() {
  lcd.begin (16, 2);
  int rtnCode = audio.init();
  audioSelect(1, 0);
  audio.muteOff();

  audio.masterVolume(0);

  audioSelectorSend(SELECT_2CH_INPUT_1);    //select 6ch input
  audioSelectorSend(UNMUTE_ALL);          //unmute all
  audioSelectorSend(ENABLE_6dB_AMP);
}

