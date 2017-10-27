//#include <avr/pgmspace.h>

#define BUTTON_PRESS_TIME 15
#define ROLL_COUNT 1 // Don't be too greedy

//******************** Tips about the sheet file *******************
// BPM value format: "B12345\n"
// BPM value can't have more than 15 digits including the decimal.
// For example, "B166.6667" is valid but "B166.66666666666667" is not.
// This is the sheet of 「前前前世」 (Not verified; might have mistakes)
char* sheetFile = "B126.6666667\n"
                  "404040404040"
                  "B190\n"
                  "1000100010102000100010001020100010001000101020001000100020102020"
                  "1000100010102000100010002010200011102010200010005555555500000000"
                  "1000201010002010001020001010200010002010100020100010200010102000"
                  "1010202210102000101020112010200010002000101020100010200011102000"
                  "1000201010002010001020101010200010002010100020100010200011102000"
                  "1010202210102010101020221010222010002000101020100010200011102000"
                  "1010202210102022101020221010222010002000100010200020101020112000"
                  "1110201110201110201110201111200055555555550020100010201000112000"
                  "1110201110201110201110201111200055555555550020100010201110102000"
                  "3000001020000010001000102000000010000010200020000010001020000000"
                  "10000010200000100010001020112000"
                  "1010201110201010201120201110200010102011102010200011111110000000"
                  "1110111011102011102011200020112011102022101020100010201110102010"
                  "0010202210102220001020112010200011102011202011200011102000102220"
                  "1110111011102011102011200020112011112022102011200010201110201120"
                  "00102022102011200022102010221120001020001010201000102000"
                  "B126.6666667\n"
                  "211211"
                  "B190\n"
                  "2000001020002010001020112020222210205555555555555555550040400000\0"
                  ;

float bpm;
int sheetCursor;
int bpmCursor;
bool started;
float currentTime;

void setup() {
  pinMode(A0, OUTPUT); // A0 - left don
  pinMode(A1, OUTPUT); // A1 - right don
  pinMode(A2, OUTPUT); // A2 - left kat
  pinMode(A3, OUTPUT); // A3 - right kat
  pinMode(A4, INPUT); // A4 - start switch

  sheetCursor = 0;
  started = false;

  Serial.begin (9600);
}

void loop() {

  currentTime = millis();
  if (analogRead(A4) >= 1023) {
    started = true;
  }
  if (sheetCursor > strlen(sheetFile)) {
    started = false; // Automatic reset after the song ends
  }
  if (!started) {
    return;
  }
  switch (sheetFile[sheetCursor]) {
    case 'B':
      bpmCursor = sheetCursor + 1;
      while (sheetFile[bpmCursor] != '\n') {
        bpmCursor++;
      }
      char bpmText[15];
      strncpy(bpmText, &sheetFile[sheetCursor + 1], bpmCursor - sheetCursor - 1);
      bpm = atof(bpmText);
      sheetCursor = bpmCursor + 1;
      return;
    case '0': // Empty
      delay (15000.0 / bpm - millis() + currentTime);
      sheetCursor++;
      return;
    case '1': // small don
      digitalWrite(A1, HIGH);
      delay (BUTTON_PRESS_TIME);
      digitalWrite(A1, LOW);
      sheetCursor++;
      delay (15000.0 / bpm - millis() + currentTime);
      return;
    case '2': // small kat
      digitalWrite(A3, HIGH);
      Serial.print ("o");
      delay (BUTTON_PRESS_TIME);
      digitalWrite(A3, LOW);
      sheetCursor++;
      delay (15000.0 / bpm - millis() + currentTime);
      return;
    case '3': // big don
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      Serial.print ("X");
      delay (BUTTON_PRESS_TIME);
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      sheetCursor++;
      delay (15000.0 / bpm - millis() + currentTime);
      return;
    case '4': // big kat
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      Serial.print ("O");
      delay (BUTTON_PRESS_TIME);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      sheetCursor++;
      delay (15000.0 / bpm - millis() + currentTime);
      return;
    case '5': // ROLL_COUNT
      for (int i = 0; i < ROLL_COUNT; i++) {
        digitalWrite(A1, HIGH);
        delay (BUTTON_PRESS_TIME);
        digitalWrite(A1, LOW);
        delay (BUTTON_PRESS_TIME);
      }
      sheetCursor++;
      delay (15000.0 / bpm - millis() + currentTime);
      return;
  }
}
