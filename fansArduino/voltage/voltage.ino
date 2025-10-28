

const int voltageSensor = A3;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
float value = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(voltageSensor, INPUT);

}

void loop()
{
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  Serial.print("Input = ");
  Serial.print(vIN);
  Serial.println(" V");    
  delay(500);
}
