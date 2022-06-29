import rospy # input the rospy module
import math # input the math module for calculate etc.
import time # input the time module
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Vector3 # dari library geometry_msgs.msg masukkan vector 3 
from nav_msgs.msg import Odometry # dari library nav_msgs.msg masukkan modul odometry
from std_msgs.msg import Float64,Int64 


Kpx = 3
KpY = 3
Kph = 10

x = 0.0
y = 0.0 
xtarget=0.0
ytarget=0.0
theta = 0.0

def Kinematik( msg ) :
   global x
   global y
   global theta

   x = msg.pose.pose.position.x
   y = msg.pose.pose.position.y
   theta= msg.pose.pose.position.z

   x=round(x,2)
   y=round(y,2)
   theta=round(theta,2)

rospy.init_node("Kontrol_kecepatan")
subOdom = rospy.Subscriber("/odometry", Odometry )
pub = rospy.Publisher("/Polebot/V1_controller/command" , Float64 , queue_size=1)
pub1 = rospy.Publisher("/Polebot/V2_controller/command" , Float64 , queue_size=1)
pub2 = rospy.Publisher("/Polebot/V3_controller/command", Float64 , queue_size=1)

v1 = Float64()
v2 = Float64()
v3 = Float64()
pv_theta = Float64()
pv_y = Float64()
pv_x = Float64()

r = rospy.Rate(10)

while not rospy.is_shutdown():
  
  heading = input("Heading_target = ")
  pos_x = input ("x_target = ")
  pos_y = input ("y_target")
  print("X TARGET:",xtarget, "Y TARGET:",ytarget)
  
  errorH   = heading - pv_theta # perhitungan PID sampe MV
  MVH = Kph * errorH

  errorX   = pos_x - pv_x # perhitungan PID sampe MV
  MVX = Kpx * errorX 
  if MVX >=400 :
    MVX =400
  elif MVX <= -400:
    MVX = -400
  
  errorY   = pos_y - pv_y # perhitungan PID sampe MV
  MVY = KpY * errorY
  if MVY >= 400 :
    MVY = 400
  elif MVY <= -400:
    MVY = -400

  v1 = -0.333 * MVX + 0.5774 * MVY + 0.045* MVH
  v2 = -0.333 * MVX + (-0.5774) * MVY + 0.045*MVH
  v3 = 0.667 * MVX + 0.045*MVH
