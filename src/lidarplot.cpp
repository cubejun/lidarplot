#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "opencv2/opencv.hpp"
#include <math.h>
#define RAD2DEG(x) ((x)*180./M_PI)

static void scanCb(sensor_msgs::msg::LaserScan::SharedPtr scan) {
  int count = scan->scan_time / scan->time_increment;
  int x, y;
  printf("[SLLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
  printf("[SLLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min),
         RAD2DEG(scan->angle_max));
  cv::Mat img(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
  for (int i = 0; i < count; i++) {
    float degree = scan->angle_min + scan->angle_increment * i;
    printf("[SLLIDAR INFO]: angle-distance : [%f, %f]\n", degree, scan->ranges[i]);
    x = 250 - scan->ranges[i]*50 * cos(degree);
    y = 250 + scan->ranges[i]*50 * sin(degree);
    
    
    cv::circle(img, cv::Point(x, y), 1, cv::Scalar(0, 0, 255), 1);
  }
  cv::imshow("img", img);
  cv::waitKey(1);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("sllidar_client");

  auto lidar_info_sub = node->create_subscription<sensor_msgs::msg::LaserScan>("scan", rclcpp::SensorDataQoS(), scanCb);


  
  rclcpp::spin(node);
  rclcpp::shutdown();


  return 0;
}
