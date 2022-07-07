#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Pose2D
from nav_msgs.msg import Odometry
from std_msgs.msg import Float64

Kpx = 3
KpY = 3
Kph = 10

def Kinematik(msg):
    global pv_x ,pv_y, pv_theta

    pv_x = msg.pose.pose.position.x
    pv_y = msg.pose.pose.position.y
    pv_theta= msg.pose.pose.position.z 

def pose_Cb(pose_msg) :

    global x_target, y_target, theta_target 

    x_target = pose_msg.x
    y_target = pose_msg.y
    theta_target = pose_msg.theta

    rospy.loginfo("x: %f", x_target)
    rospy.loginfo("y: %f", y_target)
    rospy.loginfo("theta: %f", theta_target)

    pub = rospy.Publisher("/Polebot/V1_controller/command" , Float64 , queue_size=10)
    pub1 = rospy.Publisher("/Polebot/V2_controller/command" , Float64 , queue_size=10)
    pub2 = rospy.Publisher("/Polebot/V3_controller/command", Float64 , queue_size=10)

    v1 = Float64()
    v2 = Float64()
    v3 = Float64()
        

    r = rospy.Rate(10)

    while not rospy.is_shutdown():
   
        errorX   = x_target - pv_x 
        errorY   = y_target - pv_y
        errorH   = ((theta_target)*-1) - pv_theta 

        MVX = Kpx * errorX 
        MVY = KpY * errorY
        MVH = Kph * errorH

        if MVX >=400 :
            MVX =400
        elif MVX <= -400:
            MVX = -400

        if MVY >= 400 :
            MVY = 400
        elif MVY <= -400:
            MVY = -400      

        v1 = -0.333 * MVX + 0.5774 * MVY + 0.045* MVH
        v2 = -0.333 * MVX + (-0.5774) * MVY + 0.045*MVH
        v3 = 0.667 * MVX + 0.045*MVH

        # v1 = Float64()
        # v2 = Float64()
        # v3 = Float64()

        # pub = rospy.Publisher("/Polebot/V1_controller/command" , Float64 , queue_size=10)
        # pub1 = rospy.Publisher("/Polebot/V2_controller/command" , Float64 , queue_size=10)
        # pub2 = rospy.Publisher("/Polebot/V3_controller/command", Float64 , queue_size=10)

        pub.publish(v1)
        pub1.publish(v2)
        pub2.publish(v3)

def sub():
    rospy.init_node("Kinematik" ,anonymous=False) # penamaan node
    rospy.Subscriber("/pose_Input", Pose2D, pose_Cb )
    rospy.Subscriber("/Odometry", Odometry, Kinematik )
    rospy.spin()
        
if __name__ == '__main__':
    sub()