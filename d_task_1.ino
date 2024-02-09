const int pirSensorPin = A0; // Simulated motion sensor (analog input)
const int soundSensorPin = A1; // Simulated sound sensor (analog input)
const int soilMoisturePin = A2; // Simulated soil moisture sensor (analog input)
const int temperatureSensorPin = A3; // Simulated temperature sensor (analog input)
const int ledPinMotion = 13;
const int ledPinMoisture = 12;
const int ledPinTemperature = 11; // New LED for temperature
const int buzzerPin = 10; // Buzzer pin
const int motionThreshold = 500; // Motion detection threshold
const int soundThreshold = 100; // Sound detection threshold
const int timerInterval = 2000; // Timer interval (milliseconds)

int motionDetected = LOW;
int soundDetected = LOW;
int soilMoistureValue = 0;
int temperatureValue = 0;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ledPinMotion, OUTPUT);
  pinMode(ledPinMoisture, OUTPUT);
  pinMode(ledPinTemperature, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= timerInterval) {
    // Time to check sensors and perform actions
    previousMillis = currentMillis;
    
    // Simulated sensor readings
    motionDetected = analogRead(pirSensorPin); // Simulating motion detection
    soundDetected = analogRead(soundSensorPin) > soundThreshold; // Simulating sound detection
    soilMoistureValue = analogRead(soilMoisturePin); // Simulating soil moisture reading
    temperatureValue = analogRead(temperatureSensorPin); // Simulating temperature reading

    // Convert temperature reading to Celsius
    float temperature = (temperatureValue * 5.0 / 1023) * 100;

    // Print sensor values for debugging
    Serial.print("Motion Sensor Value: ");
    Serial.println(motionDetected);
    Serial.print("Sound Sensor Value: ");
    Serial.println(soundDetected);
    Serial.print("Soil Moisture Value: ");
    Serial.println(soilMoistureValue);
    Serial.print("Temperature Value: ");
    Serial.println(temperature);

    // Process sensor data
    if (motionDetected > motionThreshold && soilMoistureValue < 500 && temperature > 25) {
      digitalWrite(ledPinMoisture, LOW);
      digitalWrite(ledPinTemperature, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
    } else if (motionDetected > motionThreshold && temperature > 25) {
      digitalWrite(ledPinTemperature, HIGH);
    } else if (soilMoistureValue < 500 && temperature > 25) {
      digitalWrite(ledPinMoisture, LOW);
      digitalWrite(ledPinTemperature, HIGH);
    } else if (soilMoistureValue < 500) {
      digitalWrite(ledPinMoisture, LOW);
    } else if (temperature > 25) {
      digitalWrite(ledPinTemperature, HIGH);
    } else {
      // Reset LEDs and buzzer if no condition is met
      digitalWrite(ledPinMotion, LOW);
      digitalWrite(ledPinMoisture, LOW);
      digitalWrite(ledPinTemperature, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }
}


