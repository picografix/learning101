#include "ros/ros.h"
#include "geometry_msgs/Twist.h"


ros::Publisher velocity_publisher;
#define PI 3.1415926535897

using namespace std;

//move the robot straight
char move();

int main(int argc, char **argv)
{
	ros::init(argc, argv, "robot_cleaner");
	ros::NodeHandle n;
	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	char t1='f';
	while(t1!='e'){			
	move();}
}

char move()
{

	double speed=1;
	double speed2=30;
	double distance=2;
	char isForward;
	double angular_speed = speed2*2*PI/360;
	double relative_angle = 90*2*PI/360;
	
	cout<<"f for forward, b for backward , r for right , l for left, e for exit : ";
	cin>>isForward;
	geometry_msgs::Twist vel_msg;
	//distance = speed*time
	
	//set a random linear velocity in the x-axis
	if(isForward=='f'){
		vel_msg.linear.x =abs(speed);
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;
		vel_msg.angular.x =0;
		vel_msg.angular.y =0;
		vel_msg.angular.z =0;
	//t0: initial time
	double t0 = ros::Time::now().toSec();
	double current_distance=0;
	ros::Rate loop_rate(10);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_distance = speed*(t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	  }while(current_distance < distance);
	
	vel_msg.linear.x = 0;
	velocity_publisher.publish(vel_msg); 
	return isForward;
        }
	else if(isForward=='b'){
	vel_msg.linear.x =-abs(speed);
	vel_msg.linear.y = 0;
	vel_msg.linear.z = 0;
	vel_msg.angular.x =0;
	vel_msg.angular.y =0;
	vel_msg.angular.z =0;


	//t0: initial time
	double t0 = ros::Time::now().toSec();
	double current_distance=0;
	ros::Rate loop_rate(10);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_distance = speed*(t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	  }while(current_distance < distance);
	
	vel_msg.linear.x = 0;
	velocity_publisher.publish(vel_msg); 
	return isForward;
	//loop
	//publish the velocity
	//estimate the current_distance=speed*(t1-t0)
	//current_distance_moved_by_robot<=distance
}
	else if(isForward=='r'){
		vel_msg.linear.x =0;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;
		vel_msg.angular.x =0;
		vel_msg.angular.y =0;
		vel_msg.angular.z =-abs(angular_speed);
	double t0 = ros::Time::now().toSec();
	double current_angle = 0;
	ros::Rate loop_rate(1000);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_angle = angular_speed * (t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_angle < relative_angle);
	vel_msg.angular.z=0;
	velocity_publisher.publish(vel_msg);	
}
else if(isForward=='l'){
		vel_msg.linear.x =0;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;
		vel_msg.angular.x =0;
		vel_msg.angular.y =0;
		vel_msg.angular.z =abs(angular_speed);
	double t0 = ros::Time::now().toSec();
	double current_angle = 0;
	ros::Rate loop_rate(1000);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_angle = angular_speed * (t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_angle<relative_angle);
	vel_msg.angular.z=0;
	velocity_publisher.publish(vel_msg);	
}
}
