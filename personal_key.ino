#include "Keyboard.h" // Keyboard library
#include "Mouse.h"    // Mouse library
#include <TimerOne.h>

// definition
#define PUSH(x) digitalRead(x)==LOW 
#define RELEASE(x) digitalRead(x)==HIGH 
#define debounceTime 50

#define KEY_0  8
#define KEY_1  9
#define KEY_2  10
#define KEY_3  11

long last_time_ms = 0; 
long current_time_ms;
boolean is_first_push = false;
const int LED1 = 6;

//Key_0
const char key0_sen0[] = "I Checked the completion of the basic test from the person in charge.";
const char key0_sen1[] = "It seems to be no problem when checking the change list.";
const char key0_sen2[] = "Approved";
//Key_1
const char key1_sen0[] = "flqbgkduTtmqslek.";  //Reviewed
//Key_2
const char key2_sen0[] = "0153pyk*";  //password_1
//Key_3
const char key3_sen0[] = "ykp0153*";  //password_2

enum key_state {
    KEY_NONE,
    KEY_PUSH_0,
    KEY_RELEASE_0,
    KEY_PUSH_1,
    KEY_RELEASE_1,
    KEY_PUSH_2,
    KEY_RELEASE_2,
    KEY_PUSH_3,
    KEY_RELEASE_3,
    KEY_MAX
};

key_state state = KEY_NONE;

void timerIsr(void) {
    // Toggle LED
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}

int key_input_check(void) {
  switch(state){
      case KEY_NONE:
          if(PUSH(KEY_0)){    //Key_0
            current_time_ms = millis();
            if( !is_first_push ){
              is_first_push = true;
              last_time_ms = current_time_ms;
            }
            if((current_time_ms - last_time_ms) > debounceTime){
               state = KEY_PUSH_0;
               //Serial.println("KEY_PUSH_0!!");
               Keyboard.println(key0_sen0);
               Keyboard.println(key0_sen1);
               Keyboard.print(key0_sen2);
               digitalWrite( LED1, HIGH );
               is_first_push = false;     
            }
          } 
          else if(PUSH(KEY_1)){   //Key_1
            current_time_ms = millis();
            if( !is_first_push ){
              is_first_push = true;
              last_time_ms = current_time_ms;
            }
            if((current_time_ms - last_time_ms) > debounceTime){
              state = KEY_PUSH_1;
              //Serial.println("KEY_PUSH_1!!");
              Keyboard.print(key1_sen0);
              digitalWrite( LED1, HIGH );
              is_first_push = false;   
            }
          }
          else if(PUSH(KEY_2)){   //Key_2
            current_time_ms = millis();
            if( !is_first_push ){
              is_first_push = true;
              last_time_ms = current_time_ms;
            }
            if((current_time_ms - last_time_ms) > debounceTime){
              state = KEY_PUSH_2;
              //Serial.println("KEY_PUSH_2!!");
              Keyboard.print(key2_sen0);
              digitalWrite( LED1, HIGH );
              is_first_push = false;   
            }
          }
          else if(PUSH(KEY_3)){   //Key_3
            current_time_ms = millis();
            if( !is_first_push ){
              is_first_push = true;
              last_time_ms = current_time_ms;
            }
            if((current_time_ms - last_time_ms) > debounceTime){
              state = KEY_PUSH_3;
              //Serial.println( "KEY_PUSH_3!!");
              Keyboard.print(key3_sen0);
              digitalWrite( LED1, HIGH );
              is_first_push = false;
            }
          } else {
            is_first_push = false; 
          }
          break;

      case KEY_PUSH_0:
          if(RELEASE(KEY_0)){
            state = KEY_RELEASE_0;
            //Serial.println("KEY_RELEASE_0!!");
          }
          break;
        case KEY_PUSH_1:
          if(RELEASE(KEY_1)){
            state = KEY_RELEASE_1;
            //Serial.println("KEY_RELEASE_1!!");
          }
          break;
      case KEY_PUSH_2:
          if(RELEASE(KEY_2)){
            state = KEY_RELEASE_2;
            //Serial.println("KEY_RELEASE_2!!");
          }
          break;
      case KEY_PUSH_3:
          if(RELEASE(KEY_3)){
            state = KEY_RELEASE_3;
            //Serial.println("KEY_RELEASE_3!!");
          }
          break;

      case KEY_RELEASE_0:
      case KEY_RELEASE_1:
      case KEY_RELEASE_2:
      case KEY_RELEASE_3:
          digitalWrite( LED1, LOW );
          is_first_push = false; 
          state = KEY_NONE;
          break;
      
      default:
          break;
    }
}

// Initialization
void setup()
{
    // initialize input and outout pins
    pinMode(KEY_0, INPUT_PULLUP);
    pinMode(KEY_1, INPUT_PULLUP);
    pinMode(KEY_2, INPUT_PULLUP);
    pinMode(KEY_3, INPUT_PULLUP);
    pinMode(13, OUTPUT);
    pinMode(LED1, OUTPUT);

    Serial.begin(57600); // initialize mouse and keyboard control
    Mouse.begin();
    Keyboard.begin();
    
    // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
    Timer1.initialize(1000000); 
    Timer1.attachInterrupt( timerIsr ); // attach the service routine here
    Serial.println("Boot!!");
}

void loop()
{
    key_input_check();
}
