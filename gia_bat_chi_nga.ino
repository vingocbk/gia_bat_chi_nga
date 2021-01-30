#include "gia_bat_chi_nga.h"

void setup(void)
{
  Serial.begin(115200);
	pinMode(RF0, INPUT);
	pinMode(RF1, INPUT);
	pinMode(RF2, INPUT);
	pinMode(PIN_LOA, OUTPUT);
	pinMode(MODE, INPUT);
	pinMode(BUTTON_UP, INPUT);
	pinMode(BUTTON_DOWN, INPUT);


	// configure LED PWM functionalitites
  	ledcSetup(L1UpChannel, freq, resolution);
	ledcSetup(L1DownChannel, freq, resolution);
	ledcSetup(L2UpChannel, freq, resolution);
	ledcSetup(L2DownChannel, freq, resolution);
  
	// attach the channel to the GPIO to be controlled
	ledcAttachPin(L1, L1UpChannel);
	ledcAttachPin(L2, L1DownChannel);
	ledcAttachPin(L3, L2UpChannel);
	ledcAttachPin(L4, L2DownChannel);

	ledcWrite(L1UpChannel, 0);
	ledcWrite(L1DownChannel, 0);
	ledcWrite(L2UpChannel, 0);
	ledcWrite(L2DownChannel, 0);


}

void loop(void)
{
  if(!isCaution){
    digitalWrite(PIN_LOA, LOW);
    if(digitalRead(BUTTON_UP) == LOW && digitalRead(BUTTON_DOWN) == HIGH){
      ledcWrite(L1UpChannel, Max_L1_UP);
      ledcWrite(L1DownChannel, 0);
      ledcWrite(L2UpChannel, Max_L2_UP);
      ledcWrite(L2DownChannel, 0);
      delay(10);

      I1 = analogRead(I1IN);
      I2 = analogRead(I2IN);
      if(((MIN_ERROR <= I1 && I1 <= MAX_ERROR) && (I2 <= MIN_ERROR || I2 >= MAX_ERROR)) || ((MIN_ERROR <= I2 && I2 <= MAX_ERROR) && (I1 <= MIN_ERROR || I1 >= MAX_ERROR))){
        countCurrent++;
        if(countCurrent >= 50){
          isCaution = true;
          countSpeaker = 0;
        }
      }else{
        countCurrent = 0;
      }

    }
    else if(digitalRead(BUTTON_UP) == HIGH && digitalRead(BUTTON_DOWN) == LOW){
      ledcWrite(L1UpChannel, 0);
      ledcWrite(L1DownChannel, Max_L1_DOWN);
      ledcWrite(L2UpChannel, 0);
      ledcWrite(L2DownChannel, Max_L2_DOWN);  
      delay(10);

      I1 = analogRead(I1IN);
      I2 = analogRead(I2IN);
      if(((MIN_ERROR <= I1 && I1 <= MAX_ERROR) && (I2 <= MIN_ERROR || I2 >= MAX_ERROR)) || ((MIN_ERROR <= I2 && I2 <= MAX_ERROR) && (I1 <= MIN_ERROR || I1 >= MAX_ERROR))){
        countCurrent++;
        if(countCurrent >= 50){
          isCaution = true;
          countSpeaker = 0;
        }
      }else{
        countCurrent = 0;
      }
 
    }
    else{
      countCurrent = 0;
      ledcWrite(L1UpChannel, 0);
      ledcWrite(L1DownChannel, 0);
      ledcWrite(L2UpChannel, 0);
      ledcWrite(L2DownChannel, 0);
      delay(10);
    }
  }
  else{
    ledcWrite(L1UpChannel, 0);
    ledcWrite(L1DownChannel, 0);
    ledcWrite(L2UpChannel, 0);
    ledcWrite(L2DownChannel, 0);
    if((digitalRead(BUTTON_UP) && digitalRead(BUTTON_DOWN)) || (!digitalRead(BUTTON_UP) && !digitalRead(BUTTON_DOWN))){
      isCaution = false;
      digitalWrite(PIN_LOA, LOW);
    }
    countSpeaker++;
    if(countSpeaker == 1){
      digitalWrite(PIN_LOA, HIGH);
    }
    else if(countSpeaker == 2){
      digitalWrite(PIN_LOA, LOW);
    }
    else if(countSpeaker == 11){
      countSpeaker = 0;
    }
    delay(100);
  }
	
    
}
