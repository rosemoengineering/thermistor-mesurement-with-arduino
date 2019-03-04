#include <math.h>
int thermistor_output = 1;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  int thermistor_adc_val;
  double output_voltage, thermistor_resistance, therm_res_ln, temperature; 
  thermistor_adc_val = analogRead(thermistor_output);
  output_voltage = ( (thermistor_adc_val * 5) / 1023.0 );
  thermistor_resistance = ( ( 5 * ( 1.0 / output_voltage ) ) - 1 ); /* Resistance in kilo ohms */
  
  thermistor_resistance = thermistor_resistance * 1000 ; /* Resistance in ohms   */
  therm_res_ln = log(thermistor_resistance);
  
  /*  Steinhart-Hart Thermistor Equation: */
  /*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)   */
 
  temperature = ( 1 / ( 0.002694902179 + ( -0.0000001652194432 * therm_res_ln ) + ( 0.000001922597897 * therm_res_ln * therm_res_ln * therm_res_ln ) ) ); /* Temperature in Kelvin */
  temperature = temperature - 273.15; /* Temperature in degree Celsius */
  Serial.print("Temperature in degree Celsius = ");
  Serial.print(temperature);
  Serial.print("\n\n");
  delay(1000);
}
