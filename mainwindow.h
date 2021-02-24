//ISOPassungen ITRechner
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

//#include "passungen.h"


#include <QMenuBar>
#include <QDialog>
#include <qmessagebox.h>
#include <sstream>
#include <QMenuBar>

class FitDimensions : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT
  public:
  FitDimensions (QMainWindow *parent = nullptr);
 ~FitDimensions();
  double  nennmass;
  QString grundabmass;
  QString toleranzgrad;
  double  tolerbreite;
  int     intgrundabmass;
  int     inttoleranzgrad;
  int     ITBreiteSpalte;
  int     beginnspalte;
  double  wellebeginn;
  int     rechenrichtung;
  double  masswelleende;
  QString dummy;
  double  bohrnennmass;
  QString bohrtoleranzgrad;
  int     bohrinttoleranzgrad;
  double  deltawert;
  QString bohrgrundabmass;
  int     bohrspalte;
  double  bohrtolerbreite;
  int     bohrITBreiteSpalte;
  double  bohrbeginn;
  int     bohrrechenrichtung;
  double  bohrende;
  double  bohrgob;
  double  bohrgub;
  double  shaftgow;
  double  shaftguw;
  QString nachricht;


private slots:
  void CalculateFit();
  void about();
  int  getRowofITArray();
  double getITToleranz();
  void getWelleSpalte();
  void getwellebeginn();
  void getcalcdirectionwelle();
  void welleende();
  void sortesei();
  void CalculateFitbore();
  void getdeltabohrung();
  void getBohrungSpalte();
  void getbohrITTolSpalte();
  double getBohrITToleranz();
  void getbohrungbeginn();
  void getcalcdirectionbohrung();
  void bohrungende();
  void sortESEI();
  void on_pB_Dialog_clicked();
  void on_pB_gewinde_clicked();

};


#endif // MAINWINDOW_H
