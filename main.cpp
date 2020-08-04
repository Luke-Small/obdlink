#include "obd_pids.h"
#include <stdlib.h>
#include <string>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream> 

using namespace std; 

int main() {
     string def = "/dev/ttyUSB0";
     string filename, spf; 
     
      printf("\n------------------OBDLink SX Interface---------------\n");
      printf("Enter the name of the serial port file or type default.\n");
          cout << "Current default = " << def << '\n'; 
          cin >> filename; 
      if(filename == "default"){
          spf = def; 
      }
      else {
          spf = filename; 
      }
 /* --------------------- Open the Serial Port ---------------------*/ 
    int fd; //File Descriptor
  //openPort(fd);
    printf("\nOpening Serial Port......\n");
    fd = open(spf.c_str(), O_RDWR | O_NOCTTY);
  //Check for Errors
      if (fd < 0) {
          printf("Error %i from open: %s\n", errno, strerror(errno));
      }

 
 /* ------------------- Make new Termios Structure ---------------*/ 

 struct termios tty; 
 memset(&tty, 0, sizeof tty); 

 if(tcgetattr(fd, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
 }

 /* ---------------------- Set Attributes of Termios Structure------*/
 
 tty.c_cflag &= ~PARENB; //Disable Parity Bit 
 tty.c_cflag &= ~CSTOPB; // Clear Stop Field
 tty.c_cflag |= CS8; // 8 bits per byte
 tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control
 tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
 tty.c_cflag &= ~CSIZE; // Clears the mask for setting the data size
 tty.c_cflag &= ~HUPCL; 
 
 tty.c_lflag |= ECHOE; 
 tty.c_lflag &= ~(ICANON | ECHO | ISIG); // Disable Canonical Mode

 tty.c_iflag |= IXON; 
 tty.c_iflag &= ~( IXOFF | IXANY); 
 tty.c_iflag |= IGNPAR; 
 tty.c_iflag |= BRKINT; 
 tty.c_iflag &= ICRNL; 
 tty.c_oflag &= ~OPOST; 
 tty.c_oflag &= ~ONLCR; 
 
 tty.c_cc[VTIME] = 20; 
 tty.c_cc[VMIN] = 0; 
 cfsetospeed(&tty, B115200); 
// CHECK FOR ERRORS IN THE TERMIOS STRUCT CONFIGURATIONS
     if (tcsetattr(fd, TCSANOW, &tty) != 0) {
          printf("Error %i from tcsetattr: %s\n", errno, strerror(errno)); 
     }
     cout << "\n\n\tSERIAL PORT CONFIGURED..\n";  

/*-------------------- MAIN MENU LOOP -----------------------------*/
char iter = 'N'; 
char* COMMAND;  
int ans, delay; 
int ans2 = 0;
 
 while(iter == 'N' || iter == 'n'){
    system("clear"); 
    cout << "SELECT A COMMAND: \n\n"; 
    cout << "1.)\tGET SPEED\n"; 
    cout << "2.)\tGET RPM\n"; 
    cout << "3.)\tGET DEVICE INFO\n"; 
    cin >> ans;
            do{
               if(ans == 1){
                       COMMAND = PID_SPEED; 
                       cout << "\nThis is the command you sent = " << COMMAND;  
                    } 
               else if(ans == 2){
                       COMMAND = PID_RPM;                  
                       cout << "\nThis is the command you sent = " << COMMAND; 
                     
                    }
               else if(ans == 3){
                       COMMAND = DEVICE_INFO; 
                       cout << "\nThis is the command you sent = " << COMMAND;  
                    }
               else{
                        cout << ("You didn't press the right thing man."); 
                    }
                } while (ans2 == 1); 

//FLUSH THE RX TERMINAL 
    tcflush(fd, TCIFLUSH);
//WRITE TO THE SERIAL PORT
    write(fd, COMMAND, sizeof(COMMAND));  
     if (delay){
        long int sleep = delay * 1000000L; 
        usleep(sleep); //sleep time in the united states
     }

// ASSIGN MEMORY AND RECORD TO THE BUFFER
    char answer[256]; 
    memset(&answer, '\0', sizeof(answer));

//READ FROM SERIAL PORT AND RECORD # OF BYTES
    int bytes_read = read(fd, &answer, sizeof(answer));  
  
     printf("   read buffer = %s\n bytes read = %d\n", answer, bytes_read);
     printf(" Would You Like to Exit the Program? (Y/N)"); 
   cin >> iter; 
    }
} 
