#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>


const QString MainWindow::NO_FILE_WARN = "No such file";
const QString MainWindow::NO_FILE_TITLE = "Cannot open file";
const QString MainWindow::DEFAULT_FILE_NAME = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    filePath(MainWindow::DEFAULT_FILE_NAME)
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
    QFile *filePtr = new QFile(filePath);

    if(!filePtr->open(QFile::WriteOnly | QFile::Text)){
        delete filePtr;
        filePath = QFileDialog::getSaveFileName(this, "Save", QDir::currentPath());
        filePtr = new QFile(filePath);
        filePtr->open(QFile::WriteOnly | QFile::Text);
    }

    QTextStream textSteam(filePtr);
    textSteam << ui->textEdit->toPlainText();
    filePtr->flush();
    filePtr->close();
    delete filePtr;
}

void MainWindow::on_actionSave_As_triggered()
{
    filePath = QFileDialog::getSaveFileName(this, "Save as", QDir::homePath());
    QFile file(filePath);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream textSteam(&file);
    textSteam << ui->textEdit->toPlainText();
    file.flush();
    file.close();
}

void MainWindow::on_actionOpen_triggered()
{
    filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    QFile file(filePath);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        filePath = "file.txt";
        QMessageBox::warning(this, MainWindow::NO_FILE_TITLE, MainWindow::NO_FILE_WARN);
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());
}

void MainWindow::on_actionNew_triggered()
{
    filePath = MainWindow::DEFAULT_FILE_NAME;
    ui->textEdit->setText("");
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}
