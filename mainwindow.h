#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>

#include <QMainWindow>
#include <QVector>
#include <iostream>
#ifdef __cplusplus

extern "C" {
#endif
#include "s21_smart_calc.h"

#ifdef __cplusplus
}
#endif

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

 private slots:
  void on_Button_dot_clicked();

  void on_Button_0_clicked();

  void on_Button_1_clicked();

  void on_Button_2_clicked();

  void on_Button_3_clicked();

  void on_Button_plus_clicked();

  void on_Button_4_clicked();

  void on_Button_5_clicked();

  void on_Button_6_clicked();

  void on_Button_minus_clicked();

  void on_Button_7_clicked();

  void on_Button_8_clicked();

  void on_Button_9_clicked();

  void on_Button_mod_clicked();

  void on_Button_pow_clicked();

  void on_Button_div_clicked();

  void on_Button_mul_clicked();

  void on_Button_log_clicked();

  void on_Button_ln_clicked();

  void on_Button_sqrt_clicked();

  void on_Button_atan_clicked();

  void on_Button_acos_clicked();

  void on_Button_asin_clicked();

  void on_Button_r_br_clicked();

  void on_Button_l_br_clicked();

  void on_Button_sin_clicked();

  void on_Button_cos_clicked();

  void on_Button_tan_clicked();

  void on_Button_ac_clicked();

  void on_Button_eq_clicked();

  void for_first_graph();

  void graph(QString str);

  void expression(char *str);

  void on_Button_X_clicked();

  void x_with_number(QString str, char *str_num);

 private:
  Ui::MainWindow *ui;
  QCustomPlot *customPlot;  // Объявляем графическое полотно
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
