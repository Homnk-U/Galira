# Galira

Código fuente necesario para operar la placa ESP32 como punto de acceso inalámbrico y servidor de datos. Permite monitorear el clima en tiempo real mediante el sensor BME280 para asistir a astrónomos aficionados durante sus observaciones y prevenir la condensación en los instrumentos ópticos.

## Requisitos Previos

* **Contar** con una placa de desarrollo ESP32 y un sensor ambiental BME280.
* **Instalar** el entorno de desarrollo Arduino IDE.
* **Añadir** el soporte para tarjetas ESP32 en el gestor de tarjetas de Arduino.
* **Descargar** e **instalar** las librerías `Adafruit_Sensor` y `Adafruit_BME280` desde el gestor de librerías.

## Instrucciones de Instalación y Uso

1. **Clonar** o **descargar** este repositorio en el equipo local.
2. **Abrir** el archivo `.ino` mediante el software Arduino IDE.
3. **Conectar** el microcontrolador ESP32 al puerto USB del ordenador.
4. **Seleccionar** el modelo de placa (ej. "DOIT ESP32 DEVKIT V1") y el puerto COM correspondiente en la pestaña de herramientas.
5. **Compilar** y **cargar** el código en el microcontrolador.
6. **Alimentar** el circuito mediante una batería o fuente externa.
7. **Buscar** la red inalámbrica denominada "Galira" desde el dispositivo móvil u ordenador.
8. **Ingresar** la contraseña de red establecida en el código fuente.
9. **Ejecutar** la aplicación móvil GALIRA para **iniciar** la recepción de datos, o **ingresar** a la dirección IP `192.168.4.1` a través de cualquier navegador web para **visualizar** la interfaz de respaldo.
