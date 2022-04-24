#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QGraphicsView* view, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    v = view;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username=="test" && password == "test")
    {
        QMessageBox::information(this,"Login","Username and password are correct");
        this->hide();
        v->show();
    }
    else
    {
        QMessageBox::warning(this,"Login","Username or password is not correct");

    }
}

