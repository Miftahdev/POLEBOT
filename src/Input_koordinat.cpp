#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"

class Polebot{
    private:
        ros::Publisher pose_pub;

    public:
        Polebot(ros::NodeHandle *nh){
            pose_pub = nh->advertise<geometry_msgs::Pose2D>("/pose_test", 100);
            input();
        }
    
    void input(){
        geometry_msgs::Pose2D pose;

        std::cout << "input x: ";
        std::cin >> pose.x;
        std::cout << "input y: ";
        std::cin >> pose.y;
        std::cout << "input theta: ";
        std::cin >> pose.theta;
        
        pose_pub.publish(pose);
    }


};

int main(int argc, char** argv){
    ros::init(argc, argv, "Koordinat");
    ros::NodeHandle nh;
    Polebot semiauto = Polebot(&nh);
    ros::spin(); 
    return 0;
}
