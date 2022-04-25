// North Carolina State University ECE Senior Design Team 3
// TI Machine Learning Robotics
// Data Sampling Template Code
// Available at https://github.com/asoakley/TI-ML-Tutorial

// RSLK library
#include <SimpleRSLK.h>

/* Add any other necessary libraries here */

// Define input pins, change to pin location of your sensor(s)
#define INPUT_PIN        5

// Set sampling period (in milliseconds)
// Period = 1000 / sampling frequency (in Hz)
#define SAMPLE_PERIOD       1

void setup() {

  // Initialize RSLK pin definitions
  setupRSLK();

  // Initialize sensor pin as an input
  // Use whatever code you need to set up your sensor, the following line is only an example
  pinMode(INPUT_PIN, INPUT);

  // Uncomment the line below for 14-bit resolution (default is 12)
  // analogReadResolution(14);

  /* Optional functions to initialize LED pins */
  // pinMode(LED_FR_PIN, OUTPUT); 
  // pinMode(LED_FL_PIN, OUTPUT); 
  // pinMode(LP_RED_LED_PIN, OUTPUT);
  // pinMode(LP_RGB_LED_RED_PIN, OUTPUT);
  // pinMode(LP_RGB_LED_BLUE_PIN, OUTPUT); 
  // pinMode(LP_RGB_LED_GREEN_PIN, OUTPUT);
  /* Turn an LED on (HIGH) or off (LOW) by using the line below */
  // digitalWrite(LED_FR_PIN, HIGH);

  /* Optional functions to enable and control the RSLK's motors */
  /* Can use "BOTH_MOTORS", "LEFT_MOTOR", or "RIGHT_MOTOR" */
  // enableMotor(BOTH_MOTORS);
  // setMotorSpeed(BOTH_MOTORS,0);
  // setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);

  /* Optional functions to set up interrupts with the MSP432's side switches */
  // pinMode(LP_S1_PIN, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(LP_S1_PIN),SW1_ISR, RISING);
  // pinMode(LP_S2_PIN, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(LP_S2_PIN),SW2_ISR, RISING);
  /* If you choose to use interrupts, create a function for each one like below:
          void SW1_ISR(){
            {Your code here}         
          }
     Do this outside of void setup() or any other functions */

  Serial.begin(115200); // Initialize Serial communication
  while (!Serial);      // Wait for the serial port to open
  delay(100);
}

void loop() {
  // Continuously read in data and print it to the serial port
  // Code to control the robot while sampling can be added if need be
  
  // Initialize variable(s) for your data as whatever type suits your sensor (i.e. int, float, etc.)
  // Create more varaibles for additional sensors / sensor axes
  int data;

  // Read data from your input
  // The example uses analogRead, replace with whatever sampling method you need for your sensor
  data = analogRead(INPUT_PIN);

  /* Do any required data processing here before it is printed to serial */
    
  // Print data to the serial port
  // This is how the Edge Impulse data forwarder reads and uploads your sensor readings
  Serial.print(data);
  
  // If you have data from more than one sensor / sensor axes, comma-separate them before printing, like below
  // Serial.print(",");
  // Serial.print(data2);
  // Serial.print(",");
  // Serial.print(data3);
  // The forwarder automatically detects the number of sensor axes by counting the comma-separated datapoints
  
  Serial.println(); // End in a newline so the forwarder knows that the data in that time frame is complete

  // Wait for sample period to complete
  delay(SAMPLE_PERIOD);
}
