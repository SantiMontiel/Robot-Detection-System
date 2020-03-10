# Robot-Detection-System

##  Descripción
Sistema de detección de robots enemigos para el Equipo de Robótica de la Universidad de Alcalá, compitiendo en Eurobot 2020. Basado en los sensores de vuelo ST VL53L1X, manejados via I2C, y comunicaciones via UART con Raspberry Pi.

## Programas
Se han generado tres programas en el desarrollo del proyecto.
* **Example-Single-Sensor**: Ejemplo en el que se ejecuta un único sensor.
* **Example-Multiple-Sensor**: Ejemplo en el que se ejecutan dos sensores de manera simultánea.
* **VL53L1X-Arduino**: Programa final. Expansión a cuatro sensores, diseñado de manera modular y desarrollo de las comunicaciones con Raspberry Pi.

## Funciones
En el programa *VL53L1X-Arduino* se han creado 3 funciones para facilitar la integración del sistema en una máquina de estados o en otro sistema de mayor envergadura.
* **TOF_Init**: Rutina de inicialización de los sensores (void *setup*)
* **TOF_TestCom**: Función que printea por puerto serie la medida de cada uno de los sensores. Ideal para testear que el sistema funciona correctamente.
* **TOF_RaspiCom**: Función que printea por puerto serie en caso de que alguna de las lecturas sea inferior a la distancia de seguridad definida.

## Documentación
Como documentación se ha generado el siguiente [plano eléctrico](https://github.com/SantiMontiel/Robot-Detection-System/blob/master/Esquema%20de%20conexionado%20VL53L1X.pdf) para facilitar el conexionado en posteriores instalaciones.

## Consideraciones eléctricas
Se recomienda usar una tensión estable (preferiblemente una referencia de tensión) de 3V para alimentar los sensores y tener las masas conectadas de manera segura. De manera experimental, se ha detectado que el sistema es poco robusto ante variaciones de corriente. En términos de corriente, cada sensor consume entre 10-15 mA.

## Futuros desarrollos
Para dejar el sistema totalmente modular y de carácter "plug-and-play", se debería desarrollar una librería externa con la que en el programa inicial solo fuese necesario hacer un #include y llamar a las funciones.
