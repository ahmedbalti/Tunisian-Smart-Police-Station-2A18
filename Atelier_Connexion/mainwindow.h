#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "citoyen.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

private:
    Ui::MainWindow *ui;
    Citoyen C;
};

#endif // MAINWINDOW_H