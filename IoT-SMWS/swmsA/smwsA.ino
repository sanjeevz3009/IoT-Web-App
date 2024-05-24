#include <DHT.h>

// Define the pins for the ultrasonic sensor, LED, and buzzer
#define trigPin 3
#define echoPin 2
#define ledPin 10 // Built-in LED on Arduino Uno
#define buzzerPin 9

// Define the DHT11 sensor pin and type
#define DHTPIN 6
#define DHTTYPE DHT11

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

// Define the threshold distance (in centimeters)
const int binThreshold = 10;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Define pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize the DHT sensor
  dht.begin();
  
  // Give the sensors some time to settle
  delay(50);
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
  // Speed of sound in air = 343 m/s = 0.0343 cm/µs
  // Distance = (duration * speed of sound) / 2
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
  
  // Delay before taking the next measurement
  delay(2000);
}

