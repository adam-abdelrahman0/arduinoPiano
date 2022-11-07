#define speakerPinGs2 6
#define speakerPinB2 3
#define speakerPinA2 7
#define speakerPinC3 9
#define speakerPinD3 10
#define buttonGs2 5
#define buttonB2 4
#define buttonA2 2
#define buttonAll 8

byte notesActive = 0;
String button = "button";
const char* buttons[12] = {buttonGs2,buttonB2,buttonA2,buttonAll}; //array to track all buttons currently pressed
byte pressed[12];
byte pressedCopy[12]; //meant to be separate from pressed in memory to check against pressed
int keyToPitch[5][2] = {{speakerPinGs2, 24},
                          {speakerPinA2, 20},
                          {speakerPinB2, 27},
                          {speakerPinC3, 28},
                          {speakerPinD3, 30}};

int pinToChar[7] = {6,3,7,5,4,2,8};
const char* DUPpinToChar[7][2] = {{"speakerPinGs2", "6"},
                      {"speakerPinB2", "3"},
                      {"speakerPinA2", "7"},
                      {"buttonGs2", "5"},
                      {"buttonB2", "4"},
                      {"buttonA2", "2"},
                      {"buttonAll", "8"}};



//returns note at index [i][1]
int noteInArray(const char* note) {
  for (int i = 0; i < 5; i++) {
    if (keyToPitch[i][0] == note) {
      return keyToPitch[i][1];
    }
  }
  return -1;
}

int pinToInt(const char* note) {
  for (int i = 0; i < 5; i++) {
    if (DUPpinToChar[i][0] == note) {
      return pinToChar[i];
    }
  }
  return -1;
}

void setup() {
  Serial.begin(9600);

  pinMode(speakerPinGs2, OUTPUT);
  pinMode(speakerPinB2, OUTPUT);
  pinMode(speakerPinA2, OUTPUT);

  pinMode(buttonGs2, INPUT_PULLUP);
  pinMode(buttonB2, INPUT_PULLUP);  
  pinMode(buttonA2, INPUT_PULLUP);
  pinMode(buttonAll, INPUT_PULLUP);

}

void playNoteGs2() {
  long halfPeriod = getPeriodForKey(24) / 2;
  while(halfPeriod > 0 && digitalRead(buttonGs2) == 0 && digitalRead(buttonB2) == 1) {
    digitalWrite(speakerPinGs2, HIGH);
    wait(halfPeriod);
    digitalWrite(speakerPinGs2, LOW);
    wait(halfPeriod);
  }
}
void playNoteB2() {
  long halfPeriod = getPeriodForKey(27) / 2;
  while(halfPeriod > 0 && digitalRead(buttonB2) == 0 && digitalRead(buttonGs2)==1) {
    digitalWrite(speakerPinB2, HIGH);
    wait(halfPeriod);
    digitalWrite(speakerPinB2, LOW);
    wait(halfPeriod);
  }
}

void playNoteA2() {
  long halfPeriodA2 = getPeriodForKey(20) / 2000;

  unsigned long lastPressed = millis();

  boolean i = HIGH;

  while(halfPeriodA2 > 0 && digitalRead(buttonA2) == 0 && digitalRead(buttonB2) == 1 && digitalRead(buttonGs2) == 1) {
    if (millis() - lastPressed >= halfPeriodA2) {
      digitalWrite(speakerPinB2, i);
      i = !i;
      lastPressed = millis();
    }
  
  }
}

void playNotesGs2B2() {
  float halfPeriodB2 = getPeriodForKey(27) / 2;
  float halfPeriodGs2 = getPeriodForKey(24) / 2;


  float lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed
  float lastPressed2 = micros();

  boolean k = HIGH;
  boolean j = HIGH;
  while(digitalRead(buttonB2) == 0 && digitalRead(buttonGs2) == 0 && digitalRead(buttonA2) == 1) {
    if (micros() - lastPressed1 >= halfPeriodB2) {
      digitalWrite(speakerPinB2, k);
      k = !k;
      lastPressed1 = micros();
    }
    if (micros() - lastPressed2 >= halfPeriodGs2) {
      digitalWrite(speakerPinGs2, j);
      j = !j;
      lastPressed2 = micros();
    }
  }
}

//plays 1 note
void playNote(const char* note1) {
  long halfPeriod1 = getPeriodForKey(noteInArray(note1)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed

  int button1 = pinToInt(note1);

  boolean i = HIGH;
  
  while(checkSamePressed(pressedCopy)) {
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(note1, i);
      i = !i;
      lastPressed1 = micros();
    }
  }
  for (int i = 0; i < 3; i++) { //checks buttons pushed
    pressed[i] = digitalRead(buttons[i]);
  }
}

//plays 2 notes simultaneously
void playNotes(const char* note1, const char* note2) {
  long halfPeriod1 = getPeriodForKey(noteInArray(note1)) / 2;
  long halfPeriod2 = getPeriodForKey(noteInArray(note2)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed
  unsigned long lastPressed2 = micros();

  int button1 = pinToInt(note1);
  int button2 = pinToInt(note2);

  boolean i, j = HIGH;

  while(checkSamePressed(pressedCopy)) {
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(note1, i);
      i = !i;
      lastPressed1 = micros();
    }
    if (micros() - lastPressed2 >= halfPeriod2) {
      digitalWrite(note2, j);
      j = !j;
      lastPressed2 = micros();
    }
  }
  for (int i = 0; i < 3; i++) { //checks buttons pushed
    pressed[i] = digitalRead(buttons[i]);
  }
}

void playNotes(const char* note1, const char* note2, const char* note3) { //takes in the speaker pin (i.e. note1 = speakerPinA2)
  long halfPeriod1 = getPeriodForKey(noteInArray(note1)) / 2;
  long halfPeriod2 = getPeriodForKey(noteInArray(note2)) / 2;
  long halfPeriod3 = getPeriodForKey(noteInArray(note3)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed
  unsigned long lastPressed2 = micros();
  unsigned long lastPressed3 = micros();

  int button1 = pinToInt(note1);
  int button2 = pinToInt(note2);
  int button3 = pinToInt(note3);

  boolean i, j, k = HIGH;
  
  while(checkSamePressed(pressedCopy)) {
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(note1, i);
      i = !i;
      lastPressed1 = micros();
    }
    if (micros() - lastPressed2 >= halfPeriod2) {
      digitalWrite(note2, j);
      j = !j;
      lastPressed2 = micros();
    }
    if (micros() - lastPressed3 >= halfPeriod3) {
      digitalWrite(note3, k);
      k = !k;
      lastPressed3 = micros();
    }
  }
  for (int i = 0; i < 3; i++) { //checks buttons pushed
    pressed[i] = digitalRead(buttons[i]);
  }
}

/*
 * Returns the period for a key or zero for key numbers outside the range of 1 -
 * 88.
 * 
 * keyNumber - The key number (1 - 88)
 * function retrieved from https://gist.github.com/codeandmake/1add672bc7957135ac4e212360acbc98#file-gistfile1-txt
 */
long getPeriodForKey(uint8_t keyNumber) {
  // If the key is between 1 and 88
  if(keyNumber >= 1 && keyNumber <= 88) {
    // Return the period (one second divided by the frequency of the key)
    return 1000000L / (pow(2.0, (keyNumber - 49.0) / 12.0) * 440.0);
  }

  // Otherwise return zero
  return 0;
}

/*
 * Delay for a number of microseconds. This is necessary because
 * delayMicroseconds() has an upper limit.
 * 
 * us - The delay in microseconds
 */
void wait(long us) {
  // First delay for the number of whole milliseconds using delay()
  delay(us / 1000);
  // Then delay for the remainder of microseconds using delayMicroseconds()
  delayMicroseconds(us % 1000);
}

boolean checkSamePressed(const char* buttonsPressed) {

  for (int i = 0; i < 3; i++) {
    pressedCopy[i] = pressed[i];
    pressed[i] = digitalRead(buttons[i]);
    if (pressed[i] != buttonsPressed[i]) {
      return false;
    } 
  }
  return true;
}

void loop() {
  for (int i = 0; i < 3; i++) { //checks buttons pushed
    pressed[i] = digitalRead(buttons[i]);
  }

  if(digitalRead(buttonB2) == 0 && digitalRead(buttonGs2)==0 && digitalRead(buttonA2)== 0) {
    Serial.println("G#2, A2, B2");
    playNotes(speakerPinGs2,speakerPinB2,speakerPinA2);
  }
  else if (digitalRead(buttonA2) == 1 && digitalRead(buttonB2) == 1 && digitalRead(buttonGs2)==0) {
    Serial.println("G#2");
    playNote(speakerPinGs2);
  }
  else if (digitalRead(buttonA2) == 1 && digitalRead(buttonB2) == 0 && digitalRead(buttonGs2)==1) {
    Serial.println("B2");
    playNote(speakerPinB2);
  }
  else if (digitalRead(buttonA2) == 0 && digitalRead(buttonB2) == 1 && digitalRead(buttonGs2)==1) {
    Serial.println("A2");
    playNote(speakerPinA2);
  }
  else if (digitalRead(buttonB2) == 0 && digitalRead(buttonGs2)==0 && digitalRead(buttonA2) == 1) {
    Serial.println("B2 and G#2");
    playNotes(speakerPinB2, speakerPinGs2);
  }
  else if (digitalRead(buttonB2) == 1 && digitalRead(buttonGs2)==0 && digitalRead(buttonA2) == 0) {
    Serial.println("G#2 and A2");
    playNotes(speakerPinGs2, speakerPinA2);
  }
  else if (digitalRead(buttonB2) == 0 && digitalRead(buttonGs2)==1 && digitalRead(buttonA2) == 0) {
    Serial.println("B2 and A2");
    playNotes(speakerPinB2, speakerPinA2);
  }


  
  
}