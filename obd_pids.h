#ifndef OBD_PIDS_H
#define OBD_PIDS_H



/////////////////////AT COMMANDS/////////////////////////////
#define SET_NO_SPACES "ats0\r"
#define DEVICE_HARD_RESET "atz\r"
#define DEVICE_INFO "ati\r"

/////////////////////ST COMMANDS/////////////////////////////

/////////////////////OBD COMMANDS/////////////////////////////
#define PID_SPEED "010D1\r"
#define PID_RPM "010C\r"

#endif
