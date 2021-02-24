#include <iostream>
#include <iomanip>
#include <string.h>
#include "Getvalwelle.h"

struct wellenwerte
 {
  double nennmass;
  char   grundabmass[10];
  char   toleranzgrad[10];
  int    inttolergrad;
  double toleranz;
  int    spalte;
  double beginn;
  int    rechenrichtung;
  double ende;
  double deltawert;
 };

struct bohrungswerte
{
 // Werte für Bohrungsberechnungen
  double deltawert;
  double bohrnennmass;
  char   bohrgrundabmass[10];
  char   bohrtoleranzgrad[10];
  int    bohrinttolergrad;
  double bohrtoleranz;
  int    bohrspalte;
  double bohrbeginn;
  int    bohrrechenrichtung;
  double bohrende;
};


using namespace std;

//Sucht im Stringarray ITBereich die Nummer der gesuchten Spalte
void getRowofITArray(struct wellenwerte *ew, char ITBereich[22][5])   //char toleranzgrad[], char ITBereich[22][5])
 {
  int slei, erge, rewer = 0;

    for (slei = 0; slei <= 21; slei++)
     {
      //cout << "\ntolgrad" << ew->toleranzgrad << "  itbereich " << ITBereich[slei];
      erge = strcmp(ew->toleranzgrad, ITBereich[slei]);
      if (erge == 0)
      {
       //cout << "\nITBereich  Nr.: " << ew->grundabmass << " = " << ITBereich[slei];
        rewer = slei - 1;
      }
     }
 ew->inttolergrad = rewer;
 }
// Sucht die Toleranzbreite
         // alt war: double nennmass, int itb
void getITToleranz(struct wellenwerte *ew, double ITBreite[22][22])
   {
    int slei;
    double ug, og, toleranz = 0;

    for (slei = 0; slei <= 21; slei++)
     {
      ug = ITBreite[slei][0];
      og = ITBreite[slei][1];
      toleranz = ITBreite[slei][ew->inttolergrad + 1];
      //cout << "\ntoleranz= " << toleranz;
      if ((ew->nennmass > ug) &&(ew->nennmass <= og))
      {
       //cout << "\nMassbereich von " << ug << " bis " << og << " mm";
       break;
      }
     }
     ew->toleranz = toleranz / 1000;
     //cout << "  getITTolerance rewer = " << ew->toleranz;
 }

 void getWelleSpalte(struct wellenwerte *ew, char Letterwelle[31][15])
{
 int slei, erge, rewer = 0;
    //f ((ew->inttolergrad >=5) &&  (ew->inttolergrad <= 6) && (0 == (strcmp(ew->grundabmass, "j"))))  strcpy(ew->grundabmass, "j5-6");
    if ((ew->inttolergrad ==7) &&  (0 == (strcmp(ew->grundabmass, "j")))) strcpy(ew->grundabmass, "j7");
    if ((ew->inttolergrad ==8) &&  (0 == (strcmp(ew->grundabmass, "j")))) strcpy(ew->grundabmass, "j8");
    if ((ew->inttolergrad >=4) &&  (ew->inttolergrad <= 7) && ( 0 == (strcmp(ew->grundabmass, "k")))) strcpy(ew->grundabmass, "k4-7");
    if ((ew->inttolergrad < 3) ||  (ew->inttolergrad >  8))
     if ( 0 == (strcmp(ew->grundabmass, "k"))) strcpy(ew->grundabmass, "k<3>8");
    //cout << "getWelleSpalte   suche nach: " << ew->grundabmass;

    for (slei = 0; slei < 31; slei++)
     {
      //cout << "\n getWelleSpalte it=" << ew->grundabmass <<" letterwelle = " << Letterwelle[slei];
      erge = strcmp(ew->grundabmass, Letterwelle[slei]);
      if (erge == 0)
       {
        //cout << "\ngetWelleSpalte LetterBohrung  Nr.: " << ew->inttolergrad << " = " << Letterwelle[slei];

        rewer = slei;

        break;
       }
     }
//cout <<  "\ngetWelleSpalte rewer = " << rewer;
 ew->spalte = rewer;
}
           //alt war: double nennmass, int suchspalte
void getwellebeginn(struct wellenwerte *ew, short welle[41][33])
{
short zeile;
short ug, og;
double rewer = -1;

//cout << "\nGetwellebeginn:\n";
for (zeile = 0; zeile < 41; zeile++)
 {
  ug = welle[zeile][0];
  og = welle[zeile][1];
  if ((ew->nennmass > ug) && (ew->nennmass <= og))
  {
   rewer = (double)(welle[zeile][ew->spalte + 2]);
   if (rewer == 7777) rewer = ew->toleranz / 2;
   else rewer /= 1000;
   //cout <<"\nug=" << ug << "   og="<< og << "    wert=" << rewer <<  " suchspalte=" << ew->spalte + 2 << " zeile=" <<zeile << endl;
   //cout << "  toleranz: " << ew->toleranz;
   break;
  }
 }
//cout << "  Getwellebeginn rewer = " << rewer;

ew->beginn = rewer;
}

//Für Einheitswelle feststellen ob Topfboden oder -deckel
void getcalcdirectionwelle(struct wellenwerte *ew) //char it[])
    {
     int erge, direction = 0;
     char it[20];
     strcpy(it, ew->grundabmass);

     //Bei -1 ist Rechenrichtung ins Minus, bei +1 ins Plus
     if ((it[0] >= 'a') && (it[0] <= 'h')) direction = -1;
     if ((it[0] >= 'j') && (it[0] <= 'z')) direction = 1;
      erge = strcmp(it, "js");
     if (erge == 0) direction = 0;

     ew->rechenrichtung = direction;
    }

  void welleende(struct wellenwerte *ew)
    {
     double rewer = 0;
     if (ew->rechenrichtung ==  1) rewer = ew->beginn + ew->toleranz;
     if (ew->rechenrichtung == -1) rewer = ew->beginn - ew->toleranz;
     if (ew->rechenrichtung ==  0) rewer = ew->beginn - ew->toleranz;
     ew->ende = rewer;
    }

void Ausgabe( struct wellenwerte *ew)//double nennmass, char grundabmass[10], char toleranzgrad[10])
   {
    cout << "\nNennass...: "   << ew->nennmass;
    cout << "\nGrundabmaß: "   << ew->grundabmass;
    cout << "\nToleranzgrad: " << ew->toleranzgrad;
    cout << "\n\nITBereich  Nr.: " << ew->inttolergrad;
    cout << "\nToleranzbreite: "  << ew->toleranz << " mm";
    cout << "\nGetwelleSpalte: " << ew->spalte;
    cout << "\nRechenrichtung: " << ew->rechenrichtung;
    cout << "\nOberes Abmaß..: " << ew->beginn << "mm";
    cout << "\nUnteres Abmaß.: " << ew->ende << "mm";
   }

void EingabeWelle(struct wellenwerte *ew)//double *nennmass, char grundabmass[10], char toleranzgrad[10])
   {
    cout << "Passungsrechner für Wellen!" << endl;
    cout << "\nMass: " ;
    cin  >> ew->nennmass;

    cout << "\nEingabe Buchstabe Welle: ";
    cin  >> ew->grundabmass;

    cout << "\nToleranzgrad: ";
    cin  >> ew->toleranzgrad;
   }

void sortesei(struct wellenwerte *ew)
{
 double es, ei;
 ei = ew->beginn < ew->ende ? ew->beginn : ew->ende;
 es = ew->beginn > ew->ende ? ew->beginn : ew->ende;
 ew->beginn = es;
 ew->ende = ei;
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*************Funktionen für die Bohrungsberechnungen****************************************/
// Wegen der Konformität zu Symantec-Compiler
void strupr(char ar[])
{
  int slei = 0;
  while ( ar[slei] != '\0' )
  {
   if ((ar[slei] >= 'a') && (ar[slei] <= 'z')) ar[slei] -= 32;
   slei++;
  }
}
// sucht aus Tabelle den Deltawert zur Korrektur der Wellenabmaße
void getdeltabohrung(struct bohrungswerte *eb, double deltax[14][8])
{
int zeile;
double ug, og, rewer = -1;
//cout << "\nBohrnennmass: " << eb->bohrnennmass;

if ((eb->bohrinttolergrad >= 3) && (eb->bohrinttolergrad <=8))
for (zeile = 0; zeile < 14; zeile++)
 {
  ug = deltax[zeile][0];
  og = deltax[zeile][1];
  //cout <<"\n*ug " <<ug << " og "<< og << "delta " <<rewer;
  if ((eb->bohrnennmass > ug) && (eb->bohrnennmass <= og))
  {
   rewer = deltax[zeile][eb->bohrinttolergrad - 1];
   //cout <<"\nug " <<ug << " og "<< og << "delta " <<rewer;
   break;
  }
 }
else rewer = 0;

eb->deltawert = rewer / 1000;
}
void EingabeBohrung(struct bohrungswerte *eb)//double *nennmass, char grundabmass[10], char toleranzgrad[10])
   {
    cout << "Passungsrechner für Bohrungen!" << endl;
    cout << "\nBohrung Nennmass: " ;
    cin  >> eb->bohrnennmass;

    cout << "\nEingabe Buchstabe Bohrung: ";
    cin  >> eb->bohrgrundabmass;
    strupr(eb->bohrgrundabmass);
    cout << "\nBohrung Toleranzgrad: ";
    cin  >> eb->bohrtoleranzgrad;
   }

void AusgabeBohrung( struct bohrungswerte *eb)//double nennmass, char grundabmass[10], char toleranzgrad[10])
   {
    cout << fixed << setprecision(5);
    cout << "\nNennass...: "   << eb->bohrnennmass;
    cout << "\nGrundabmaß: "   << eb->bohrgrundabmass;
    cout << "\nToleranzgrad: " << eb->bohrtoleranzgrad;
    cout << "\n\nITBereich  Nr.: " << eb->bohrinttolergrad;
    cout << "\nToleranzbreite: "  << eb->bohrtoleranz << " mm";
    //cout << "\nGetbohrungspalte: " << eb->bohrspalte;
    //cout << "\nRechenrichtung: " << eb->bohrrechenrichtung;
    cout << "\nOberes Abmaß..: " << eb->bohrbeginn << "mm";
    cout << "\nUnteres Abmaß.: " << eb->bohrende << "mm";
    cout << "\nDelta = " << eb->deltawert;
   }

void getRowofITArray(struct bohrungswerte *eb, char ITBereich[22][5]) //char toleranzgrad[], char ITBereich[22][5])
 {
  int slei, erge, rewer = 0;

    for (slei = 0; slei <= 21; slei++)
     {
      //cout << "\ntolgrad" << eb->bohrtoleranzgrad << "  itbereich " << ITBereich[slei];
      erge = strcmp(eb->bohrtoleranzgrad, ITBereich[slei]);
      if (erge == 0)
      {
       //cout << "\nITBereich  Nr.: " << eb->bohrgrundabmass << " = " << ITBereich[slei];
        rewer = slei - 1;
      }
     }
 eb->bohrinttolergrad = rewer;
 }


     // alt war: double nennmass, int itb
    // Sucht die Toleranzbreite
void getITToleranzbohrung(struct bohrungswerte *eb, double ITBreite[22][22])
   {
    int slei;
    double ug, og, toleranz = 0;

    for (slei = 0; slei <= 21; slei++)
     {
      ug = ITBreite[slei][0];
      og = ITBreite[slei][1];
      toleranz = ITBreite[slei][eb->bohrinttolergrad + 1];
      //cout << "\ntoleranz= " << toleranz;
      if ((eb->bohrnennmass > ug) &&(eb->bohrnennmass <= og))
      {
       //cout << "\nMassbereich von " << ug << " bis " << og << " mm";
       break;
      }
     }
     eb->bohrtoleranz = toleranz / 1000;
 }

void getBohrungSpalte(struct bohrungswerte *eb, char Letterbohrung[32][15])
{
 int slei, erge, rewer = 0, tolergrad;
 tolergrad = eb->bohrinttolergrad;

    //cout << "\ngesucht: " << eb->bohrgrundabmass;
    if ((tolergrad <= 6) &&  (0 == (strcmp(eb->bohrgrundabmass, "J"))))  strcpy(eb->bohrgrundabmass, "J6");
    if ((tolergrad == 7) &&  (0 == (strcmp(eb->bohrgrundabmass, "J"))))  strcpy(eb->bohrgrundabmass, "J7");
    if ((tolergrad == 8) &&  (0 == (strcmp(eb->bohrgrundabmass, "J"))))  strcpy(eb->bohrgrundabmass, "J8");
    if ((tolergrad >= 7) &&  (tolergrad <= 8) && ( 0 == (strcmp(eb->bohrgrundabmass, "J")))) strcpy(eb->bohrgrundabmass, "J7-8");
    if ((tolergrad <= 8) &&  (0 == (strcmp(eb->bohrgrundabmass, "K")))) strcpy(eb->bohrgrundabmass, "K<=8");
    if ((tolergrad >  8) &&  (0 == (strcmp(eb->bohrgrundabmass, "K")))) strcpy(eb->bohrgrundabmass, "K>8");
    if ((tolergrad <= 8) &&  (0 == (strcmp(eb->bohrgrundabmass, "N")))) strcpy(eb->bohrgrundabmass, "N<=8");
    if ((tolergrad >  8) &&  (0 == (strcmp(eb->bohrgrundabmass, "N")))) strcpy(eb->bohrgrundabmass, "N>8");
    //cout << "   suche nach: " << eb->bohrgrundabmass;

    for (slei = 0; slei < 31; slei++)
     {
      //cout << "\nit=" << eb->bohrgrundabmass <<" letterwelle = " << Letterbohrung[slei];
      erge = strcmp(eb->bohrgrundabmass, Letterbohrung[slei]);
      if (erge == 0)
       {
        //cout << "\nLetterBohrung  Nr.: " << eb->bohrinttolergrad << " = " << Letterbohrung[slei];
        //cout <<  "rewer = " << rewer;
        rewer = slei;

        break;
       }
     }

 eb->bohrspalte = rewer;
}

void getbohrungbeginn(struct bohrungswerte *eb, short Bohrungen[41][34])
{
short zeile;
short ug, og;
double rewer = -1;

for (zeile = 0; zeile < 41; zeile++)
 {
  ug = Bohrungen[zeile][0];
  og = Bohrungen[zeile][1];
  if ((eb->bohrnennmass > ug) && (eb->bohrnennmass <= og))
  {
   rewer = (double)(Bohrungen[zeile][eb->bohrspalte + 2]);
   if (rewer == 7777) rewer = eb->bohrtoleranz / 2; // Bei js-Passungen
    else rewer /= 1000;
   //cout <<"\nug=" << ug << "   og="<< og << "    wert=" << rewer <<  " suchspalte=" << eb->bohrspalte + 2 << " zeile=" <<zeile << endl;
   break;
  }
 }
// Ausnahmeregelungen für Delta
if (eb->bohrgrundabmass[0] == 'K')
{
 if ((eb->bohrinttolergrad == 7) && (eb->bohrnennmass >= 18) && (eb->bohrnennmass <= 30)) eb->deltawert = 0.008;
 if (eb->bohrinttolergrad <= 8) rewer += eb->deltawert;
}
if (eb->bohrgrundabmass[0] == 'M')
{
 if ((eb->bohrinttolergrad == 6) && (eb->bohrnennmass >= 250) && (eb->bohrnennmass <= 315)) eb->deltawert = 0.011;
 if (eb->bohrinttolergrad <= 8) rewer += eb->deltawert;
}
if (eb->bohrgrundabmass[0] == 'S')
{
 if ((eb->bohrinttolergrad == 6) && (eb->bohrnennmass >= 18) && (eb->bohrnennmass <= 30)) eb->deltawert = 0.004;
  rewer += eb->deltawert;
}
eb->bohrbeginn = rewer;
//cout << " \nGetbohrbeginn rewer: " << rewer;
}


void getcalcdirectionbohrung(struct bohrungswerte *eb) //char it[])
    {
     int erge, direction = 0;
     char it[20];
     strcpy(it, eb->bohrgrundabmass);

     //Bei -1 ist Rechenrichtung ins Minus, bei +1 ins Plus
     if ((it[0] >= 'A') && (it[0] <= 'H')) direction = 1;
     if ((it[0] >= 'J') && (it[0] <= 'Z')) direction = -1;
      erge = strcmp(it, "JS");
     if (erge == 0) direction = 0;

     eb->bohrrechenrichtung = direction;
    }

 void bohrungende(struct bohrungswerte *eb)
    {
     double rewer = 0;
     //cout << "\n 5 Bohrtoleranz: " << eb->bohrtoleranz;
     //cout << "\n 5 Bohrbeginn: " << eb->bohrbeginn;
     if (eb->bohrrechenrichtung ==  1) rewer = eb->bohrbeginn + eb->bohrtoleranz;
     if (eb->bohrrechenrichtung == -1) rewer = eb->bohrbeginn - eb->bohrtoleranz;
     if (eb->bohrrechenrichtung ==  0) rewer = eb->bohrbeginn - eb->bohrtoleranz;
     eb->bohrende = rewer;
    //cout << "\n 5 Bohrtolende: " << eb->bohrende;
    }

void sortESEI(struct bohrungswerte *eb)
{
 double es, ei;
 ei = eb->bohrbeginn < eb->bohrende ? eb->bohrbeginn : eb->bohrende;
 es = eb->bohrbeginn > eb->bohrende ? eb->bohrbeginn : eb->bohrende;
 eb->bohrbeginn = es;
 eb->bohrende = ei;
}

