#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
#include <string.h>
#define BUFFER_SIZE 1024
using namespace std;


// ###################################### DECLARE VARIABLE ################################################ //

const char*      portACM         = "/dev/ttyACM1";
char 			 bufferRead[BUFFER_SIZE];
char 			 bufferWrite[BUFFER_SIZE];
int 			 fd;		 // File descriptor for serial port
// ###################################### DECLARE VARIABLE ################################################ //

// ###################################### Serial Communication ################################################ //


void clearIOQueue(){
	tcflush(fd, TCIOFLUSH);
	usleep(10000);
}
int serialStart(const char* portname, speed_t baud){
	// Open the serial port as read/write, not as controlling terminal, and
	//   don't block the CPU if it takes too long to open the port.
	fd = open(portname, O_RDWR | O_NOCTTY);
		
	if (fd == -1) {
      return 0;
	}
	
	struct termios toptions;	// struct to hold the port settings
	
	// Fetch the current port settings
	tcgetattr(fd, &toptions);
	
	// Set Input and Output BaudRate
	cfsetispeed(&toptions, baud);
	cfsetospeed(&toptions, baud);
	
	// Set up the frame information.
	toptions.c_cflag &= ~PARENB;	// no parity
	toptions.c_cflag &= ~CSTOPB;	// one stop bit
	toptions.c_cflag &= ~CSIZE;		// clear frame size info
	toptions.c_cflag |= CS8;		// 8 bit frames
	
	// c_cflag contains a few important things- CLOCAL and CREAD, to prevent
	// this program from "owning" the port and to enable receipt of data.
	// Also, it holds the settings for number of data bits, parity, stop bits,
	// and hardware flow control.
	toptions.c_cflag |= CREAD ;
	toptions.c_cflag |= CLOCAL;
	
	 /* no hardware flow control */
	 toptions.c_cflag &= ~CRTSCTS;
	 
	 /* disable input/output flow control, disable restart chars */
	 toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
	 
	/*
	ICRNL
	: map CR to NL (otherwise a CR input on the other computer
	will not terminate input)
	otherwise make device raw (no other input processing)
	*/
	toptions.c_iflag = ICRNL;
	 
	 /* disable canonical input, disable echo,
	 disable visually erase chars,
	 disable terminal-generated signals */
	 toptions.c_lflag = ICANON;
	 /* disable output processing, output set to raw*/
	 toptions.c_oflag =  ~OPOST;
	 
	// Now that we've populated our options structure, let's push it back to the
	//   system.
	tcsetattr(fd, TCSANOW, &toptions);
	
	usleep(1000000);
	
	// Flush the input and output buffer one more time.
	tcflush(fd, TCIOFLUSH);
	return 1;
}

void serialRead(int dataRead){
	// Now, let's wait for an input from the serial port.
	tcflush(fd, TCIOFLUSH);
	fcntl(fd, F_SETFL, 0); // block until data comes in
	read(fd, bufferRead, dataRead);
}

void serialWrite(const char* data_out, int data_size){
	tcflush(fd, TCIOFLUSH);
	sprintf(bufferWrite,"%s\r\n",data_out);
	int n = write(fd, bufferWrite, data_size+3);
	if (n < 0)
		fputs("write() of 4 bytes failed!\n", stderr);
}

// ###################################### Serial Communication ################################################ //


int main(){
	serialStart(portACM, B9600,READ_SIZE);
	while(1){
		serialRead(8);
		printf("You entered: %s\n", bufferRead);
	}
  close(fd);
	
}

