#include <DHT.h>

#define DHTPIN 2               // Pin connected to the DATA pin of the DHT11 sensor
#define DHTTYPE DHT11          // DHT 11
#define RELAYPIN 3             // Pin connected to the IN pin of the relay module
#define DEFAULT_TEMP_THRESHOLD 28 // Default temperature threshold in degrees Celsius

DHT dht(DHTPIN, DHTTYPE);
float tempThreshold = DEFAULT_TEMP_THRESHOLD;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // Make sure relay is off initially

  Serial.println("System Initialized");
  Serial.print("Default Temperature Threshold: ");
  Serial.print(tempThreshold);
  Serial.println(" °C");
  Serial.println("To change the threshold, type a new value and press Enter.");
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Check if temperature exceeds the threshold
  if (temperature > tempThreshold) {
    // Turn on the fan
    digitalWrite(RELAYPIN, HIGH);
    Serial.println("Fan turned ON");
  } else {
    // Turn off the fan
    digitalWrite(RELAYPIN, LOW);
    Serial.println("Fan turned OFF");
  }

  // Check for serial input to change the temperature threshold
  if (Serial.available() > 0) {
    String input = Serial.readString();
    float newThreshold = input.toFloat();
    if (newThreshold > 0) {  // Basic validation of input
      tempThreshold = newThreshold;
      Serial.print("New Temperature Threshold: ");
      Serial.print(tempThreshold);
      Serial.println(" °C");
    } else {
      Serial.println("Invalid input. Please enter a valid number.");
    }
  }
}
