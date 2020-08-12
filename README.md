# obdlink
# project start date: July 11, 2020
# version 1.0 

# SUMMARY
#  The obdlink is a stepping stool for a Linux to CAN communication interface through OBD protocols. It provides basic serial configuration tools using the Linux termios header to initize a termios structure. Serial configuration/transmission functions are integrated in as well. The obd_pids header file contains a few OBD and AT commands that can be accessed through the defined macros. 

# Installation Guide
#   Download main.cpp and obd_pids.h to a convenient directory and compiel using g++ compiler. A file called a.out should be created, you must then execute this by running "./a.out". Use vim or any other text editor to manipulate the program. 

# MISSION
#   Although obdlinks input and output are obviously limited in functionality, this is just to allow standard interaction with the process. The mission is to transform this program into its own class "serial_config.h" then use it in a GUI across multiple platforms within a universal vehicle infotainment/diagnostic system. Giving the driver full functionality of their vehicle. Any comments would be appreciated. 

# HARDWARE REQUIREMENTS
#   Obdlink Interface is configured to pair with the OBDLink SX Cable. This cable uses the standard RS232 to ELM327 protocols (ELM327 talks to the vehicles CAN using obd protocols) at a baudrate of 115200. 
