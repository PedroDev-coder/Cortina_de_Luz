#define Fotodiodo1 A0
#define Fotodiodo2 A1
#define Btn_Reset 2
#define Rele 3
#define Robo 6
#define LedV 4
#define LedA 5
#define Brilho 700
#define Delay_ms 300
#define Delay2_ms 50

int Sensor1;
int Sensor2;
float Volts1;
float Volts2;

void setup()
{
  Serial.begin(9600);
  pinMode(Rele, OUTPUT);
  pinMode(Robo, OUTPUT);
  pinMode(LedV, OUTPUT);
  pinMode(LedA, OUTPUT);
  pinMode(Fotodiodo1, INPUT);
  pinMode(Fotodiodo2, INPUT);
  pinMode(Btn_Reset, INPUT);
}

void loop()
{
  Sensor1 = analogRead(Fotodiodo1);
  Sensor2 = analogRead(Fotodiodo2);

  Serial.print("Valor do Fotodiodo1: ");
  Serial.println(Sensor1);
  Serial.print("Valor do Fotodiodo2: ");
  Serial.println(Sensor2);
  
  //testa se os sensores estão funcionando
  if(Sensor1 != 0 && Sensor2 != 0){
    digitalWrite(LedA,LOW);
    delay(Delay2_ms);
  }else{
    digitalWrite(LedA,HIGH);
  }
  
  //testa a área de proteção
  if(Sensor1 < Brilho || Sensor2 < Brilho){
    digitalWrite(Rele,LOW);
    digitalWrite(Robo,LOW);
    digitalWrite(LedA,HIGH);
    digitalWrite(LedV,LOW);
  }else{
    digitalWrite(LedA,LOW);
    digitalWrite(LedV,HIGH);
  }

  Volts1 = (float)Sensor1*5/1023;
  Serial.print("Tensao1 (V): ");Serial.println(Volts1);
  delay(Delay2_ms);
  Volts2 = (float)Sensor2*5/1023;
  Serial.print("Tensao2 (V): ");Serial.println(Volts2);
  delay(Delay2_ms);
  
  //testa o reset
  if(Sensor1 > Brilho && Sensor2 > Brilho && digitalRead(Btn_Reset) == true){
    digitalWrite(LedV,LOW);
    digitalWrite(LedA,LOW);
    delay(Delay_ms);
    digitalWrite(Rele,HIGH);
    digitalWrite(Robo,HIGH);
  }
}