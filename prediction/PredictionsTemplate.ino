// North Carolina State University ECE Senior Design Team 3
// TI Machine Learning Robotics
// Live Classification Template Code
// Available at https://github.com/asoakley/TI-ML-Tutorial
// Adapted from https://github.com/edgeimpulse/example-ti-msp432-mcu-motion

// Edge Impulse library, change the name to match your project
#include <TI-ML-Audio-Classification_inferencing.h>
// RSLK library
#include <SimpleRSLK.h>

/* Add any other necessary libraries here */

// Define input pins, change to pin location of your sensor(s)
#define INPUT_PIN        5

// Set sampling period (in milliseconds)
// Period = 1000 / sampling frequency (in Hz)
#define SAMPLE_PERIOD       1


// Private variables
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
// From our experience, the code does not work properly if debug_nn is set to "true"

// Allocate a buffer for input data values
float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

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

void getData() {
  // Initialize variable(s) for your data as whatever type suits your sensor (i.e. int, float, etc.)
  // Create more varaibles for additional sensors / sensor axes
  int data;

  // Loop for as long as it takes to fill one window of data
  // Loop increments by the number of sensor axes that Edge Impulse reads in your project
  for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i += EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME) {
    // Read data from your input
    // The example uses analogRead, replace with whatever sampling method you need for your sensor
    data = analogRead(INPUT_PIN);

    /* Do any required data processing here before it is added to the buffer */
    
    // Add data to buffer
    buffer[i] = data;

    // If you have more than one sensor or sensor axes, add them to the next location in the buffer, like below
    // buffer[i+1] = data2;
    // buffer[i+2] = data3;
    // Place each data point in the buffer in the order that you have defined in Edge Impulse

    // Wait for sample period to complete
    delay(SAMPLE_PERIOD);
  }
}

void predict() {
  Serial.println("\nSampling...");
  // Call your sampling function
  getData();

  // Turn the raw buffer into a signal that can be classified
  signal_t signal;
  int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  if (err != 0) {
    ei_printf("Failed to create signal from buffer (%d)\n", err);
    return;
  }

  // Run the classifier
  ei_impulse_result_t result = { 0 };
  err = run_classifier(&signal, &result, debug_nn);
  if (err != EI_IMPULSE_OK) {
    ei_printf("ERR: Failed to run classifier (%d)\n", err);
    return;
  }

  // Print the confidence of each class prediction to the serial port
  float check = 0.0;
  String pred = "";
  ei_printf("Predictions ");
  ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
            result.timing.dsp, result.timing.classification, result.timing.anomaly);
  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    
    // If the current prediction has the highest confidence so far, the name of its class is saved
    // When the loop ends, the program will have saved the class name of the model's best prediction
    if (result.classification[ix].value > check) {
      pred = result.classification[ix].label;
      check = result.classification[ix].value;
    }
  }
/////////////////////////// Edit this section according to your model classes ///////////////////////////
  // Add or remove if statements as needed, replace the words in quotes with the names of your classes
  // Within each if statement, code what you would like the robot to due as a result of that prediction
  if (pred == "Class 1"){
    /* Action 1 */
  }
  if (pred == "Class 2"){
    /* Action 2 */
  }
  if (pred == "Class 3"){
    /* Action 3 */
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void loop(){
  // Program loops through the prediction function, other desired actions can be added here
  predict();
}
