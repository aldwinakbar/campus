#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <sensor_msgs/Imu.h>
#include <stdlib.h>
#include <math.h>
#include "include/Kalman.h"
#define RAD_TO_DEG (180.0/M_PI)
#define DEG_TO_RAD (M_PI/180.0)
#define MPS2_TO_G 0.101972

using namespace std;

void IMUCallback(const sensor_msgs::Imu& msg);
static double GetTime();
double accToPitch();
double accToRoll();

double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double last_time      = 0.0;
std_msgs::Float64 acc_roll;
std_msgs::Float64 acc_pitch;
std_msgs::Float64 gyro_roll;
std_msgs::Float64 gyro_pitch;
std_msgs::Float64 gyro_yaw;
std_msgs::Float64 compl_roll;
std_msgs::Float64 compl_pitch;
std_msgs::Float64 kalman_roll;
std_msgs::Float64 kalman_pitch;

std_msgs::Float64 gyine_roll_rate;
std_msgs::Float64 gyine_roll;
std_msgs::Float64 gyine_pitch_rate;
std_msgs::Float64 gyine_pitch;
std_msgs::Float64 gyine_yaw_rate;
std_msgs::Float64 gyine_yaw;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "gyro_kinematic_attitude");
  ros::NodeHandle n;
  ros::Subscriber sub_imu = n.subscribe("/bzseplate/android/imu", 10, IMUCallback);
  
  ros::Publisher pub_gyine_roll = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/roll", 10);
  ros::Publisher pub_compl_roll = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/complementary/roll", 10);
  ros::Publisher pub_kalman_roll = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/kalman/roll", 10);

  ros::Publisher pub_gyine_pitch = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/pitch", 10);	
  ros::Publisher pub_compl_pitch = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/complementary/pitch", 10);
  ros::Publisher pub_kalman_pitch = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/kalman/pitch", 10);

  ros::Publisher pub_gyine_yaw = n.advertise<std_msgs::Float64>("/internship/imu/kinematic/yaw", 10);
	
  ros::spinOnce();
 
  // ######################################################################################### //
  acc_roll.data  = accToRoll();
  gyro_roll.data = acc_roll.data;
  compl_roll.data = acc_roll.data;
  Kalman kalmanX;
  double kalAngleX;
  kalmanX.setAngle(acc_roll.data);
  
  acc_pitch.data  = accToPitch();
  gyro_pitch.data = acc_pitch.data;
  compl_pitch.data = acc_pitch.data;
  Kalman kalmanY;
  double kalAngleY;
  kalmanY.setAngle(acc_pitch.data);
  /* 
   *Note if you set a larger value for Q, the more noise in the estimation of the state. 
   * So for instance if the estimated angle starts to drift you have to increase the value of Q_{\dot{\theta}_b} (Qbias). 
   * Otherwise if the estimate tends to be slow you are trusting the estimate of the angle too much and should 
   * try to decrease the value of Q_\theta (Qangle) to make it more responsive.
   *  
  */
  kalmanY.setQangle(0.001);
  kalmanY.setQbias(0.003);	// proses noise of the bias
  
  /*
   *Note that if you set the measurement noise variance Rmeasure too high 
   * the filter will respond really slowly as it is trusting new measurements less, 
   * but if it is too small the value might overshoot and be noisy 
   * since we trust the accelerometer measurements too much. 
   * 
  */
  kalmanY.setRmeasure(0.03); // R besar maka pengukuran dari acc lebih kecil. Semakin kecil, semakin noisy.
	
  gyro_yaw.data = 0;
  
  // ########################### Gyro Kinematics Equation ########################### //
  gyine_roll.data = 0;
  gyine_pitch.data = 0;
  gyine_yaw.data = 0;
  // ########################### Gyro Kinematics Equation  ########################### //

while (ros::ok()){
	ros::spinOnce();
	double	time = GetTime();
	double	dt = time - last_time;

	if (last_time == 0.0){
		dt = 0.0;
	}
    last_time = time;
    
    
	// ########################### Raw RPY from Accelerometer and Gyrometer ########################### //
	
	acc_roll.data  = accToRoll();
	gyro_roll.data += gyroX * dt; // Calculate gyro angle without any filter
	
	acc_pitch.data  = accToPitch();
	gyro_pitch.data += gyroY * dt; // Calculate gyro angle without any filter

	gyro_yaw.data += gyroZ * dt;
	
   // ########################### Raw RPY from Accelerometer and Gyrometer ########################### //
	

	
	// ########################### Gyro Kinematics Equation ########################### //
	long double gyro_roll_rad = gyro_roll.data*DEG_TO_RAD;
	long double gyro_pitch_rad = gyro_pitch.data*DEG_TO_RAD;
	
	gyine_roll_rate.data = gyroX + (gyroY*sin(gyro_roll_rad)*tan(gyro_pitch_rad)) + (gyroZ*cos(gyro_roll_rad)*tan(gyro_pitch_rad));
	gyine_roll.data += gyine_pitch_rate.data * dt;
	compl_roll.data = 0.98 * (compl_roll.data + gyine_roll_rate.data * dt) + 0.02 * acc_roll.data;
	kalman_roll.data = kalmanX.getAngle(acc_roll.data, gyine_roll_rate.data, dt); // Calculate the angle using a Kalman filter

	gyine_pitch_rate.data = (gyroY*cos(gyro_roll_rad)) - (gyroZ*sin(gyro_roll_rad));
	gyine_pitch.data += gyine_pitch_rate.data * dt;
	compl_pitch.data = 0.98 * (compl_pitch.data + gyine_pitch_rate.data * dt) + 0.02 * acc_pitch.data;
	kalman_pitch.data = kalmanY.getAngle(acc_pitch.data, gyine_pitch_rate.data, dt); // Calculate the angle using a Kalman filter

	long double kalman_roll_rad = kalman_roll.data*DEG_TO_RAD;
	long double kalman_pitch_rad = kalman_pitch.data*DEG_TO_RAD;
	gyine_yaw_rate.data = (gyroY*(sin(kalman_roll_rad)/cos(kalman_pitch_rad))) + (gyroZ*(cos(kalman_roll_rad)/cos(kalman_pitch_rad)));
	gyine_yaw.data += gyine_yaw_rate.data * dt;
	
	pub_gyine_roll.publish(gyine_roll);
	pub_compl_roll.publish(compl_roll);
	pub_kalman_roll.publish(kalman_roll);
	
	pub_gyine_pitch.publish(gyine_pitch);
	pub_compl_pitch.publish(compl_pitch);
	pub_kalman_pitch.publish(kalman_pitch);

	pub_gyine_yaw.publish(gyine_yaw);
	// ########################### Gyro Kinematics Equation ########################### //

	
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

static double GetTime(){
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1e6;
}

double accToPitch(){
	
	return atan2(-accX, sqrt(accY*accY + accZ*accZ)) * RAD_TO_DEG;
	/*
	double acc_pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
	if (isnan(acc_pitch)){
		return 0;
	}
	else {
		return atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
	}
	*/
}
double accToRoll(){
	return atan2(accY, accZ) * RAD_TO_DEG;
}
