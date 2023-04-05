float href, Vout, BN, t;
float u[3] = {0,0,0}; // u = {u(k), u(k-1), u(k-2)}
float e[3] = {0,0,0}; // e = {e(k), e(k-1), e(k-2)}
bool a;
void setup() {
  // Define PortD pins as Output
  DDRD = B11111111;
  pinMode(13,OUTPUT);
}

void loop() {
  // Read current time
  t = millis();
  
  // Read the output from the conditioned signal measured by the sensor
  Vout = analogRead(A3)/1023.0*5.0;      // [/1023.0*5.0] => 0->5
  // Read the reference point
  href = analogRead(A4)/1023.0*5.0*10.0; // [/1023.0*5.0*10] => 0->50 cm

  // Summation point operation
  e[0] = href - Vout;
  // Control action using the digital controller difference equation
  u[0] = 1.83974*u[1]-0.85097*u[2]+0.1238*e[1]-0.11987*e[2];

  // Output to the DAC point
  BN = u[0]/33.2*255.0; // [/33.2*255.0] => 0->255 (33.2:highest u)
  PORTD = BN;

  // Update values each sampling period
  u[2] = u[1];
  u[1] = u[0];

  e[2] = e[1];
  e[1] = e[0];
  a=!a;
  digitalWrite(13,a);
  delay(100-(millis()-t));
}
