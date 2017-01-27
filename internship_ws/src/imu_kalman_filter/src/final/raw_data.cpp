#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <sensor_msgs/Imu.h>
#include <stdlib.h>
#include <math.h>
#define RAD_TO_DEG (180.0/M_PI)
#define DEG_TO_RAD (M_PI/180.0)
#define MPS2_TO_G 0.101972

using namespace std;

void IMUCallback(const sensor_msgs::Imu& msg);
static double getTime();
double accToPitch();
double accToRoll();

double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double last_time      = 0.0;
std_msgs::Float64 acc_roll;
std_msgs::Float64 acc_pitch;
std_msgs::Float64 gyro_roll;
std_msgs::Float64 gyro_pitch;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "raw_data");
  ros::NodeHandle n;
  ros::Subscriber sub_imu = n.subscribe("/bzseplate/android/imu", 10, IMUCallback);
  
  ros::Publisher pub_gyro_roll = n.advertise<std_msgs::Float64>("/internship/imu/gyro/roll", 10);
  ros::Publisher pub_acc_roll = n.advertise<std_msgs::Float64>("/internship/imu/acc/roll", 10);
  
  ros::Publisher pub_gyro_pitch = n.advertise<std_msgs::Float64>("/internship/imu/gyro/pitch", 10);
  ros::Publisher pub_acc_pitch = n.advertise<std_msgs::Float64>("/internship/imu/acc/pitch", 10);
  
  ros::spinOnce();
 
  // ######################################################################################### //
  acc_roll.data  = accToRoll();
  gyro_roll.data = acc_roll.data;
  
  acc_pitch.data  = accToPitch();
  gyro_pitch.data = acc_pitch.data;

while (ros::ok()){
	ros::spinOnce();
	double	time = getTime();
	double	dt = time - last_time;

	if (last_time == 0.0){
		dt = 0.0;
	}
    last_time = time;
    
    
	// ######################################################################################### //
	
	acc_roll.data  = accToRoll();
	gyro_roll.data += gyroX * dt; // Calculate gyro angle without any filter
	
	acc_pitch.data  = accToPitch();
	gyro_pitch.data += gyroY * dt; // Calculate gyro angle without any filter
	
	pub_gyro_roll.publish(gyro_roll);
	pub_acc_roll.publish(acc_roll);
		
	pub_gyro_pitch.publish(gyro_pitch);
	pub_acc_pitch.publish(acc_pitch);
	
	// ######################################################################################### //
	usleep(500);
}


  return 0;
}

void IMUCallback(const sensor_msgs::Imu& msg){

	accX = msg.linear_acceleration.x*MPS2_TO_G;
	accY = msg.linear_acceleration.y*MPS2_TO_G;
	accZ = msg.linear_acceleration.z*MPS2_TO_G;
	gyroX = msg.angular_velocity.x*RAD_TO_DEG;
	gyroY = msg.angular_velocity.y*RAD_TO_DEG;
	gyroZ = msg.angular_velocity.z*RAD_TO_DEG;
}

static double getTime(){
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1e6;
}

double accToPitch(){
	
	return atan2(-accX, sqrt(accY*accY + accZ*accZ)) * RAD_TO_DEG;

}
double accToRoll(){
	return atan2(accY, accZ) * RAD_TO_DEG;
}
