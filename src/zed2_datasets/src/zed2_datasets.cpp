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

bool isrecord1 = false;

void imageCallback1(const sensor_msgs::ImageConstPtr& msg)
{
    std::string prefix="frame";
    std::string suffix=".jpg";
    std::string path1="/home/leo/Datasets/zed2/left/";
    char file1[5];
    char cc1[100];
    static int cnt1=0;
    //cv_bridge::CvImagePtr image_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC4);
    //cv::Mat matTemp = image_ptr->image;
    //cv::Mat result;
    //matTemp.copyTo(result);
    cv::imshow("image",cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC4)->image);
    cv::waitKey(1);
    if(isrecord1)
    {
        try 
        {
            sprintf(file1,"%04d",cnt1);
            std::string name = path1 + prefix + file1 + suffix;
            strcpy(cc1, name.c_str());
            cv::imwrite(name, cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_8UC4)->image);
            cnt1++;
            ROS_INFO("Successfully save image to '%s' ", cc1); 
            isrecord1 = false;
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert for '%s' to 'bgr8'.", msg->encoding.c_str());
        }
    }
    isrecord1 = false;
}
/*
void imageCallback2(const sensor_msgs::ImageConstPtr& msg)
{
    std::string prefix="frame";
    std::string suffix=".jpg";
    std::string path2="/home/leo/Datasets/zed2/right/";
    char file2[5];
    char cc2[100];
    static int cnt2=0;
    if(isrecord)
    {
        try 
        {
            sprintf(file2,"%04d",cnt2);
            std::string name = path2 + prefix + file2 + suffix;
            strcpy(cc2, name.c_str());
            cv::imwrite(name, cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_8UC4)->image);
            cnt2++;
            ROS_INFO("Successfully save image to '%s' ", cc2); 
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert for '%s' to 'bgr8'.", msg->encoding.c_str());
        }
    }
}
*/
/*
void imageCallback3(const sensor_msgs::ImageConstPtr& msg)
{
    
    std::string prefix="frame";
    std::string suffix=".jpg";
    std::string path3="/home/leo/Datasets/zed2/depth/";
    char file3[5];
    char cc3[100];
    static int cnt3=0;
    
    cv_bridge::CvImagePtr depth_ptr;
    //cv::Mat matTemp = cv::Mat::zeros(1080,1920,CV_32FC1);
    if(isrecord)
    {
        try  
        {	
            sprintf(file3,"%04d",cnt3);
            std::string name = path3 + prefix + file3 + suffix;
            strcpy(cc3, name.c_str());
            //depth_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_32FC1);
            //cv::Mat matTemp = depth_ptr->image;
            //cv::imwrite(name, matTemp);
            cv::imwrite(name, cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_32FC1)->image);
            cnt3++;
            ROS_INFO("Successfully save image to '%s' ", cc3);    
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("Could not convert for '%s' to '32fc1'.", msg->encoding.c_str());
        }
    }
    
}
*/

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    String text = msg->data;
    if(text == "shoot")
    {
        isrecord1 = true;
    }
    //ROS_INFO("I heard: [%s]", msg->data.c_str());
}

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
