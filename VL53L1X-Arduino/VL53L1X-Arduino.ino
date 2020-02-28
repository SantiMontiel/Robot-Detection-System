/***************************************************************
 * 
 * Sistema de detección de enemigos basado en sensor de tiempo
 * de vuelo VL53L1X + Comunicaciones via UART con Mini-DK2
 * 
 * Santiago Montiel Marín - UAH ROBOTICS TEAM
 * 23/02/2020
 *  
 ***************************************************************/

#include <Wire.h>                       // I2C communications
#include <VL53L1X.h>                    // Sensor support

/**** Definición de variables globales ****/

#define Distance_Threshold  100

int Measurement1 = 0;
int Measurement2 = 0;
int Measurement3 = 0;
int Measurement4 = 0;
int Flag_Error = 0;

/**** Definición de los sensores ****/

VL53L1X Sensor1;
#define Sensor1_XSHUT        2
#define Sensor1_Address     31

VL53L1X Sensor2;
#define Sensor2_XSHUT        3
#define Sensor2_Address     33

VL53L1X Sensor3;
#define Sensor3_XSHUT        4
#define Sensor3_Address     35

VL53L1X Sensor4;
#define Sensor4_XSHUT        5
#define Sensor4_Address     37

/**** Función de inicialización del programa ****/

void Init_Function(){

  // Pines de salida para XSHUT
  pinMode(Sensor1_XSHUT, OUTPUT);
  pinMode(Sensor2_XSHUT, OUTPUT);
  pinMode(Sensor3_XSHUT, OUTPUT);
  pinMode(Sensor4_XSHUT, OUTPUT);

  digitalWrite(Sensor1_XSHUT, LOW);
  digitalWrite(Sensor2_XSHUT, LOW);
  digitalWrite(Sensor3_XSHUT, LOW);
  digitalWrite(Sensor4_XSHUT, LOW);

  // Inicialización de la comunicación UART (serie)
  Serial.begin(9600);
  
  // Inicialización de la comunicación I2C
  Wire.begin();
  Wire.setClock(400000);            // Use 400 kHz I2C

  // Inicialización del sensor 1
  digitalWrite(Sensor1_XSHUT, HIGH);
  Sensor1.setAddress(Sensor1_Address);
  Sensor1.setTimeout(500);
  if(!Sensor1.init()){
    Serial.println("Inicialización del sensor 1 fallida");
    while(1);  
  }
  Sensor1.setDistanceMode(VL53L1X::Long);
  Sensor1.setMeasurementTimingBudget(50000);
  Sensor1.startContinuous(50);

  // Inicialización del sensor 2
  digitalWrite(Sensor2_XSHUT, HIGH);
  Sensor2.setAddress(Sensor2_Address);
  Sensor2.setTimeout(500);
  if(!Sensor1.init()){
    Serial.println("Inicialización del sensor 2 fallida");
    while(1);  
  }
  Sensor2.setDistanceMode(VL53L1X::Long);
  Sensor2.setMeasurementTimingBudget(50000);
  Sensor2.startContinuous(50);

  // Inicialización del sensor 3
  digitalWrite(Sensor3_XSHUT, HIGH);
  Sensor3.setAddress(Sensor3_Address);
  Sensor3.setTimeout(500);
  if(!Sensor3.init()){
    Serial.println("Inicialización del sensor 3 fallida");
    while(1);  
  }
  Sensor3.setDistanceMode(VL53L1X::Long);
  Sensor3.setMeasurementTimingBudget(50000);
  Sensor3.startContinuous(50);

  // Inicialización del sensor 4
  digitalWrite(Sensor4_XSHUT, HIGH);
    Sensor4.setAddress(Sensor4_Address);
  Sensor4.setTimeout(500);
  if(!Sensor1.init()){
    Serial.println("Inicialización del sensor 4 fallida");
    while(1);  
  }
  Sensor4.setDistanceMode(VL53L1X::Long);
  Sensor4.setMeasurementTimingBudget(50000);
  Sensor4.startContinuous(50);

}

/**** Función de lectura de los sensores ****/

void Read_VL53L1X(){

    Sensor1.read();
    Measurement1 = Sensor1.ranging_data.range_mm;
    Sensor2.read();
    Measurement2 = Sensor1.ranging_data.range_mm;
    Sensor3.read();
    Measurement3 = Sensor1.ranging_data.range_mm;
    Sensor4.read();
    Measurement4 = Sensor1.ranging_data.range_mm;
    if (Measurement1 || Measurement2 || Measurement3 ||
        Measurement4 < Distance_Threshold) {
          Flag_Error = 1;
    }
}

/**** Función de envío de paquete por UART ****/

void Send_Package(){

  Serial.print("Sensor 1: ");
  Serial.print(Measurement1);
  Serial.print("\nSensor 2: ");
  Serial.print(Measurement2);
  Serial.print("\nSensor 3: ");
  Serial.print(Measurement3);
  Serial.print("\nSensor 4: ");
  Serial.print(Measurement4);
  if (Flag_Error == 1){
    Serial.print("\n¡OBJETIVO PRÓXIMO!\n\n");
  } else {
    Serial.print("\nTODO BIEN, TODO CORRECTO Y YO QUE ME ALEGRO\n\n");
  }
  delay(1000);
  
}

/**** Main functions ****/

void setup() {
  // put your setup code here, to run once:
  Init_Function();
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_VL53L1X();
  Send_Package();

}

/****************************************************************
 * Notas:
 * · startContinuous (ms) >= setMeasurementTimingBudget (us)
 * ·
 * 
 * 
 * 
 * **************************************************************/
 
