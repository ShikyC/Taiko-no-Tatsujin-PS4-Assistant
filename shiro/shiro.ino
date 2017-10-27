//#include <avr/pgmspace.h>

#define BUTTON_PRESS_TIME 20

//******************** Tips about the sheet file *******************
// BPM value format: "B12345\n"
// BPM value can't have more than 15 digits including the decimal. 
// For example, "B166.6667" is valid but "B166.66666666666667" is not.
char* sheetFile = "B194\n"
  "300020202020200020201000"
  "100020202020111122221000"
  "102020102010201020000000"
  "100000000000100000000000"
  "102020102010201020000000"
  "100000000000100000100012"
  "102020102010201020100010"
  "100000100020102220122000"
  "102020102010201020100010"
  "100000100010202020102020"
  "1"
  "B193\n"
  "0002"
  "B192\n"
  "0200"
  "B191\n"
  "0001"
  "B184\n"
  "0102"
  "B183\n"
  "0200"
  "B182\n"
  "0001"
  "B181\n"
  "0102"
  "B178\n"
  "0200"
  "B176\n"
  "0001"
  "B162\n"
  "0102"
  "B150\n"
  "0201"
  "B140\n"
  "0200"
  "B120\n"
  "0000000"
  "3"
  "B194\n"
  "010201020112010"
  "0020001000112010"
  "0010202010112010"
  "0010202010111010"
  "0010201011201010"
  "0020001011201010"
  "0010202011201010"
  "0010201101201111"
  "0010201012112010"
  "0020001000112010"
  "2020112020112020"
  "1011201020111110"
  "0010201011201010"
  "0020001101201010"
  "0012201011201020"
  "1222122211121112"
  "0000300020102000"
  "1000201020102000"
  "1000201020002000"
  "1011221022112220"
  "1022221110102010"
  "1020201020102000"
  "1022221110102010"
  "1222122210107700"
  "100020002000100020002000"
  "100020002000100020001020"
  "100020002000100020002000"
  "100020102020102010101000"
  "1"
  "B145.5\n"
  "00200200122200100"
  "100222111222111212"
  "100212122122122122"
  "100200222100200200"
  "1"
  "B194\n"
  "11122227700111122227700"
  "111122227700111122227700"
  "100020002000100020202000"
  "100020002000100020002000"
  "100020002000100020002000"
  "202020202000202020202000"
  "202020202000202020202000"
  "202220202000202220202000"
  "20302020202020303000"
  "100020100010100010001000"
  "10002010001010001000"
  "100000100010100010001000"
  "100000100020100010221020"
  "300010200020100010002000"
  "101000200020100020001020"
  "202010200010200010002000"
  "10002010001020001022"
  "100010200010200010002000"
  "10001020001010002000"
  "102210200020100020001000"
  "102210201020102010201020"
  "102210201020102222222222"
  "100000000000"
  "5555555555555555"
  "5555555500112020"
  "1210201010112210"
  "1011221010221022"
  "1000201011200010"
  "1110201011201010"
  "0010201011112222"
  "1000201012221011"
  "2211221122112211"
  "2211221122112011"
  "2011102011102011"
  "1020111122221110"
  "1220102012201020"
  "1220102012201020"
  "B145.5\n"
  "101010101010"
  "B194\n"
  "1111111177777700"
  "0030000000000000"
  "\0"
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
  started = true;
  
  Serial.begin (9600);
  delay(5000);
}

void loop() {
  
  currentTime = millis();
  if (analogRead(A4) >= 1023) {
    Serial.print("Started\n");
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
  case '0':
    delay (15000.0/bpm - millis() + currentTime);
    sheetCursor++;
    return;
  case '1':
    Serial.print ("x");
    digitalWrite(A1, HIGH);
    delay (BUTTON_PRESS_TIME - millis() + currentTime);
    digitalWrite(A1, LOW);
    delay (15000.0/bpm - BUTTON_PRESS_TIME);
    sheetCursor++;
    return;
  case '2':
    Serial.print ("o");
    digitalWrite(A3, HIGH);
    delay (BUTTON_PRESS_TIME - millis() + currentTime);
    digitalWrite(A3, LOW);
    delay (15000.0/bpm - BUTTON_PRESS_TIME);
    sheetCursor++;
    return;
  case '3':
    Serial.print ("X");
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    delay (BUTTON_PRESS_TIME - millis() + currentTime);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    delay (15000.0/bpm - BUTTON_PRESS_TIME);
    sheetCursor++;
    return;
  case '4':
    Serial.print ("O");
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    delay (BUTTON_PRESS_TIME - millis() + currentTime);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    delay (15000.0/bpm - BUTTON_PRESS_TIME);
    sheetCursor++;
    return;
  default:
    delay (15000.0/bpm - millis() + currentTime);
    sheetCursor++;
    return;
  }
}
