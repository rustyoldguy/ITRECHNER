//ISOPassungen mainwindow.cpp
//mainwindow.cpp von Passungen
#include <math.h>
#include "mainwindow.h"
#include <qstring.h>
#include "dialog.h"
#include "gewindem.h"

FitDimensions::FitDimensions(QMainWindow *parent) : QMainWindow(parent)
{
   setupUi(this);
   this->setWindowTitle("IT-Passungsrechner V1.01");
   this->move(150,100); //Setzt die Widget-Ausgabeposition

   QMenuBar *fimen = new QMenuBar(this);
   setMenuBar(fimen);

   //fimen->addMenu("&Info");
   QAction *newa = new QAction("&Autor", fimen);
   QAction *gewinde = new QAction("&Gewinde", fimen);

   fimen->addAction(newa);
   fimen->addAction(gewinde);

   // "a","b","c","cd","d","e","ef","f","fg","g","h","js","j5-6","j7","j8", "k4-7","k<3>8","m","n","p","r","s","t","u","v","x","y","z","za","zb","zc"};

   comboBox->addItem("a");
   comboBox->addItem("b");
   comboBox->addItem("c");
   comboBox->addItem("cd");
   comboBox->addItem("e");
   comboBox->addItem("ef");
   comboBox->addItem("f");
   comboBox->addItem("fg");
   comboBox->addItem("g");
   comboBox->addItem("h");
   comboBox->addItem("js");
   comboBox->addItem("j");
   comboBox->addItem("k");
   comboBox->addItem("m");
   comboBox->addItem("n");
   comboBox->addItem("p");
   comboBox->addItem("r");
   comboBox->addItem("s");
   comboBox->addItem("t");
   comboBox->addItem("u");
   comboBox->addItem("v");
   comboBox->addItem("x");
   comboBox->addItem("y");
   comboBox->addItem("z");
   comboBox->addItem("za");
   comboBox->addItem("zb");
   comboBox->addItem("zc");

   //99", "99", "1", "2", "3", "4", "5",  "6", "7", "8", "9", "10", "11", "12", "13", "14","15","16","17", "18","0","01"};
   DegOfTolerance -> addItem("0"); // ImQT-Designer bei Input-Widgets
   DegOfTolerance -> addItem("01");
   DegOfTolerance -> addItem("1");
   DegOfTolerance -> addItem("2");
   DegOfTolerance -> addItem("3");
   DegOfTolerance -> addItem("4");
   DegOfTolerance -> addItem("5");
   DegOfTolerance -> addItem("6");
   DegOfTolerance -> addItem("7");
   DegOfTolerance -> addItem("8");
   DegOfTolerance -> addItem("9");
   DegOfTolerance -> addItem("10");
   DegOfTolerance -> addItem("11");
   DegOfTolerance -> addItem("12");
   DegOfTolerance -> addItem("13");
   DegOfTolerance -> addItem("14");
   DegOfTolerance -> addItem("15");
   DegOfTolerance -> addItem("16");
   DegOfTolerance -> addItem("17");
   DegOfTolerance -> addItem("18");

   basesize -> setText("50");   // Voreinstellung für Einheitswelle
   borebasesize->setText("50"); // Voreinstellung für Einheitsbohrung
   // "A","B","C","CD","D","E","EF","F","FG","G","H","JS","J6","J7", "J8","K<=8","K>8","M","N<=8","N>8","P","R","S","T","U","V","X","Y","Z","ZA","ZB","ZC"};
   boreallowance->addItem("A");
   boreallowance->addItem("B");
   boreallowance->addItem("C");
   boreallowance->addItem("CD");
   boreallowance->addItem("E");
   boreallowance->addItem("EF");
   boreallowance->addItem("F");
   boreallowance->addItem("FG");
   boreallowance->addItem("G");
   boreallowance->addItem("H");
   boreallowance->addItem("JS");
   boreallowance->addItem("J");
   boreallowance->addItem("K");
   boreallowance->addItem("M");
   boreallowance->addItem("N");
   boreallowance->addItem("P");
   boreallowance->addItem("R");
   boreallowance->addItem("S");
   boreallowance->addItem("T");
   boreallowance->addItem("U");
   boreallowance->addItem("V");
   boreallowance->addItem("X");
   boreallowance->addItem("Y");
   boreallowance->addItem("Z");
   boreallowance->addItem("ZA");
   boreallowance->addItem("ZB");
   boreallowance->addItem("ZC");

   boreDegOfTolerance -> addItem("0"); // ImQT-Designer bei Input-Widgets
   boreDegOfTolerance -> addItem("01");
   boreDegOfTolerance -> addItem("1");
   boreDegOfTolerance -> addItem("2");
   boreDegOfTolerance -> addItem("3");
   boreDegOfTolerance -> addItem("4");
   boreDegOfTolerance -> addItem("5");
   boreDegOfTolerance -> addItem("6");
   boreDegOfTolerance -> addItem("7");
   boreDegOfTolerance -> addItem("8");
   boreDegOfTolerance -> addItem("9");
   boreDegOfTolerance -> addItem("10");
   boreDegOfTolerance -> addItem("11");
   boreDegOfTolerance -> addItem("12");
   boreDegOfTolerance -> addItem("13");
   boreDegOfTolerance -> addItem("14");
   boreDegOfTolerance -> addItem("15");
   boreDegOfTolerance -> addItem("16");
   boreDegOfTolerance -> addItem("17");
   boreDegOfTolerance -> addItem("18");


   //allowance -> setText("h");
   //DegOfTolerance -> setText("7");

   connect(newa,        SIGNAL(triggered()), this, SLOT(about()));
   connect(gewinde,     SIGNAL(triggered()), this, SLOT(on_pB_gewinde_clicked()));

   connect(pB_Dialog,     SIGNAL(triggered()), this, SLOT(on_pB_Dialog_clicked()));
   connect(calculate,     SIGNAL(clicked()),   this, SLOT(CalculateFit() ) );
   connect(calculatebore, SIGNAL(clicked()),   this, SLOT(CalculateFitbore() ) );
   connect(finito,        SIGNAL (clicked()),  qApp, SLOT(quit() ) );
}

FitDimensions::~FitDimensions()
{
}
//Sucht im Stringarray ITBereich die Nummer der gesuchten Spalte
int  FitDimensions::getRowofITArray(void)
 {
  QString ITBereich[22] ={
  "99", "99", "1", "2", "3", "4", "5",  "6", "7", "8", "9", "10", "11", "12", "13", "14","15","16","17", "18","0","01"};
  int slei, rewer = 0;

    for (slei = 0; slei <= 21; slei++)
     {
     // vergleicht die zwei Strings miteinander, bei Übereinstimmung Rückgabewert = 0
     if(ITBereich[slei].compare(toleranzgrad)==0)
      {
       rewer = slei - 1;
       break;
      }
     }
 return (rewer);
 }

// Sucht die Toleranzbreite
 double FitDimensions::getITToleranz(void)
   {
     //Grundtoleranzen
   double ITBreite[22][22]= {
         {0,    0,   1,   2,   3,  4,  5,   6,   7,   8,   9,  10,   11,   12,   13,   14,   15,    16,    17,    18,   0, 0.1},
         {1,    3, 0.8, 1.2,   2,  3,  4,   6,  10,  14,  25,  40,   60,  100,  140,  250,  400,   600,  1000,  1400, 0.3, 0.5},
         {3,    6,   1, 1.5, 2.5,  4,  5,   8,  12,  18,  30,  48,   75,  120,  180,  300,  480,   750,  1200,  1800, 0.4, 0.6},
         {6,   10,   1, 1.5, 2.5,  4,  6,   9,  15,  22,  36,  58,   90,  150,  220,  360,  580,   900,  1500,  2200, 0.4, 0.6},
        {10,   18, 1.2,   2,   3,  5,  8,  11,  18,  27,  43,  70,  110,  180,  270,  430,  700,  1100,  1800,  2700, 0.5, 0.8},
        {18,   30, 1.5, 2.5,   4,  6,  9,  13,  21,  33,  52,  84,  130,  210,  330,  520,  840,  1300,  2100,  3300, 0.6,   1},
        {30,   50, 1.5, 2.5,   4,  7, 11,  16,  25,  39,  62, 100,  160,  250,  390,  620, 1000,  1600,  2500,  3900, 0.6,   1},
        {50,   80,   2,   3,   5,  8, 13,  19,  30,  46,  74, 120,  190,  300,  460,  740, 1200,  1900,  3000,  4600, 0.8, 1.2},
        {80,  120, 2.5,   4,   6, 10, 15,  22,  35,  54,  87, 140,  220,  350,  540,  870, 1400,  2200,  3500,  5400,   1, 1.5},
       {120,  180, 3.5,   5,  10, 12, 18,  25,  40,  63, 100, 100,  250,  400,  630, 1000, 1600,  2500,  4000,  6300, 1.2,   2},
       {180,  250, 4.5,   7,  12, 14, 20,  29,  46,  72, 115, 185,  290,  460,  720, 1150, 1850,  2900,  4600,  7200,   2,   3},
       {250,  315,   6,   8,  12, 16, 23,  32,  52,  81, 130, 210,  320,  520,  810, 1300, 2100,  3200,  5200,  8100, 2.5,   4},
       {315,  400,   7,   9,  13, 18, 25,  36,  57,  89, 140, 230,  360,  570,  890, 1400, 2300,  3600,  5700,  8900,   3,   5},
       {400,  500,   8,  10,  15, 20, 27,  40,  63,  97, 155, 250,  400,  630,  970, 1550, 2500,  4000,  6300,  9700,   4,   6},
       {500,  630,   9,  11,  16, 22, 32,  44,  70, 110, 175, 280,  440,  700, 1100, 1750, 2800,  4400,  7000, 11000,   0,   0},
       {630,  800,  10,  13,  18, 25, 36,  50,  80, 125, 200, 320,  500,  800, 1250, 2000, 3200,  5000,  8000, 12500,   0,   0},
       {800, 1000,  11,  15,  21, 28, 40,  56,  90, 140, 230, 360,  560,  900, 1400, 2300, 3600,  5600,  9000, 14000,   0,   0},
      {1000, 1250,  13,  18,  24, 33, 47,  66, 105, 165, 260, 420,  660, 1050, 1650, 2600, 4200,  6600, 10500, 16500,   0,   0},
      {1250, 1600,  15,  21,  29, 39, 55,  78, 125, 195, 310, 500,  780, 1250, 1950, 3100, 5000,  7800, 12500, 19500,   0,   0},
      {1600, 2000,  18,  25,  35, 46, 65,  92, 150, 230, 370, 600,  920, 1500, 2300, 3700, 6000,  9200, 15000, 23000,   0,   0},
      {2000, 2500,  22,  30,  41, 55, 78, 110, 175, 280, 440, 700, 1100, 1750, 2800, 4400, 7000, 11000, 17500, 28000,   0,   0},
      {2500, 3150,  26,  36,  50, 68, 96, 135, 210, 330, 540, 860, 1350, 2100, 3300, 5400, 8600, 13500, 21000, 33000,   0,   0}};

    int slei;
    double ug, og, toleranz = 0;

    for (slei = 0; slei <= 21; slei++)
     {
      ug = ITBreite[slei][0];
      og = ITBreite[slei][1];
      toleranz = ITBreite[slei][ITBreiteSpalte];
    if ((nennmass > ug) &&(nennmass <= og))
      {
       //cout << "\nMassbereich von " << ug << " bis " << og << " mm";
       break;
      }
     }

    return(toleranz / 1000);

 }

 void FitDimensions::getWelleSpalte(void)
{
    QString GrundabmassWelle[31] = {
      "a","b","c","cd","d","e","ef","f","fg","g","h","js","j5-6","j7","j8", "k4-7","k<3>8","m","n","p","r","s","t","u","v","x","y","z","za","zb","zc"};
     //0   1   2    3   4   5   6    7    8   9   10  11    12    13    14    15     16     17  18  19  20  21  22  23  24  25  26  27  28   29   30
   QString gruab = grundabmass.toLower();
   grundabmass = gruab;

   int slei, rewer = 0;
   if ((inttoleranzgrad >= 5) &&  (inttoleranzgrad <= 6) && (grundabmass.compare("j") == 0)) grundabmass = QString::fromLatin1("j5-6");
   if ((inttoleranzgrad == 7) &&  (grundabmass.compare("j") == 0)) grundabmass = QString::fromLatin1("j7");
   if ((inttoleranzgrad == 8) &&  (grundabmass.compare("j") == 0)) grundabmass = QString::fromLatin1("j8");
   if ((inttoleranzgrad >=4) &&  (inttoleranzgrad <= 7) && (grundabmass.compare("k") == 0)) grundabmass = QString::fromLatin1("k4-7");
   if ((inttoleranzgrad <= 3) || (inttoleranzgrad > 7))
    if (grundabmass.compare("k") == 0)  grundabmass = QString::fromLatin1("k<3>8");
     for (slei = 0; slei < 31; slei++)
       {
        if(grundabmass.compare(GrundabmassWelle[slei])==0)
         {
          rewer = slei;
          break;
         }
       }

 beginnspalte = rewer;
}

void FitDimensions::getwellebeginn(void)
{
    // Werte zur Berechnung der Toleranzen von Wellen
    /*
    Merke:
    Die Grundabmaße a und b sind nicht für Nennmaße einschließlich 1mm anzuwenden
    Bei den Toleranzklassen js7 bis js11 kann der IT-Zahlenwert, n, falls er aus einer
    ungeraden Zahl besteht, auf die unmittelbar darunterliegende Zahl gerundet werden,
    also in ganzen Mikrometer.
    */

    // 0     1    2     3     4    5     6    7    8    9     10  11  12  13   14   15  16   17   18  19  20  21  22   23   24   25  26    27  28    29   30   31   32
    // ug   og    a     b     c   cd     d    e    ef   f     fg   g  h   js  j5-6  j7  j8  k4-7 k<3>8 m   n  p   r    s    t     u   v    x   y      z   za   zb   zc

     static short welle[41][33] ={
       {0,   3,  -270, -140,  -60, -32,  -20, -14, -10,  -6,  -4,  -2, 0, 7777,  -2,  -4,  -6, 0,   0,  2,  4,  6, 10,  14,9999,  18,9999,  20,9999,  26,  32,  40,  60},
       {3,   6,  -270, -140,  -70, -46,  -30, -20, -14, -10,  -6,  -4, 0, 7777,  -2,  -4,9999, 1,   0,  4,  8, 12, 15,  19,9999,  23,9999,  28,9999,  35,  42,  50,  80},
       {6,  10,  -280, -150 , -80, -56,  -40, -25, -18, -13,  -8,  -5, 0, 7777,  -2,  -5,9999, 1,   0,  6, 10, 15, 19,  23,9999,  28,9999,  34,9999,  42,  52,  67,  97},
      {10,  14,  -290, -150,  -95,9999,  -50, -32,9999, -16,9999,  -6, 0, 7777,  -3,  -6,9999, 1,   0,  7, 12, 18, 23,  28,9999,  33,9999,  40,9999,  50,  64,  90, 130},
      {14,  18,  -290, -150,  -95,9999,  -50, -32,9999, -16,9999,  -6, 0, 7777,  -3,  -6,9999, 1,   0,  7, 12, 18, 23,  28,9999,  33,  39,  45,9999,  60,  77, 108, 150},
      {18,  24,  -300, -160, -110,9999,  -65, -40,9999, -20,9999,  -7, 0, 7777,  -4,  -8,9999, 2,   0,  8, 15, 22, 28,  35,9999,  41,  47,  54,  63,  73,  98, 136, 188},
      {24,  30,  -300, -160, -110,9999,  -65, -40,9999, -20,9999,  -7, 0, 7777,  -4,  -8,9999, 2,   0,  8, 15, 22, 28,  35,  41,  48,  55,  64,  75,  88, 118, 160, 218},
      {30,  40,  -310, -170, -120,9999,  -80, -50,9999, -25,9999,  -9, 0, 7777,  -5, -10,9999, 2,   0,  9, 17, 26, 34,  43,  48,  60,  68,  80,  94, 112, 148, 200, 274},
      {40,  50,  -320, -180, -130,9999,  -80, -50,9999, -25,9999,  -9, 0, 7777,  -5, -10,9999, 2,   0,  9, 17, 26, 34,  43,  54,  70,  81,  97, 114, 136, 180, 242, 325},
      {50,  65,  -340, -190, -140,9999, -100, -60,9999, -30,9999, -10, 0, 7777,  -7, -12,9999, 2,   0, 11, 20, 32, 41,  53,  66,  87, 102, 122, 144, 172, 226, 300, 405},
      {65,  80,  -360, -200, -150,9999, -100, -60,9999, -30,9999, -10, 0, 7777,  -7, -12,9999, 2,   0, 11, 20, 32, 43,  59,  75, 102, 120, 146, 174, 210, 274, 360, 480},
      {80, 100,  -380, -220, -170,9999, -120, -72,9999, -36,9999, -12, 0, 7777,  -9, -15,9999, 3,   0, 13, 23, 37, 51,  71,  91, 124, 146, 178, 214, 258, 335, 445, 585},
     {100, 120,  -410, -240, -180,9999, -120, -72,9999, -36,9999, -12, 0, 7777,  -9, -15,9999, 3,   0, 13, 23, 37, 54,  79, 104, 144, 172, 210, 254, 310, 400, 525, 690},
     {120, 140,  -460, -260, -200,9999, -145, -85,9999, -43,9999, -14, 0, 7777, -11, -18,9999, 3,   0, 15, 27, 43, 63,  92, 122, 170, 202, 248, 300, 365, 470, 620, 800},
     {140, 160,  -520, -280, -210,9999, -145, -85,9999, -43,9999, -14, 0, 7777, -11, -18,9999, 3,   0, 15, 27, 43, 65, 100, 134, 190, 228, 280, 340, 415, 535, 700, 900},
     {160, 180,  -580, -310, -230,9999, -145, -85,9999, -43,9999, -14, 0, 7777, -11, -18,9999, 3,   0, 15, 27, 43, 68, 108, 146, 210, 252, 310, 380, 465, 600, 780,1000},
     {180, 200,  -660, -340, -240,9999, -170,-100,9999, -50,9999, -15, 0, 7777, -13, -21,9999, 4,   0, 17, 31, 50, 77, 122, 166, 236, 284, 350, 425, 520, 670, 880,1150},
     {200, 225,  -740, -380, -260,9999, -170,-100,9999, -50,9999, -15, 0, 7777, -13, -21,9999, 4,   0, 17, 31, 50, 80, 130, 180, 258, 310, 385, 470, 575, 740, 960,1250},
     {225, 250,  -820, -420, -280,9999, -170,-100,9999, -50,9999, -15, 0, 7777, -13, -21,9999, 4,   0, 17, 31, 50, 84, 140, 196, 284, 340, 425, 520, 640, 820,1050,1350},
     {250, 280,  -920, -480, -300,9999, -190,-110,9999, -56,9999, -17, 0, 7777, -16, -26,9999, 4,   0, 20, 34, 56, 94, 158, 218, 315, 385, 475, 580, 710, 920,1200,1550},
     {280, 315, -1050, -540, -330,9999, -190,-110,9999, -56,9999, -17, 0, 7777, -16, -26,9999, 4,   0, 20, 34, 56, 98, 170, 240, 350, 425, 525, 650, 790,1000,1300,1700},
     {315, 355, -1200, -600, -360,9999, -210,-125,9999, -62,9999, -18, 0, 7777, -18, -28,9999, 4,   0, 21, 37, 62,108, 190, 268, 390, 475, 590, 730, 900,1150,1500,1900},
     {355, 400, -1350, -680, -400,9999, -210,-125,9999, -62,9999, -18, 0, 7777, -18, -28,9999, 4,   0, 21, 37, 62,114, 208, 294, 435, 530, 660, 820,1000,1300,1650,2100},
     {400, 450, -1500, -760, -440,9999, -230,-135,9999, -68,9999, -20, 0, 7777, -20, -32,9999, 5,   0, 23, 40, 68,126, 232, 330, 490, 595, 740, 920,1100,1450,1850,2400},
     {450, 500, -1650, -840, -480,9999, -230,-135,9999, -68,9999, -20, 0, 7777, -20, -32,9999, 5,   0, 23, 40, 68,132, 252, 360, 540, 660, 820,1000,1250,1600,2100,2600},
     {500, 560,  9999,9999 , 9999,9999, -260,-145,9999, -76,9999, -76, 0, 7777,9999,9999,9999, 0,   0, 26, 44, 78,150, 280, 400, 600,9999,9999,9999,9999,9999,9999,9999},
     {560, 630,  9999,9999 , 9999,9999, -260,-145,9999, -76,9999, -76, 0, 7777,9999,9999,9999, 0,   0, 26, 44, 78,155, 310, 450, 660,9999,9999,9999,9999,9999,9999,9999},
     {630, 710,  9999,9999 , 9999,9999, -290,-160,9999, -80,9999, -24, 0, 7777,9999,9999,9999, 0,   0, 30, 50, 88,175, 340, 500, 740,9999,9999,9999,9999,9999,9999,9999},
     {710, 800,  9999,9999 , 9999,9999, -290,-160,9999, -80,9999, -24, 0, 7777,9999,9999,9999, 0,   0, 30, 50, 88,185, 380, 560, 840,9999,9999,9999,9999,9999,9999,9999},
     {800, 900,  9999,9999 , 9999,9999, -320,-170,9999, -86,9999, -26, 0, 7777,9999,9999,9999, 0,   0, 34, 56,100,210, 430, 620, 940,9999,9999,9999,9999,9999,9999,9999},
     {900,1000,  9999,9999 , 9999,9999, -320,-170,9999, -86,9999, -26, 0, 7777,9999,9999,9999, 0,   0, 34, 56,100,220, 470, 680,1050,9999,9999,9999,9999,9999,9999,9999},
    {1000,1120,  9999,9999 , 9999,9999, -350,-195,9999, -98,9999, -28, 0, 7777,9999,9999,9999, 0,   0, 40, 66,120,250, 520, 780,1150,9999,9999,9999,9999,9999,9999,9999},
    {1120,1250,  9999,9999 , 9999,9999, -350,-195,9999, -98,9999, -28, 0, 7777,9999,9999,9999, 0,   0, 40, 66,120,260, 580, 840,1300,9999,9999,9999,9999,9999,9999,9999},
    {1250,1400,  9999,9999 , 9999,9999, -390,-220,9999,-110,9999, -30, 0, 7777,9999,9999,9999, 0,   0, 48, 78,140,300, 640, 960,1450,9999,9999,9999,9999,9999,9999,9999},
    {1400,1600,  9999,9999 , 9999,9999, -390,-220,9999,-110,9999, -30, 0, 7777,9999,9999,9999, 0,   0, 48, 78,140,330, 720,1050,1600,9999,9999,9999,9999,9999,9999,9999},
    {1600,1800,  9999,9999 , 9999,9999, -430,-240,9999,-120,9999, -32, 0, 7777,9999,9999,9999, 0,   0, 58, 92,170,370, 820,1200,1850,9999,9999,9999,9999,9999,9999,9999},
    {1800,2000,  9999,9999 , 9999,9999, -430,-240,9999,-120,9999, -32, 0, 7777,9999,9999,9999, 0,   0, 58, 92,170,400, 920,1350,2000,9999,9999,9999,9999,9999,9999,9999},
    {2000,2240,  9999,9999 , 9999,9999, -480,-260,9999,-130,9999, -34, 0, 7777,9999,9999,9999, 0,   0, 68,110,195,440,1000,1500,2300,9999,9999,9999,9999,9999,9999,9999},
    {2240,2500,  9999,9999 , 9999,9999, -480,-260,9999,-130,9999, -34, 0, 7777,9999,9999,9999, 0,   0, 68,110,195,460,1100,1650,2500,9999,9999,9999,9999,9999,9999,9999},
    {2500,2800,  9999,9999 , 9999,9999, -520,-290,9999,-145,9999, -38, 0, 7777,9999,9999,9999, 0,   0, 76,135,240,550,1250,1900,2900,9999,9999,9999,9999,9999,9999,9999},
    {2800,3150,  9999,9999 , 9999,9999, -520,-290,9999,-145,9999, -89, 0, 7777,9999,9999,9999, 0,   0, 76,135,240,580,1400,2100,3200,9999,9999,9999,9999,9999,9999,9999}};

short zeile;
short ug, og;
double rewer = -1;

 for (zeile = 0; zeile < 41; zeile++)
  {
   ug = welle[zeile][0];
   og = welle[zeile][1];
   if ((nennmass > ug) && (nennmass <= og))
    {
     rewer = static_cast<double>(welle[zeile][beginnspalte + 2]);
     if ((rewer >= 7776) &&(rewer <= 7777))rewer = tolerbreite / 2;
     else rewer /= 1000;
     break;
    }
  }

wellebeginn = rewer;
}


//Für Einheitswelle feststellen ob Topfboden oder -deckel
void FitDimensions::getcalcdirectionwelle(void)
    {
     int direction = 0;

     //Bei -1 ist Rechenrichtung ins Minus, bei +1 ins Plus
     if (beginnspalte <= 10) direction = -1;
     if (beginnspalte >= 12) direction = 1;
     if (beginnspalte == 11) direction = 0;

     rechenrichtung = direction;
    }

void FitDimensions::welleende(void)
    {
     if (rechenrichtung ==  1) masswelleende = wellebeginn + tolerbreite;
     if (rechenrichtung == -1) masswelleende = wellebeginn - tolerbreite;
     if (rechenrichtung ==  0) masswelleende = wellebeginn - tolerbreite;
    }

void FitDimensions::sortesei(void)
{
 double es, ei;
  ei = wellebeginn < masswelleende ? wellebeginn : masswelleende;
  es = wellebeginn > masswelleende ? wellebeginn : masswelleende;
 wellebeginn = es;
 masswelleende = ei;
}

//Wellenwerte berechnen
void FitDimensions::CalculateFit()
{
   QMessageBox *msgBox = new QMessageBox(this);
    //Grundinformationen einlesen
   nennmass        = (basesize -> text()).toDouble();
   grundabmass = comboBox->currentText();
   //  grundabmass     = allowance-> text();
   toleranzgrad    = DegOfTolerance->currentText();
   inttoleranzgrad = toleranzgrad.toInt();

   if (inttoleranzgrad != 0){
   nachricht = (QString("QD_inttolergrad %1").arg(inttoleranzgrad,3,10, QChar('0')));
   msgBox->setText(nachricht);}

   if (nennmass < 1)
    {
     msgBox->setText("No nominal size less than 1 mm");
     msgBox->show();
    }
   if (nennmass > 3150)
    {
     msgBox->setText("No nominal size greater than 3150 mm");
     msgBox->show();
    }



   // int i = 42;
   // QString s = QString::number(i);
   ITBreiteSpalte = (getRowofITArray()) + 1;

   if ((ITBreiteSpalte < 1) || (ITBreiteSpalte > 21))
    {
     msgBox->setText("degree of tolerance:\nallowed is 0, 01,12,3,4,5,6,7,8,9\n10,11,12,13,14,15,16,17,18");
     msgBox->show();
    }

   getWelleSpalte();

   if (((beginnspalte == 3)|| (beginnspalte == 6) || (beginnspalte == 8)) && (nennmass > 10))
    {
     msgBox->setText("By allowance de, ef, gf:\nno nominal size greater than 10mm");
     msgBox->show();
    }
   if (((beginnspalte == 0)|| (beginnspalte == 1) || (beginnspalte == 2)|| (beginnspalte == 12) || (beginnspalte == 13)) && (nennmass > 500))
    {
     msgBox->setText("By allowance a, b, c, j5, j6, j7:\nno nominal size greater than 500mm");
     msgBox->show();
    }
   if ((beginnspalte >= 24) && (beginnspalte <= 1) && (nennmass > 500))
    { // 24 ist v, 30 ist zc
     msgBox->setText("By allowance v up to zc:\nno nominal size greater than 500mm");
     msgBox->show();
    }
   if ((beginnspalte == 22) && (nennmass < 24))
    { //22 ist t
     msgBox->setText("By allowance t:\nno nominal size less than 24mm");
     msgBox->show();
    }
   if ((beginnspalte == 24) && (nennmass < 14))
    { //24 ist v
     msgBox->setText("By allowance t:\nno nominal size less than 14mm");
     msgBox->show();
    }
   if ((beginnspalte == 26) && (nennmass < 18))
    { //26 ist y
     msgBox->setText("By allowance y:\nno nominal size less than 18mm");
     msgBox->show();
    }

   if ((beginnspalte == 14) && (nennmass > 3))
    { //14 ist j8
     msgBox->setText("By allowance j8:\nno nominal size greater than 3mm");
     msgBox->show();
    }

   //dummy = QString::number(beginnspalte);
   //allowance -> setText(dummy);  //zur Überprüfung: grundabmass

   //dummy = QString::number(ITBreiteSpalte);
   //DegOfTolerance->setText(dummy);

   tolerbreite = getITToleranz();
   toleranzbreite -> setText(QString("%1").arg(tolerbreite,0,'f',5));

   getwellebeginn();
   getcalcdirectionwelle();
   welleende();
   sortesei();
   shaftgow = nennmass + wellebeginn;
   shaftguw = nennmass + masswelleende;
   abmassoben -> setText(QString("%1").arg(wellebeginn,0,'f',5));
   abmassunten-> setText(QString("%1").arg(masswelleende,0,'f',5));
   GoW -> setText(QString("%1").arg(shaftgow,0,'f',5));
   GuW -> setText(QString("%1").arg(shaftguw,0,'f',5));


}

void FitDimensions::about()
{
  QMessageBox::about( this, "Autor",
                        "ITRechner V1.0\n"
                        "von Josef Wismeth\n"
                        );
}

// Funktion für Bohrungen
void FitDimensions::CalculateFitbore()
{
   //QMessageBox *msgBox = new QMessageBox(this);
   //Grundinformationen einlesen
   bohrnennmass        = (borebasesize -> text()).toDouble();
   bohrgrundabmass     = boreallowance-> currentText();
   bohrtoleranzgrad    = boreDegOfTolerance->currentText();
   bohrinttoleranzgrad = bohrtoleranzgrad.toInt();

   //bohrinttoleranzgrad = 42;
   //dummy = QString::number(bohrinttoleranzgrad);
   //boreDegOfTolerance -> setText(dummy);  //zur Überprüfung: toleranzgrad

   getdeltabohrung();

   dummy = QString::number(deltawert);
   boredelta -> setText(dummy);  //zur Überprüfung: deltawert

   getbohrITTolSpalte();   // Setzt Wert für bohrITBreiteSpalte
   //dummy = QString::number(bohrITBreiteSpalte);
   //bohrtoleranzbreite->setText(dummy);

   bohrtolerbreite = getBohrITToleranz();
   bohrtoleranzbreite -> setText(QString("%1").arg(bohrtolerbreite,0,'f',5));

   getBohrungSpalte(); // setzt den Wert für bohrspalte zur suche des ersten Abmasses

   //dummy = QString::number(bohrspalte);
   //ESbore->setText(dummy);

   getbohrungbeginn();

   getcalcdirectionbohrung();

   bohrungende();

   sortESEI();

   ESbore -> setText(QString("%1").arg(bohrbeginn,0,'f',5));
   EIbore -> setText(QString("%1").arg(bohrende,0,'f',5));
   bohrgob = bohrnennmass + bohrbeginn;
   bohrgub = bohrnennmass + bohrende;

   GoB -> setText(QString("%1").arg(bohrgob,0,'f',5));
   GuB -> setText(QString("%1").arg(bohrgub,0,'f',5));
}

// Funktionen für die Einheitsbohrung noch nicht implementiert

void FitDimensions::getdeltabohrung(void)
{
int zeile;
double ug, og, rewer = -1;
double delta[14][8]=
{//0   1    2    3  4   5    6   7   =Spaltennummerierung
  {0,   0,   3,   4, 5,  6,   7,  8},  //0  Spalte 2 ist IT3, Spalte 7 ist IT8
  {0,   3,   0,   0, 0,	0,   0,	 0},  //1
  {3,   6,   1, 1.5, 1,	3,   4,	 6},  //2
  {6,  10,   1, 1.5, 2,	3,   6,	 7},  //3
 {10,  18,   1,   2, 3,	3,   7,	 9},  //4
 {18,  30, 1.5,   2, 3,	4,   8,	12},  //5
 {30,  50, 1.5,   3, 4,	5,   9,	14},  //6
 {50,  80,   2,   3, 5,	6,  11,	16},  //7
 {80, 120,   2,   4, 5,	7,  13,	19},  //8
{120, 180,   3,   4, 6,	7,  15,	23},  //9
{180, 250,   3,   4, 6,	9,  17,	26},  //10
{250, 315,   4,   4, 7,  9,  20, 29},  //11
{315, 400,   4,   5, 7, 11,  21, 32},  //12 connect(newa, SIGNAL(triggered()), this, SLOT(about()));
{400, 500,   5,   5, 7, 13,  23, 34}}; //13

if ((bohrinttoleranzgrad >= 3) && (bohrinttoleranzgrad <=8))
for (zeile = 0; zeile < 14; zeile++)
 {
  ug = delta[zeile][0];
  og = delta[zeile][1];
 if ((bohrnennmass > ug) && (bohrnennmass <= og))
  {
   rewer = delta[zeile][bohrinttoleranzgrad - 1];
   break;
  }
 }
else rewer = 0;

deltawert = rewer / 1000;
}


void FitDimensions::getBohrungSpalte(void)
{
char GrundabmassBohrung[32][15] = {
 "A","B","C","CD","D","E","EF","F","FG","G","H","JS","J6","J7", "J8","K<=8","K>8","M","N<=8","N>8","P","R","S","T","U","V","X","Y","Z","ZA","ZB","ZC"};
//0   1   2   3    4   5   6    7   8    9   10  11   12   13    14    15     16   17   18    19    20  21  22  23  24  25  26  27  28  29   30   31
int slei, itgrad;
QString bogru = bohrgrundabmass.toUpper();
bohrgrundabmass = bogru;

itgrad = bohrinttoleranzgrad;

    if ((itgrad <= 6) && (bohrgrundabmass.compare("J") == 0)) bohrgrundabmass = QString::fromLatin1("J6");
    if ((itgrad == 7) && (bohrgrundabmass.compare("J") == 0)) bohrgrundabmass = QString::fromLatin1("J7");
    if ((itgrad == 8) && (bohrgrundabmass.compare("J") == 0)) bohrgrundabmass = QString::fromLatin1("J8");
    if ((itgrad >= 7) && (itgrad <= 8) && (bohrgrundabmass.compare("J") == 0)) bohrgrundabmass = QString::fromLatin1("J7-8");
    if ((itgrad <= 8) && (bohrgrundabmass.compare("K") == 0)) bohrgrundabmass = QString::fromLatin1("K<=8");
    if ((itgrad >  8) && (bohrgrundabmass.compare("K") == 0)) bohrgrundabmass = QString::fromLatin1("K>8");
    if ((itgrad <= 8) && (bohrgrundabmass.compare("N") == 0)) bohrgrundabmass = QString::fromLatin1("N<=8");
    if ((itgrad >  8) && (bohrgrundabmass.compare("N") == 0)) bohrgrundabmass = QString::fromLatin1("N>8");

    for (slei = 0; slei < 31; slei++)
     {
      if(bohrgrundabmass.compare(GrundabmassBohrung[slei])==0)
       {
        bohrspalte = slei;
        break;
       }
     }

}

void FitDimensions::getbohrITTolSpalte(void)
 {
  QString ITBereich[22] ={
  "99", "99", "1", "2", "3", "4", "5",  "6", "7", "8", "9", "10", "11", "12", "13", "14","15","16","17", "18","0","01"};
  int slei;

   for (slei = 0; slei <= 21; slei++)
    {
     // vergleicht die zwei Strings miteinander, bei Übereinstimmung Rückgabewert = 0
     if(ITBereich[slei].compare(bohrtoleranzgrad) == 0)
      {
       bohrITBreiteSpalte = slei;
       break;
      }
    }
 }


// Sucht die Toleranzbreite
 double FitDimensions::getBohrITToleranz(void)
   {
     //Grundtoleranzen
   double ITBreite[22][22]= {
       // 0    1    2    3    4   5   6    7    8    9   10   11    12    13    14    15    16     17     18     19   21   22
         {0,    0,   1,   2,   3,  4,  5,   6,   7,   8,   9,  10,   11,   12,   13,   14,   15,    16,    17,    18,   0, 0.1},
         {1,    3, 0.8, 1.2,   2,  3,  4,   6,  10,  14,  25,  40,   60,  100,  140,  250,  400,   600,  1000,  1400, 0.3, 0.5},
         {3,    6,   1, 1.5, 2.5,  4,  5,   8,  12,  18,  30,  48,   75,  120,  180,  300,  480,   750,  1200,  1800, 0.4, 0.6},
         {6,   10,   1, 1.5, 2.5,  4,  6,   9,  15,  22,  36,  58,   90,  150,  220,  360,  580,   900,  1500,  2200, 0.4, 0.6},
        {10,   18, 1.2,   2,   3,  5,  8,  11,  18,  27,  43,  70,  110,  180,  270,  430,  700,  1100,  1800,  2700, 0.5, 0.8},
        {18,   30, 1.5, 2.5,   4,  6,  9,  13,  21,  33,  52,  84,  130,  210,  330,  520,  840,  1300,  2100,  3300, 0.6,   1},
        {30,   50, 1.5, 2.5,   4,  7, 11,  16,  25,  39,  62, 100,  160,  250,  390,  620, 1000,  1600,  2500,  3900, 0.6,   1},
        {50,   80,   2,   3,   5,  8, 13,  19,  30,  46,  74, 120,  190,  300,  460,  740, 1200,  1900,  3000,  4600, 0.8, 1.2},
        {80,  120, 2.5,   4,   6, 10, 15,  22,  35,  54,  87, 140,  220,  350,  540,  870, 1400,  2200,  3500,  5400,   1, 1.5},
       {120,  180, 3.5,   5,  10, 12, 18,  25,  40,  63, 100, 100,  250,  400,  630, 1000, 1600,  2500,  4000,  6300, 1.2,   2},
       {180,  250, 4.5,   7,  12, 14, 20,  29,  46,  72, 115, 185,  290,  460,  720, 1150, 1850,  2900,  4600,  7200,   2,   3},
       {250,  315,   6,   8,  12, 16, 23,  32,  52,  81, 130, 210,  320,  520,  810, 1300, 2100,  3200,  5200,  8100, 2.5,   4},
       {315,  400,   7,   9,  13, 18, 25,  36,  57,  89, 140, 230,  360,  570,  890, 1400, 2300,  3600,  5700,  8900,   3,   5},
       {400,  500,   8,  10,  15, 20, 27,  40,  63,  97, 155, 250,  400,  630,  970, 1550, 2500,  4000,  6300,  9700,   4,   6},
       {500,  630,   9,  11,  16, 22, 32,  44,  70, 110, 175, 280,  440,  700, 1100, 1750, 2800,  4400,  7000, 11000,   0,   0},
       {630,  800,  10,  13,  18, 25, 36,  50,  80, 125, 200, 320,  500,  800, 1250, 2000, 3200,  5000,  8000, 12500,   0,   0},
       {800, 1000,  11,  15,  21, 28, 40,  56,  90, 140, 230, 360,  560,  900, 1400, 2300, 3600,  5600,  9000, 14000,   0,   0},
      {1000, 1250,  13,  18,  24, 33, 47,  66, 105, 165, 260, 420,  660, 1050, 1650, 2600, 4200,  6600, 10500, 16500,   0,   0},
      {1250, 1600,  15,  21,  29, 39, 55,  78, 125, 195, 310, 500,  780, 1250, 1950, 3100, 5000,  7800, 12500, 19500,   0,   0},
      {1600, 2000,  18,  25,  35, 46, 65,  92, 150, 230, 370, 600,  920, 1500, 2300, 3700, 6000,  9200, 15000, 23000,   0,   0},
      {2000, 2500,  22,  30,  41, 55, 78, 110, 175, 280, 440, 700, 1100, 1750, 2800, 4400, 7000, 11000, 17500, 28000,   0,   0},
      {2500, 3150,  26,  36,  50, 68, 96, 135, 210, 330, 540, 860, 1350, 2100, 3300, 5400, 8600, 13500, 21000, 33000,   0,   0}};

    int slei;
    double ug, og, toleranz = 0;

    for (slei = 0; slei <= 21; slei++)
     {
      ug = ITBreite[slei][0];
      og = ITBreite[slei][1];
      toleranz = ITBreite[slei][bohrITBreiteSpalte];
      if ((bohrnennmass > ug) &&(bohrnennmass <= og))
        break;
     }

    return(toleranz / 1000);
 }


 void FitDimensions::getbohrungbeginn(void)
 {

//Bei Grundabmaß M wird nur delta dazugezählt, wenn der Tolaranzgrad <= 8 ist
 //Bei K7 im Bereich 18 bis 30 mm: delta ist 8 µm, deshalb ist ES = -2µm +8µm = 6µm
 //          A    B    C    CD  D   E    EF   F   FG G  H   JS    J6   J7   J8 "K<=8 K>8  M  N<=8  N>8   P    R     S    T      U    V    X    Y     Z    ZA     ZB    ZC
 // 0    1   2    3    4    5   6   7    8    9   10 11 12  13    14   15   16  17   18  19   20   21   22   23    24    25    26   27   28   29     30    31    32    33
short Bohrungen[41][34] =   {
   {0,   3, 270, 140,  60,  34, 20, 14,  10,  6,   4, 2,0, 7777,   2,   4,   6, 0,   0, -2,  -4,  -4,  -6, -10,  -14, 9999,  -18,9999, -20, 9999,  -26,  -32,  -40,  -60},
   {3,   6, 270, 140,  70,  46, 30, 20,  14, 10,   6, 4,0, 7777,   5,   6,  10,-1,   0, -4,  -8,   0, -12, -15,  -19, 9999,  -23,9999, -29, 9999,  -35,  -42,  -50,  -80},
   {6,  10, 280, 150,  80,  56, 40, 25,  18, 13,   8, 5,0, 7777,   5,   8,  12,-1,   0, -6, -10,   0, -15, -19,  -23, 9999,  -28,9999, -34, 9999,  -42,  -52,  -67,  -97},
  {10,  14,-290, 150,  95,9999, 50, 32,9999, 16,9999, 6,0, 7777,   6,  10,  15,-1,   0, -7, -12,   0, -18, -23,  -28, 9999,  -33,9999, -40, 9999,  -50,  -64,  -90, -130},
  {14,  18,-290, 150,  95,9999, 50, 32,9999, 16,9999, 6,0, 7777,   6,  10,  15,-1,   0, -7, -12,   0, -18, -23,  -28, 9999,  -33,9999, -45, 9999,  -60,  -77, -108, -150},
  {18,  24, 300, 160, 110,9999, 65, 40,9999, 20,9999, 7,0, 7777,   8,  12,  20,-2,   0, -8, -15,   0, -22, -28,  -35, 9999,  -41, -47, -54,  -63,  -73,  -98, -136, -188},
  {24,  30, 300, 160, 110,9999, 65, 40,9999, 20,9999, 7,0, 7777,   8,  12,  20,-2,   0, -8, -15,   0, -22, -28,  -35,  -41,  -48, -55, -64,  -75,  -88, -118, -160, -218},
  {30,  40, 310, 170, 120,9999, 80, 50,9999, 25,9999, 9,0, 7777,  10,  14,  24,-2,   0, -9, -17,   0, -26, -34,  -43,  -48,  -60, -68, -80,  -94, -112, -149, -200, -274},
  {40,  50, 320, 180, 130,9999, 80, 50,9999, 25,9999, 9,0, 7777,  10,  14,  24,-2,   0, -9, -17,   0, -26, -34,  -43,  -54,  -70, -81, -97, -114, -136, -180, -242, -325},
  {50,  65, 340, 190, 140,9999,100, 60,9999, 30,9999,10,0, 7777,  13,  18,  28,-2,   0,-11, -20,   0, -32, -41,  -53,  -55,  -87,-102,-122, -144, -172, -226, -300, -405},
  {65,  80, 360, 200, 150,9999,100, 60,9999, 30,9999,10,0, 7777,  13,  18,  28,-2,   0,-11, -20,   0, -32, -43,  -59,  -75, -102,-120,-146, -174, -210, -274, -360, -580},
  {80, 100, 380, 220, 170,9999,120, 72,9999, 36,9999,12,0, 7777,  16,  22,  34,-3,   0,-13, -23,   0, -37, -51,  -71,  -91, -124,-146,-178, -214, -258, -335, -445, -585},
 {100, 120, 410, 240, 180,9999,120, 72,9999, 36,9999,12,0, 7777,  16,  22,  34,-3,   0,-13, -23,   0, -37, -54,  -79, -104, -144,-172,-210, -254, -310, -400, -525, -690},
 {120, 140, 460, 260, 200,9999,145, 85,9999, 43,9999,14,0, 7777,  18,  26,  41,-3,   0,-15, -27,   0, -43, -63,  -92, -122, -170,-202,-248, -300, -365, -470, -620, -800},
 {140, 160, 520, 290, 210,9999,145, 85,9999, 43,9999,14,0, 7777,  18,  26,  41,-3,   0,-15, -27,   0, -43, -65, -100, -134, -190,-228,-290, -340, -415, -535, -700, -900},
 {160, 180, 580, 310, 230,9999,145, 85,9999, 43,9999,14,0, 7777,  18,  26,  41,-3,   0,-15, -27,   0, -43, -68, -108, -146, -210,-252,-310, -380, -465, -600, -790,-1000},
 {180, 200, 660, 340, 240,9999,170,100,9999, 50,9999,15,0, 7777,  22,  30,  47,-4,   0,-17, -31,   0, -50, -77, -122, -166, -236,-284,-350, -425, -520, -670, -880,-1150},
 {200, 225, 740, 380, 260,9999,170,100,9999, 50,9999,15,0, 7777,  22,  30,  47,-4,   0,-17, -31,   0, -50, -80, -130, -180, -258,-310,-385, -470, -575, -740, -960,-1250},
 {225, 250, 820, 420, 280,9999,170,100,9999, 50,9999,15,0, 7777,  22,  30,  47,-4,   0,-17, -31,   0, -50, -84, -140, -196, -294,-340,-425, -520, -640, -820,-1050,-1350},
 {250, 280, 920, 480, 300,9999,190,110,9999, 56,9999,17,0, 7777,  25,  36,  55,-4,   0,-20, -34,   0, -56, -94, -158, -218, -315,-385,-475, -580, -710, -920,-1200,-1550},
 {280, 315,1050, 540, 330,9999,190,110,9999, 56,9999,17,0, 7777,  25,  36,  55,-4,   0,-20, -34,   0, -56, -98, -170, -240, -350,-425,-525, -650, -790,-1000,-1300,-1700},
 {315, 355,1200, 600, 360,9999,210,125,9999, 62,9999,18,0, 7777,  29,  39,  60,-4,   0,-21, -37,   0, -62,-108, -190, -268, -390,-475,-590, -730, -900,-1150,-1500,-1900},
 {355, 400,1350, 680, 400,9999,210,125,9999, 62,9999,18,0, 7777,  29,  39,  60,-4,   0,-21, -37,   0, -62,-114, -208, -294, -435,-530,-660, -830,-1000,-1300,-1650,-2100},
 {400, 450,1500, 760, 440,9999,230,135,9999, 68,9999,20,0, 7777,  33,  43,  66,-5,   0,-23, -40,   0, -68,-126, -232, -330, -490,-595,-740, -920,-1100,-1450,-1850,-2400},
 {450, 500,1650, 840, 480,9999,230,135,9999, 68,9999,20,0, 7777,  33,  43,  66,-5,   0,-23, -40,   0, -68,-132, -252, -360, -540,-660,-820,-1000,-1250,-1600,-2100,-2600},
 {500, 560,9999,9999,9999,9999,260,145,9999, 76,9999,22,0, 7777,9999,9999,9999, 0,9999,-26, -44, -44, -78,-150, -280, -400, -600,9999,9999, 9999, 9999, 9999, 9999, 9999},
 {560, 630,9999,9999,9999,9999,260,145,9999, 76,9999,22,0, 7777,9999,9999,9999, 0,9999,-26, -44, -44, -78,-155, -310, -450, -660,9999,9999, 9999, 9999, 9999, 9999, 9999},
 {630, 710,9999,9999,9999,9999,290,160,9999, 80,9999,24,0, 7777,9999,9999,9999, 0,9999,-30, -50, -50, -88,-175, -340, -500, -740,9999,9999, 9999, 9999, 9999, 9999, 9999},
 {710, 800,9999,9999,9999,9999,290,160,9999, 80,9999,24,0, 7777,9999,9999,9999, 0,9999,-30, -50, -50, -88,-185, -380, -560, -840,9999,9999, 9999, 9999, 9999, 9999, 9999},
 {800, 900,9999,9999,9999,9999,320,170,9999, 86,9999,26,0, 7777,9999,9999,9999, 0,9999,-34, -56, -56,-100,-210, -430, -620, -940,9999,9999, 9999, 9999, 9999, 9999, 9999},
 {900,1000,9999,9999,9999,9999,320,170,9999, 86,9999,26,0, 7777,9999,9999,9999, 0,9999,-34, -56, -56,-100,-220, -470, -680,-1050,9999,9999, 9999, 9999, 9999, 9999, 9999},
{1000,1120,9999,9999,9999,9999,350,195,9999, 98,9999,28,0, 7777,9999,9999,9999, 0,9999,-40, -66, -66,-120,-250, -520, -780,-1150,9999,9999, 9999, 9999, 9999, 9999, 9999},
{1120,1250,9999,9999,9999,9999,350,195,9999, 98,9999,28,0, 7777,9999,9999,9999, 0,9999,-40, -66, -66,-120,-260, -580, -840,-1300,9999,9999, 9999, 9999, 9999, 9999, 9999},
{1250,1400,9999,9999,9999,9999,390,220,9999,110,9999,30,0, 7777,9999,9999,9999, 0,9999,-48, -78, -78,-140,-300, -640, -960,-1450,9999,9999, 9999, 9999, 9999, 9999, 9999},
{1400,1600,9999,9999,9999,9999,390,220,9999,110,9999,30,0, 7777,9999,9999,9999, 0,9999,-48, -78, -78,-140,-330, -720,-1050,-1600,9999,9999, 9999, 9999, 9999, 9999, 9999},
{1600,1800,9999,9999,9999,9999,430,240,9999,120,9999,32,0, 7777,9999,9999,9999, 0,9999,-58, -92, -92,-170,-370, -820,-1200,-1850,9999,9999, 9999, 9999, 9999, 9999, 9999},
{1800,2000,9999,9999,9999,9999,430,240,9999,120,9999,32,0, 7777,9999,9999,9999, 0,9999,-58, -92, -92,-170,-400, -920,-1350,-2000,9999,9999, 9999, 9999, 9999, 9999, 9999},
{2000,2240,9999,9999,9999,9999,480,260,9999,130,9999,34,0, 7777,9999,9999,9999, 0,9999,-68,-110,-110,-195,-440,-1000,-1500,-2300,9999,9999, 9999, 9999, 9999, 9999, 9999},
{2240,2500,9999,9999,9999,9999,480,260,9999,130,9999,34,0, 7777,9999,9999,9999, 0,9999,-68,-110,-110,-195,-440,-1100,-1650,-2500,9999,9999, 9999, 9999, 9999, 9999, 9999},
{2500,2800,9999,9999,9999,9999,520,290,9999,145,9999,38,0, 7777,9999,9999,9999, 0,9999,-76,-135,-135,-240,-550,-1250,-1900,-2900,9999,9999, 9999, 9999, 9999, 9999, 9999},
{2800,3150,9999,9999,9999,9999,520,290,9999,145,9999,38,0, 7777,9999,9999,9999, 0,9999,-76,-135,-135,-240,-580,-1400,-2100,-3200,9999,9999, 9999, 9999, 9999, 9999, 9999}};

 short zeile;
 short ug, og;
 double rewer = 0;

 for (zeile = 0; zeile < 41; zeile++)
  {
   ug = Bohrungen[zeile][0];
   og = Bohrungen[zeile][1];
   if ((bohrnennmass > ug) && (bohrnennmass <= og))
    {
     rewer = static_cast<double>(Bohrungen[zeile][bohrspalte + 2]);
     if ((rewer >= 7776) && (rewer <= 7777)) rewer = bohrtolerbreite / 2; // Bei js-Passungen
      else rewer /= 1000;
     break;
    }
   }
 // Ausnahmeregelungen für Delta
 if ((bohrspalte == 15) || (bohrspalte == 16)) // 15 bis 16 ist bei bohrspalte für == 'K'
 {
  if ((bohrinttoleranzgrad == 7) && (bohrnennmass >= 18) && (bohrnennmass <= 30)) deltawert = 0.008;
  if (bohrinttoleranzgrad <= 8) rewer += deltawert;
 }
 if (bohrspalte == 17)  // 17 ist bei bohrspalte für == 'M'
 {
  if ((bohrinttoleranzgrad == 6) && (bohrnennmass >= 250) && (bohrnennmass <= 315)) deltawert = 0.011;
  if (bohrinttoleranzgrad <= 8) rewer += deltawert;
 }
 if (bohrspalte == 22) // 22 ist bei bohrspalte für == 'S'
 {
  if ((bohrinttoleranzgrad == 6) && (bohrnennmass >= 18) && (bohrnennmass <= 30)) deltawert = 0.004;
   rewer += deltawert;
 }
 bohrbeginn = rewer;
}

 // Rechewnrichtung Einheitsbohrung bestimmen
 void FitDimensions::getcalcdirectionbohrung(void)
     {
      int direction = 0;

      //Bei -1 ist Rechenrichtung ins Minus, bei +1 ins Plus
      if ((bohrspalte  >= 0) && (bohrspalte <= 10)) direction = 1; // 0 ist A, H ist 10 bei bohrspalte
      if ((bohrspalte >= 11) && (bohrspalte <= 31)) direction = -1;
      if (bohrspalte == 11) direction = 0;  // 11 ist bei bohrspalte JS

      bohrrechenrichtung = direction;
     }


 void FitDimensions::bohrungende(void)
     {
      double rewer = 0;
      if (bohrrechenrichtung ==  1) rewer = bohrbeginn + bohrtolerbreite;
      if (bohrrechenrichtung == -1) rewer = bohrbeginn - bohrtolerbreite;
      if (bohrrechenrichtung ==  0) rewer = bohrbeginn - bohrtolerbreite;
       bohrende = rewer;
     }

 // Bohrbeginn und Ende festlegen
 void FitDimensions::sortESEI(void)
 {
  double es, ei;
/*
  if (bohrbeginn > bohrende)
   {
    es = bohrbeginn;
    ei = bohrende;
    }
     else
      {
      ei = bohrbeginn;
      es = bohrende;
      }*/
  ei = bohrbeginn < bohrende ? bohrbeginn : bohrende;
  es = bohrbeginn > bohrende ? bohrbeginn : bohrende;
  bohrbeginn = es;
  bohrende = ei;
 }

 void FitDimensions::on_pB_Dialog_clicked()
 {
   //Modal aproach
   //Dialog fensterb;
   Dialog *fensterb = new Dialog(this);
   fensterb->setModal(true);
   //connect(&fensterb, SIGNAL(sendSignal()), this, SLOT(setSlots())); //the important part
   fensterb->exec();

 }

 void FitDimensions::on_pB_gewinde_clicked()
 {
   //Modal aproach
   //Dialog fensterb;
   GewindeM *fensterc = new GewindeM(this);
   fensterc->setModal(true);
   //connect(&fensterb, SIGNAL(sendSignal()), this, SLOT(setSlots())); //the important part
   fensterc->exec();

 }

