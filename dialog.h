#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString Nachricht;
    QString QS_dummy;
    //Wellenwerte
    double  QD_nennmass;     //Einheitswelle
    QString QD_grundabmass;
    int     QD_inttolergrad;
    double  QD_tolerbreite;
    double  QD_wellebeginn;
    int     QD_rechenrichtung;
    double  QD_masswelleende;
    double  QD_shaftgow;
    double  QD_shaftguw;
    //Bohrungserte
    double  QD_bohrnennmass;
    double  QD_bohrtolerbreite;
    QString QD_bohrtoleranzgrad;
    int     QD_bohrinttolergrad;
    QString QD_bohrgrundabmass;
    double  QD_ESbore;
    double  QD_EIbore;
    double  QD_bohrgob;
    double  QD_bohrgub;
    double  QD_bohrbeginn;
    int     QD_bohrrechenrichtung;
    double  QD_beginn;
    double  QD_ende;
    double  QD_bohrende;   // unteres Abmass
    double  QD_deltawert;

    double QD_diffmax;
    double QD_diffmin;

    /// Berechnung der Werte fuer Grenztlehrdorne
     double T_Wert;
     double z_Wert;
     double hh_Wert;
     double y_Wert;
     double a_Wert;
     double hsh_Wert;  // Fuer Kugelendmasse
     ///Werte fuer Grenzlehrdorne
     double GLD_EI_neu_max;
     double GLD_EI_neu_min;
     double GLD_EI_alt;
     double GLD_ES_max;
     double GLD_ES_min;
     ///Werte fuer Kugelendmasse
     double GLS_EI_neu_max;
     double GLS_EI_neu_min;
     double GLS_EI_alt;
     double GLS_ES_max;
     double GLS_ES_min;

     ///Berechnung der Werte fuer Grenzrachenlehren
     double z1_Wert;
     double y1_Wert;
     double hp2_Wert;
     double h12_Wert;
     double Tw_Wert;
     double a1_Wert;
     ///Werte fuer GrenzRachenlehren
     double GRL_es_neu_max;
     double GRL_es_neu_min;
     double GRL_es_alt;
     double GRL_ei_max;
     double GRL_ei_min;


private:
    Ui::Dialog *ui;

private slots:
    void getTfeld();
    void getWelleTFeld(void);
    void kopieren(void);
    void showshaftvalues(void);
    void showborevalues(void);
    void copyvalues(QWidget *parent);
};

#endif // DIALOG_H
