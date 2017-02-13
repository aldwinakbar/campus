#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <fstream>
#include <arpa/inet.h>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// ./server_multiple_udp 7891 0 90

using namespace std;
using namespace cv;

void *clientVideo ( void *ptr );   
void *videoCapture ( void *ptr );   
int nBytes,encoded;
vector<int> param = vector<int>(2);
Mat image_capture;

int main(int argc, char** argv){
  
  char buffer[16];
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t addr_size, client_addr_size;
  int i, client_id, client_port,x,udpSocket, server_port,video_device;
  
  pthread_t client_video[128];	// Thread untuk setiap Client yang konek
  pthread_t video_capture;		// Thread untuk mengambil gambar
	
  /*	Inisialisasi Socket Server */
  server_port = atoi(argv[1]);
  udpSocket = socket(AF_INET, SOCK_DGRAM, 0);		// membuka koneksi UDP
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(server_port);			// Port Server
  serverAddr.sin_addr.s_addr = inet_addr("127.00.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); 
  addr_size = sizeof clientAddr;
   /*	Inisialisasi Socket Server */
  
  
  param[0] = CV_IMWRITE_JPEG_QUALITY;	// Menggunakan JPEG Encoding
  param[1] = atoi(argv[3]);				// Kualitas Encoding
  video_device = atoi(argv[2]);			// Kamera yang dipakai
  pthread_create (&video_capture, NULL , videoCapture, &video_device);	// Thread untuk membuka kamera
  
  i = 0;
  
  /* Selalu menunggu untuk koneksi dari client */
  while(1){
 
    nBytes = recvfrom(udpSocket,buffer,16,0,(struct sockaddr *)&clientAddr, &addr_size); // menerima ID Client
    
    /* mengubah id client menjadi port number */
    client_id = (buffer[0] - '0')*100+(buffer[1] - '0')*10+(buffer[2] - '0');
    client_port = client_id + 8000;
    memset(&buffer[0], 0, nBytes);
	sprintf(buffer,"%d",client_port);
	/* mengubah id client menjadi port number */
	
	nBytes = strlen(buffer);
    cout << "New Client on Port " << client_port << endl;
    pthread_create (&client_video[i], NULL , clientVideo, &client_port);			// thread untuk mengirim data ke client 
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&clientAddr,addr_size);		// mengirim port number untuk client me-rekonek ke server

	i++;
  }
	
  for(x = 0 ; x < i; x++){ 
	  pthread_join(client_video[x], NULL);
  }
  
  pthread_join(video_capture, NULL);
  return 0;
}

void *videoCapture ( void *ptr ){
	int x, device, nBytesAfter;
	device = *((int *) ptr);
	VideoCapture cap(device);				// membuka kamera
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);	// set lebar pixel
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 360);	// set tinggi pixel
	
	nBytesAfter = 0;
 
	while(1){
		
		cap >> image_capture;				// mengambil gambar
    
	}
}


void *clientVideo ( void *ptr ){
	
	char buffer[16];
    char encoded_image[100000];
    vector<uchar> buff;
	
	int clientSocket, nBytes,client_port_number, x;
	struct sockaddr_in serverAddr,clientAddr;
	socklen_t addr_size;
    client_port_number = *((int *) ptr);			// Port Server yang akan dihubungi client
	
	/* Inisialisasi Port Khusus untuk Client i */
	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(client_port_number);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	bind(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	addr_size = sizeof clientAddr;	
	/* Inisialisasi Port Khusus untuk Client i */

	recvfrom(clientSocket,buffer,16,0,(struct sockaddr *)&clientAddr, &addr_size); // menunggu client untuk terhubungi 
	Mat image_sent;
	while(1){
	
		image_sent = image_capture;
		cvtColor(image_sent, image_sent, CV_8U);
		imencode(".jpeg",image_sent, buff,param);	// di-encode
		
		for (x = 0; x < buff.size(); x++){			// meng-konversi image yang terencode dari tipe vector ke array
			encoded_image[x] = buff[x];
		}
	
		nBytes = buff.size();
		sendto(clientSocket,encoded_image,nBytes,0,(struct sockaddr *)&clientAddr,addr_size);		// Mengirim data
		memset(&encoded_image[0], 0, nBytes);	// menclear buffer encoded image 
  }
    
	
}
