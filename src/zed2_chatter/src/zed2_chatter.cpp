#include <ros/ros.h>
#include <iostream>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <stdio.h>
#include <string.h>
#include <std_msgs/String.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    
    ros::init(argc, argv, "zed2_datasets_node");   
    
    ros::NodeHandle n;
    ros::Subscriber msg = n.subscribe("chatter",1000,chatterCallback);

    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh); 
    image_transport::Subscriber imageSub1 = it.subscribe("/zed2/zed_node/left/image_rect_color", 1000, imageCallback1);
    //image_transport::Subscriber imageSub2 = it.subscribe("/zed2/zed_node/right/image_rect_color", 1000, imageCallback2); 
    //image_transport::Subscriber imageSub3 = it.subscribe("/zed2/zed_node/depth/depth_registered", 1000, imageCallback3); 
    ros::spin();
    return 0;
}
