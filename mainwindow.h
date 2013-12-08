#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqldatabase>

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
    void on_connectButton_clicked();
    void on_executeButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    void addLog(QString log);
};

#endif // MAINWINDOW_H
