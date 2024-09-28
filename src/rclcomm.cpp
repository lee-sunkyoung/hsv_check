
#include "rclcomm.h"
rclcomm::rclcomm()  {
  int argc=0;
  char **argv=NULL;
  rclcpp::init(argc,argv);
  node=rclcpp::Node::make_shared("hsv_check");
   image_sub = node->create_subscription<sensor_msgs::msg::Image>(
      "camera/image_raw", 10,
      std::bind(&rclcomm::callbackImage, this, std::placeholders::_1));

 this->start();
}
void rclcomm::run(){
    //20HZ
    rclcpp::WallRate loop_rate(100);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    rclcpp::shutdown();
}

void rclcomm::callbackImage(
    const sensor_msgs::msg::Image::ConstSharedPtr msg_img) {

  try {
    cv::Mat image = cv_bridge::toCvCopy(msg_img, "bgr8")->image;
    imgRaw = image;
    emit sigRcvImg();
  } catch (cv_bridge::Exception &e) {
    // RCLCPP_INFO(node->get_logger(), "cv_bridge: %s", e.what());
  }
}