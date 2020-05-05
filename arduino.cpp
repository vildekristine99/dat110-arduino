void setup()
{
  //Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(2, INPUT);


}

  const int LOCKED = 1;
  const int WAITING1 = 2;
  const int WAITING2 = 3;
  const int UNLOCKED = 4;
  const int CHECKING = 5;
  int state = LOCKED;
  const int sensor = 2;

  int trykk = 0;
  int pin1 = 0;
  int pin2 = 0;
  int pushhandled = 0;

void loop()
{
  int knapp1 = digitalRead(7);
  int knapp2 = digitalRead(6);

  if ((knapp1 == LOW) && (knapp2 == LOW))
    pushhandled = 0;

  switch(state){
    case LOCKED:
     digitalWrite(13, HIGH);

     if(digitalRead(sensor) == HIGH){
       state = WAITING1;
       digitalWrite(13, LOW);
     }

    break;

    case WAITING1:
     digitalWrite(12, HIGH);
     if((knapp1 == HIGH || knapp2 == HIGH) && !pushhandled){
       pushhandled = 1;
       digitalWrite(12, LOW);
       delay(500);
       if(knapp1==HIGH){
         pin1=1;
       }
       state = WAITING2;
    }


    break;

    case WAITING2:
     digitalWrite(12, HIGH);
     if((knapp1 == HIGH || knapp2 == HIGH)&&!pushhandled){
       pushhandled=1;
       digitalWrite(12, LOW);
       delay(500);
       digitalWrite(12, HIGH);

       if(knapp2==HIGH){
         pin2=1;
       }
       state = CHECKING;
       digitalWrite(12, LOW);
      }



    break;

    case CHECKING:
    if((pin1 && pin2) == 1){
      state=UNLOCKED;
    }else {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      state = LOCKED;
    }
    break;

    case UNLOCKED:
     digitalWrite(11, HIGH);
     delay(5000);
     state = LOCKED;
     digitalWrite(11, LOW);
    break;
  }

}
