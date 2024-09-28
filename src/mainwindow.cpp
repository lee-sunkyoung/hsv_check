#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  commNode = new rclcomm();
  connect(commNode, SIGNAL(sigRcvImg()), this, SLOT(slotUpdateImg()));
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::slotUpdateImg() {

  cv::imshow("Received Image", commNode->imgRaw);
  raw_img = commNode->imgRaw;
  QImage qImage = matToQImage(raw_img);

  ui->label->setPixmap(QPixmap::fromImage(qImage).scaled(
      ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

  int value[6] = {hl, hh, sl, sh, vl, vh};
  std::cout << hl << " " << hh << " " << sl << " " << sh << " " << vl << " "
            << vh << std::endl;
  Change_to_Binary(raw_img, bin_img, value);

  QImage qImage2 = matToQImage(bin_img);

  ui->label_2->setPixmap(QPixmap::fromImage(qImage2).scaled(
      ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QImage MainWindow::matToQImage(const cv::Mat &mat) {
  // 8-bit, 4 channel 이미지 (BGRA)
  if (mat.type() == CV_8UC4) {
    return QImage(mat.data, mat.cols, mat.rows, mat.step,
                  QImage::Format_ARGB32);
  }
  // 8-bit, 3 channel 이미지 (BGR)
  else if (mat.type() == CV_8UC3) {
    return QImage(mat.data, mat.cols, mat.rows, mat.step,
                  QImage::Format_BGR888);
  }
  // 8-bit, 1 channel 이미지 (Grayscale)
  else if (mat.type() == CV_8UC1) {
    static QVector<QRgb> sColorTable;
    // 컬러 테이블이 없으면 생성
    if (sColorTable.isEmpty()) {
      for (int i = 0; i < 256; ++i)
        sColorTable.push_back(qRgb(i, i, i));
    }
    QImage image(mat.data, mat.cols, mat.rows, mat.step,
                 QImage::Format_Indexed8);
    image.setColorTable(sColorTable);
    return image;
  } else {
    // 지원하지 않는 포맷
    std::cout << "Unsupported cv::Mat format!" << std::endl;
    return QImage();
  }
}
void MainWindow::Change_to_Binary(cv::Mat &input_img, cv::Mat &output_img,
                                  int value[6]) {
  output_img = input_img.clone();
      cv::imshow("output_img1", output_img);

  cv::cvtColor(output_img, output_img, cv::COLOR_RGB2HSV); // 색공간 변경
      std::cout << "cvtcolor!" << std::endl;
    cv::imshow("output_img2", output_img);

  cv::GaussianBlur(output_img, output_img, cv::Size(5, 5), 0);

  // 범위안에  255(흰색)로 만들어주고 나머지는 0(검은색)으로 만들어
  // 흑백 이미지들어가게되면를 만든다.
  
  std::cout << value[0] << " " << value[1] << " " << value[2] << " " << value[3] << " " << value[4] << " "
            << value[5] << std::endl;

  cv::inRange(output_img, cv::Scalar(value[0], value[2], value[4]),
              cv::Scalar(value[1], value[3], value[5]), output_img);
                  cv::imshow("output_img3", output_img);

}
void MainWindow::on_horizontalSlider_actionTriggered(int action) {

  hl = ui->horizontalSlider->value(); // low h
}

void MainWindow::on_horizontalSlider_2_actionTriggered(int action) {
  hh = ui->horizontalSlider_2->value(); // high h
}

void MainWindow::on_horizontalSlider_3_actionTriggered(int action) {
  sl = ui->horizontalSlider_3->value(); // low s
}

void MainWindow::on_horizontalSlider_4_actionTriggered(int action) {
  sh = ui->horizontalSlider_4->value(); // high s
}

void MainWindow::on_horizontalSlider_5_actionTriggered(int action) {
  vl = ui->horizontalSlider_5->value(); // low v
}

void MainWindow::on_horizontalSlider_6_actionTriggered(int action) {
  vh = ui->horizontalSlider_6->value(); // high v
}
