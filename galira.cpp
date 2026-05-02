// Incluir librerías necesarias para operar el hardware y los protocolos de red
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

// Definir los pines físicos para establecer la comunicación I2C
#define SDA_PIN 21
#define SCL_PIN 22
// Instanciar el objeto para controlar el sensor BME280
Adafruit_BME280 bme;

// Establecer las credenciales para configurar el Punto de Acceso (SoftAP)
const char* ssid = "Galira";
const char* password = "123456789";

// Crear el servidor web y asignar el puerto 80 para el tráfico HTTP
WebServer server(80);

// Almacenar el código de la interfaz gráfica web en la memoria del microcontrolador
const char HTML_PAGE[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>BME280 ESP32</title>
    <style>
        body { font-family: Arial; text-align: center; margin-top: 50px; }
        .card { border: 1px solid #ccc; padding: 20px; width: 250px; margin: 10px auto; border-radius: 10px; box-shadow: 2px 2px 5px #aaa; }
    </style>
</head>
<body>
    <h2>Datos BME280</h2>
    <div class="card">
        <p><strong>Temperatura:</strong> <span id="temp">--</span> °C</p>
        <p><strong>Humedad:</strong> <span id="hum">--</span> %</p>
        <p><strong>Presión:</strong> <span id="pres">--</span> hPa</p>
    </div>

    <script>
        async function obtenerDatos() {
            try {
                const res = await fetch('/api/data');
                const json = await res.json();
                document.getElementById('temp').innerText = json.temp.toFixed(1);
                document.getElementById('hum').innerText = json.hum.toFixed(1);
                document.getElementById('pres').innerText = json.pres.toFixed(1);
            } catch (e) {
                console.error('Error:', e);
            }
        }
        setInterval(obtenerDatos, 2000);
        obtenerDatos();
    </script>
</body>
</html>
)rawliteral";

// Transmitir la página HTML al recibir una solicitud en el directorio raíz
void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

// Leer las variables físicas, estructurar el paquete JSON y enviar la respuesta
void handleData() {
  // Extraer las mediciones térmicas y barométricas del registro del sensor
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 100.0F;

  // Concatenar los valores adquiridos para formar la cadena JSON
  String json = "{";
  json += "\"temp\":" + String(temp, 1) + ",";
  json += "\"hum\":" + String(hum, 1) + ",";
  json += "\"pres\":" + String(pres, 1);
  json += "}";

  // Responder al cliente con el código de éxito y el paquete de datos
  server.send(200, "application/json", json);
}

// Configurar los parámetros iniciales del sistema antes del bucle infinito
void setup() {
  // Iniciar la comunicación serial para permitir la depuración
  Serial.begin(115200);
  
  // Iniciar el bus I2C y validar la comunicación física con el componente
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!bme.begin(0x76)) {
    // Detener la ejecución en caso de fallar la localización del sensor
    Serial.println("Error: BME280 no encontrado");
    while(1);
  }

  // Activar el módulo WiFi en modo Punto de Acceso
  WiFi.softAP(ssid, password);
  // Imprimir la dirección IP local asignada al host
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  // Asignar las funciones de control a los endpoints específicos
  server.on("/", handleRoot);
  server.on("/api/data", handleData);
  
  // Arrancar el proceso de escucha del servidor HTTP
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

// Ejecutar el proceso lógico de forma repetitiva
void loop() {
  // Atender las peticiones entrantes de los clientes conectados
  server.handleClient();
  // Aplicar un retardo mínimo para estabilizar los procesos internos del procesador
  delay(10);
}
