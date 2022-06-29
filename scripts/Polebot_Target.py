

import rospy
import time
import socket
import struct
from nav_msgs.msg import Odometry
from tf.transformations import euler_from_quaternion
from geometry_msgs.msg import Point, Twist
from std_msgs.msg import Float64, Int64
from math import atan, atan2, dist, sqrt, pow 
x = 0.0
y = 0.0
theta = 0.0
a=0

def newOdom(msg):
     global x
     global y
     global theta

     x = msg.pose.pose.position.x
     y = msg.pose.pose.position.y
     theta = msg.pose.pose.position.z

     x=round(x,2)
     y=round(y,2)
     theta=round(theta,2)

rospy.init_node("speed_controller")
subodom = rospy.Subscriber("/odometry", Odometry, newOdom)

pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)
pub = rospy.Publisher('/polebot/right_joint_velocity/command', Float64, queue_size=1)
pub1 = rospy.Publisher('/polebot/left_joint_velocity/command', Float64, queue_size=1)
pub2 = rospy.Publisher('/polebot/back_joint_velocity/command', Float64, queue_size=1)
reset_enc = rospy.Publisher('/reset_enc', Int64, queue_size=10)

vel = Float64()
vel1 = Float64()
vel2 = Float64()

r = rospy.Rate(10)
goal=Point()
goal.x=float(input("X Position : "))
goal.y=float(input("Y Position : "))
while not rospy.is_shutdown():
     inc_x = goal.x-x
     inc_y = goal.y-y
     print("X Position",goal.x, "Y Position :", goal.y)
     angle_to_goal = (atan2(inc_y, inc_x))-1.57
     angle_to_goal = round(angle_to_goal,2)
     distance = sqrt(pow(inc_x,2)+pow(inc_y,2))
     if abs(angle_to_goal - theta ) > 0.1 and a==0 and distance > 6:
         print(a,distance,angle_to_goal,theta)
         vel.data = 20 if (angle_to_goal - theta) > 0 else -20
         vel1.data = 20 if (angle_to_goal - theta) > 0 else -20
         vel2.data = 20 if (angle_to_goal - theta) > 0 else -20
         pub.publish(vel)
         pub1.publish(vel1)
         pub2.publish(vel2)
     elif abs(angle_to_goal - theta) <=0.01 and a==0 :
         print(a, distance, angle_to_goal,theta)
         vel.data = 0
         vel1.data = 0
         vel2.data = 0
         pub.publish(vel)
         pub1.publish(vel1)
         pub2.publish(vel2)
         a=1
     elif distance > 10 and a==1:
         print(a, distance, angle_to_goal, theta)
         time.sleep(1)
         vel.data = 50
         vel1.data = -50
         vel2.data = 0
         pub.publish(vel)
         pub1.publish(vel1)
         pub2.publish(vel2)
     elif distance <=10 and a ==1:
         print(a, distance, angle_to_goal, theta)
         a=2
     if a == 2:
         print(a, distance, angle_to_goal, theta)
         
         vel.data = 0
         vel1.data = 0
         vel2.data = 0
         pub.publish(vel)
         pub.publish(vel1)
         pub.publish(vel2)

         a=3
         print("DONE")
         print("Enter New Coordinates : ")
         goal.x = float(input("X Position : "))
         goal.y = float(input("Y Position : "))
         a=0
         
     pub.publish(vel)
     pub1.publish(vel1)
     pub2.publish(vel2)
     r.sleep()
