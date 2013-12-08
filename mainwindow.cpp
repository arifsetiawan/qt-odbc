#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");

    ui->lineEditDBName->setText("Chinook");
    ui->lineEditQuery->setText("Select * from Track");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    QString databaseName = ui->lineEditDBName->text();
    addLog("Opening connection " + databaseName);

    db.setDatabaseName(databaseName);
    bool ok = db.open();
    if (ok) {
        addLog("Opening OK");
        QStringList tables = db.tables(QSql::Tables);
        addLog("Tables " + tables.join(","));
    }
    else {
        addLog("Opening Failed " + db.lastError().text());
    }
}

void MainWindow::on_executeButton_clicked()
{
    QString queryStr = ui->lineEditQuery->text();
    addLog("Run query " + queryStr);

    QSqlQuery query(db);
    bool ok = query.exec(queryStr);
    if (ok) {
        addLog("Query OK");

        QSqlRecord rec = query.record();
        int cols = rec.count();
        int count = 0;
        addLog("First 5 records in table");
        while (query.next()) {
            if (count < 5) {
                QString line = "";
                for( int c=0; c<cols; c++ ) {
                    line += query.value(c).toString() + ((c < cols - 1) ? " , " : "");
                }
                addLog(line);
                count ++;
            }
            else
                break;
        }

    }
    else {
        addLog("Query Failed " + query.lastError().text());
    }
}

void MainWindow::addLog(QString log)
{
    ui->listWidget->addItem(log);
}

void MainWindow::on_clearButton_clicked()
{
    ui->listWidget->clear();
}
