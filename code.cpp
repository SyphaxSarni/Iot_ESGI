#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int led = 4;
int sensor1 = 9;              // capteur 1 relié à la pin 2
int sensor2 = 7;              // capteur 2 relié à la pin 7
int state1 = LOW;             // aucun mouvement par defaut pour le capteur 1
int state2 = LOW;             // aucun mouvement par defaut pour le capteur 2
int val1 = 0;                // variable pour stocker l'état du capteur 1
int val2 = 0;                // variable pour stocker l'état du capteur 2
int count_entry = 0;
int count_exit = 0;   
int first = 0;


void setup() {
  pinMode(led, OUTPUT);      // pin 4 en sortie
  pinMode(sensor1, INPUT);   // pin 2 en entrée pour le capteur 1
  pinMode(sensor2, INPUT);   // pin 7 en entrée pour le capteur 2
  Serial.begin(9600);        // initialise le port serie
  lcd.begin(16, 2); 
}


void loop(){
  
  lcd.setCursor(0,0);
  lcd.print("ENTR=" + String(count_entry) + "  EXIT=" + String(count_exit)); 
  int tot = count_entry - count_exit;
  if (tot<=0){tot=0;}
  lcd.setCursor(0,1);
  lcd.print("TOT=");
  lcd.print(tot);

  val1 = digitalRead(sensor1);
  val2 = digitalRead(sensor2);

  if (val1 == HIGH && state1 == LOW) {
    digitalWrite(led, HIGH);
    Serial.println("Sensor 1 triggered");
    state1 = HIGH;
    if(first == 2){
      first = 0;
      count_entry++;
      Serial.println("Entry counted");
    }
    else{
      first = 1;
    }
  } else if (val1 == LOW && state1 == HIGH) {
    state1 = LOW;
  }

  if (val2 == HIGH && state2 == LOW) {
    digitalWrite(led, HIGH);
    Serial.println("Sensor 2 triggered");
    state2 = HIGH;
  } else if (val2 == LOW && state2 == HIGH) {
    state2 = LOW;
    if (first == 1){
      first = 0;
      count_exit++;
      Serial.println("Exit counted");
    }
    else{
      first = 2;
    }
  }

  delay(10);
}
