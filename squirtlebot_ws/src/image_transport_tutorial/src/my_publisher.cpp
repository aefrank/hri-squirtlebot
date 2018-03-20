#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


void rot90(cv::Mat &matImage, int rotflag){
      //1=CW, 2=CCW, 3=180
      if (rotflag == 1){
           transpose(matImage, matImage);  
           flip(matImage, matImage,1); //transpose+flip(1)=CW
      } else if (rotflag == 2) {
           transpose(matImage, matImage);  
           flip(matImage, matImage,0); //transpose+flip(0)=CCW     
      } else if (rotflag ==3){
           flip(matImage, matImage,-1);    //flip(-1)=180          
      } else if (rotflag != 0){ //if not 0,1,2,3:
          std::cout  << "Unknown rotation flag(" << rotflag << ")" << std::endl;
      }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("webcam/image", 1);
  
  int webcam_source=-1;
  cv::VideoCapture cap(webcam_source);
  // check if video device can be opened
  if(!cap.isOpened()) return 1;
  
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // Check if frame is full
    if(!frame.empty()) { 
        // rotate counterclockwise for easier line detection
        rot90(frame, 2);
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);
        cv::waitKey(1);
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
}

