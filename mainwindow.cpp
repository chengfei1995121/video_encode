#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stb_import.h"
#include <QtWidgets>
#include <QDebug>
#include <thread>
#include <chrono>

#include "easing.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1280,720);

    timer_ = new QTimer(this);
    timer_->setInterval(30);
    timer_->setSingleShot(false);

    bg_image_width_ = 1280;
    bg_image_height_ = 720;

    connect(timer_,SIGNAL(timeout()),this,SLOT(onTimer()));

    image_ = fr.create_image(bg_image_width_,bg_image_height_);
    image_->create();
    bg_image_data_ = image_->get_data();


    f_dst_                  = fopen("/home/chengfei/yuv_viedo_512_512.yuv","wb");
    compose_image_data_     = new uint8_t[bg_image_width_ * bg_image_height_ * 3];
    i_420_                  = new uint8_t[(bg_image_width_ * bg_image_height_ * 3) / 2];

    funny_image_data_       = stbi_load("/home/chengfei/lianxi/rsources/funny.png",&sub_image_width_,&sub_image_height_,&channels,4);

    cp_image_.rgba_compose(bg_image_width_,bg_image_height_,sub_image_width_,sub_image_height_,0,0,compose_image_data_,bg_image_data_,funny_image_data_);

    wk.create_viedo(filename,bg_image_width_,bg_image_height_);

    funny_image_ = new QImage(funny_image_data_,sub_image_width_,sub_image_height_,QImage::Format_RGBA8888);
    timer_->start();
}

MainWindow::~MainWindow()
{
    wk.close();
    delete image_;
    delete ui;
    delete []compose_image_data_;
    delete []i_420_;
    fclose(f_dst_);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect(0,0,this->width(),this->height());
    painter.drawImage(rect,*funny_image_);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mouse_pressed_ = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_pressed_ = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_pressed_)
        mouse_position_ = event->pos();
}

void MainWindow::onTimer()
{
    if(funny_image_ != nullptr)
        delete funny_image_;
    create_new_image();
    update();
}


void MainWindow::create_new_image()
{    
    {
        const  float step = 0.01;
        static float x = 0;
        static float y = 0;

        float x_easing = easingFunctions[kOutCubic].function(y,0,0.8,0.8);
        float y_easing = easingFunctions[kOutBounce].function(y,0,0.5,0.8);

        mouse_position_.setX(x_easing * this->width());
        mouse_position_.setY(y_easing * this->height());

        x += step;
        y += step;
        if(x > 1.0)
            x = 0;
        if(y > 1.0)
            y = 0;
    }
    //qWarning("Mouse position: %d#%d",mouse_position_.x(),mouse_position_.y());
    cp_image_.rgba_compose(bg_image_width_,bg_image_height_,sub_image_width_,sub_image_height_,mouse_position_.x(),mouse_position_.y(),compose_image_data_,bg_image_data_,funny_image_data_);

    cp_image_.rgb24_to_i420(compose_image_data_,i_420_,bg_image_width_,bg_image_height_);
    fwrite(i_420_,(bg_image_width_ * bg_image_height_ *3)/2,1,f_dst_);

    funny_image_ = new QImage(compose_image_data_,bg_image_width_,bg_image_height_,QImage::Format_RGB888);

    if(start_record_systime_.isValid() == false){
        start_record_systime_ = QTime::currentTime();
    }
    int32_t diff_ms = start_record_systime_.msecsTo(QTime::currentTime());

    wk.encode_frame(i_420_,diff_ms);
}
