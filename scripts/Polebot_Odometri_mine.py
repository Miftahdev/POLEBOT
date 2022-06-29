import rospy # input the rospy module
from geometry_msgs.msg import Vector3 # dari library geometry_msgs.msg masukkan vector 3 
from nav_msgs.msg import Odometry # dari library nav_msgs.msg masukkan modul odometry
from std_msgs.msg import Float64,Int64 # dari library std_msgs.msg masukkan modul tipe float 64 dan int 64
global encoder1 , encoder2 , encoder3
#Deklarasi variabel perhitungan odometri
h_max = 21810 # heading max pada pulse 2810, 360 derajat
y_max = 375 # set 30 cm sumbu y pada pulse 375
x_max = 345 # set 30 cm sumbu x pada pulse 345

# deklarasi PID posisi dengan proposional


def Odometri (pulse_encoder) :
    
    encoder1 = pulse_encoder.x
    encoder2 = pulse_encoder.y
    encoder3 = pulse_encoder.z

    # perhitungan odometri
    x_pos = -0.5 * pulse_encoder.x - 0.5 *pulse_encoder.y + 1 * pulse_encoder.z
    y_pos = 0.866 * pulse_encoder.x - 0.866 * pulse_encoder.y
    h_pos = pulse_encoder.x + pulse_encoder.y + 1.5* pulse_encoder.z

    #heading
    pv_theta = 360 * (h_pos / h_max)
    if pv_theta >= 360 :
     pv_theta = 0
    elif pv_theta <= -360:
     pv_theta = 0

    # gerak sumbu x
    pv_x = 30*x_pos/x_max
    
    # gerak sumbu Y
    pv_y = 30*y_pos/y_max
    
    odom_pub = rospy.Publisher('/odometry', Odometry, queue_size=10)
    odom = Odometry()

    odom.pose.pose.position.x = x_pos
    odom.pose.pose.position.y = y_pos
    odom.pose.pose.position.z = h_pos
    odom_pub.publish(odom)
    print("X:", round(x_pos,2),"Y:",round(y_pos,2), "Theta", round(h_pos,2))

def sub():
    rospy.init_node('perhitungan_odometri', anonymous=False) # penamaan node
    rospy.Subscriber('/pulse_encoder', Float64, Odometri)
    rospy.spin()

if __name__== '__main__':
    sub()
