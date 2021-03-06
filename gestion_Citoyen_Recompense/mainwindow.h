#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "citoyen.h"
#include "recompense.h"
#include <QDialog>
#include <QApplication>
#include "login.h"
#include "smtp.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QSound>
#include <QNetworkAccessManager>
#include <QUrlQuery>

#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QMouseEvent>
#include <QtWidgets/QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendMail();
    void mailSent(QString);
    void browse();
    void on_ajouter_clicked();

    void on_supp_clicked();

    void on_modifer_clicked();

    void on_pushButton_recherche_clicked();

    void on_tri_clicked();

    void on_pushButton_modifierconges_clicked();

    void on_modifierRecompense_clicked();

    void on_ajouterRecomp_clicked();

    void on_pushButton_clicked();

    void on_rechercheRecompense_clicked();

    void on_triRecomp_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_tableCitoyen_activated(const QModelIndex &index);

    void on_tableRecompense_activated(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void replyFinished(QNetworkReply* reply);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::MainWindow *ui;
    Citoyen tmpcitoyen;
    recompense tmprecompense;
    QStringList files;
    QSound *son;
    QMediaPlayer *mMediaPlayer;
    QMediaPlayer musicAdd;


};
#endif // MAINWINDOW_H
