#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>


const QString MainWindow::NO_FILE_WARN = "No such file";
const QString MainWindow::NO_FILE_TITLE = "Cannot open file";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    filePath("")
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_As_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    QFile file(filePath);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        filePath = "";
        QMessageBox::warning(this, MainWindow::NO_FILE_TITLE, MainWindow::NO_FILE_WARN);
        return;
    }

    QTextStream in(&file);
    this->setWindowTitle(file.fileName());
    ui->textEdit->setPlainText(in.readAll());
}

void MainWindow::on_actionNew_triggered()
{
    filePath = "";
    ui->textEdit->setText("");
}
