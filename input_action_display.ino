void executeAction(uint8_t button) {
  switch (button) {
    case 0:
      currentFunction++;
      if (currentFunction >= FEnd)
        currentFunction = FMasterVolume;
      displayFunction();
      Serial.println(currentFunction);
      return;

    case 1:
      if (functionValues[currentFunction] < maxValues[currentFunction])
        functionValues[currentFunction] += 1;
      displayFunction();
      return;

    case 2:
      if (functionValues[currentFunction] > minValues[currentFunction])
        functionValues[currentFunction] -= 1;
      displayFunction();
      return;
  }
}


void displayFunction() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (currentFunction) {
    default:
    case FMasterVolume:
      lcd.print("Master Volume");
      if (functionValues[FMasterVolume] == 0)
        audio.masterVolume(-79);
      else if (functionValues[FMasterVolume] <= 5)
        audio.masterVolume((functionValues[FMasterVolume] * 5) - 64); //15-79
      else
        audio.masterVolume(functionValues[FMasterVolume] - 40);       //35-79
      break;
    case FFrontLeftVolume:
      lcd.print("Front Left Vol.");
      audio.leftVolume(functionValues[FFrontLeftVolume] - 15);
      break;
    case FFrontRightVolume:
      lcd.print("Front Right Vol.");
      audio.rightVolume(functionValues[FFrontRightVolume] - 15);
      break;
    case FCenterVolume:
      lcd.print("Center Volume");
      audio.centerVolume(functionValues[FCenterVolume] - 15);
      break;
    case FRearLeftVolume:
      lcd.print("Rear Left Vol.");
      audio.rearLeftVolume(functionValues[FRearLeftVolume] - 15);
      break;
    case FRearRightVolume:
      lcd.print("Rear Right Vol.");
      audio.rearRightVolume(functionValues[FRearRightVolume] - 15);
      break;
    case FSubVolume:
      lcd.print("Subwoofer Vol.");
      audio.subwooferVolume(functionValues[FSubVolume] - 15);
      break;
//    case FBass:
//      lcd.print("Bass");
//      audio.bass(functionValues[FBass]);
//      break;
//    case FMiddle:
//      lcd.print("Middle");
//      audio.middle(functionValues[FMiddle]);
//      break;
//    case FTreble:
//      lcd.print("Treble");
//      audio.treble(functionValues[FTreble]);
//      break;
    case F3D:
      lcd.print("3D");
      lcd.setCursor(0, 1);
      if (functionValues[F3D] == true) {
        lcd.print("On");
        audio._3DOn();
      }
      else {
        lcd.print("Off");
        audio._3DOff();
      }
      return;

    case FDBFB:
      lcd.print("DBFB LEVEL");
      lcd.setCursor(0, 1);
      if (functionValues[FDBFB] == 0) {
        lcd.print("Off");
      }
      else if (functionValues[FDBFB] == 1) {
        lcd.print("low");
      }
      else {
        lcd.print("high");
      }
      return;


    case FFilter:
      lcd.print("FILTER");
      lcd.setCursor(0, 1);
      if (functionValues[FFilter] == true) {
        lcd.print("On");
      }
      else {
        lcd.print("Off");
      }
      return;


    case FEnchancedSurround:
      lcd.print("ENHANCED SURR");
      lcd.setCursor(0, 1);
      if (functionValues[FEnchancedSurround] == true) {
        lcd.print("On");
      }
      else {
        lcd.print("Off");
      }
      return;


    case F6dBAmp:
      lcd.print("6dB AMP");
      lcd.setCursor(0, 1);
      if (functionValues[F6dBAmp] == true) {
        lcd.print("On");
      }
      else {
        lcd.print("Off");
      }
      return;


    case FEq:
      lcd.print("FRONT CHANNEL EQ");
      lcd.setCursor(0, 1);
      if (functionValues[FEq] == 0) {
        lcd.print("OFF");
        audio.toneOff();
      }
      else if (functionValues[FEq] == 1) {
        lcd.print("JAZZ");
        //audio.toneOff();
      }
      else if (functionValues[FEq] == 2) {
        lcd.print("ROCK");
        //audio.toneOff();
      }
      else {
        lcd.print("CUSTOM");
        //audio.toneOff();
      }
      return;
  }
  lcd.setCursor(0, 1);
  lcd.print(functionValues[currentFunction]);
}
