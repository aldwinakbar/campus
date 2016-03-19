#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
#include <string.h>

#define READ_SIZE 6	// in byte

using namespace std;

// ###################################### DECLARE VARIABLE ################################################ //

const char*      portACM         = "/dev/ttyACM1";
char 			 bufferRead[READ_SIZE];
char 			 bufferWrite[42];
int 			 fd;		 // File descriptor for serial port
// ###################################### DECLARE VARIABLE ################################################ //

// ###################################### Serial Communication ################################################ //

//serialStart(Lokasi Port, Baud Rate-nya, Besar Data yang ingin diRead untuk serialRead)
void serialStart(const char* portname, speed_t baud, int data){
	// Open the serial port as read/write, not as controlling terminal, and
	//   don't block the CPU if it takes too long to open the port.
	fd = open(portname, O_RDWR | O_NOCTTY );
	
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
	
	// disable hardware flow control
	// toptions.c_cflag &= ~CRTSCTS;
	
	// enabled Canonical input. Canonical input is line-oriented
	toptions.c_iflag |= (ICANON | ECHO | ECHOE);
	
	// disabled output processing. Raw data sent.
	//toptions.c_oflag &= ~OPOST;
	
	toptions.c_cc[VMIN] = data; //minimum data received
	toptions.c_cc[VTIME] = 0;	// time to wait
	
	// Now that we've populated our options structure, let's push it back to the
	//   system.
	tcsetattr(fd, TCSANOW, &toptions);
	
	// Flush the input and output buffer one more time.
	tcflush(fd, TCIOFLUSH);
}

//Data tersimpan di BufferRead, untuk data yang udah jadi integer bisa pakai intRead
//serialRead(Besar Data yang akan diread)
//Contoh Test : serialRead(3); printf("%d   %d\n", intRead, intRead*2 );
void serialRead(int dataRead){
	// Now, let's wait for an input from the serial port.
	fcntl(fd, F_SETFL, 0); // block until data comes in   
	read(fd, bufferRead, dataRead);
}

//Ada bit 0 diakhir setiap ngirim data. Buat filter di mikon untuk nge-abaikaan 0
//serialWrite(Integer yang ingin dikirim, Besar Bilangan Integernya)
//Contoh : serialWrite(123,3);}
void serialWrite(int dataOut1, int dataWrite){
	//Lihat diarduino, awalnya startFlag emang 8 dan stopFlag 9 namun karena
	//ada bug di algoritma untuk ngubah asci jadi int == >  karena num=calc() +1;
	//semua yang hanya berdigit 2 atau 1 jadi ditambah 1
	sprintf(bufferWrite, "%d.",dataOut1);
	write(fd, bufferWrite, dataWrite);
}

void clearIOQueue(){
	tcflush(fd, TCIOFLUSH);
	usleep(10000);
}


// ###################################### Serial Communication ################################################ //


int main(){
	serialStart(portACM, B9600,READ_SIZE);
	while(1){
		serialRead(READ_SIZE);
		printf("You entered: %s\n", bufferRead);
	}
  close(fd);
	
}

