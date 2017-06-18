#include "mainwindow.h"
#include "ui_mainwindow.h"
#define N 20
#define x1Fix 0.20
#define x2Fix 0.25
#define w0Fix 0.40
#define w1Fix 0.50
#define w2Fix 0.70
#define a 3
#define t 0.60
#define h1 0.05
#define h2 0.05
#define h3 0.10
#define h4 0.10
#define h5 0.10
#define h6 0.20
#define h7 0.50

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i=0; i<7; ++i)
    {
        x.push_back(QVector<double> ());
        double y = 0;
        if(i == 0){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h1;
            }
        }
        if(i == 1){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h2;
            }
        }
        y=-1;
        if(i == 2){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h3;
            }
        }
        y=-1;
        if(i == 3){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h4;
            }
        }
        y=-1;
        if(i == 4){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h5;
            }
        }
        y = -2;
        if(i == 5){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h6;
            }
        }
        y = -5;
        if(i == 6){
            for(int j=0; j<N; ++j){
                x[i].push_back(y);
                y += h7;
            }
        }
    }
    for(int i = 0; i < 5; i++){
        S.push_back(QVector<double> ());
        if(i == 0){
            for(int j=0; j<N; ++j){
                S[i].push_back(x[i][j] * w1Fix + x2Fix * w2Fix + w0Fix);
            }
        }
        if(i == 1){
            for(int j=0; j<N ; ++j){
               S[i].push_back(x1Fix * w1Fix + x[i][j] * w2Fix + w0Fix);
            }
        }
        if(i == 2){
            for(int j=0; j<N ; ++j){
                S[i].push_back(x1Fix * w1Fix + x2Fix * w2Fix + x[i][j]);
            }
        }
        if(i == 3){
            for(int j=0; j<N ; ++j){
                 S[i].push_back(x1Fix * x[i][j] + x2Fix * w2Fix + w0Fix);
            }
        }
        if(i == 4){
            for(int j=0; j<N; ++j){
                S[i].push_back(x1Fix * w1Fix + x2Fix * x[i][j] + w0Fix);
            }
        }
    }
    //1/exp(-a(s-t)+1)
    for(int i = 0; i < 5; i++){
        Y.push_back(QVector<double> ());
        for(int j=0; j<N; ++j){
            Y[i].push_back(1/(exp(-a*(S[i][j] - t))+1));
        }
    }
    for(int i = 5; i < 7; i++){
        Y.push_back(QVector<double> ());
        if(i == 5){
            for(int j=0; j<N; ++j){
                Y[i].push_back(1/(exp(-x[i][j]*(S[4][j] - t))+1));
            }
        }
        if(i == 6){
            for(int j=0; j<N; ++j){
                Y[i].push_back(1/(exp(-a*(S[4][j] - x[i][j]))+1));
            }
        }
    }
    ui->widget->legend->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x[0], Y[0]);
    ui->widget->graph(0)->setName("Y(X1)");
    ui->widget->graph(0)->setPen(QColor(50,50,50,255));
    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x[1], Y[1]);
    ui->widget->graph(1)->setName("Y(X2)");
    // задаем имена осей координат
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // задаем размеры осей
    ui->widget->xAxis->setRange(0, 1.2);
    ui->widget->yAxis->setRange(0, 1.2);
    ui->widget->replot();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x[2], Y[2]);
    ui->widget->graph(0)->setName("Y(W0)");
    ui->widget->graph(0)->setPen(QColor(0,0,0,255));
    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x[3], Y[3]);
    ui->widget->graph(1)->setName("Y(W1)");
    ui->widget->graph(1)->setPen(QColor("red"));
    ui->widget->addGraph();
    ui->widget->graph(2)->setData(x[4], Y[4]);
    ui->widget->graph(2)->setName("Y(W2)");
    // задаем имена осей координат
    ui->widget->xAxis->setLabel("w");
    ui->widget->yAxis->setLabel("y");
    // задаем размеры осей
    ui->widget->xAxis->setRange(-1, 1.5);
    ui->widget->yAxis->setRange(0, 1.5);
    ui->widget->replot();
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x[5], Y[5]);
    ui->widget->graph(0)->setName("Y(A)");
    // задаем имена осей координат
    ui->widget->xAxis->setLabel("a");
    ui->widget->yAxis->setLabel("y");
    // задаем размеры осей
    ui->widget->xAxis->setRange(-2, 2);
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->replot();
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x[6], Y[6]);
    ui->widget->graph(0)->setName("Y(T)");
    // задаем имена осей координат
    ui->widget->xAxis->setLabel("t");
    ui->widget->yAxis->setLabel("y");
    // задаем размеры осей
    ui->widget->xAxis->setRange(-5, 5);
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->replot();
}
