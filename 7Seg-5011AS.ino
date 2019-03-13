/*
 * 7Segment 5011AS Common Cathode 
 * 13.03.2019 Baykan T. baykant@gmail.com
 * 
 */

// uncomment below for DEBUG output 
//#define DEBUG

// segmentBits[] can be used with PORTD directly if connections as follows
// a = D0, b = D1, c = D2, d = D3
// e = D4, e = D5, f = D6, dp = D7
// If only PORTD (D0-D7) is used, do not define DEBUG, also disconnect D0, D1 for program upload. 

const byte segmentBits [] {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111, // 9
  B01110111, // A
  B01111100, // b
  B00111001, // C
  B01011110, // d
  B01111001, // E
  B01110001, // F
};


// used for e = D8, f = D9, g = D10, dp = D11 
const byte upperSegmentBits [] {
  B00000011, // 0
  B00000000, // 1
  B00000101, // 2
  B00000100, // 3
  B00000110, // 4
  B00000110, // 5
  B00000111, // 6
  B00000000, // 7
  B00000111, // 8
  B00000110, // 9
  B00000111, // A
  B00000111, // b
  B00000011, // C
  B00000101, // d
  B00000111, // E
  B00000111, // F
};

// used for a = D4, b = D5, c = D6, d = D7
const byte lowerSegmentBits [] {
  B11110000, // 0
  B01100000, // 1
  B10110000, // 2
  B11110000, // 3
  B01100000, // 4
  B11010000, // 5
  B11010000, // 6
  B01110000, // 7
  B11110000, // 8
  B11110000, // 9
  B01110000, // A
  B11000000, // b
  B10010000, // C
  B11100000, // d
  B10010000, // E
  B00010000, // F
};

int count = 0;
const int firstPin = 4;
const int lastPin  = 12;

void writeSegment(int value) {
#ifdef DEBUG
  Serial.println(PORTD);
#endif  
  PORTD &= ~(B11110000); // clear lower bits D4-D7, do not change other PORTD bits
#ifdef DEBUG
  Serial.println(PORTD); // set bits for D4-D7 in PORTD
#endif  
  PORTB &= ~(B00001111); // clear upper bits D8-D11, do not change other PORTB bits
  PORTD |= lowerSegmentBits[value];
#ifdef DEBUG
  Serial.println(PORTD); // set bits for D8-D11 in PORTB
#endif  
  PORTB |= upperSegmentBits[value];  
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  for (int i = firstPin; i < lastPin; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  if (count < 0x10) {
#ifdef DEBUG    
    Serial.println(count);
#endif
    writeSegment(count);
    delay(500);
    count++;
  } else {
    count = 0;
  }
}
