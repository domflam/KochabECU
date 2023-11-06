#define NTC 3950              // ntc coef
#define RESISTOR 220000       // resistor value
#define THERMISTOR 100000     // thermistor initial value, 100 k
#define REF_TEMP 25           // température nominale

#define OilSensor A0          //Input used to monitor oil temp

void setup() {
  Serial.begin(9600);          // Used for debuging 
  pinMode(OilSensor, INPUT);   //Thermistor
  pinMode(12, OUTPUT);         //HOT Lamp
  pinMode(10, OUTPUT);         //Fan

  digitalWrite(12, HIGH);
  delay (1000);
  digitalWrite(12, LOW);
  delay (1000);
  digitalWrite(12, HIGH);
  delay (1000);
  digitalWrite(12, LOW);
}

void loop() {
  int t = analogRead(OilSensor);
  float tr = 1023.0 / t - 1;
  tr = RESISTOR / tr;
  Serial.print("R=");
  Serial.print(tr);
  Serial.print(", t=");

  float steinhart;               //Steinhart-Hart mathematic formula 
  steinhart = tr / THERMISTOR;
  steinhart = log(steinhart);
  steinhart /= NTC;
  steinhart += 1.0 / (REF_TEMP + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;
  Serial.println(steinhart);

  if (steinhart < 115 ) {      //If temp is OK
    digitalWrite(10, LOW);
    digitalWrite(12, LOW);
  }
  if ((steinhart >= 123) and (steinhart < 143)) {      //Need Fan ?
    digitalWrite(10, HIGH);
    digitalWrite(12, LOW);
  }
if (steinhart >= 143) {        //Warning Fan + Hot Lamp
    digitalWrite(10, HIGH);
    digitalWrite(12, HIGH);
  }
  delay(1000);
}
