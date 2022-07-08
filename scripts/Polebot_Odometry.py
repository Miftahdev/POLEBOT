import rospy # input the rospy module
import math # input the math module for calculate etc.
import time # input the time module
from geometry_msgs.msg import Vector3 # dari library geometry_msgs.msg masukkan vector 3 
from nav_msgs.msg import Odometry # dari library nav_msgs.msg masukkan modul odometry
from std_msgs.msg import Float64,Int64 # dari library std_msgs.msg masukkan modul tipe float 64 dan int 64
global enc1 , enc2, enc3


#deklarasi posisi pada ros serial
s1 = 0.0
s2 = 0.0
s3 = 0.0

x = 0.0
y = 0.0
theta = 0.0
ppcm =  3.5# pulse per cm (hitung dulu cuy)
L = 20 # jarak dari titik pusat ke roda ( coba ukur lagi coy)

Xpos = 0.0
Ypos = 0.0

a = 0
b = 0
c = 0
d = 0
e = 0
vel1 = 0.0
vel2 = 0.0
vel3 = 0.0

#deklarasi posisi saat ini pada topic
Xposnow = 0.0
Yposnow = 0.0
Thetanow = 0.0

def velm1 (vel) :
    global vel1 
    vel1 = vel.data

def velm2 (vel) :
    global vel2 
    vel2 = vel.data

def velm3 (vel) :
    global vel3
    vel3 = vel.data

def callback (enc) :
    global a, b, c, d, e, Xposnow, Yposnow, Thetanow, theta
    enc1 = enc.x
    enc2 = enc.y
    enc3 = enc.z

    s1 = enc1/ppcm
    s2 = enc2/ppcm
    s3 = enc3/ppcm 

    x = 0.666*s3-0.333*s1-0.333*s2 # hasil dari perhitungan kinematika kayak 1/2 *2 dibagi 3
    y = 0.577*s1-0.577*s2 # hasil dari perhitungan kinematika
    theta = e+((1/39)*(s1+s2+s3))# theta = Thetanow + (1/3*L)*(s1+s2+s3)// L = jarak dari titik pusat ke roda . liat robot sendiri berapa jaraknya

    Xpos = math.cos(theta)*x-math.sin(theta)*y
    Ypos = math.sin(theta)*x+math.cos(theta)*y

    b = vel1/(vel2+0.01)
    reset_enc = rospy.Publisher('/reset_enc', Int64, queue_size=10)
    if b < 0 and abs(vel1)>5 and abs (vel2)>5:
        Xposnow = c + Xpos
        Yposnow = d + Ypos
        Thetanow = theta
        a = 1
    
    if a==1 and (b > 0 or abs(vel3)>5):
        c = Xposnow
        d = Yposnow
        e = Thetanow
        reset_enc.publish(1)
        time.sleep(0.5)
        reset_enc.publish(0)
        a = 0
    
    odom_pub = rospy.Publisher('/odometry', Odometry, queue_size=10)
    odom = Odometry()

    odom.pose.pose.position.x = Xposnow
    odom.pose.pose.position.y = Yposnow
    odom.pose.pose.position.z = theta
    odom_pub.publish(odom)
    print("Xnow :", round(Xpos,2),"Ynow:",round(Ypos,2), "Theta", round(theta,2))

def sub():
    rospy.init_node('Algoritma_Odometry', anonymous=False) # penamaan node
    rospy.Subscriber('/vel_m1', Float64, velm1)
    rospy.Subscriber('/vel_m2', Float64, velm2)
    rospy.Subscriber('/vel_m3', Float64, velm3)
    rospy.Subscriber('/encoder', Vector3, callback)
    rospy.spin()

if __name__== '__main__':
    sub()
