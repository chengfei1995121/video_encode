#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "color_space.h"
#include "image_generate.h"
#include <stdio.h>
#include <stdlib.h>
#include "work_flow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onTimer();
private:
    void create_new_image();

private:
    Ui::MainWindow* ui;
    uint8_t*        funny_image_data_       = nullptr;
    QImage*         funny_image_            = nullptr;
    QTimer*         timer_                  = nullptr;
    uint8_t*        bg_image_data_          = nullptr;
    uint8_t*        compose_image_data_     = nullptr;
    uint8_t*        bg_image_               = nullptr;
    uint8_t*        compose_image_          = nullptr;
    uint8_t*        dst_image_              = nullptr;
    uint8_t*        i_420_                  = nullptr;
    Workflow        wk;

    Image           *image_                 = nullptr;
    ColorSpace      cp_image_;
    FactoryRgba     fr;

    int             channels                = 0;
    int             sub_image_width_        = 0;
    int             sub_image_height_       = 0;
    int             bg_image_width_         = 0;
    int             bg_image_height_        = 0;
    FILE*           f_dst_                  = nullptr;

    bool            mouse_pressed_          = false;
    QPoint          mouse_position_;

    QTime           start_record_systime_;
    char*           filename                ="/home/chengfei/product.mp4";
    // QWidget interface

};

#endif // MAINWINDOW_H
