byte changed;
byte state;
byte mask;
byte which;
byte vals[3];

void setup() {
  Serial.begin(250000);
}

void loop() {
  if (Serial.available()) {
    char got = Serial.read();
    if (got == 'T') {
      state = 1;
    } else if (isdigit(got)) {
      if (state == 1) {
        if (got >= '1' && got <= '3') {
          state = 2;
          which = got - '1';
          mask = 1 << which;
          vals[which] = 0;
        } else {
          state = 0;
        }
      } else if (state == 3) {
        vals[which] <<= 1;
        if (got == '1') {
          vals[which]++;
        } else if (got != '0') {
          state = 0;
        }
      }
    } else if (got == ':') {
      if (state == 2) {
        state = 3;
      }
    } else if (got == 10 || got == ',') {
      if (state == 3) {
        changed |= mask;
        state = 0;
      }
    }
  }
  if (changed) {
    for (byte i = 0; i < sizeof(vals); i++) {
      if (changed & (1 << i)) {
        Serial.print(F(" T"));
        Serial.print(i + 1);
        Serial.print(F(" = "));
        Serial.print(vals[i], BIN);
      }
    }
    Serial.println();
    changed = 0;
  }
}
