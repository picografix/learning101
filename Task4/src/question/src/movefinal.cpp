#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<cmath>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"


ros::Publisher velocity_publisher;
#define PI 3.1415926535897
using namespace cv;
using namespace std;

void move(char);

 int main( int argc, char** argv )
 {
	ros::init(argc, argv, "robot_cleaner");
	ros::NodeHandle n;
	velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

 int iLowH = 170;
 int iHighH = 179;

 int iLowS = 150; 
 int iHighS = 255;

 int iLowV = 60;
 int iHighV = 255;

 //Create trackbars in "Control" window
 createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 createTrackbar("HighH", "Control", &iHighH, 179);

 createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255);

 createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255);

 int iLastX = -1; 
 int iLastY = -1;

 //Capture a temporary image from the camera
 Mat imgTmp;
 cap.read(imgTmp); 

 //Create a black image with the size as the camera output
 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
 

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video



         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

  Mat imgHSV;

  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  //morphological opening (removes small objects from the foreground)

  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

  //morphological closing (removes small holes from the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

  //Calculate the moments of the thresholded image
  Moments oMoments = moments(imgThresholded);

  double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

  // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
  if (dArea > 10000)
  {
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea;
   int max=0;        
   if(abs(posX-iLastX)>abs(posY-iLastY)) max=0;
   else max=1;     
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
    //Draw a red line from the previous point to the current point
    if(posY-iLastY>0&&max==1){ move('f');
   cout<<"forward"<<" "<<posX<<" "<<posY<<endl;

}
 else if((posY-iLastY)<0&&max==1){ move('b');
	cout<<"backward"<<" "<<posX<<" "<<posY<<endl;
}
    if((posX-iLastX)>0&&max==0){ move('r');
 cout<<"right"<<" "<<posX<<" "<<posY<<endl;
}
   else if(posX-iLastX<0&&max==0){ move('l');
	cout<<"left"<<" "<<posX<<" "<<posY<<endl;
}
  
    
   }

   iLastX = posX;
   iLastY = posY;
  }

  imshow("Thresholded Image", imgThresholded); //show the thresholded image

  imgOriginal = imgOriginal + imgLines;
  imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;
}
void move(char isForward)
{

	double speed=1;
	double speed2=30;
	double distance=2;
	double angular_speed = speed2*2*PI/360;
	double relative_angle = 90*2*PI/360;
	
	//cout<<"f for forward, b for backward , r for right , l for left, e for exit : ";
	//cin>>isForward;
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
