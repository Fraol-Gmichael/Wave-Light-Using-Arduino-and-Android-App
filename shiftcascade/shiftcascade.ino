const int latchPin = 11; //SCTP
const int clockPin = 9; //HsCP
const int dataPin = 10;
String voice;
float distance;
float lap;
float time_token = 100;
String order;
String x;

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  writeReg();
}

int r[17][16] = {
{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};

int registers[17];
void writeReg(){
  
  digitalWrite(latchPin, LOW);
  
  for (int i=16; i>=0; i--){
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, registers[i]);
    digitalWrite(clockPin, HIGH); 
  }
  
  digitalWrite(latchPin, HIGH);
  
}

void wr(int reg[], String ord){
    digitalWrite(latchPin, LOW);
  
    for (int i=15; i>=0; i--){
      digitalWrite(clockPin, LOW);
      if (order == "off"){
        digitalWrite(dataPin, 0);
        }else{
          digitalWrite(dataPin, reg[i]);}
      
      digitalWrite(clockPin, HIGH); 
    }
    digitalWrite(latchPin, HIGH);
    }

void loop(){
  
  while (Serial.available())
  {
     delay(10);
     char c = Serial.read(); 
     x = x+c;
      if (c == ' '){
          order = voice;
          voice = "";
          continue;
        }
        
      else if(c == 'm'){
          distance = voice.toFloat();
          voice = "";
          continue;
        }
      else if(c == 't'){
          time_token = voice.toFloat();
          voice = "";
          continue;
        }
      voice += c;
    }

    if (order == "off"){
      for (int i=0; i<=16; i++){
            registers[i] = 0;
            wr(r[i], "off");
            }
      }
      else if(order.length() > 0){
       Serial.println(order);
        if( order == "on"){
          for (int i=0; i<=16; i++){
            registers[i] = 1;
            delay(time_token);
            wr(r[i], "on");
            }
      }
    
  }
  
}
