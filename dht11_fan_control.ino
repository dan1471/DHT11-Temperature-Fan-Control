#include <DHT.h>

#define DHTPIN 2          // Pin connected to the DATA pin of the DHT11 sensor
#define DHTTYPE DHT11     // DHT 11
#define RELAYPIN 3        // Pin connected to the IN pin of the relay module
#define TEMPERATURE_THRESHOLD 28 // Temperature threshold in degrees Celsius

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // Make sure relay is off initially
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read temperature in Celsius
  float temperature = dht.readTemperature();

  // Check if the reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check if temperature exceeds the threshold
  if (temperature > TEMPERATURE_THRESHOLD) {
    // Turn on the fan
    digitalWrite(RELAYPIN, HIGH);
    Serial.println("Fan turned ON");
  } else {
    // Turn off the fan
    digitalWrite(RELAYPIN, LOW);
    Serial.println("Fan turned OFF");
  }
}
