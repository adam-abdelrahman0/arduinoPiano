#define speaker1 6
#define speaker2 3
#define speaker3 7
#define speaker4 9
#define speaker5 10
#define buttonGs2 5
#define buttonB2 4
#define buttonE2 2
#define buttonC3 8

byte notesActive = 0;
String button = "button";
const char* buttons[12] = {buttonGs2,buttonB2,buttonE2,buttonC3}; //array to track all buttons currently pressed
byte pressed[12];
byte pressedCopy[12]; //meant to be separate from pressed in memory to check against pressed
int keyToPitch[5][2] = {{buttonGs2, 24},
                          {buttonE2, 20},
                          {buttonB2, 27},
                          {buttonC3, 28},
                          };


//returns note at index [i][1]
int noteInArray(const char* note) {
  for (int i = 0; i < 5; i++) {
    if (keyToPitch[i][0] == note) {
      return keyToPitch[i][1];
    }
  }
  return -1;
}


void setup() {
  Serial.begin(9600);

  pinMode(speaker1, OUTPUT);
  pinMode(speaker2, OUTPUT);
  pinMode(speaker3, OUTPUT);
  pinMode(speaker4, OUTPUT);

  pinMode(buttonGs2, INPUT_PULLUP);
  pinMode(buttonB2, INPUT_PULLUP);  
  pinMode(buttonE2, INPUT_PULLUP);
  pinMode(buttonC3, INPUT_PULLUP);

}

//plays 1 note
void playNote(const char* button1) {
  long halfPeriod1 = getPeriodForKey(noteInArray(button1)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed

  boolean i = HIGH;
  
  while(digitalRead(button1) == 0 && checkNumPressed(1) == true) { //change conditional
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(speaker1, i);
      i = !i;
      lastPressed1 = micros();
    }
  }
  
}

//plays 2 notes simultaneously
void playTwoNotes(const char* button1, const char* button2) {
  long halfPeriod1 = getPeriodForKey(noteInArray(button1)) / 2;
  long halfPeriod2 = getPeriodForKey(noteInArray(button2)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed
  unsigned long lastPressed2 = micros();
  
  boolean i, j = HIGH;
  
  while(digitalRead(button1) == 0 && digitalRead(button2)==0 && checkNumPressed(2) == true) {/////////////
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(speaker1, i);
      i = !i;
      lastPressed1 = micros();
    }
    if (micros() - lastPressed2 >= halfPeriod2) {
      digitalWrite(speaker2, j);
      j = !j;
      lastPressed2 = micros();
    }
  }
}

void playThreeNotes(const char* button1, const char* button2, const char* button3) { //takes in the speaker pin (i.e. note1 = speakerPinA2)
  long halfPeriod1 = getPeriodForKey(noteInArray(button1)) / 2;
  long halfPeriod2 = getPeriodForKey(noteInArray(button2)) / 2;
  long halfPeriod3 = getPeriodForKey(noteInArray(button3)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed
  unsigned long lastPressed2 = micros();
  unsigned long lastPressed3 = micros();

  boolean i, j, k = HIGH;
  
  while(digitalRead(button1) == 0 && digitalRead(button2) == 0 && digitalRead(button3) == 0 && checkNumPressed(3) == true) {
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(speaker1, i);
      i = !i;
      lastPressed1 = micros();
    }
    if (micros() - lastPressed2 >= halfPeriod2) {
      digitalWrite(speaker2, j);
      j = !j;
      lastPressed2 = micros();
    }
    if (micros() - lastPressed3 >= halfPeriod3) {
      digitalWrite(speaker3, k);
      k = !k;
      lastPressed3 = micros();
    }
  }
}

void playFourNotes(const char* button1, const char* button2, const char* button3, const char* button4) { //takes in the speaker pin (i.e. note1 = speakerPinA2)
  long halfPeriod1 = getPeriodForKey(noteInArray(button1)) / 2;
  long halfPeriod2 = getPeriodForKey(noteInArray(button2)) / 2;
  long halfPeriod3 = getPeriodForKey(noteInArray(button3)) / 2;
  long halfPeriod4 = getPeriodForKey(noteInArray(button4)) / 2;

  unsigned long lastPressed1 = micros(); //stores last time pressed (microseconds) for periods elapsed
  unsigned long lastPressed2 = micros();
  unsigned long lastPressed3 = micros();
  unsigned long lastPressed4 = micros();

  boolean i, j, k, l = HIGH;
  
  while(digitalRead(button1) == 0 && digitalRead(button2) == 0 && digitalRead(button3) == 0 && digitalRead(button4) == 0 && checkNumPressed(4) == true) {
    if (micros() - lastPressed1 >= halfPeriod1) {
      digitalWrite(speaker1, i);
      i = !i;
      lastPressed1 = micros();
    }
    if (micros() - lastPressed2 >= halfPeriod2) {
      digitalWrite(speaker2, j);
      j = !j;
      lastPressed2 = micros();
    }
    if (micros() - lastPressed3 >= halfPeriod3) {
      digitalWrite(speaker3, k);
      k = !k;
      lastPressed3 = micros();
    }
    if (micros() - lastPressed4 >= halfPeriod4) {
      digitalWrite(speaker4, l);
      l = !l;
      lastPressed4 = micros();
    }
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

boolean checkNumPressed(int numberPressed) {
  int numPressed = 0;
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttons[i]) == 0) {
      numPressed++;
    }
  }
  if (numPressed != numberPressed) {
    return false;
  }
  return true;
}
int checkNumPressed() {
  int numPressed = 0;
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttons[i]) == 0) {
      numPressed++;
    }
  }
  return numPressed;
}

void getArrayPressed(int expectedLow) {
  int numLow = 0;
  int index = 0;
  while (numLow < expectedLow) {
    if (digitalRead(buttons[index]) == 0) {
      numLow++;
      pressed[index] = buttons[index];      
    }
    index++;
  }
}


void loop() {
  if (checkNumPressed() == 1) {
    Serial.println("one pressed");
    getArrayPressed(1);
    playNote(pressed[0]);
  }
  else if (checkNumPressed() == 2) {
    Serial.println("two pressed");
    getArrayPressed(2);
    playTwoNotes(pressed[0], pressed[1]);
  }
  else if (checkNumPressed() == 3) {
    Serial.println("three pressed");
    getArrayPressed(3);
    playThreeNotes(pressed[0], pressed[1], pressed[2]);
  }
  else if (checkNumPressed() == 4) {
    Serial.println("four pressed");
    getArrayPressed(4);
    playFourNotes(pressed[0], pressed[1], pressed[2], pressed[3]);
  }
}