// ---------------- IR Sensor Pin ----------------
#define IR_PIN D5   // GPIO14

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);
}

void loop() {
  int raw_ir = digitalRead(IR_PIN);

  int plot_value;

  // Convert raw sensor output to logical value
  if (raw_ir == LOW) {
    plot_value = 1;   // Object Detected
  } else {
    plot_value = 0;   // No Object
  }

  // Send ONLY number for Serial Plotter
  Serial.println(plot_value);

  delay(100);  // Smooth plotting
}
