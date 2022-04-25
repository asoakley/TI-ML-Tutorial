# TI-ML-Tutorial
<html>
<body>
<h1>TI Machine Learning Robotics</h1>
<h3>Tutorial repository for TI-RSLK MAX Machine Learning used for NC State ECE Senior Design Fall 2021-Spring 2022</h3>
<ul>
    <li>PCB folder contains Eagle CAD files for the custom PCB schematic file as well as the board file. It also includes the necessary gerbers and libraries needed to recreate the custom sensors PCB</li>
    <ul>
        <li>Eagle Libraries contains the libraries needed to recreate our schematic and board</li>
        <li>PCB Gerbers are the gerber files that can be sent to a manufacturer for printing</li>
    </ul>
    <li>libraries folder contains the libraries used in Arduino IDE to get the MSP432 microcontroller and the RSLK MAX to function. 
    It also contains two pretrained Edge Impulse libraries that we have tested</li>
    <li>prediction folder contains the Arduino code for running edge impulse models. 
    It contains code for both Audio and Accelerometer Machine Learning as well as a template code for any sensors you would like to have.</li>
    <li>test and training folder contains Arduino code to sample accelerometer and/or audio data of the RSLK MAX</li>
</ul>

</body>
</html>
