#ifndef GEWINDEM_H
#define GEWINDEM_H

#include <QDialog>
#include <qmessagebox.h>
#include <cmath>

namespace Ui {
class GewindeM;
}

class GewindeM : public QDialog
{
    Q_OBJECT

public:
    explicit GewindeM(QWidget *parent = nullptr);
    ~GewindeM();

     double pi;
     double da;
     double P;
     double d2atheo;
     double d3a;
     double R;
     double D1i;
     double S;
     double bohrerd;
     QString Steigung_in;
     QString GrndAbmassAussenD;
     double A0Wert;
     double damax;
     double damin;
     QString ITGradBolzenD;
     double ITBolzenD;
     double TdWert;
     QString ITd2Wertstr;
     double Td2Wert;
     double d2max;
     double d2min;
     QString ITd3Wertstr;
     double ITd3Wert;
     double Td3Wert;
     double Rmin;
     double d3max;
     double d3min;
     QString GAInnenstr;
     QString ITD1str;
     double ITD1Wert;
     double AuWert;
     double TD1Wert;
     double D1imax;
     double D1imin;
     QString ITD2str;
     double ITD2Wert;
     double TD2Wert;
     double D2imax;
     double D2imin;
     double dD;
     double C;
     double MD;
     double Ccalc;
     double PruefmassMmax;
     double PruefmassMmin;
     double AussenGtiefe;
     double InnenGtiefe;
     QString Nabpl;
     double Nx;
     double MKN;
     short fehlernummer;
     short fehler;

     void GetGewindeWerte(void);
     void CalcGewindewerte(void);
     void SucheA0Werte(void); //double Steigung, double Grundabmass
     void SucheTdWerte(void); //double Steigung, double Toleranzgrad)
     void SucheTd2Wert(void);
     void SucheTd3Wert(void);
     void SucheAuWert(void);
     void SucheTD1Wert(void);
     void SucheTD2Wert(void);
     void A0Fehlertest(void);
     void SucheDMess(void);
     double Bogenmass(double WinkelInGrad);
     double Sinus(double WinkelInGrad);
     double Cosinus(double WinkelInGrad);
     double Tangens(double WinkelInGrad);
     double Cotangens(double WinkelInGrad);
     void GetKorrC(void);
     void Regelgewindetest(void);
     void NennDSteigungsFehlertest(void);
     void GewindeWerteAnzeigen(void);

private slots:
     void berechnen(void);



private:
    Ui::GewindeM *ui;
};

#endif // GEWINDEM_H
