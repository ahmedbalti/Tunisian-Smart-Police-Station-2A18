#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citoyen.h"
#include "recompense.h"
#include "QSqlDatabase"
#include <QMessageBox>
#include<QIntValidator>
#include<QValidator>
#include "QDebug"
#include<QDate>
#include <QComboBox>
#include <QMediaPlayer>
#include <QSound>
#include<QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->tableCitoyen->setModel(tmpcitoyen.afficher());
    ui->tableRecompense->setModel(tmprecompense.afficher());


    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    mMediaPlayer=new QMediaPlayer(this);
    connect(mMediaPlayer,&QMediaPlayer::positionChanged,[&](qint64 pos){ui->progressBar->setValue(pos);});
    connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur){ui->progressBar->setMaximum(dur);});



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();


    QString numCin=ui->numCin ->text();
   ui->numCin->setMaxLength(8);

     QString daten=ui->date->date().toString("yyyy/MM/dd");
   // QString daten=ui->date->text();

    QString nom=ui->nom->text();
     ui->nom->setMaxLength(15);
    QString prenom=ui->prenom->text();
    ui->prenom->setMaxLength(15);
//    ui->comboBox->addItem("Homme");
//     ui->comboBox->addItem("Femme");
    QString sexe=ui->comboBox->currentText();
    // ui->comboBox->setMaxLength(10);

     QString activite=ui->activite->text();
      ui->activite->setMaxLength(15);
      int nbrPts=ui->nbr_pts ->text().toInt();
      int numRec=ui->lineEdit ->text().toInt();



    Citoyen C(numCin,nom,prenom,daten,sexe,activite,nbrPts,numRec);

    if((prenom=="")&&(nom=="")&&(sexe=="")&&(numCin=="")&&(activite=="")&&(daten==""))
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
        }
//       else if(((numCin>=99999999) && (numCin<=9999999)) )
//          {
//              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
//                          QObject::tr("Attention ! Le numéro de Cin doit contenir 8 chiffres"), QMessageBox::Ok);

//          }
    else if(numCin =="")
     {
         QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                     QObject::tr("Veuillez remplir le numéro de CIN"), QMessageBox::Ok);

     }
       else if(prenom =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez remplir le prénom"), QMessageBox::Ok);

          }
       else if(nom =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez remplir le nom"), QMessageBox::Ok);

          }
       else if(sexe =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez choisir le sexe"), QMessageBox::Ok);

          }

       else if(activite =="")
          {
              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                          QObject::tr("Veuillez remplir l'activité"), QMessageBox::Ok);

          }
    else if(daten=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                       QObject::tr("Veuillez remplir la date de naissance"), QMessageBox::Ok);

       }
else {

    if(C.ajouter())
      {
           ui->tableCitoyen->setModel(tmpcitoyen.afficher());
         QMessageBox::information(nullptr, QObject::tr("BIEN"),
                     QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);

                 ui->numCin->setText("");
                 ui->nom->setText("");
                 ui->prenom->setText("");
                 ui->lineEdit_3->setText("");
            //  ui->sexe->setText("");
                 ui->activite->setText("");
                 ui->nbr_pts->setText("");
                 ui->lineEdit->setText("");

    }else{
            QMessageBox::information(nullptr, QObject::tr("ECHEC!!!"),
                        QObject::tr("Citoyen existe déja.\n"), QMessageBox::Cancel);
        }
}
}

void MainWindow::on_supp_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    Citoyen c1;
    // c1.setnumCin(ui->comboBox_2->currentText().toInt());
     c1.setnumCin(ui->lineEdit_3->text());
     if(c1.supprimer(c1.getnumCin()))
     {
          ui->tableCitoyen->setModel(tmpcitoyen.afficher());
         QMessageBox::information(nullptr, QObject::tr("Supprimer un citoyen"),
                     QObject::tr("Suppression avec succés.\n" ), QMessageBox::Cancel);
     }
     else
    {
         QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                             QObject::tr("pas de suppression.\n"
                                         ), QMessageBox::Cancel);

     }
}

void MainWindow::on_modifer_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();


    QString numCin=ui->lineEdit_2->text();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
    QString daten=ui->date_2->date().toString();
    QString sexe=ui->comboBox_2->currentText();
    QString activite=ui->activite_2->text();
    int nbrPts=ui->nbrPts->text().toInt();
   int numRec=ui->comboBox_3->currentText().toInt();

Citoyen C(numCin,nom,prenom,daten,sexe,activite,nbrPts,numRec);

if((prenom=="")&&(nom=="")&&(sexe=="")&&(numCin=="")&&(activite=="")&&(daten==""))
   {
       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                   QObject::tr("Attention!! Les champs sont vides , Veuillez les remplir"), QMessageBox::Ok);
    }
  else if(numCin =="")
   {
       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                   QObject::tr("Veuillez remplir le numéro de CIN"), QMessageBox::Ok);

   }
   else if(prenom =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez remplir le prénom"), QMessageBox::Ok);

      }
   else if(nom =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez remplir le nom"), QMessageBox::Ok);

      }
   else if(sexe =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez choisir le sexe"), QMessageBox::Ok);

      }

   else if(activite =="")
      {
          QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                      QObject::tr("Veuillez remplir l'activité"), QMessageBox::Ok);

      }
else if(daten=="")
   {
       QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                   QObject::tr("Veuillez remplir la date de naissance"), QMessageBox::Ok);

   }
else {

if(C.modifier(numCin))
{
         QMessageBox::information(nullptr, QObject::tr("Modifier un Citoyen"),
                     QObject::tr("citoyen modifié.\n"), QMessageBox::Cancel);

}
else
{
   QMessageBox::critical(nullptr, QObject::tr("Modifier un Citoyen"),

                         QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
}
}
}

void MainWindow::on_pushButton_recherche_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    QString recherche =ui->rechercheBTN->text();
    ui->tableCitoyen->setModel(tmpcitoyen.chercher(recherche));
}

void MainWindow::on_tri_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

     ui->tableCitoyen->setModel(tmpcitoyen.tri());
}


void MainWindow::on_ajouterRecomp_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    int numRec=ui->numRec->text().toInt();
     QString nomRec=ui->nomRec_2->text();
     ui->nomRec_2->setMaxLength(15);
     int nbrEx=ui->nbrEx->text().toInt();
     QString description=ui->lineEdit_5->text();
     ui->lineEdit_5->setMaxLength(50);
     int nbrPts=ui->lineEdit_4->text().toInt();



        recompense r(numRec,nomRec,nbrEx,description,nbrPts);
        if(numRec ==0)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez taper un numéro différent de 0"), QMessageBox::Ok);

              }
        else if(nomRec =="")
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Veuillez remplir le nom de la récompense"), QMessageBox::Ok);

              }
        else if(nbrEx <1 )
           {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                           QObject::tr("Veuillez donnez un nombre d'exemplaires supérieur ou égal à 1"), QMessageBox::Ok);

           }
           else if(nbrPts <50)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Le nombre de points est insuffisant pour avoir une récompense"), QMessageBox::Ok);

              }
        else {

        if(r.ajouter()) {
             ui->tableRecompense->setModel(tmprecompense.afficher());
            QMessageBox::information(nullptr, QObject::tr("BIEN"),
                        QObject::tr("Ajout effectuer avec succés.\n" ), QMessageBox::Cancel);

            ui->numRec->setText("");
            ui->nomRec_2->setText("");
                ui->nbrEx->setText("");
                    ui->lineEdit_5->setText("");
                    ui->lineEdit_4->setText("");


    }else{
            QMessageBox::information(nullptr, QObject::tr("ECHEC!!!"),
                        QObject::tr("recompense existe déja.\n"), QMessageBox::Cancel);
        }
}
}

void MainWindow::on_pushButton_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    recompense r1;
   r1.setnumRec(ui->suppRec->currentText().toInt());
           // r1.setnumRec(ui->supp->text().toInt());
    if(r1.supprimer(r1.getnumRec()))
    {
        ui->tableRecompense->setModel(tmprecompense.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer une récompense"),
                    QObject::tr("Suppression avec succés.\n" ), QMessageBox::Cancel);
    }
    else
   {
        QMessageBox::critical(nullptr, QObject::tr("Erreur!"),
                            QObject::tr("pas de suppression.\n"
                                        ), QMessageBox::Cancel);

    }
}

void MainWindow::on_modifierRecompense_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

    int numRec=ui->numRec_2->currentText().toInt();
    // int numRec=ui->modifierRec->text().toInt();
     QString nomRec=ui->nomRec->text();
     ui->nomRec->setMaxLength(15);
     int nbrEx=ui->nbrEx_2->text().toInt();
     QString description=ui->lineEdit_6->text();
      ui->lineEdit_6->setMaxLength(50);
     int nbrPts=ui->nbrPts_2->text().toInt();

     recompense r(numRec,nomRec,nbrEx,description,nbrPts);

     if(numRec ==0)
           {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                           QObject::tr("Veuillez taper un numéro différent de 0"), QMessageBox::Ok);

           }
     else if(nomRec =="")
           {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                           QObject::tr("Veuillez remplir le nom de la récompense"), QMessageBox::Ok);

           }
     else if(nbrEx <1 )
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                        QObject::tr("Veuillez donnez un nombre d'exemplaires supérieur ou égal à 1"), QMessageBox::Ok);

        }
        else if(nbrPts <50)
           {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                           QObject::tr("Le nombre de points est insuffisant pour avoir une récompense"), QMessageBox::Ok);

           }
     else {


     if(r.modifier(numRec))
     {
         ui->tableRecompense->setModel(tmprecompense.afficher());
               QMessageBox::information(nullptr, QObject::tr("Modifier une Récompense"),
                           QObject::tr("Récompense modifie.\n"), QMessageBox::Cancel);

     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("Modifier une Récompense"),
                           QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
     }
     }
}

void MainWindow::on_rechercheRecompense_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();


    QString recherche =ui->edit_recherche->text();
    ui->tableRecompense->setModel(tmprecompense.chercher(recherche));
 ui->tableRecompense->setModel(tmprecompense.afficher());

}

void MainWindow::on_triRecomp_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
           player->setMedia(QUrl::fromLocalFile("C:/music/bruit-clic.mp3"));
           player->setVolume(3000);
           player->play();

     ui->tableRecompense->setModel(tmprecompense.tri());
}
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QString utilisateur=ui->lineEdit_12->text();
    QString mdp=ui->lineEdit_13->text();
    MainWindow w;
    if ((utilisateur=="ahmed")&&(mdp=="ahmed"))
    {

        //w.show();

    }

    else{ QMessageBox::critical(nullptr, QObject::tr("Problème de connexion"),
                                      QObject::tr("Veuillez revérifier vos informations"), QMessageBox::Cancel);

        hide();
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,"ouvrir");
        if (filename.isEmpty()){return;}
        mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
      on_pushButton_4_clicked();

}

void MainWindow::on_pushButton_4_clicked()
{
    mMediaPlayer->play();

}

void MainWindow::on_pushButton_5_clicked()
{
   mMediaPlayer->pause();
}

void MainWindow::on_pushButton_6_clicked()
{
   mMediaPlayer->stop();
}

void MainWindow::on_pushButton_7_clicked()
{
    if(ui->pushButton_7->text()=="Muet"){
        mMediaPlayer->setMuted(true);
       ui->pushButton_7->setText("Unmuet");}
       else{ mMediaPlayer->setMuted(false);
           ui->pushButton_7->setText("Muet");}
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
      mMediaPlayer->setVolume(value);
}
