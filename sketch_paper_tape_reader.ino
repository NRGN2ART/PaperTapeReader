/*
 * Andrew Seawright
 *
 * Arduino paper tape reader interface
 * 
 * Reads tape and prints hex bytes to serial
 * REMAX RRS7155BA1/660
 *
 * Sketch for Arduino Uno R3
 */

/* IO pin assignments */
#define DATA0 2 /* TRACK 1 */
#define DATA1 3 /* TRACK 2 */
#define DATA2 4 /* TRACK 3 */
#define DATA3 5 /* TRACK 4 */
#define DATA4 6 /* TRACK 5 */
#define DATA5 7 /* TRACK 6 */
#define DATA6 8 /* TRACK 7 */
#define DATA7 9 /* TRACK 8 */

#define DATA_READY 10
#define SYSTEM_READY_B 11
#define DRIVE_RIGHT_B 12
#define DRIVE_LEFT_B 13

#define BUTTON1 14
#define BUTTON2 15

#define STATE_IDLE 0
#define STATE_DRIVE1 1
#define STATE_DRIVE2 2
#define STATE_CAPTURE 3


#define DRIVE_B DRIVE_LEFT_B

int state = STATE_IDLE;
int byte_count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(DATA0, INPUT);
  pinMode(DATA1, INPUT);
  pinMode(DATA2, INPUT);
  pinMode(DATA3, INPUT);
  pinMode(DATA4, INPUT);
  pinMode(DATA5, INPUT);
  pinMode(DATA6, INPUT);
  pinMode(DATA7, INPUT);
  pinMode(DATA_READY, INPUT);
  pinMode(SYSTEM_READY_B, INPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  pinMode(DRIVE_RIGHT_B, OUTPUT);
  pinMode(DRIVE_LEFT_B, OUTPUT);

  digitalWrite(DRIVE_RIGHT_B, 1);
  digitalWrite(DRIVE_LEFT_B, 1);

  Serial.begin(9600);
  Serial.println("\n# Paper tape reader");
  Serial.println("# Push button 1 to start...");

  state = STATE_IDLE;
}

void loop() {
  // put your main code here, to run repeatedly:

  int ready = digitalRead(DATA_READY);
  int system_ready_b = digitalRead(SYSTEM_READY_B);
  int button1_b = digitalRead(BUTTON1);
  int button2_b = digitalRead(BUTTON2);
  int data = 0;

  switch (state) {
    case STATE_IDLE:
      byte_count = 0;
      digitalWrite(DRIVE_B, 1);
      if(button1_b==0) {
        state = STATE_DRIVE1;
         Serial.println("#Start");
      } 
      break;
    
    case STATE_DRIVE1:
      digitalWrite(DRIVE_B, 0);
       if (button2_b==0) {
        state = STATE_IDLE;
      }
      if (ready==0) {
        state = STATE_DRIVE2;
      }
      break;

    case STATE_DRIVE2:
      digitalWrite(DRIVE_B, 0);
      if (button2_b==0) {
        state = STATE_IDLE;
      }
      if (ready == 1) {
        state = STATE_CAPTURE;
      }
      break;
    
    case STATE_CAPTURE:
      data = (0x1 & digitalRead(DATA0)) | 
          ((0x1 & digitalRead(DATA1))<<1) | 
          ((0x1 & digitalRead(DATA2))<<2) |
          ((0x1 & digitalRead(DATA3))<<3) |
          ((0x1 & digitalRead(DATA4))<<4) |
          ((0x1 & digitalRead(DATA5))<<5) |
          ((0x1 & digitalRead(DATA6))<<6) |
          ((0x1 & digitalRead(DATA7))<<7);
   
      digitalWrite(DRIVE_B, 1);

      Serial.print((data<16) ? "0" : "");
      Serial.print(data, HEX);
      if ((byte_count%16)==15) {
        Serial.println();
      } else {
        Serial.print(" ");
      }
      ++byte_count;
      state = STATE_DRIVE1;
    break;

    
  }
}
