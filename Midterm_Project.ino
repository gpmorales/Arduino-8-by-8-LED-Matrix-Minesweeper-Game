/* @Author George Morales */
#include <Arduino.h>  

#define ROW_1 22  // PA0
#define ROW_2 23  // PA1
#define ROW_3 24  // PA2
#define ROW_4 25  // PA3
#define ROW_5 26  // PA4
#define ROW_6 27  // PA5
#define ROW_7 28  // PA6
#define ROW_8 29  // PA7

#define COL_1 30  // PC7
#define COL_2 31  // PC6
#define COL_3 32  // PC5
#define COL_4 33  // PC4
#define COL_5 34  // PC3
#define COL_6 35  // PC2
#define COL_7 36  // PC1
#define COL_8 37  // PC0

#define LEFT 50    // PB0 
#define RIGHT 52   // PB1 
#define UP 53      // PB2 
#define DOWN 51    // PB3 
#define MARKER 12  // PB6 



/* DEFINE GLOBAL VARS */
const int ONE_SECOND = 1000; // 1 second = 1000 milliseconds


/* PART 1 : BUFFERS and MESSAGES */
const byte FIRST_MESSAGE[] = {B01111110,B11100111,B11000011,B11000011,B11000011,B11000011,B11100111,B01111110}; // O
const byte SECOND_MESSAGE[] = {B01100011,B01100110,B01101100,B01111000,B01101100,B01100110,B01100011,B01100001}; // K
const byte FINAL_MESSAGE[] = {B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001}; // Hi

const byte MY_MESSAGE[] = {
    B00000000,B01111110,B00001000,B00001000,B01111110,B00000000,B00000000,B00000000, // H
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B00000000,B00000000,B00000000, 
    B00111110,B01000000,B00111100,B01000000,B00111110,B00000000,B00000000,B00000000, // W
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01111110,B00001010,B00001110,B01110000,B00000000,B00000000,B00000000,           // R
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B01111110,B01000010,B01000010,B00100100,B00011000,B00000000,B00000000,B00000000, // D
    B00000000,B01011110,B01011110,B00000000,B00000000,B00000000                      // !
};


/* PART 2 : GAME MESSAGES AND BUFFERS */
const byte LEVEL_ONE[] = {B00000000,B10000010,B10000110,B10000010,B10000010,B11100111,B00000000,B00000000};
const byte LEVEL_TWO[] = {B00000000,B10000111,B10000001,B10000111,B10000100,B11100111,B00000000,B00000000};
const byte LEVEL_THREE[] = {B00000000,B10000111,B10000001,B10000111,B10000001,B11100111,B00000000,B00000000};
const byte LEVEL_FOUR[] = {B00000000,B10000101,B10000101,B10000111,B10000001,B11100001,B00000000,B00000000};
const byte* LEVELS[] = { LEVEL_ONE, LEVEL_TWO, LEVEL_THREE, LEVEL_FOUR };
const byte SINGLE_DOT[] = {B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000000,B00000000}; 

const byte RINGS[4][8] = {
  {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},
  {B00000000,B00000000,B00011000,B00100100,B00100100,B00011000,B00000000,B00000000},
  {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000},
  {B01111110,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B01111110}
};

const byte READY_MESSAGE[] = {
    B00000000,B01111110,B00001010,B00001110,B01110000,B00000000,B00000000,B00000000, // R
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B01111110,B00001010,B00001010,B01111110,B00000000,B00000000,B00000000,           // A
    B01111110,B01000010,B01000010,B00100100,B00011000,B00000000,B00000000,B00000000, // D
    B00000010,B00000100,B01111000,B00000100,B00000010,B00000000,B00000000,B00000000, // Y
    B00000010,B00000001,B10111001,B00001001,B00000110,B00000000,B00000000,B00000000  // ?
};

const byte TASK_MESSAGE[] = {
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B00000010,B00000010,B01111110,B00000010,B00000010,B00000000,B00000000,           // T
    B01001110,B01001010,B01001010,B01111010,B00000000,B00000000,B00000000,           // S
    B00000000,B00000000,B00000000, // Space
    B00000010,B00000010,B01111110,B00000010,B00000010,B00000000,B00000000,           // T
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B01001110,B01001010,B01001010,B01111010,B00000000,B00000000,B00000000,           // S
    B00000010,B00000010,B01111110,B00000010,B00000010,B00000000,B00000000,B00000000, // T
    B00000000,B00000000,B00000000,
    B00000010,B00000100,B01111000,B00000100,B00000010,B00000000,B00000000,           // Y
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01111110,B01000000,B01000000,B01111110,B00000000,B00000000,B00000000,           // U
    B01111110,B00001010,B00001110,B01110000,B00000000,B00000000,B00000000,           // R
    B00000000,B00000000,B00000000, // Space
    B01111110,B00000100,B00001000,B00000100,B01111110,B00000000,B00000000,B00000000, // M
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B01111110,B00000100,B00001000,B00000100,B01111110,B00000000,B00000000,B00000000, // M
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01111110,B00001010,B00001110,B01110000,B00000000,B00000000,B00000000,           // R
    B00000010,B00000100,B01111000,B00000100,B00000010,B00000000,B00000000,           // Y
};

const byte LEVEL_MESSAGE[] = {
    B00111100,B01000010,B01000010,B01000010,B00000000,B00000000,B00000000,           // C
    B01111110,B00001000,B00001000,B01111110,B00000000,B00000000,B00000000,           // H
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01001110,B01001010,B01001010,B01111010,B00000000,B00000000,B00000000,           // S
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B00000000,B00000000,B00000000,
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B00111110,B01000000,B01000000,B00111110,B00000000,B00000000,B00000000,           // V
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B01100110,B01100110,B00000000,B00000000,B00000000,B00000000,B00000000            // :
};

const byte WIN_MESSAGE[] = {
    B00000010,B00000100,B01111000,B00000100,B00000010,B00000000,B00000000,           // Y
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01111110,B01000000,B01000000,B01111110,B00000000,B00000000,B00000000,           // U
    B00000000,B00000000, // Space
    B00111110,B01000000,B00111100,B01000000,B00111110,B00000000,B00000000,           // W
    B00000000,B01111010,B01111010,B00000000,B00000000,B00000000,                     // I
    B01111110,B00000100,B00001000,B00010000,B00100000,B01111110,B00000000,B00000000, // N
    B00000000,B00000000, // Space
    B00110000,B01000110,B01000000,B01000000,B01000110,B00110000,B00000000,B00000000  // (:
};

const byte LOSE_MESSAGE[] = {
    B00000010,B00000100,B01111000,B00000100,B00000010,B00000000,B00000000,           // Y
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01111110,B01000000,B01000000,B01111110,B00000000,B00000000,B00000000,           // U
    B00000000,B00000000,
    B01111110,B01000000,B01000000,B01000000,B00000000,B00000000,B00000000,           // L
    B00111100,B01000010,B01000010,B01000010,B00111100,B00000000,B00000000,B00000000, // O
    B01001110,B01001010,B01001010,B01111010,B00000000,B00000000,B00000000,           // S
    B01111110,B01001010,B01001010,B01001010,B00000000,B00000000,B00000000,           // E
    B00000000,B00000000,
    B01100000,B00010110,B00010000,B00010000,B00010110,B01100000,B00000000,B00000000  // ):
};



/********* GENERAL FUNCTIONS AND UTILITES *********/

void drawOnMatrixAndInvert(byte my_buffer[], boolean invert){ 
  byte message[8] = {0}; // Buffer to hold inverted LED pattern buffer strings
  
  for (byte i = 0; i < 8; i++) { 
    if (invert) message[i] = ~my_buffer[i]; 
    else message[i] = my_buffer[i];
    PORTC = ~(message[i]); // Invert the bit string from 'message[i]'. This sets the corresponding column pins in PORTC to HIGH, enabling the active column LEDS for that row
    PORTA |= (1 << i); // Set the ith bit in the PORTA register to HIGH, which activates the corresponding row (from PA0 to PA7) in the LED matrix
    delay(2);
    PORTA &= ~(1 << i); 
  }
}


void scrollMessageOnMatrix(const byte message[], int messageLength, int delayTime) {
  const int displayWidth = 8;
  byte displayBuffer[8] = {0};
  
  // Scroll the message from right to left
  for (int startColumn = -displayWidth; startColumn < messageLength + displayWidth; startColumn++) {
    // Fill the display buffer
    for (int col = 0; col < displayWidth; col++) {
      int messageColumn = startColumn + col; // Determine the message column to display
      byte columnData = 0;

      // Check if the current column is valid and access in reverse
      if (messageColumn >= 0 && messageColumn < messageLength) {
        columnData = message[messageColumn]; // Access message in reverse
      }
      
      // Fill the display buffer based on column data
      for (int row = 0; row < 8; row++) {
        if (columnData & (1 << row)) {
          displayBuffer[row] |= (1 << (7 - col)); // Set the corresponding bit
        } else {
          displayBuffer[row] &= ~(1 << (7 - col)); // Clear the corresponding bit
        }
      }
    }
    
    // Display the current frame
    long frame_start = millis();
    while (millis() - frame_start < delayTime) { // set delay between frames
      for (byte row = 0; row < 8; row++) {
        PORTC = ~(displayBuffer[row]); // Activate LED columns via the PORTC register pins for each row 
        PORTA |= (1 << row); // Set row to HIGH (PORTA register controls matrix rows)
        delay(2);
        PORTA &= ~(1 << row); // Set row to LOW
      }
    }
  }
}


// More basic implementation of scroll thats always 8 columns wide
void scrollMessageOnMatrix(const byte message[]){
  byte temp[8];
  for (int shift = 7; shift >= 0; shift--) { // shift bits more and more each time
    long frame_start = millis();
    while (millis() - frame_start < 100) { // delay current 'frame' on matrix
      for (byte i = 0; i < 8; i++) { // iterate through each row
        temp[i] = (message[i] << shift) | (message[i] >> 8 - shift);
        PORTC = ~(temp[i]); // Activate LED columns via the PORTC register pins for each row 
        PORTA |= (1 << i); // Set row to HIGH (PORTA register controls matrix rows)
        delay(2);
        PORTA &= ~(1 << i); 
      }
    }
  }
}


// Display flashing screen to capture players attention
void flashScreen(int flash) {
  for (int i = 0; i < 3; i++) {
    for (int state = 0; state < 2; state++) {
      byte columnData = state == 0 ? B11111111 : B00000000;
      long startTime = millis();
      while (millis() - startTime < flash) {  // Run for 350 milliseconds
        for (byte j = 0; j < 8; j++) { // iterate through each row
          PORTC = ~(columnData); // Activate LED columns via the PORTC register pins for each row 
          PORTA |= (1 << j); // Set row to HIGH (PORTA register controls matrix rows)
          delay(2);
          PORTA &= ~(1 << j); 
        }
      }
    }
  }
}



/********* GAME FUNCTIONS AND UTILITES *********/

int selectDifficulty() {
  int current_level = 1;
  
  while (true) {
    // Display current level
    drawOnMatrixAndInvert(LEVELS[current_level - 1], false); // Start at 'L 1'
    delay(2); 

    // Check buttons
    if (digitalRead(MARKER) == HIGH) {
      return current_level;
    } else if (digitalRead(UP) == HIGH && current_level < 4) {
      current_level++;
      while (digitalRead(UP) == HIGH) {
        drawOnMatrixAndInvert(LEVELS[current_level - 1], false);
        delay(3);  // Wait for button to be unpressed
      }
    } else if (digitalRead(DOWN) == HIGH && current_level > 1) {
      current_level--;
      while (digitalRead(DOWN) == HIGH) {
        drawOnMatrixAndInvert(LEVELS[current_level - 1], false);
        delay(3);  // Wait for button to be unpressed
      }
    }
  }
}

void mineAnimation() {
  // Add a distinct pattern to indicate the function is called
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) { 
      for (int k = 0; k < 5; k++) {
        drawOnMatrixAndInvert(RINGS[i], false);
      }
    }
  }
}

byte* plantMinesOnBoard(int N) {

  byte* board = (byte*) malloc(sizeof(byte) * 8);
  
  // Initialize board
  for (int i = 0; i < 8; i++) {
    board[i] = 0;
  }
  
  // Set exactly N random bits to 1
  for (int i = 0; i < N; i++) {
    while (true) {
      int row = random(8);
      int col = random(8);
      byte mask = 1 << (7 - col);  // Create a mask for the selected bit
      
      // If the bit is not already set, set it and break the loop
      if ((board[row] & mask) == 0) {
        board[row] |= mask;
        break;
      }
    }
  }

  return board;
}

void checkPlayerGuesses(byte finalBoard[]) {
  // Check if board was cleared, so all bits are 0
  for (int row = 0; row < 8; row++) {
   for (int col = 7; col >= 0; col--) {
     // Check if the bit is set (mine was not disarmed)
     if (finalBoard[row] & (1 << (7 - col))) { // Player Loses
       flashScreen(125);
       mineAnimation();
       flashScreen(125);
       scrollMessageOnMatrix(LOSE_MESSAGE, sizeof(LOSE_MESSAGE)/sizeof(LOSE_MESSAGE[0]), 60);
       return;
     } 
   }
  }
  
  scrollMessageOnMatrix(WIN_MESSAGE, sizeof(WIN_MESSAGE)/sizeof(WIN_MESSAGE[0]), 60);
}


void beginLevel(const int difficulty) {
    
  int N = 4;
  int flash_screen = 100;

  switch (difficulty) {
    case 1:
      N = 2;
      flash_screen = 200;
      break;
    case 2:
      N = 2;
      flash_screen = 150;
      break;
    case 3:
      N = 3;
      flash_screen = 125;
      break;
    default:
      break;
  }

  // Use random number gen to flips some bits on board for user to try and locate
  byte* board = plantMinesOnBoard(N);
 
  // flash random pattern for TODO time difficulty
  delay(150);
  for (int i = 0; i < flash_screen; i++) {
    drawOnMatrixAndInvert(board, false);
  }
  delay(150);
  

  // **** Start Level ****
  int i = 0;
  int crosshairX = 4;  // Start in the middle
  int crosshairY = 4;  
  int attempts = N;
  int markedPositions[5][2];
  
  // Now allow User to move with Cross-heir to try and pin the flashed LEDS
  byte tempBoard[8];
  
  for (int i = 0; i < 8; i++) {
    tempBoard[i] = SINGLE_DOT[i];
  }

  while (true) {
    // Display current level
    drawOnMatrixAndInvert(tempBoard, false);
    delay(2); 
  
    if (digitalRead(MARKER) == HIGH) {
      attempts--;
      markedPositions[i][0] = crosshairX; // Save marked positions
      markedPositions[i++][1] = crosshairY;
      if (attempts <= 0) break;
      while (digitalRead(MARKER) == HIGH) {
        byte markedPosition[8] = {0}; 
        markedPosition[crosshairX] = (1 << (7 - crosshairY));
      }
    } else if (digitalRead(UP) == HIGH) { // Move Up
      crosshairX = (crosshairX - 1 + 8) % 8;
      byte temp = tempBoard[0];
      for (int i = 0; i < 7; i++) {
        tempBoard[i] = tempBoard[i + 1];
      }
      tempBoard[7] = temp; 
      while (digitalRead(UP) == HIGH) {
        drawOnMatrixAndInvert(tempBoard, false);
        delay(3);
      }
    } else if (digitalRead(DOWN) == HIGH) { // Move Down
      crosshairX = (crosshairX + 1) % 8;  
      byte temp = tempBoard[7];
      for (int i = 7; i > 0; i--) {
        tempBoard[i] = tempBoard[i - 1];
      }
      tempBoard[0] = temp; 
      while (digitalRead(DOWN) == HIGH) {
        drawOnMatrixAndInvert(tempBoard, false);
        delay(3);  
      }
    } else if (digitalRead(RIGHT) == HIGH) { // Move Right
      crosshairY = (crosshairY + 1) % 8;
      for (byte i = 0; i < 8; i++) { 
        tempBoard[i] = (tempBoard[i] >> 1) | (tempBoard[i] << 7);
      }
      while (digitalRead(RIGHT) == HIGH) {
        drawOnMatrixAndInvert(tempBoard, false);
        delay(3); 
      }
    } else if (digitalRead(LEFT) == HIGH) { // Move Left  
      crosshairY = (crosshairY - 1 + 8) % 8; 
      for (byte i = 0; i < 8; i++) { 
        tempBoard[i] = (tempBoard[i] << 1) | (tempBoard[i] >> 7);
      }
      while (digitalRead(LEFT) == HIGH) {
        drawOnMatrixAndInvert(tempBoard, false);
        delay(3); 
      }
    }
  }

  // Mark the board using saved positions
  for (int i = 0; i < N; i++) {
    int markedRow = markedPositions[i][0];
    int markedCol = markedPositions[i][1];
    
    byte row = board[markedRow];
    byte mask = 1 << (7 - markedCol); 
    
    if (row & mask) row ^= mask;
    
    // Update the random_pattern with the possibly modified row
    board[markedRow] = row;
  }

  delay(200);
  
  checkPlayerGuesses(board);
}




/* GAME ROUTINE */
void playGame() {

  delay(ONE_SECOND / 2 );
  
  scrollMessageOnMatrix(READY_MESSAGE, sizeof(READY_MESSAGE)/sizeof(READY_MESSAGE[0]), 65);
 
  delay(200);
 
  flashScreen(350);

  scrollMessageOnMatrix(TASK_MESSAGE, sizeof(TASK_MESSAGE)/sizeof(TASK_MESSAGE[0]), 55);
 
  flashScreen(350);

  scrollMessageOnMatrix(LEVEL_MESSAGE, sizeof(LEVEL_MESSAGE)/sizeof(LEVEL_MESSAGE[0]), 65);
 
  delay(200);
}


/* PART 1 ROUTINE */
void displayPatternsAndMessages() {

  unsigned long startTime = millis();

  // Display first pattern for one second  
  while (millis() - startTime < ONE_SECOND) {  // Run for 1000 milliseconds (1 second)
    drawOnMatrixAndInvert(FIRST_MESSAGE, false);
  }
  
  delay(ONE_SECOND);

  // Display the second pattern for one second 
  startTime = millis();
  while (millis() - startTime < ONE_SECOND) {  // Run for 1000 milliseconds (1 second)
    drawOnMatrixAndInvert(SECOND_MESSAGE, false);
  }
  
  delay(ONE_SECOND);
  
  // Invert the first pattern and display it for 1 second
  startTime = millis();
  while (millis() - startTime < ONE_SECOND) {  // Run for 1000 milliseconds (1 second)
    drawOnMatrixAndInvert(FIRST_MESSAGE, true);
  }

  delay(ONE_SECOND);

  // Invert the second pattern and display it for 1 second
  startTime = millis();
  while (millis() - startTime < ONE_SECOND) {  // Run for 1000 milliseconds (1 second)
    drawOnMatrixAndInvert(SECOND_MESSAGE, true);
  }


  delay(ONE_SECOND);


  // Scroll custom messages
  scrollMessageOnMatrix(MY_MESSAGE, sizeof(MY_MESSAGE)/sizeof(MY_MESSAGE[0]), 70);
  
  delay(ONE_SECOND / 2);  
 
  for (int i = 0; i < 12; i++) {
    scrollMessageOnMatrix(FINAL_MESSAGE);
  }

}


void setup() {
  // Set all pins on the PORTA register (DDRA -> PA0-PA7) as OUTPUT to drive the matrix rows
  DDRA = 0xFF;  // All PORTA pins set to OUTPUT (rows)
  
  // Set all pins on the PORTC register (DDRC -> PC0-PC7) as OUTPUT to drive the matrix columns
  DDRC = 0xFF;  // All PORTC pins set to OUTPUT (columns)

  // Set all rows and columns to LOW initially (all LEDs start off)
  PORTA &= 0x00; 
  PORTC &= 0x00;  

  // PORTB register pins
  DDRB = 0b00000000;  // PB0-PB3 and PB6 as INPUT, disregard others
  PORTB = 0b00000000;

  displayPatternsAndMessages();
  
  // Initialize random seed for board pattern
  randomSeed(analogRead(1));
  
  // Start Game
  playGame();
}


void loop() {
  
  int difficulty = selectDifficulty();
  
  delay(200);
  
  beginLevel(difficulty);
  
}
