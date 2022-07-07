#!/usr/bin/env python3
import rospy # input the rospy module
from geometry_msgs.msg import Pose2D # dari library geometry_msgs.msg masukkan vector 3 


def Input():
    koordinat = Pose2D
    target = rospy.Publisher("/Target" , Pose2D, queue_size=1)
    rospy.init_node("Input_Koordinat" , anonymous=False)
    rate = rospy.Rate(10)
    pos_x = float(input("x_target = %f", koordinat.x ))
    pos_y = float(input("y_target = %f", koordinat.y ))

    while not rospy.is_shutdown():
        koordinat.x = pos_x
        koordinat.y = pos_y
        target.publish(koordinat)
        rate.sleep()



if __name__ == '__main__':
    try:
        Input()
    except rospy.ROSInterruptException:
        pass