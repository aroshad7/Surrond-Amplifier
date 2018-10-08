void handleRemote() {
  if (irrecv.decode(&results)) {
    if ((results.value == CHH) || (results.value == CHH_2)) {
      switchPower(!relay_state);
    }
    else if (relay_state) {
      if ((results.value == CHL) || (results.value == CHL_2)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mute");
        lcd.setCursor(0, 1);
        if (mute_state) {
          mute_state = false;
          audio.muteOff();
          audioSelectorSend(UNMUTE_ALL);
          lcd.print("Off");
          delay(500);
          currentFunction = FMasterVolume;
          displayFunction();
        }
        else {
          mute_state = true;
          audio.muteOn();
          audioSelectorSend(MUTE_ALL);
          lcd.print("On");
        }
      }
      else if ((results.value == CH) || (results.value == CH_2)) {
        input_source_state++;
        if (input_source_state > 1)
          input_source_state = 0;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  INPUT SOURCE  ");
        lcd.setCursor(0, 1);
        if (input_source_state == 0) {
          audioSelectorSend(SELECT_6CH_INPUT);
          lcd.print(" SURROUND INPUT ");
        }
        else if (input_source_state == 1) {
          audioSelectorSend(SELECT_2CH_INPUT_1);
          lcd.print("  STEREO INPUT  ");
        }
      }

      else if (results.value == PP) {

        if (currentFunction == FEq && functionValues[FEq] == maxValues[FEq]) {
          if (currentSubFunction < FTreble)
            currentSubFunction++;
          else
            currentSubFunction = FBass;

          lcd.clear();
          lcd.print("CUSTOM EQUALIZER");
          lcd.setCursor(0, 1);
          switch (currentSubFunction) {
            case FBass:
              lcd.print("BASS");
              break;
            case FMiddle:
              lcd.print("MID");
              break;
            case FTreble:
              lcd.print("TREBLE");
              break;
          }
          displayEQValues();
        }

        else if ((currentFunction != FDBFB) && (currentFunction != FFilter) && (currentFunction != FEnchancedSurround) && (currentFunction != F6dBAmp) && (currentFunction != F3D)) {
          currentFunction = FDBFB;
          displayFunction();
        }

        else if (currentFunction == F3D) {
          currentFunction = FDBFB;
          displayFunction();
        }

        else {
          currentFunction++;
          displayFunction();
        }
      }

      else if (results.value == NEXT) {
        if (currentFunction == FEq) {
          if (subFunctionValues[currentSubFunction] < subMaxValues[currentSubFunction])
            subFunctionValues[currentSubFunction] += 1;
          displayEQValues();
        }
        else if ((currentFunction == FDBFB) || (currentFunction == FFilter) || (currentFunction == FEnchancedSurround) || (currentFunction == F6dBAmp) || (currentFunction == F3D)) {
          if (functionValues[currentFunction] < maxValues[currentFunction])
            functionValues[currentFunction] += 1;
          else
            functionValues[currentFunction] = minValues[currentFunction];
          displayFunction();
        }
      }

      else if (results.value == PREV) {
        if (currentFunction == FEq) {
          if (subFunctionValues[currentSubFunction] > subMinValues[currentSubFunction])
            subFunctionValues[currentSubFunction] -= 1;
          displayEQValues();
        }
        else if ((currentFunction == FDBFB) || (currentFunction == FFilter) || (currentFunction == FEnchancedSurround) || (currentFunction == F6dBAmp) || (currentFunction == F3D)) {
          if (functionValues[currentFunction] > minValues[currentFunction])
            functionValues[currentFunction] -= 1;
          else
            functionValues[currentFunction] = maxValues[currentFunction];
          displayFunction();
        }
      }

      else if (results.value == EQ) {
        if (currentFunction != FEq)
          currentFunction = FEq;
        else if (functionValues[FEq] < maxValues[FEq])
          functionValues[currentFunction] += 1;
        else
          functionValues[FEq] = minValues[FEq];
        displayFunction();
      }
    }
    irrecv.resume(); // Receive the next value
  }
}

void displayEQValues() {
  lcd.setCursor(13, 1);
  if (subFunctionValues[currentSubFunction] < -9) {
    lcd.print(itoa(subFunctionValues[currentSubFunction], itoaBuffer, 10));
  }
  else if (subFunctionValues[currentSubFunction] < 0 || subFunctionValues[currentSubFunction] > 9 ) {
    lcd.print(" ");
    lcd.print(itoa(subFunctionValues[currentSubFunction], itoaBuffer, 10));
  }
  else {
    lcd.print("  ");
    lcd.print(itoa(subFunctionValues[currentSubFunction], itoaBuffer, 10));
  }
}

