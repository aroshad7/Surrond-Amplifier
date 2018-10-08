eepromUpdate(uint8_t parameter, int value) {
  EEPROM.update(parameter, value);
}

eepromRestore() {
  functionValues[FBass] = EEPROM.read(0);
  functionValues[FMiddle] = EEPROM.read(1);
  functionValues[FTreble] = EEPROM.read(2);
  functionValues[F3D] = EEPROM.read(3);
  functionValues[FEq] = EEPROM.read(4);

  mute_state = EEPROM.read(5);
  threeD_state = EEPROM.read(6);
  enhanced_surround_state = EEPROM.read(7);
  sixdB_amp_state = EEPROM.read(8);
  DBFB_state = EEPROM.read(9);
  DBFB_level_state = EEPROM.read(10);
  hpf_state = EEPROM.read(11);
  filter_state = EEPROM.read(12);
  hlpf_state = EEPROM.read(13);
  input_source_state = EEPROM.read(14);
}

