#include <Wire.h>
#include <VL53L1X.h>

VL53L1X Sensor1;
VL53L1X Sensor2;


void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  
  // Inicialización de la UART a 115200
  Serial.begin(115200);

  // Inicialización de la I2C (400 kHz)
  Wire.begin();
  Wire.setClock(400000);

  // Inicialización del sensor 1
  pinMode(2, INPUT);
  Sensor1.setTimeout(500);
  if(!Sensor1.init()){
    Serial.println("Fallo al inicializar el sensor 1");
    while(1);  
  }
  
  Sensor1.setAddress(0x31);
  Sensor1.setDistanceMode(VL53L1X::Long);
  Sensor1.setMeasurementTimingBudget(50000);
  Sensor1.startContinuous(50);

  // Inicialización del sensor 2
  pinMode(3, INPUT);
  Sensor2.setTimeout(500);
  if(!Sensor2.init()){
    Serial.println("Fallo al inicializar el sensor 2");
    while(1);  
  }
  
  Sensor2.setAddress(0x33);
  Sensor2.setDistanceMode(VL53L1X::Long);
  Sensor2.setMeasurementTimingBudget(50000);
  Sensor2.startContinuous(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // delay(250);
  Sensor1.read();
  Serial.print("S1: ");
  Serial.print(Sensor1.ranging_data.range_mm);

  // delay(250);
  Sensor2.read();
  Serial.print("\tS2: ");
  Serial.print(Sensor2.ranging_data.range_mm); 

  if(Sensor1.ranging_data.range_mm < 300) {
    Serial.print("\tAlerta Sensor 1");  
  }

  Serial.println();

}
