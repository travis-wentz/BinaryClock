/*
Travis Wentz
 12 hour binary clock
 */

int button1State = 0;
int button2State = 0;
int button1 = 12;         // attach button1 to pin 13
int button2 = 13;         // attach button2 to pin 14

void setup() {
  pinMode(button1, INPUT);  // button will give input
  pinMode(button2, INPUT);

  for(int pin = 1; pin < 12; pin++)
    pinMode(pin, OUTPUT);             //sets all the pins being used to output
}

void loop(){
  int num_hours = 12;   // 12 or 24 hour clock?
  int hour_pins = 4;   // sets 4 pins for 12 hour clock
  int starting_hour = 1;
  if (num_hours == 24){ // else
    num_hours = 23;
    hour_pins = 5;    // sets 5 pins for a 24 hour clock
    starting_hour = 0;  //adds a zero hour for a 24 hour clock
  }
  for (int hour = starting_hour; hour <= num_hours; hour++){        //loops through the hour to be displayed
    for (int i = 0; i < hour_pins; i++){        //loops through the diodes that display the current number
      if((hour >> i) & 1)
        digitalWrite(i + 7, HIGH);      // i + 8 because the first hour pin is pin 8
      else
        digitalWrite(i + 7, LOW);
    }
    for (int minute = 0; minute < 60; minute++){    //loops through the minuted to be displayed
      for (int j = 0; j < 6; j++){    //loops through the diodes that display the current number
        if((minute >> j) & 1)              //takes the current number, bit shifts to the least sig digit, then the next least and so on
          digitalWrite(j + 1, HIGH);  //if it's a 1, the diode turns on
        else
          digitalWrite(j + 1, LOW);   //else it doesn't
      }
      /*
      if this loop wasn't here we would have the default delay be 60000
      (60 seconds) but then you have to wait until the end of the 60 second
      delay before the buttons will work. The buttons speed up the time
      so you can set the clock
      */
      for(int d = 0; d < 100; d++){
        button1State = digitalRead(button1);
        button2State = digitalRead(button2);
        if (button1State == HIGH)    //fast button (1/20th sec)
          delay(.5);                  //for setting the current time
        else if (button2State == HIGH) //less fast button
          delay(5);                   // (1/2 second total including the loop)
        else
          delay(600);        //one minute between each num displayed
      }
    }

  }
}



