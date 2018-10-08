int audioSelectorSend(unsigned char c)
{
  //  shift address to right - Wire library always uses 7 bit addressing
  Wire.beginTransmission(0x94 >> 1); // transmit to device 0x94, PT2323
  Wire.write(c);
  int rtnCode = Wire.endTransmission(); // stop transmitting
  return rtnCode;
}


void audioSelect(uint8_t hpf, uint8_t hlpf) {

  digitalWrite(HPF_PIN, hpf);

  switch (hlpf) {
    case 0:
      digitalWrite(HPF_LPF_PIN_A, LOW);
      digitalWrite(HPF_LPF_PIN_B, LOW);
      break;
    case 1:
      digitalWrite(HPF_LPF_PIN_A, HIGH);
      digitalWrite(HPF_LPF_PIN_B, LOW);
      break;
    case 2:
      digitalWrite(HPF_LPF_PIN_A, LOW);
      digitalWrite(HPF_LPF_PIN_B, HIGH);
      break;
    case 3:
      digitalWrite(HPF_LPF_PIN_A, HIGH);
      digitalWrite(HPF_LPF_PIN_B, LOW);
      break;
    default:
      break;
  }
}
