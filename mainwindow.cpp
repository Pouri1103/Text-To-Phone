#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
////////////////////////////////////////////////////////

void MainWindow::on_pb_Set_clicked()
{
    QString page = windowTitle().remove("Text to Phone ");

    QFile f;
    if (page == "Text to Phone")
        f.setFileName("D:/ZxZxZ/ToPhone/ToPhone.txt");
    else
        f.setFileName("D:/ZxZxZ/ToPhone/ToPhone_" +page+ ".txt");


    if (!f.open(QIODevice::WriteOnly))
        QMessageBox::critical(this,"Not exist address"," Please create this path ! \n <D:/ZxZxZ/ToPhone>");
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream set(&f);
    QString text = ui->textEdit->toPlainText();
    set<< text;

    f.close();
}

void MainWindow::on_actionOpen_triggered()
{
    QString address = QFileDialog::getOpenFileName(this, "Open a file");
    setWindowTitle(address);
    QFile f(address);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream import(&f);
    ui->textEdit->setText(import.readAll());

    f.close();
}

int i = 2;
void MainWindow::on_actionNew_Window_triggered()
{
    MainWindow *newWindow = new MainWindow();
    newWindow->show();
    newWindow->setWindowTitle("Text to Phone " + QString::number(i));
    i++;
}

void MainWindow::on_actionSave_as_triggered()
{
    QString address = QFileDialog::getSaveFileName(this, "Save the file", "", "text(*.txt)");
    QFile f(address);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&f);
    QString text = ui->textEdit->toPlainText();
    out<< text;

    f.close();
}


