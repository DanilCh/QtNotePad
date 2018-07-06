#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionUndo_triggered();
    void on_actionCopy_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

private:
    static const QString NO_FILE_WARN;
    static const QString NO_FILE_TITLE;
    static const QString DEFAULT_FILE_NAME;

    Ui::MainWindow *ui;
    QString filePath;
};

#endif // MAINWINDOW_H
