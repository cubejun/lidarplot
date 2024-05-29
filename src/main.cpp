#include "lidarplot/lidarplot.hpp"
int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<LIDARPLOT>();
  rclcpp::spin(node);
  rclcpp::shutdown();


  return 0;
}
