#include <anyrtttl.h>
#include <binrtttl.h>
#include <pitches.h>

/* 
  Makita Jukebox - @RealTimeKodi
  http://www.crt.video

  Install any rtttl from the libraries manager. Any rtttl ringtone can be pasted into the
  song strings.

  The charger will play the short jingle at the start of the charge process and the long
  jingle at the end of the charge process.

  Use any 5v tolerant arduino you would like
  Buzzer pin goes to the transistor base of the transistor that drives the buzzer
  Buzzer in goes to the line that feeds the transistor. cut the jumper between the two
  Red and green go to the microcontroller pins on the charger that control the leds
  It is important to solder them on the microcontroller side of the current limiting
  resistors or they won't be detected properly. They are used to detect the state of
  charge.
*/

//Pinout Use whichever pins you like there are no special requirements
#define BUZZER_PIN 8
#define BUZZER_IN 2
#define RED_IN 3
#define GREEN_IN 4

boolean beepTriggered=false;
boolean wasPlaying=false;
long lockout=0;

void buzz() { //Called when the buzzer on the charger goes high
  if(millis()>lockout) {
    beepTriggered=true;
  } else {//if we're here it's because we caught a rise during the lockout period. Add a second so we can wait for the charger to quiet down
    lockout=millis()+1000;
  }
}

//buddy holly weezer
const char * jingle       = "BuddyHol:d=32,o=6,b=40:c#.,d.,c#.,8g#,16f#.,c#.,b.5,a.5,8c#.,c#.,d.,c#.,8g#,16f#.,16c#,b5,16a.5";
const char * jingle_short = "BuddyHol:d=32,o=6,b=40:c#.,d.,c#.,8g#,16f#.,c#.,b.5,a.5,8c#.";

//uncomment to change the song to tetris
//const char * jingle = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
//const char * jingle_short = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a";


void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUZZER_IN,INPUT);
  pinMode(RED_IN, INPUT);
  pinMode(GREEN_IN,INPUT);

  Serial.begin(9600);
}


void loop() {
  if(digitalRead(BUZZER_IN) && ! anyrtttl::nonblocking::isPlaying()) buzz();

  if(beepTriggered) { //this will help with pin debugging
    Serial.print(digitalRead(BUZZER_IN));
    Serial.print(!digitalRead(RED_IN));
    Serial.println(!digitalRead(GREEN_IN));
  }

  if(!digitalRead(RED_IN) && beepTriggered) {//Charge start, short song
    anyrtttl::nonblocking::begin(BUZZER_PIN, jingle_short);
    beepTriggered=false;
  }

  if(!digitalRead(GREEN_IN) && beepTriggered) {//Charge end, long song
    anyrtttl::nonblocking::begin(BUZZER_PIN, jingle);
    beepTriggered=false;
  } 
  
  
    
  if( !anyrtttl::nonblocking::done() ) { //Play our song if there's any left
    anyrtttl::nonblocking::play();
    wasPlaying=true;
  } else { 
    if(wasPlaying) { //run this once! at the end of the song
      lockout=millis()+1000;//lock out the input for a second
    }
    wasPlaying=false;
  }
}
