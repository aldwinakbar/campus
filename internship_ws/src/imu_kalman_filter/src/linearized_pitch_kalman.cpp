#define ARMA_DONT_PRINT_ERRORS
#include <armadillo>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <sensor_msgs/Imu.h>
#include <stdlib.h>
#include <math.h>
#define RAD_TO_DEG (180.0/M_PI)
#define DEG_TO_RAD (M_PI/180.0)
#define MPS2_TO_G 0.101972

using namespace std;
using namespace arma;

class KalmanAttitude {
public:
    KalmanAttitude() {
		
		x.zeros(4,1);
		x_current.zeros(4,1);
		P.zeros(4,4);
		P_current.zeros(4,4);
		y.zeros(2,1);
		S.zeros(2,2);
		K.zeros(4,2);
		
		F.eye(4,4);
		B.zeros(4,3);
		u.zeros(3,1);
		Q.zeros(4,4);
		z.zeros(2,1);
		H.zeros(2,4);
		H(0,0) = 1;
		H(1,1) = 1;
		R.zeros(2,2);
		
        /* We will set the variables like so, these can also be tuned by the user */
        setQtheta	(0.001); 
		setQphi		(0.001); 
		setQBtheta	(0.003); 
		setQBphi	(0.003);
		
		setRtheta	(0.003); 
		setRphi		(0.003);

		setTheta	(0); 
		setPhi		(0); 
		setBtheta	(0);
		setBphi		(0); 
		
		lconst	= 0.000001;
    };
    
    void computeKalman(double newTheta, double newPhi, double newPrate, double newQrate, double newRrate, double dt) {
      
		/* Update Matrix */
        updateFMatrix(x_current(0,0),x_current(1,0), newPrate, newQrate, newRrate, dt);
        updateBMatrix(x_current(0,0),x_current(1,0), newPrate, newQrate, newRrate, dt);
        
        z(0,0) = newTheta;
        z(1,0) = newPhi;
        u(0,0) = newPrate;
        u(1,0) = newQrate;
        u(2,0) = newRrate;
        /* ############## */
        
        
     	x = (F * x_current) + (B * u);					// Predict
		P = ( F * P_current * F.t() ) + Q;				// Predict
		
		y = z - (H * x);								// Update
		S = ( H * P * H.t() ) + R;						// Update
		
		try{
			// if matrix S appears to be singular, then set K to 0
			K = P * H.t() * S.i();						// Update
		}
		
		catch (exception& e){
			K.zeros();
		}
		
		x_current = x + (K * y);						// Update
		P_current = (eye<mat>(4,4) - (K * H)) * P;		// Update
		
    };
   
    void setTheta(double theta) { x_current(0,0) = theta; }; 
    void setPhi(double phi) { x_current(1,0) = phi; }; 
    void setBtheta(double bias) { x_current(2,0) = bias; }; 
    void setBphi(double bias) { x_current(3,0) = bias; }; 
   
    double getTheta() { return x_current(0,0); };
    double getPhi() { return x_current(1,0); };
    double getBtheta() { return x_current(2,0); }; 
    double getBphi() { return x_current(3,0) ; };
   
    /* These are used to tune the Kalman filter */
    void setQtheta(double Q_theta) { Q(0,0) = Q_theta; };
    void setQphi(double Q_phi) { Q(1,1) = Q_phi; };
    void setQBtheta(double Q_bias) { Q(2,2) = Q_bias; };
    void setQBphi(double Q_bias) { Q(3,3) = Q_bias; };
    void setRtheta(double R_theta) { R(0,0) = R_theta; };
    void setRphi(double R_phi) { R(1,1) = R_phi; };
	void setLconst(double lconst) { this->lconst = lconst; };
    
    double getQtheta() { return Q(0,0); };
    double getQphi() { return Q(1,1); };
    double getQBtheta() { return Q(2,2); };
    double getQBphi() { return Q(3,3); };
    double getRtheta() { return R(0,0); };
    double getRphi() { return R(1,1); };
    double getLconst() { return lconst; };	
	

private:
    /* Kalman filter variables */
    mat x;
	mat x_current;
	mat P;
	mat P_current;
	mat y;
	mat S;
	mat K;
	
	mat F;
	mat B;
	mat u;
	mat Q;
	mat z;
	mat H;
	mat R;
	
   double lconst;
   
    double pitchRateDynamicEquation(double phi, double q_rate, double r_rate){
		return ((q_rate*cos(phi)) - (r_rate*sin(phi)));
	}
	
    double rollRateDynamicEquation(double theta, double phi, double p_rate, double q_rate, double r_rate){
		return p_rate + (q_rate * sin(phi) * tan(theta)) + (r_rate * cos(phi) * tan(theta));
	}
	
	void updateFMatrix(double theta, double phi, double newPrate, double newQrate, double newRrate, double dt){
		double linearized_theta_phi	= (pitchRateDynamicEquation(phi+lconst, newQrate, newRrate)-pitchRateDynamicEquation(phi-lconst, newQrate, newRrate))/2*lconst;
		double linearized_phi_theta	= (rollRateDynamicEquation(theta+lconst, phi, newPrate, newQrate, newRrate)-rollRateDynamicEquation(theta-lconst,phi,newPrate, newQrate, newRrate))/2*lconst;
		double linearized_phi_phi	= (rollRateDynamicEquation(theta, phi+lconst, newPrate, newQrate, newRrate)-rollRateDynamicEquation(theta,phi-lconst,newPrate, newQrate, newRrate))/2*lconst;
			
		F(0,1) = linearized_theta_phi * dt;
		F(0,2) = 0 - dt;
		F(1,0) = linearized_phi_theta * dt;
		F(1,1) = 1 + (linearized_phi_phi * dt);
		F(1,3) = 0 - dt;
	}
	
	void updateBMatrix(double theta, double phi, double newPrate, double newQrate, double newRrate, double dt){
		double linearized_theta_q = (pitchRateDynamicEquation(phi, newQrate+lconst, newRrate)-pitchRateDynamicEquation(phi, newQrate-lconst, newRrate))/2*lconst;
		double linearized_theta_r = (pitchRateDynamicEquation(phi, newQrate, newRrate+lconst)-pitchRateDynamicEquation(phi, newQrate, newRrate-lconst))/2*lconst;
		double linearized_phi_p	  = (rollRateDynamicEquation(theta, phi, newPrate+lconst, newQrate, newRrate)-rollRateDynamicEquation(theta,phi,newPrate-lconst, newQrate, newRrate))/2*lconst;
		double linearized_phi_q	  = (rollRateDynamicEquation(theta, phi, newPrate, newQrate+lconst, newRrate)-rollRateDynamicEquation(theta,phi,newPrate, newQrate-lconst, newRrate))/2*lconst;
		double linearized_phi_r	  = (rollRateDynamicEquation(theta, phi, newPrate, newQrate, newRrate+lconst)-rollRateDynamicEquation(theta,phi,newPrate, newQrate, newRrate-lconst))/2*lconst;
		
		B(0,1) = linearized_theta_q * dt;
		B(0,2) = linearized_theta_r * dt;
		B(1,0) = linearized_phi_p * dt;
		B(1,1) = linearized_phi_q * dt;
		B(1,2) = linearized_phi_r * dt;
	}
	
};

using namespace std;

void IMUCallback(const sensor_msgs::Imu& msg);
static double GetTime();
double accToPitch();
double accToRoll();

double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double last_time      = 0.0;

std_msgs::Float64 acc_roll;
std_msgs::Float64 gyro_roll;
std_msgs::Float64 compl_roll;
std_msgs::Float64 kalman_roll;

std_msgs::Float64 acc_pitch;
std_msgs::Float64 gyro_pitch;
std_msgs::Float64 compl_pitch;
std_msgs::Float64 kalman_pitch;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "vehicle_attitude");
  ros::NodeHandle n;
  ros::Subscriber sub_imu = n.subscribe("/bzseplate/android/imu", 10, IMUCallback);
  
  ros::Publisher pub_gyro_roll = n.advertise<std_msgs::Float64>("/internship/imu/gyro/roll", 10);
  ros::Publisher pub_acc_roll = n.advertise<std_msgs::Float64>("/internship/imu/acc/roll", 10);
  ros::Publisher pub_compl_roll = n.advertise<std_msgs::Float64>("/internship/imu/complementary/roll", 10);
  ros::Publisher pub_kalman_roll = n.advertise<std_msgs::Float64>("/internship/imu/kalman/roll", 10);
  
  ros::Publisher pub_gyro_pitch = n.advertise<std_msgs::Float64>("/internship/imu/gyro/pitch", 10);
  ros::Publisher pub_acc_pitch = n.advertise<std_msgs::Float64>("/internship/imu/acc/pitch", 10);
  ros::Publisher pub_compl_pitch = n.advertise<std_msgs::Float64>("/internship/imu/complementary/pitch", 10);
  ros::Publisher pub_kalman_pitch = n.advertise<std_msgs::Float64>("/internship/imu/kalman/pitch", 10);
  
  ros::Publisher pub_gyro_yaw = n.advertise<std_msgs::Float64>("/internship/imu/gyro/yaw", 10);
	
  ros::spinOnce();
 
  // ######################################################################################### //
  KalmanAttitude aircraft_attitude;
  acc_roll.data  = accToRoll();
  gyro_roll.data = acc_roll.data;
  compl_roll.data = acc_roll.data;
  aircraft_attitude.setPhi(acc_roll.data);
  acc_pitch.data  = accToPitch();
  gyro_pitch.data = acc_pitch.data;
  compl_pitch.data = acc_pitch.data;
  aircraft_attitude.setTheta(acc_pitch.data);
while (ros::ok()){
	ros::spinOnce();
	double	time = GetTime();
	double	dt = time - last_time;

	if (last_time == 0.0){
		dt = 0.0;
	}
    last_time = time;
    
    
	// ######################################################################################### // 
	aircraft_attitude.computeKalman(accToPitch(), accToRoll(),gyroX, gyroY, gyroZ, dt);
	
	acc_roll.data  = accToRoll();
	gyro_roll.data += gyroX * dt; // Calculate gyro angle without any filter
	compl_roll.data = 0.98 * (compl_roll.data + gyroX * dt) + 0.02 * acc_roll.data;
	kalman_roll.data = aircraft_attitude.getPhi(); // Calculate the angle using a Kalman filter

	acc_pitch.data  = accToPitch();
	gyro_pitch.data += gyroY * dt; // Calculate gyro theta without any filter
	compl_pitch.data = 0.98 * (compl_pitch.data + gyroY * dt) + 0.02 * acc_pitch.data;
	kalman_pitch.data = aircraft_attitude.getTheta(); // Calculate the angle using a Kalman filter

	pub_kalman_roll.publish(kalman_roll);
	pub_gyro_roll.publish(gyro_roll);
	pub_acc_roll.publish(acc_roll);
	pub_compl_roll.publish(compl_roll);
	
	pub_kalman_pitch.publish(kalman_pitch);
	pub_gyro_pitch.publish(gyro_pitch);
	pub_acc_pitch.publish(acc_pitch);
	pub_compl_pitch.publish(compl_pitch);

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
