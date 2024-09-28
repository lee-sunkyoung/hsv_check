
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rclcomm.h"
#include <QMainWindow>
#include <iostream>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QImage matToQImage(const cv::Mat &mat);
  void Change_to_Binary(cv::Mat &input_img, cv::Mat &output_img, int value[6]);
  int hl=0, hh=0, sl=0, sh=0, vl=0, vh=0;
private:
  Ui::MainWindow *ui;
  rclcomm *commNode;
  cv::Mat raw_img;
  cv::Mat bin_img;

public slots:
  void slotUpdateImg();
private slots:
  void on_horizontalSlider_actionTriggered(int action);
  void on_horizontalSlider_2_actionTriggered(int action);
  void on_horizontalSlider_3_actionTriggered(int action);
  void on_horizontalSlider_4_actionTriggered(int action);
  void on_horizontalSlider_5_actionTriggered(int action);
  void on_horizontalSlider_6_actionTriggered(int action);
};
#endif // MAINWINDOW_H
