// SEND AN ASCII MASSAGE BY SERIAL TO DRAW THE PIXELS.
// A AN ASCII MASSAGE IS A MESSAGE THAT STARTS WITH AN "ADDRESS".
// IT IS THEN FOLLOWED BY VALUES SEPARATED BY SPACES.
// IT ENDS WITH A NEW LINE (ASCII CODE 10).

// DO NOT FORGET THAT THE MASSAGE MUST END WITH A
// NEW LINE IF YOU ARE USING ARDUINO'S SERIAL MONITOR.


// DRAW AN IMAGE
////////////////

// SEND THE FOLLOWING MASSAGE TO DRAW AN IMAGE:
// img row0 row1 row2 row3 row4 row5 row6 row7

// EACH rowX DATA IS A NUMBER BETWEEN 0-255 THAT REPRESENTS
// THE 8 PIXELS FOR THAT ROW.

// EXAMPLES:
// CLEAR:
// img 0 0 0 0 0 0 0 0
// FILL:
// img 255 255 255 255 255 255 255 255
// FACE:
// img 255 255 189 255 255 189 195 255
// FROWN:
// img 255 255 189 255 255 195 189 255

// DRAW A PIXEL
////////////////

// SEND THE FOLLOWING MASSAGE TO DRAW A PIXEL
// pix x y state

// x AND y IS THE POSITION OF THE PIXEL.
// state IS EITHER 0 OR 1 (OFF OR ON).

// INCLUDE MASSAGE PARSER
#include <AsciiMassageParser.h>

// PACKER(FOR SENDING) AND PARSER(FOR RECEIVING) INSTANCES.
AsciiMassageParser inbound;

// WEMOS MATRIX SHIELD:
#include <Adafruit_GFX.h>
#include <WEMOS_Matrix_GFX.h>

MLED matrix(7); //set intensity=7 (maximum)

///////////
// SETUP //
///////////
void setup() {

  // INITIATE SERIAL COMMUNICATION.
  Serial.begin(57600);


}


//////////
// LOOP //
//////////
void loop() {

  // RECEIVE PACKETS OVER UDP

  while ( inbound.parseStream( &Serial ) ) {
    if ( inbound.fullMatch("img") ) {
      matrix.clear();

      for ( int y = 0 ; y < 8 ; y++ ) {
        byte p = inbound.nextByte();

        for ( int x = 0; x < 8; x++) {
          if ( bitRead(p, x) ) matrix.drawPixel( x , y , LED_ON);
        }

      }

      matrix.writeDisplay();
    } else if ( inbound.fullMatch("pix") ) {
      byte x = inbound.nextByte();
      byte y = inbound.nextByte();
      byte state = inbound.nextByte();
      matrix.drawPixel( x , y , state);
      matrix.writeDisplay();
    }
  }
}





