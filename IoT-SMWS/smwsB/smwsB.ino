#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

// Define the pins for the ultrasonic sensor, LED, and buzzer
#define trigPin D1
#define echoPin D2
#define ledPin D3
#define buzzerPin D4

// Define the DHT11 sensor pin and type
#define DHTPIN D5
#define DHTTYPE DHT11

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

// Define the threshold distance (in centimeters)
const int binThreshold = 20;

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Flask server endpoint
const char* serverName = "http://your_flask_server_endpoint/data";

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Define pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void loop() {
  // Send a pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse on the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Convert the duration into distance
  float distance_cm = (duration * 0.0343) / 2.0;

  // Read temperature and humidity from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any readings failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print all the data to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.print(" cm, ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C, ");
  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Check if the distance is below the threshold
  if (distance_cm <= binThreshold) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    // Activate the buzzer
    tone(buzzerPin, 300);
  } else {
    // Turn off the LED and buzzer
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  // Send data to Flask server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String postData = "{\"distance\": " + String(distance_cm) +
                      ", \"temperature\": " + String(temperature) +
                      ", \"humidity\": " + String(humidity) + "}";

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Delay before taking the next measurement
  delay(2000);
}
