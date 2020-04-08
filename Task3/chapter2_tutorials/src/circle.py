#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

def move():
    # Starts a new node
    rospy.init_node('robot_cleaner', anonymous=True)
    velocity_publisher = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    vel_msg = Twist()

    #Receiveing the user's input
    print("Let's make circle by robot enter r for radius and e for exit")
    isRadius= raw_input()
    speed=1	

    #Checking if the movement is forward or backwards
    if(isRadius=="r"):
	print("enter radius for circle")
	radius = input()
        vel_msg.linear.x = abs(speed)
    elif(isRadius=="e"):
        exit()
    #Since we are moving just in x-axis
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = speed/radius

    while not rospy.is_shutdown():

        #Setting the current time for distance calculus
        t0 = rospy.Time.now().to_sec()
        current_distance = 0

        #Loop to move the turtle in an specified distance
        while(current_distance < (2*3.14*radius)):
            #Publish the velocity
            velocity_publisher.publish(vel_msg)
            #Takes actual time to velocity calculus
            t1=rospy.Time.now().to_sec()
            #Calculates distancePoseStamped
            current_distance= speed*(t1-t0)
        #After the loop, stops the robot
        vel_msg.linear.z = 0
	vel_msg.angular.x=0
        #Force the robot to stop
        velocity_publisher.publish(vel_msg)
	return isRadius

if __name__ == '__main__':
    try:
        #Testing our function
	t1="r"	
	while (t1!="e"):        
		t1=move()
    except rospy.ROSInterruptException: pass
