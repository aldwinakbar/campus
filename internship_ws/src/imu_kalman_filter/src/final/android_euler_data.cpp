
#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#define RAD_TO_DEG (180.0/M_PI)


void IMUCallback(const sensor_msgs::Imu& msg);
ros::Publisher pub_rpy;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "android_euler_data");
    ros::NodeHandle n;
    pub_rpy = n.advertise<geometry_msgs::Vector3>("/bzseplate/android/imu/euler", 1000);
    ros::Subscriber sub_imu = n.subscribe("/bzseplate/android/imu", 1000, IMUCallback);

    ROS_INFO("waiting for quaternion");
    ros::spin();
    return 0;
}

void IMUCallback(const sensor_msgs::Imu& msg){

    tf::Quaternion quat(msg.orientation.x, msg.orientation.y, msg.orientation.z, msg.orientation.w);
    
    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    geometry_msgs::Vector3 rpy;
    rpy.x = roll*RAD_TO_DEG;
    rpy.y = pitch*RAD_TO_DEG;
    rpy.z = yaw*RAD_TO_DEG;

    pub_rpy.publish(rpy);
   // ROS_INFO("published rpy angles: roll=%f pitch=%f yaw=%f", rpy.x, rpy.y, rpy.z);
}
