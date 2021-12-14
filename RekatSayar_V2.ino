const int trig = 10;
const int echo = 9;
const int modeBtn = A1;
const int startBtn = A0;
int start=0;
int sure = 0;
int mesafe = 0;
int secdeSayisi = 0;
int temp;
int mode = 1;
int section = 2;
int kilinacakRekat = 2;
int digit[12] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111, 0b0011100, 0b1010000};
int digit1, digit2;  

void setup() {
  //Serial.begin(9600);
  for (int i = 2; i < 9; i++){  
    pinMode(i, OUTPUT);  
  }  
  pinMode(12, OUTPUT);  
  pinMode(13, OUTPUT);                                                                             
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  temp = 0;
}


void loop() 
{
  if (analogRead(startBtn) > 900) {
    if (start == 0) {
      start = 1;      
      secdeSayisi=0;
      switch(mode) {
        case 1:
          section = 2;
          kilinacakRekat = 2;
          break;
        case 2:
          section = 3;
          kilinacakRekat = 4;
          break;
        case 3:
          section = 2;
          kilinacakRekat = 4;
          break;
        case 4:
          section = 2;
          kilinacakRekat = 3;
          break;
        case 5:
          section = 4;
          kilinacakRekat = 4;
          break;
        case 6:
          section = 1;
          kilinacakRekat = 2;
          break;
        case 7:
          section = 1;
          kilinacakRekat = 3;
          break;
        case 8:
          section = 1;
          kilinacakRekat = 4;
          break;
      }      
      digitalWrite(12, LOW); 
      digitalWrite(13, HIGH);
      dis(0);
    }
    else {
      start = 0;
      digitalWrite(12, LOW); 
      digitalWrite(13, LOW);
    }
    while(1) {
      if (analogRead(startBtn) <= 900)
        break;
    }
  }
  if (start == 1) {
      secdeControle();
      /*Serial.print("Section: ");
      Serial.print(section);
      Serial.print(" - kilinacak: ");
      Serial.print(kilinacakRekat);
      Serial.print(" - secde: ");
      Serial.print(secdeSayisi);
      Serial.print(" - Mod: ");
      Serial.println(mode);*/
  } else {
    changeModeControle();
    if(mode > 5)
      ekran(11, mode-4);
    else
      ekran(10, mode);
  }
}
void changeModeControle() {
  if (analogRead(modeBtn) > 900) {
    if (mode == 8)
      mode=0;
    mode++;
    while(1) {
      if(mode > 5)
        ekran(11, mode-4);
      else
        ekran(10, mode);
        
      if (analogRead(modeBtn) <= 900)
        break;
    }
  }
}
void ekran(int digit1, int digit2) {
  digitalWrite(12, HIGH);  
  digitalWrite(13, LOW);  
  dis(digit1);  
  delay(10);  
  digitalWrite(13, HIGH);  
  digitalWrite(12, LOW);  
  dis(digit2);  
  delay(10); 
}
void dis(int num) {  
  for (int i = 2; i < 9; i++) {  
    digitalWrite(i, bitRead(digit[num], i - 2));
  }  
}

void secdeControle() 
{
    if(section == 0) {
      start = 0;
      digitalWrite(12, LOW); 
      digitalWrite(13, LOW);
      return;
    }
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delay(100);
    digitalWrite(trig, LOW);
    sure = pulseIn(echo, HIGH);
    mesafe = (sure / 2) / 28.5;
    if (mesafe > 55 && temp == 1)
     temp=0;
    if (mesafe < 18 && mesafe > 0 && temp == 0) {
      secdeSayisi++;
      if((secdeSayisi / 2) > 0 && (secdeSayisi % 2) == 0 && kilinacakRekat > 0) {
        dis(secdeSayisi/2);
        kilinacakRekat--;
        if (kilinacakRekat == 0) {
          secdeSayisi = 0;
          section--;          
          delay(5000);
          if(section>0) {
            sectionControle();
            dis(0);
          }
        }
      }
      delay(100);
      temp = 1;
   }
   delay(100);
}

void sectionControle() {
  switch(mode) {
    case 1:
      if(section==2)
        kilinacakRekat = 2;
      else if(section==1)
        kilinacakRekat = 2;
      break;
    case 2:
      if(section==3)
        kilinacakRekat = 4;
      else if(section==2)
        kilinacakRekat = 4;
      else if(section==1)
        kilinacakRekat = 2;
      break;
    case 3:
      if(section==2)
        kilinacakRekat = 4;
      else if(section==1)
        kilinacakRekat = 4;
      break;
    case 4:
      if(section==2)
        kilinacakRekat = 3;
      else if(section==1)
        kilinacakRekat = 2;
      break;
    case 5:
      if(section==4)
        kilinacakRekat = 4;
      else if(section==3)
        kilinacakRekat = 4;
      else if(section==2)
        kilinacakRekat = 2;
      else if(section==1)
        kilinacakRekat = 3;
      break;
    case 6:
      kilinacakRekat = 2;
      break;
    case 7:
      kilinacakRekat = 3;
      break;
    case 8:
      kilinacakRekat = 4;
      break;
  }
}
