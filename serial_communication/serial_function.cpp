#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>
#include <string.h>

using namespace std;

// ###################################### DECLARE VARIABLE ################################################ //

const char*      portACM         = "/dev/ttyUSB0";
char 			 bufferRead[256];
char 			 bufferWrite[42];
int 			 intRead;
int 			 fd;
// ###################################### DECLARE VARIABLE ################################################ //

// ###################################### Serial Communication ################################################ //

//serialStart(Lokasi Port, Baud Rate-nya, Besar Data yang ingin diRead untuk serialRead)
void serialStart(const char* portname, speed_t baud, int data)
{
 fd = open(portname, O_RDWR | O_NOCTTY);
 struct termios toptions;
 tcgetattr(fd, &toptions);
 cfsetispeed(&toptions, baud);
 cfsetospeed(&toptions, baud);
 toptions.c_cflag &= ~PARENB;
 toptions.c_cflag &= ~CSTOPB;
 toptions.c_cflag &= ~CSIZE;
 toptions.c_cflag |= CS8;
 toptions.c_cflag &= ~CRTSCTS;
 toptions.c_cflag |= CREAD | CLOCAL;
 toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
 toptions.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
 toptions.c_oflag &= ~OPOST;
 toptions.c_cc[VMIN] = data;
 toptions.c_cc[VTIME] = 0;
 tcsetattr(fd, TCSANOW, &toptions);
 usleep(1000*1000);
 tcflush(fd, TCIFLUSH);
 }

//Data tersimpan di BufferRead, untuk data yang udah jadi integer bisa pakai intRead
//serialRead(Besar Data yang akan diread)
//Contoh Test : serialRead(3); printf("%d   %d\n", intRead, intRead*2 );
void serialRead(int dataRead){
read(fd, bufferRead, dataRead);
intRead = atoi(bufferRead);
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


// ###################################### Serial Communication ################################################ //


int main()
{
	int voiceData = 1;
	serialStart(portACM, B9600, 2);
	serialWrite(voiceData,2);
}

