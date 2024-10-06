#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  h = 0.1;
  xBegin = -100 / 0.1;
  xEnd = 100 / 0.1;
  for_first_graph();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Button_dot_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '.');
}

void MainWindow::on_Button_0_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '0');
}

void MainWindow::on_Button_1_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '1');
}

void MainWindow::on_Button_2_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '2');
}

void MainWindow::on_Button_3_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '3');
}

void MainWindow::on_Button_plus_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '+');
}

void MainWindow::on_Button_4_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '4');
}

void MainWindow::on_Button_5_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '5');
}

void MainWindow::on_Button_6_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '6');
}

void MainWindow::on_Button_minus_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '-');
}

void MainWindow::on_Button_7_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '7');
}

void MainWindow::on_Button_8_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '8');
}

void MainWindow::on_Button_9_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '9');
}

void MainWindow::on_Button_mod_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "mod");
}

void MainWindow::on_Button_pow_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '^');
}

void MainWindow::on_Button_div_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '/');
}

void MainWindow::on_Button_mul_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '*');
}

void MainWindow::on_Button_log_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "log");
}

void MainWindow::on_Button_ln_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "ln");
}

void MainWindow::on_Button_sqrt_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "sqrt");
}

void MainWindow::on_Button_atan_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "atan");
}

void MainWindow::on_Button_acos_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "acos");
}

void MainWindow::on_Button_asin_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "asin");
}

void MainWindow::on_Button_r_br_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '(');
}

void MainWindow::on_Button_l_br_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + ')');
}

void MainWindow::on_Button_sin_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "sin");
}

void MainWindow::on_Button_cos_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "cos");
}

void MainWindow::on_Button_tan_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "tan");
}

void MainWindow::on_Button_ac_clicked() { ui->OutPut->setText("\n"); }

void MainWindow::for_first_graph() {
  customPlot = new QCustomPlot();  // Инициализируем графическое полотно
  ui->gridLayout->addWidget(customPlot, 0, 0, 1,
                            1);  // Устанавливаем customPlot в окно про
  customPlot->xAxis->setRange(-10, 10);
  customPlot->yAxis->setRange(-10, 20);

  customPlot->setInteraction(
      QCP::iRangeZoom, true);  // Включаем взаимодействие удаления/приближения
  customPlot->setInteraction(
      QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
  customPlot->axisRect()->setRangeZoom(
      Qt::Horizontal);  // Включаем удаление/приближение только по
                        // горизонтальной оси

  customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
  customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);

  customPlot->addGraph();  // Устанавливаем график на полотно
  customPlot->graph(0)->setPen(
      QPen(QColor(Qt::red)));  // Устанавливаем цвет графика
  QString str1 = " x=";
  QString str2 = " -x=";
  graph(str1);
  graph(str2);
}
void MainWindow::x_with_number(QString str, char *str_num) {
  QString num = QString(str_num);
  QByteArray input = str.toUtf8();
  QByteArray num2 = num.toUtf8();
  input.replace(QByteArray("x"), num2);
  QString str2 = (QString)input;
  char *str3 = str2.toLatin1().data();
  char *str4;
  str4 = &str3[1];
  double result = 0;
  int res = main_f(str4, &result);
  if (res != OK) {
    ui->OutPut->setText("\n");
    ui->OutPut->setText(ui->OutPut->toPlainText() + "Error");
  } else {
    ui->OutPut->setText("\n");
    QString str3 = QString::number(result, 'f', 7);
    ui->OutPut->setText(ui->OutPut->toPlainText() + str3);
  }
  ui->x_number->setText("");
}

void MainWindow::graph(QString str) {
  if (!ui->x_number->document()->isEmpty()) {
    char *str_num = ui->x_number->toPlainText().toLatin1().data();
    printf("%s\n", str_num);
    x_with_number(str, str_num);
  } else {
    for (int i = xBegin; i <= xEnd; i++) {
      double n = i * h;
      QString num = QString::number(n, 'f', 1);
      num = '(' + num + ')';
      QByteArray input = str.toUtf8();
      QByteArray num2 = num.toUtf8();
      input.replace(QByteArray("x"), num2);
      QString str2 = (QString)input;
      char *str3 = str2.toLatin1().data();
      char *str4;
      str4 = &str3[1];
      double result = 0;
      int res = main_f(str4, &result);
      if (res == OK) {
        x.push_back(n);
        y.push_back(result);
      }
    }
    if (x.count() != 0) {
      customPlot->graph(0)->setData(x, y);
      customPlot->replot();
    } else {
      ui->OutPut->setText("\n");
      ui->OutPut->setText(ui->OutPut->toPlainText() + "Error");
    }
    x.clear();
    y.clear();
  }
}
void MainWindow::expression(char *str) {
  double result = 0;
  int res = main_f(str, &result);
  ui->OutPut->setText("\n");
  if (res != OK)
    ui->OutPut->setText(ui->OutPut->toPlainText() + "Error");
  else {
    QString str3 = QString::number(result, 'f', 7);
    ui->OutPut->setText(ui->OutPut->toPlainText() + str3);
  }
}
void MainWindow::on_Button_eq_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + '=');
  QString inputS = ui->OutPut->toPlainText();
  char *str;
  char *str2 = inputS.toLatin1().data();
  str = &str2[1];
  if (ui->OutPut->toPlainText().contains('x')) {
    x.clear();
    y.clear();
    graph(inputS);
  } else
    expression(str);
}

void MainWindow::on_Button_X_clicked() {
  ui->OutPut->setText(ui->OutPut->toPlainText() + "x");
}
