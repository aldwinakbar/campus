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


using namespace std;
using namespace cv;

char encoded_image[100000];
vector<uchar> buff;
vector<int> param = vector<int>(2);
int clientSocket, portNum, nBytes, bytes, x, server_port;
struct sockaddr_in serverAddr;
struct sockaddr_storage serverStorage;
socklen_t addr_size;
char* server_ip;

int main(int argc, char** argv){

	// ./client_udp 127.0.0.1 7891 90 0  IP Port Quality Webcam
	param[0] = CV_IMWRITE_JPEG_QUALITY;			// set tipe encoding 
	param[1] = atoi(argv[3]);					// set kualitas encoding

	strcpy(server_ip, "127.0.0.1");						// IP Server yang dituju
	server_port = 7891;	
        
    // Initialize Streaming Connection
	struct  	sockaddr_in serverAddr;
	socklen_t 	serverAddrLen = sizeof(serverAddr);
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);
    serverAddr.sin_port = htons(server_port);
	// Initialize Streaming Connection
		
	// Connect to Server
    connect(clientSocket, (sockaddr*)&serverAddr, serverAddrLen);
    
	VideoCapture cap(atoi(argv[4]));			// Membuka Kamera
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);		// Set Lebar gambar
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 360);		// Set tinggi Gambar


	if(!cap.isOpened())
	{
		cout << "Error\n";
		return -1;
	}

	Mat image_capture;

	while(1){
    cap >> image_capture;				// mengambil gambar dari kamera
    
    cvtColor(image_capture, image_capture, CV_8U);
		
    imencode(".jpeg",image_capture, buff,param);	// meng-encode gambar
          
    for (x = 0; x < buff.size(); x++){				// merubah data gambar dari tipe vector ke array
     encoded_image[x] = buff[x];
	}
    
	nBytes = buff.size();
	bytes = send(clientSocket, encoded_image, nBytes, 0);
	cout<<buff.size()<<" Bytes Sent"<<endl;
    memset(&encoded_image[0], 0, nBytes);			// men-clear buffer gambar
	}
  return 0;
}
