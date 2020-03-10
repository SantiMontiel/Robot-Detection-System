/***************************************************************
 * 
 * Sistema de detección de enemigos basado en sensor de tiempo
 * de vuelo VL53L1X + Comunicaciones via UART con Mini-DK2
 * 
 * Santiago Montiel Marín - UAH ROBOTICS TEAM
 * 09/03/2020
 *  
 ***************************************************************/

/**** Inclusión de biblioteca y definición de los sensores ****/

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X Sensor1;
#define Sensor1_XSHUT 2
#define Sensor1_Address 31

VL53L1X Sensor2;
#define Sensor2_XSHUT 3
#define Sensor2_Address 33

VL53L1X Sensor3;
#define Sensor3_XSHUT 4
#define Sensor3_Address 35

VL53L1X Sensor4;
#define Sensor4_XSHUT 5
#define Sensor4_Address 37

#define distThreshold 100

/**** Función de inicialización de 4 sensores de vuelo ****/ 

void TOF_Init() {

  // Pines para XSHUT de los sensores
  pinMode(Sensor1_XSHUT, OUTPUT);
  digitalWrite(Sensor1_XSHUT, LOW);
  pinMode(Sensor2_XSHUT, OUTPUT);
  digitalWrite(Sensor2_XSHUT, LOW);
  pinMode(Sensor3_XSHUT, OUTPUT);
  digitalWrite(Sensor3_XSHUT, LOW);
  pinMode(Sensor4_XSHUT, OUTPUT);
  digitalWrite(Sensor4_XSHUT, LOW);

  // Inicialización de la UART a 115200 baudios
  Serial.begin(115200);

  // Inicialización de la I2C a 400 kHz
  Wire.begin();
  Wire.setClock(400000);

  // Inicialización del sensor 1
  pinMode(Sensor1_XSHUT, INPUT);
  Sensor1.setTimeout(500);
  if(!Sensor1.init()){
    Serial.println("Fallo al inicializar el sensor 1");
    while(1);  
  }
  Sensor1.setAddress(Sensor1_Address);
  Sensor1.setDistanceMode(VL53L1X::Long);
  Sensor1.setMeasurementTimingBudget(50000);
  //                   m  Sensor1.startContinuous(50);
  
  // Inicialización del sensor 2
  pinMode(Sensor2_XSHUT, INPUT);
  Sensor2.setTimeout(500);
  if(!Sensor2.init()){
    Serial.println("Fallo al inicializar el sensor 2");
    while(1);  
  }
  Sensor2.setAddress(Sensor2_Address);
  Sensor2.setDistanceMode(VL53L1X::Long);
  Sensor2.setMeasurementTimingBudget(50000);
  // Sensor2.startContinuous(50);
  
  // Inicialización del sensor 3 -> (por implementar)
  pinMode(Sensor3_XSHUT, INPUT);
  Sensor3.setTimeout(500);
  if(!Sensor3.init()){
    Serial.println("Fallo al inicializar el sensor 3");
    while(1);  
  }
  Sensor3.setAddress(Sensor3_Address);
  Sensor3.setDistanceMode(VL53L1X::Long);
  Sensor3.setMeasurementTimingBudget(50000);
  
  // Inicialización del sensor 4 -> (por implementar)
  pinMode(Sensor4_XSHUT, INPUT);
  Sensor4.setTimeout(500);
  if(!Sensor4.init()){
    Serial.println("Fallo al inicializar el sensor 4");
    while(1);  
  }
  Sensor4.setAddress(Sensor4_Address);
  Sensor4.setDistanceMode(VL53L1X::Long);
  Sensor4.setMeasurementTimingBudget(50000);

  Sensor1.startContinuous(50);
  Sensor2.startContinuous(50);
  Sensor3.startContinuous(50);
  Sensor4.startContinuous(50);
  
}

/**** Funciones de lectura de 4 sensores de vuelo:                                   ****/
/**** 1. TestCom permite ver que los sensores miden correctamente por puerto serie   ****/
/**** 2. RaspiCom es la función que envía el mensaje requerido por la Raspi de Ortiz ****/

void TOF_TestCom() {
  
  // Lectura del sensor 1
 // delay(200);
  Sensor1.read();
  Serial.print("S1: ");
  Serial.print(Sensor1.ranging_data.range_mm);

  // Lectura del sensor 2
 // delay(200);
  Sensor2.read();
  Serial.print("\tS2: ");
  Serial.print(Sensor2.ranging_data.range_mm);
  
  // Lectura del sensor 3 -> por implementar
//  delay(200);
  Sensor3.read();
  Serial.print("\tS3: ");
  Serial.print(Sensor3.ranging_data.range_mm);

  // Lectura del sensor 4 -> por implementar
  Sensor4.read();
  Serial.print("\tS4: ");
  Serial.print(Sensor4.ranging_data.range_mm);

  Serial.println();
  
}

void TOF_RaspiCom() {

  int V0 = 0;

  //delay(200);
  //Sensor1.read();
  int V1 = 0;
  if (Sensor1.ranging_data.range_mm < distThreshold) {V1 = 1;} 

  //delay(200);
  //Sensor2.read();
  int V2 = 0;
  if (Sensor2.ranging_data.range_mm < distThreshold) {V2 = 1;}
  
  //Sensor3.read();
  int V3 = 0;
  if (Sensor3.ranging_data.range_mm < distThreshold) {V3 = 1;}
  
//  Sensor4.read();
  int V4 = 0;
  if (Sensor4.ranging_data.range_mm < distThreshold) {V4 = 1;}
  
  if ((V1 || V2 || V3 || V4) == 1){
    V0 = 1;  
  }
  
  if (V0 == 1){
    Serial.print("V");
    Serial.print(V1);
    Serial.print(V2);
    Serial.print(V3);
    Serial.print(V4);
    Serial.println(); 
  }
  
}

/**** Programa principal ****/

void setup() {
  TOF_Init();
}

void loop() {
  TOF_TestCom();
  TOF_RaspiCom();  
}

/****************************************************************
 * Notas:
 * · startContinuous (ms) >= setMeasurementTimingBudget (us)
 * ·
 * 
 * 
 * 
 * **************************************************************/
 
