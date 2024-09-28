
#ifndef RCLCOMM_H
#define RCLCOMM_H
#include "std_msgs/msg/int32.hpp"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QThread>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
class rclcomm : public QThread {
  Q_OBJECT
public:

  cv::Mat imgRaw;

  rclcomm();
  void publish_topic(int count);
  void recv_callback(const std_msgs::msg::Int32::SharedPtr msg);
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub;

protected:
  void run();

private:
  void callbackImage(const sensor_msgs::msg::Image::ConstSharedPtr msg_img);

  std::shared_ptr<rclcpp::Node> node;

signals:
  void sigRcvImg();

};
#endif // RCLCOMM_H
