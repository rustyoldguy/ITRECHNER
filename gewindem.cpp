#include "gewindem.h"
#include "ui_gewindem.h"

GewindeM::GewindeM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GewindeM)
{
    ui->setupUi(this);
    this->setWindowTitle("IT-Passungsrechner V1.01");
    this->move(150,100); //Setzt die Widget-Ausgabeposition

    ui->nennmass_in -> setText("10");
      //ui->steigungin -> setText("1.5");  Wurde vorwählbare Werte umgestellt, um fehlerhafte Eingaben zu vermeiden

      ui->steigung->addItem("1.5");      //1
      ui->steigung->addItem("0.2");
      ui->steigung->addItem("0.25");
      ui->steigung->addItem("0.3");
      ui->steigung->addItem("0.35");     //5
      ui->steigung->addItem("0.4");
      ui->steigung->addItem("0.45");
      ui->steigung->addItem("0.5");
      ui->steigung->addItem("0.6");
      ui->steigung->addItem("0.7");     //10
      ui->steigung->addItem("0.75");
      ui->steigung->addItem("0.8");
      ui->steigung->addItem("1");
      ui->steigung->addItem("1.25");
      ui->steigung->addItem("1.75");    //15
      ui->steigung->addItem("2");
      ui->steigung->addItem("2.5");
      ui->steigung->addItem("3");
      ui->steigung->addItem("3.5");
      ui->steigung->addItem("0.3");     //20
      ui->steigung->addItem("4");
      ui->steigung->addItem("5");
      ui->steigung->addItem("5.5");
      ui->steigung->addItem("6");
      ui->steigung->addItem("8");

      ui->GaAussenD->addItem("g");
      ui->GaAussenD->addItem("a");
      ui->GaAussenD->addItem("b");
      ui->GaAussenD->addItem("c");
      ui->GaAussenD->addItem("d");
      ui->GaAussenD->addItem("e");
      ui->GaAussenD->addItem("f");
      ui->GaAussenD->addItem("h");

      ui->ITAussenD->addItem("6");
      ui->ITAussenD->addItem("4");
      ui->ITAussenD->addItem("8");

      ui->ITd2->addItem("6");
      ui->ITd2->addItem("01");
      ui->ITd2->addItem("0");
      ui->ITd2->addItem("1");
      ui->ITd2->addItem("2");
      ui->ITd2->addItem("3");
      ui->ITd2->addItem("4");
      ui->ITd2->addItem("5");
      ui->ITd2->addItem("7");
      ui->ITd2->addItem("8");
      ui->ITd2->addItem("9");

      ui->ITd3->addItem("6");
      ui->ITd3->addItem("3");
      ui->ITd3->addItem("4");
      ui->ITd3->addItem("5");
      ui->ITd3->addItem("7");
      ui->ITd3->addItem("8");

      ui->GAInnen->addItem("H");
      ui->GAInnen->addItem("G");

      ui->ITD1_out->addItem("6");
      ui->ITD1_out->addItem("4");
      ui->ITD1_out->addItem("5");
      ui->ITD1_out->addItem("7");
      ui->ITD1_out->addItem("8");

      ui->ITD2_out->addItem("6");
      ui->ITD2_out->addItem("02");
      ui->ITD2_out->addItem("01");
      ui->ITD2_out->addItem("0");
      ui->ITD2_out->addItem("1");
      ui->ITD2_out->addItem("2");
      ui->ITD2_out->addItem("3");
      ui->ITD2_out->addItem("4");
      ui->ITD2_out->addItem("5");
      ui->ITD2_out->addItem("7");
      ui->ITD2_out->addItem("8");

      ui->Nx_in->addItem("0");
      ui->Nx_in->addItem("3.3");
      ui->Nx_in->addItem("2.1");
      ui->Nx_in->addItem("1.5");


 connect(ui->rechne,    SIGNAL(clicked()),   this, SLOT(berechnen() ) );
 connect(ui->finito,    SIGNAL (clicked()),  this, SLOT (close()));
}

GewindeM::~GewindeM()
{
    delete ui;
}

void GewindeM::GetGewindeWerte(void)
{
 da = (ui->nennmass_in -> text()).toDouble();      // Nenndurchmesser
 Steigung_in = ui->steigung -> currentText();      // Steigung
 P = Steigung_in.toDouble();                   // QString zu double-Wert

 //Werte für Aussengewinde
 GrndAbmassAussenD = ui->GaAussenD->currentText(); // Einlesen Grundabmass für Aussendurchmesser Aussengewinde (Vergleich als Letter, keine Umwandlung zu double nötig)
 ITGradBolzenD = ui->ITAussenD->currentText();     // Einlesen IT-Grad für Aussendurchmesser Aussengewinde (Zahl Umwandlung nötig)
 ITd2Wertstr = ui->ITd2->currentText();            // Einlesen des Toleranzgrades für Flankendurchmessers Aussengewinde (Vergleich als Letter, keine Umwandlung zu double nötig)
 ITd3Wertstr = ui->ITd3->currentText();            // Einlesen des Toleranzgrades für Kerndurchmesser Aussengewinde

 ITBolzenD = ITGradBolzenD.toDouble();  // QString zu double-Wert
 ITd3Wert = ITd3Wertstr.toDouble();     // QString zu double-Wert

 // Werte für Aussen- und Innengewinde einlesen
 GAInnenstr = ui->GAInnen->currentText();  // Einlesen des Grundabmaßes Innengewinde
 ITD1str = ui->ITD1_out->currentText();    // Einlesen des IT-Grades des Kerndurchmessers Innengewinde
 ITD2str = ui->ITD2_out->currentText();    // Einlesen des Iif(ITd2Wertstr.compare(ITGrad[slei]) == 0) MKN = 0;T-Grades des Flankendurchmessers Innengewinde
 Nabpl = ui->Nx_in->currentText();        // Einlesen des IT-Grades des Flankendurchmessers Innengewinde

 ITD1Wert = ITD1str.toDouble();        // QString zu double-Wert
 ITD2Wert = ITD2str.toDouble();        // QString zu double-Wert
 Nx = Nabpl.toDouble();                // QString zu double-Wertouble();                 // QString zu double-Wert

}


void GewindeM::CalcGewindewerte(void)
{
 // theoretische Werte für Aussen- und Innengewinde berechnen
 d2atheo = da - 0.649519052838329 * P;       // theoretischer Flankendurchmesser
 d3a = da - 1.22686932202796 * P;            // theoretischer Kernurchmesser des Aussengewindes
 R = 0.144337567 * P;                             // Rundung am Kerndurchmesser des Aussengewindes
 D1i = da - 1.082531755 * P;                      // theoretischer Kerndurchmesser des Innengewindes
 S = ((d2atheo + d3a) / 2) * ((d2atheo + d3a) / 2) * pi / 4;   // Spannungsquerschnitt S in mm²
 bohrerd = da - P;                           // Bohrerdurchmesser für Kerngewinde

  // Ermittle Toleranzwerte für Aussengewinde
 SucheA0Werte();       // Voraussetzung: Steigung und Grundabmass Aussendurchmesser
 SucheTdWerte();       // Voraussetzung: Steigung und IT-Grad Aussendurchmesser Aussengewinde
 SucheTd2Wert();       // Voraussetzung: Steigung und Toleranzgrad des Flankendurchmessers Aussengewinde
 SucheTd3Wert();       // Voraussetzung: Steigung und Toleranzgrad des Kerndurchmessers Aussengewinde

 A0Wert /= 1000;      // Umrechnung von µm in mm
 TdWert /= 1000;      // Umrechnung von µm in mm
 Td2Wert /= 1000;     // Umrechnung von µm in mm
 Td3Wert /= 1000;     // Umrechnung von µm in mm
 Rmin /= 1000;        // Umrechnung von µm in mm

 damax = da + A0Wert;       // maximaler Aussendurchmesser Aussengewinde
 damin = damax - TdWert;    // minimaler Aussendurchmesser Aussengewinde TD-Wert ist Toleranz für Aussendurchmesser Aussengewinde
 d2max = d2atheo + A0Wert;  // maximaler Flankendurchmesser Aussengewinde
 d2min = d2max -Td2Wert;    // minimaler Flankendurchmesser Aussengewinde
 d3max = d3a + A0Wert;      // maximaler Kerndurchmesser Aussengewinde
 d3min = d3max - Td3Wert;   // minimaler Kerndurchmesser Aussengewinde

 // Innengewindeberechnung

 // Ermittle Toleranzwerte für Innengewinde
 SucheAuWert();    // Vorraussetzung: Steigung und Grundabmass für Innengewinde (G oder H)
 SucheTD1Wert();   // Vorraussetzung: Steigung und IT-Toleranzgrad für Kerndurchmesser Innengewinde (4,5,6,7,8)
 SucheTD2Wert();   // Vorraussetzung: Steigung und IT-Toleranzgrad für Flankendurchmesser Innengewinde (02,02,0,1,2,3,4,5,6,7,8)

 AuWert /= 1000;   // Umrechnung von µm in mm
 TD1Wert /= 1000;  // Umrechnung von µm in mm
 TD2Wert /= 1000;  // Umrechnung von µm in mm

 D1imin = D1i + AuWert;         // minimaler Kerndurchmesser Innengewinde
 D1imax = D1imin + TD1Wert;     // maximaler Kerndurchmesser Innengewinde
 D2imin = d2atheo + AuWert;     // minimaler Flankendurchmesser Innengewinde
 D2imax = D2imin + TD2Wert;     // maximaler Kerndurchmesser Innengewinde
}

// Suche den A0-Wert
 void GewindeM::SucheA0Werte(void) //double Steigung, double Grundabmass)
 {
 char Ga[9][4] = { "z", "a", "b", "c", "d",	"e", "f", "g", "h"};
 int slei, zeile = 0, spalte = 0;
 //double rewer = 0;

 double A0[25][9] =
  {
 // in mm"a	      b	       c	  d	    e	    f	     g	    h
{0.2,	0,	      0,	   0,	  0,	-45,	-32,	-17,	0},    // 1
{0.25,	0,	      0,       0,	  0,	-45,	-33,	-18,	0},
{0.3,	0,	      0,	   0,	  0,	-46,	-33,	-18,	0},
{0.35,	0,	      0,	   0,	  0,	-46,	-34,	-19,	0},
{0.4,	0,	      0,	-120,	-72,	-48,	-34,	-19,	0},    //5
{0.45,	0,	      0,	-120,	-73,	-48,	-35,	-20,	0},
{0.5,	0,	      0,	-122,	-74,	-50,	-36,	-20,	0},
{0.6,	0,	      0,	-124,	-76,	-53,	-36,	-21,	0},
{0.7,	0,	      0,	-125,	-78,	-56,	-38,	-22,	0},
{0.75,	0,	      0,	-126,	-79,	-56,	-38,	-22,	0},    //10
{0.8,	0,	      0,	-127,	-80,	-60,	-38,	-24,	0},
{1,	   -290,	-200,	-130,	-85,	-60,	-40,	-26,	0},
{1.25,	-295,	-205,	-135,	-90,	-63,	-42,	-28,	0},
{1.5,	-300,	-212,	-140,	-95,	-67,	-45,	-32,	0},
{1.75,	-310,	-220,	-145,	-100,	-71,	-48,	-34,	0},    //15
{2,	    -315,	-225,	-156,	-105,	-71,	-52,	-38,	0},
{2.5,	-325,	-235,	-160,	-110,	-80,	-58,	-42,	0},
{3,	    -335,	-245,	-170,	-115,	-85,	-63,	-48,	0},
{3.5,	-345,	-255,	-180,	-125,	-90,	-70,	-53,	0},
{4,	    -355,	-265,	-190,	-130,	-95,	-75,	-60,	0},   //20
{4.5,	-365,	-280,	-200,	-135,	-100,	-80,	-63,	0},
{5,	    -375,	-290,	-212,	-140,	-106,	-85,	-71,	0},
{5.5,	-385,	-300,	-224,	-150,	-112,	-90,	-75,	0},
{6,  	-395,	-310,	-236,	-155,	-118,	-95,	-80,	0},
{8,	   -425,	-340,	-265,	-180,	-140,	-118,	-100,	0}
};

 for (slei = 0; slei < 25; slei++)
   {
    if (A0[slei][0] == P)
     {
      zeile = slei;
      break;
     }
   }


 for (slei = 0; slei < 9; slei++)
   {
     if(GrndAbmassAussenD.compare(Ga[slei]) == 0)
      {
       spalte = slei;
       break;
      }
   }

 A0Wert = A0[zeile][spalte];

}

 // Suche den Td-Wert
 void GewindeM::SucheTdWerte(void) //double Steigung, double Toleranzgrad)
  {
  int slei, zeile, spalte;
  //double rewer = 0;

  // Toleranz Nenndurchmesser Aussengewinde
 double Td[26][4] = {
 {0,      4,    6,  8},
 {0.2,	36,    56,	0},
 {0.25,	42,    67,  0},
 {0.3,	48,    75,  0},
 {0.35,	53,    85,	0},
 {0.4,	60,    95,  0},
 {0.45,	63,   100,	0},
 {0.5,	67,   106,	0},
 {0.6,	80,   125,	0},
 {0.7,	90,	  140,	0},
 {0.75,	90,	  140,	0},
 {0.8,  95,   150,	236},
 {1,   112,   180,	280},
 {1.25, 132,  212,	335},
 {1.5,  150,  236,	375},
 {1.75, 170,  265,	425},
 {2,    180,  280,	450},
 {2.5,  212,  335,	530},
 {3,   236,   375,	600},
 {3.5,  265,  425,	670},
 {4,   300,	  475,	750},
 {4.5,  315,  500,	800},
 {5,	335,  530,	850},
 {5.5,  355,  560,	900},
 {6,    375,  600,	950},
 {8,   450,	  710,	1180}
 };

  zeile = spalte = 0;

  for (slei = 1; slei < 26; slei++)
   {
    if (Td[slei][0] == P)
     {
      zeile = slei;
      break;
     }
   }


  for (slei = 0; slei < 4; slei++)
   {
    if (ITBolzenD == Td[0][slei])
     {
      spalte = slei;
      break;
     }
   }

  TdWert = Td[zeile][spalte];

 }

 // Funktion nur für Aussengewinde
  void GewindeM::SucheTd2Wert(void)
  {
   int slei, zeile = 0, spalte = 0;
   char ITGrad[11][5] = {"01", "0", "1",	"2", "3", "4", "5",	"6", "7", "8", "9"};

   // Toleranz Flankendurchmesser Aussengewinde
  double Td2[76][14] = {
  // 0     1       2      3     4     5   6   7   8        9      10      11      12      13
  // IT-Grad             01   0      1	2   3   4       5       6       7,      8,      9
  {-1,     -2,    0,  0.1,    0,	1,	2,  3,  4,	    5,	    6,	      7,	 8,   	  9},    // 0
  {0.99,  1.4,	0.2,	0,	  0,	0,	19,	24,	30,	    38,	    48,	      0,	 0,	      0},
  {0.99,  1.4,	0.25,	0,	  0,	17,	21,	26,	34,	    42,	    53,	      0,	 0,	      0},
  {0.99,  1.4,	0.3,	0,	  0,	18,	22,	28,	36,	    45,	    56,	      0,	 0,	      0},
  {1.4,	  2.8,	0.2,	0,	  0,	0,	20,	25,	32,	    40,	    50,	      0,	 0,	      0},
  {1.4,	  2.8,	0.25,	0,	  0,	18,	22,	28,	36,	    45,	    56,	      0,	 0,	      0},
  {1.4,	  2.8,	0.35,	0,	  0,	20,	25,	32,	40,	    50,	    63,	     80,	 0,	      0},
  {1.4,	  2.8,	0.4,	0,	  0,	21,	26,	34,	42, 	53,	    67,	     85,	 0,	      0},
  {1.4,	  2.8,	0.45,	0,	  0,	22,	28,	36,	45,	    56,	    71,	     90,	 0,	      0},
  {2.8,	  5.6,	0.2,	0,	  0,	0,	21,	26,	34,	    42,	    53,	      0,	 0,   	  0},
  {2.8,	  5.6,	0.25,	0,	  0,	19,	24,	30,	38,	    48,	    60,	      0,	 0,   	  0},    // 10
  {2.8,	  5.6,	0.35,	0,	  0,	21,	26,	34,	42,	    53,	    67,	     85,	 0,   	  0},
  {2.8,	  5.6,	 0.5,	0,	  0,	24,	30,	38,	48,	    60,	    75,	     95,	 0,	      0},
  {2.8,	  5.6,	 0.6,	0,	  21,	26,	34,	42,	53,	    67,	    85,	    106,	 0,	      0},
  {2.8,	  5.6,	 0.7,	0,	  22,	28,	36,	45,	56,	    71,	    90,	    112,	 0,	      0},
  {2.8,	  5.6,	0.75,	0,	  22,	28,	36,	45,	56,	    71,	    90,	    112,	 0,	      0},
  {2.8,	  5.6,	 0.8,	0,	  24,	30,	38,	48,	60,	    75,	    95,	    118,   150,	    190},
  {5.6,	 11.2,	 0.2,	0,	  0,	0,	22,	28,	36,	    45,	    56,	      0,	 0,	      0},
  {5.6,	 11.2,	0.25,	0,	  0,	20,	25,	32,	40,	    50,	    63,  	  0,	 0,   	  0},
  {5.6,	 11.2,	0.35,	0,	  0,	22,	28,	36,	45,	    56,	    71,	      0,	 0,	      0},
  {5.6,	 11.2,	 0.5,	0,	  0,	26,	34,	42,	53,	    67,	    85,	    106,	 0,       0},    //20
  {5.6,	 11.2,	0.75,	0,	  22,	32,	40,	50,	63,	    80,	    100,	125,	 0,	      0},
  {5.6,	 11.2,	   1,  22,	  28,	36,	45,	56,	71,	    90,	    112,	140,    180,	224},
  {5.6,	 11.2,	1.25,  24,	  30,	38,	48,	60,	75,	    95,	    118,	150,	190,	236},
  {5.6,	 11.2,	 1.5,  26,	  34,	0,	0,	0,	85,	    106,	132,	170,	212,	265},
  {11.2, 22.4,	0.35,	0,	  20,	25,	32,	40,	50,	    63,	    80,	      0,      0,	  0},   // 25
  {11.2, 22.4,	 0.5,	0,	  22,	28,	36,	45,	56,	    71,	    90,	      0,	  0,	  0},
  {11.2, 22.4,	0.75,  21,	  26,	34,	42,	53,	67,	    85,	    106,	132,	  0,      0},
  {11.2, 22.4,	   1,  24,	  30,	38,	48,	60,	75,	    95,	    118,	150,	190,	236},
  {11.2, 22.4,	1.25,  26,	  34,	42,	53,	67,	85,	    106,	132,	170,	212,	265},
  {11.2, 22.4,	 1.5,	0,	  0,	0,	0,	0,	90,	    112,	140,	180,	224,	280},
  {11.2, 22.4,	1.75,	0,	  0,	0,	0,	0,	95,	    118,	150,	190,	236,	300},
  {11.2, 22.4,	   2,   0,	  0,	0,	0,	0,	100,	125,	160,	200,	250,	315},
  {11.2, 22.4,	 2.5,	0,	  0,	0,	0,	0,	106,	132,	170,	212,	265,	335},
  {22.4,   45,	0.35,	0,	  21,	26,	34,	42,	53,	    67,	    85,	      0,      0,	  0},
  {22.4,   45,   0.5,	0,	  24,	30,	38,	48,	60,	    75,	    95,	      0,	  0,	  0},
  {22.4,   45,  0.75,  22,	  28,	36,	45,	56,	71,	    90,	    112,	140,	  0,      0},
  {22.4,   45,	   1,  25,	  32,	40,	50,	63,	80,	    100,	125,	160,	200,	250},
  {22.4,   45,	 1.5,	0,	  0,	0,	0,	0,	95,	    118,	150,	190,	250,	315},
  {22.4,   45,     2,   0,    0,    0,	0,	0,  106,    132,	170,	212,	265,	335},
  {22.4,   45,	   3,   0,    0,    0,	0,	0,  125,    160,	200,	250,	315,	400},
  {22.4,   45,	 3.5,	0,	  0,	0,	0,	0,	132,	170,	212,	265,	335,	425},
  {22.4,   45,	   4,   0,    0,    0,	0,	0,  140,    180,	224,	280,	355,	450},
  {22.4,   45,   4.5,	0,	  0,	0,	0,	0,	159,	190,	236,	300,	375,	475},
  {45,     90,  0.35,	0,	  22,  28, 36, 45,	 56,     71,      0,      0,      0,      0},
  {45,	   90,   0.5,  21,	  26,  34, 42, 53,	 67,     85,    106,	  0,	  0,	  0},
  {45,     90,  0.75,  24,	  30,  38, 48, 60,	 75,     95,    118,	  0,	  0,	  0},
  {45,     90,     1,  28,	  36,  45, 56, 71,	 90,    112,	140,	180,	224,	  0},
  {45,     90,	 1.5,	0,	  0,	0,	0,	0,	100,	125,	160,	200,	250,	315},
  {45,     90,     2,   0,	  0,	0,	0,	0,	160,	200,	250,	315,	400,	500},
  {45,     90,     3,   0,	  0,	0,	0,	0,	132,	170,	212,	265,	335,	425},
  {45,     90,     4,   0,	  0,	0,	0,	0,	150,	190,	236,	300,	375,	475},
  {45,     90,     5,   0,	  0,	0,	0,	0,	160,	200,	250,	315,	400,	500},
  {45,     90,	 5.5,	0,	  0,	0,	0,	0,	170,	212,	265,	335,	425,	530},
  {45,     90,     6,   0,	  0,	0,	0,	0,	180,	224,	280,	355,	450,	560},
  {90,    180,  0.75,  26,	 34,   42, 53, 67,   85,    106,	132,	  0,      0,      0},
  {90,    180,	   1,  30,	 38,   48, 60, 75,   95,    118,	150,	  0,	  0,	  0},
  {90,    180,	 1.5,   0,	  0,	0,	0,	0,	106,	118,	150,	  0,	  0,	  0},
  {90,    180,	   2,   0,	  0,	0,	0,	0,	118,	150,	190,	236,	300,	375},
  {90,    180,	   3,   0,	  0,	0,	0,	0,	140,	180,	224,	280,	355,	450},
  {90,    180,	   4,   0,	  0,	0,	0,	0,	160,	200,	250,	315,	400,	500},
  {90,    180,	   6,   0,	  0,	0,	0,	0,	190,	236,	300,	375,	475,	600},
  {90,    180,	   8,   0,	  0,	0,	0,	0,	212,	265,	335,	425,	530,	670},
  {180,	  355,	   1,   0,	  0,	0,	0,	0,	100,	125,	160,	  0,      0,      0},
  {180,	  355,	 1.5,   0,	  0,	0,	0,	0,	112,	140,	180,	  0,	  0,	  0},
  {180,	  355,	   2,   0,	  0,	0,	0,	0,	132,	170,	212,	  0,	  0,	  0},
  {180,	  355,	   3,   0,	  0,	0,	0,	0,	160,	200,	250,	315,	400,	500},
  {180,	  355,	   4,   0,	  0,	0,	0,	0,	180,	224,	280,	355,	450,	560},
  {180,	  355,	   6,   0,	  0,	0,	0,	0,	200,	250,	315,	400,	500,	630},
  {180,	  355,	   8,   0,	  0,	0,	0,	0,	224,	280,	355,	450,	560,	710},
  {355,	  500,	   2,   0,	  0,	0,	0,	0,	140,	170,	212,	  0,      0,      0},
  {355,	  500,	   3,   0,	  0,	0,	0,	0,	160,	200,	250,	315,	400,	500},
  {355,	  500,	   4,   0,	  0,	0,	0,	0,	180,	224,	280,	355,	450,	710},
  {355,   500,	   6,   0,	  0,	0,	0,	0,	212,	265,	335,	425,	530,	670},
  {355,	  500,	   8,   0,	  0,	0,	0,	0,	236,	300,	375,	475,	600,	750},
  {500,	  1000,	   8,   0,	  0,	0,	0,	0,	  0,    315,	400,	500,	630,	800}
  };

   for (slei = 0; slei < 76; slei++)
    {
     if ((da >= Td2[slei][0] ) && (da <= Td2[slei][1]) && (P == Td2[slei][2]))
      {
       zeile = slei;
       break;
      }
    }

   for (slei = 0; slei < 11; slei++)
    {
     if(ITd2Wertstr.compare(ITGrad[slei]) == 0)
      {
       spalte = slei;
       break;
      }
    }


   Td2Wert = Td2[zeile][spalte + 3];

  }
  void GewindeM::SucheTd3Wert(void)
   {
   int slei, zeile, spalte;

   // Toleranz für Kerndurchmesser Aussengewinde
  double Td3[76][11] ={
  //0        1       2      3    4         5     6         7       8       9
  // über bis                                                                  Rmin
  {0,	    0,	     0,	    3,	4,	      5,	6,        7,	  8,	  9,	  0},    // 0
  {0.99,	1.4,	0.2,   38,	44,	     52,	62,       0,	  0,	  0,	 20},
  {0.99,	1.4,   0.25,   44,	52,	     60,	71,       0,	  0,	  0,	 25},
  {0.99,	1.4,	0.3,   50,	58,	     67,	78,       0,	  0,	  0,	 30},
  {1.4,	    2.8,	0.2,   39,	45,	     54,	64,       0,	  0,	  0,	 20},
  {1.4,	   2.8,	   0.25,   46,	54,	     63,	74,	      0,	  0,	  0,	 25},
  {1.4,	   2.8,	   0.35,   57,	65,	     75,	88,	    105,	  0,	  0,	 35},
  {1.4,	   2.8,	    0.4,   63,	71,	     82,	96,	    114,	  0,	  0,	 40},
  {1.4,	   2.8,	   0.45,   68,	77,	     88,	103,	122,	  0,	  0,	 45},
  {2.8,	   5.6,	    0.2,   40,	48,	     56,	67,	      0,	  0,	  0,	 20},
  {2.8,	   5.6,	   0.25,   48,	56,	     66,	78,	      0,	  0,	  0,	 25},    //10
  {2.8,	   5.6,	   0.35,   59,	67,	     78,	92,	    110,	  0,	  0,	 35},
  {2.8,	   5.6,	    0.5,   74,	84,	     96,	111,	131,	  0,	  0,	 50},
  {2.8,	   5.6,	    0.6,   85,	96,	    110,	128,	149,	  0,	  0,	 60},
  {2.8,	   5.6,	    0.7,   95,	106,	121,	140,	162,	  0,	  0,	 70},
  {2.8,	   5.6,	   0.75,   99,	110,	125,	144,	166,	  0,	  0,	 75},
  {2.8,	   5.6,	    0.8,  106,	118,	133,	153,	176,	208,	248,	 80},
  {5.6,	  11.2,	    0.2,   42,	50,	     59,	70,	      0,	  0,	  0,	 20},
  {5.6,	  11.2,	   0.25,   50,	58,	     68,	81,	      0,	  0,	  0,     25},
  {5.6,	  11.2,    0.35,   61,	70,	     81,	96,	      0,	  0,	  0,	 35},
  {5.6,	  11.2,	    0.5,   78,	89,	    103,	121,	142,	  0,	  0,	 50},    // 20
  {5.6,	  11.2,	   0.75,  104,	117,	134,	154,	179,	  0,	  0,     75},
  {5.6,	  11.2,	      1,  128,	143,	162,	184,	212,	252,	296,	100},
  {5.6,	  11.2,	   1.25,  150,	165,	185,	208,	240,	280,	326,	125},
  {5.6,	  11.2,	    1.5,	0,	193,	214,	240,	278,	320,	373,	150},
  {11.2,  22.4,	   0.35,   65,	75,	     88,	105,	  0,	  0,	  0,     35},    // 25
  {11.2,  22.4,	    0.5,   50,	58,	     68,	81,	      0,	  0,	  0,     50},
  {11.2,  22.4,	   0.75,   61,	70,	     81,	96,	      0,	  0,	  0,     75},
  {11.2,  22.4,	      1,  132,	147,	167,	190,	222,	262,	308,	100},
  {11.2,  22.4,	   1.25,  157,	175,	196,	22,	    260,	302,	355,	125},
  {11.2,  22.4,	    1.5,	0,	198,	220,	248,	288,	332,	388,	150},    // 30
  {11.2,  22.4,	   1.75,	0,	221,	244,	276,	316,	362,	308,	100},
  {11.2,  22.4,	      2,    0,	244,	269,	304,	344,	394,	459,	200},
  {11.2,  22.4,	    2.5,	0,	286,	312,	350,	392,	445,	515,	250},
  {22.4,    45,	   0.35,   67,	 78,	92,	    110,	0,	      0,   	  0,	 35},
  {22.4,    45,	    0.5,   84,	 96,	111,	131,	0,	      0,      0,	 50},
  {22.4,    45,	   0.75,  110,	125,	144,	166,	194,	  0,      0,     75},
  {22.4,    45,	      1,  135,	152,	172,	197,	232,	272,	322,	100},
  {22.4,    45,	    1.5,	0,	203,	226,	258,	298,	344,	408,	150},
  {22.4,    45,	      2,    0,	250,	276,	314,	356,	409,	479,	200},
  {22.4,    45,	      3,    0,	341,	376,	416,	466,	531,	616,	300},
  {22.4,    45,	    3.5,	0,	384,	422,	464,	517,	587,	677,	350},
  {22.4,    45,	      4,    0,	428,	468,	512,	568,	643,	738,	400},
  {22.4,    45,	    4.5,	0,	474,	514,	560,	624,	699,	799,	450},
  {45,	    90,	   0.35,   70,	 81,	96,	      0,	0,	      0,	  0,     35},
  {45,      90,	    0.5,   89,	103,	121,	142,	0,	      0,	  0,	 50},
  {45,      90,	   0.75,  114,	129,	149,	172,	0,	      0,	  0,	 75},
  {45,      90,	      1,  143,	162,	184,	212,	252,	290,	  0,	100},
  {45,      90,	    1.5,	0,	208,	233,	268,	308,	358,	423,	150},
  {45,      90,	      2,    0,	256,	284,	324,	368,	424,	499,	200},
  {45,      90,	      3,    0,	348,	386,	428,	481,	551,	641,	300},
  {45,      90,	      4,    0,	438,	478,	524,	588,	663,	763,	400},
  {45,      90,	      5,    0,	529,	560,	610,	675,	760,	860,	500},
  {45,      90,	    5.5,	0,	566,	608,	661,	731,	821,	926,	550},
  {45,      90,	      6,    0,	612,	656,	712,	787,	881,	992,	600},
  {90,    180,	   0.75,  121,	139,	160,	186,	0,	      0,	  0,     75},
  {90,    180,	      1,  147,	167,	190,	222,	0,	      0,	  0,	100},
  {90,    180,	    1.5,    0,	214,	240,	278,	0,	      0,	  0,	150},
  {90,    180,        2,    0,	262,	294,	334,	380,	444,	519,	200},
  {90,    180,	      3,    0,	356,	396,	440,	496,	571,	666,	300},
  {90,    180,	      4,    0,  448,	488,	538,	603,	688,	788,	 40},
  {90,    180,	      6,	0,  622,	668,	732,	807,	907,	1032,	600},
  {90,    180,	      8,	0,  788,	841,	911,	1001,	1106,	1246,	800},
  {180,	  355,	      1,  152,  172,	197,	232,	0,	    0,	    0,	    100},
  {180,   355,	    1.5,    0,  220,	248,	288,	0,	    0,	    0,	    150},
  {180,	  355,	      2,    0,  276,	314,	356,	 0,	    0,	    0,	    200},
  {180,	  355, 	      3,	0,  376,	416,	466,	531,	616,	716,	300},
  {180,	  355,	      4,	0,  468,	512,	568,	643,	738,	862,	400},
  {180,	  355,	      6,	0,  632,	682,	747,	832,	932,	1062,	600},
  {180,	  355,	      8,	0,   800,    856,	931,	1026,	1136,	1286,	800},
  {355,	  500,	      2,	0,  284,	314,	356,	0,  	0,	    0,	    200},
  {355,	  500,	      3,	0,  376,	416,	466,	531,	616,	716,	300},
  {355,	  500,	      4,	0,  468,	512,	568,	643,	738,	862,	400},
  {355,	  500,	      6,	0,  644,	697,	767,	857,	962,	1102,	600},
  {355,	  500,	      8,	0,  812,	876,	951,	1051,	1176,	1326,	800},
  {500,	 1000,	      8,	0,    0,   	891,	976,	1076,   1206,	1376,	800}
  };

  zeile = spalte = 0;

   for (slei = 0; slei < 76; slei++)
    {

     if ((da >= Td3[slei][0] ) && (da <= Td3[slei][1]) && (P == Td3[slei][2]))
      {
       zeile = slei;
       break;
      }
    }


  for (slei = 3; slei < 10; slei++)
    {
     if (ITd3Wert == Td3[0][slei])
      {
       spalte = slei;
       break;
      }
    }

  Td3Wert = (double)Td3[zeile][spalte]; // rewer
  Rmin = Td3[zeile][10];  //Rmin

 }
  void GewindeM::SucheAuWert(void)
   {
   int slei, zeile = 0, spalte = 0;
   // double rewer = 0;

   double Au[25][3]= {
   //in mm	G	H
   {0.2,	17,	0},
   {0.25,	18,	0},
   {0.3,	18,	0},
   {0.35,	19,	0},
   {0.4,	19,	0},
   {0.45,	20,	0},
   {0.5,	20,	0},
   {0.6,	21,	0},
   {0.7,	22,	0},
   {0.75,	22,	0},
   {0.8,	24,	0},
   {1,	    26,	0},
   {1.25,	28,	0},
   {1.5,	32,	0},
   {1.75,	34,	0},
   {2,	    38,	0},
   {2.5,	42,	0},
   {3,	    48,	0},
   {3.5,	53,	0},
   {4,	    60,	0},
   {4.5,	63,	0},
   {5,	    71,	0},
   {5.5,	75,	0},
   {6,	    80,	0},
   {8,	   100,	0}
   };

   for (slei = 0; slei < 25; slei++)
    {
      //cout << "slei: " << slei << "  Steigung: " << Au[slei][0] << endl;
      if (P == Au[slei][0])
       {
        zeile = slei;
        break;
       }
    }
   if(GAInnenstr.compare("G") == 0) spalte = 1;
    else                             spalte = 2;

    AuWert =  Au[zeile][spalte];

   }

   void GewindeM::SucheTD1Wert(void)
   {
   int slei, zeile = 0, spalte = 3;
   //double rewer = 0;

   double TD1[26][6]= {
   //Grundabmaße TD1 für die Berechnung des Kerndurchmessers von Muttergewinden
   //"Steigung P
   {0,	    4,	 5,	      6,	  7,	  8},
   {0.2,   38,	 0,	      0,      0,	  0},
   {0.25,  45,	56,	      0,      0,	  0},
   {0.3,   53,	67,	     85,	  0,	  0},
   {0.35,  63,	80,	    100,      0,	  0},
   {0.4,   71,	90,	    112,	  0,	  0},
   {0.45,  80,	100,	125,	  0,	  0},
   {0.5,   90,	112,	140,	180,	  0},
   {0.6,  100,	125,	160,	200,	  0},
   {0.7,  112,	140,	180,	224,	  0},
   {0.75, 118,	150,	190,	236,	  0},
   {0.8,  125,	160,	200,	250,	315},
   {1,    150,	190,	236,	300,	375},
   {1.25, 170,	212,	265,	335,	425},
   {1.5,  190,	236,	300,	375,	475},
   {1.75, 212,	265,	335,	425,	530},
   {2,    236,	300,	375,	475,	600},
   {2.5,  280,	355,	450,	560,	710},
   {3,    315,	400,	500,	630,	800},
   {3.5,  355,	450,	560,	710,	900},
   {4,	  375,	475,	600,	750,	950},
   {4.5,  425,	530,	670,	850,	1060},
   {5,	  450,	560,	710,	900,	1120},
   {5.5,  475,	475,	750,	950,	1180},
   {6,	  500,	630,	800,	1000,	1250},
   {8,	  630,	800,	1000,	1250,	1600}
   };

   // cout << "Suche TD1" << endl;
   for (slei = 1; slei < 26; slei++)
    {
      //cout << "slei: " << slei << "  Steigung: " << Au[slei][0] << endl;
      if (P == TD1[slei][0])
       {
        zeile = slei;
        break;
       }
    }
   if (ITD1Wert == 4) spalte = 1;
   if (ITD1Wert == 5) spalte = 2;
   if (ITD1Wert == 6) spalte = 3;
   if (ITD1Wert == 7) spalte = 4;
   if (ITD1Wert == 8) spalte = 5;

    TD1Wert = TD1[zeile][spalte]; // rewer

   //return rewer;
   }

   void GewindeM::SucheTD2Wert(void)
    {
    int slei, zeile = 0, spalte = 0;

    double TD2[76][14] = {
   //  TD2 bei Toleranz zur Berechung der Toleranzen des Flankendurchmessers Muttergewinde
   {0,      0,	    0,	0.2,  0.1,   0,	     1,	  2,	 3,	 4,	      5,	  6,	  7,      8},
   {0.99,	1.4,  0.2,	  0,	0,   0,	     0,	 25,	32,	40,       0,	  0,	  0,      0},
   {0.99,	1.4, 0.25,	  0,	0,   0,	    22,	 28,	36,	45,      56,	  0,	  0,      0},
   {0.99,	1.4,  0.3,	  0,	0,	19,	    24,	 30,	38,	48,      60,	 75,	  0,	  0},
   {1.4,	2.8,  0.2,	  0,	0,   0,	     0,	 26,	34,	42,       0,	  0,	  0,	  0},
   {1.4,	2.8, 0.25,	  0,	0,   0,	    24,	 30,	38,	48,      60,	  0,	  0,	  0},
   {1.4,	2.8, 0.35,	  0,	0,	21,	    26,	 34,	42,	53,      67,	 85,	  0,	  0},
   {1.4,	2.8,  0.4,	  0,	0,	22,	    28,	 36,	45,	56,      71,	 90,	  0,	  0},
   {1.4,	2.8, 0.45,	  0,	0,	24,	    30,	 38,	48,	60,      75,	 95,	  0,	  0},
   {2.8,	5.6,  0.2,	  0,	0,	 0,	     0,	 28,	36,	45,       0,      0,	  0,	  0},
   {2.8,	5.6, 0.25,	  0,	0,	 0,	    25,	 32,	40,	50,      63,      0,	  0,	  0},
   {2.8,	5.6, 0.35,	  0,	0,	22,	    28,	 36,	45,	56,      71,      0,	  0,	  0},
   {2.8,	5.6,  0.5,	  0,   20,	25,	    32,	 40,	50,	63,      80,    100,	125,	  0},
   {2.8,	5.6,  0.6,	  0,   22,	28,	    36,	 45,	56,	71,      90,    112,	140,	  0},
   {2.8,	5.6,  0.7,	  0,   24,	30,	    38,	 48,	60,	75,	     95,    118,	150,      0},
   {2.8,	5.6, 0.75,	  0,   24,	30,	    38,	 48,	60,	75,	     95,    118,	150,      0},
   {2.8,	5.6,  0.8,	 20,   25,	32,	    40,	 50,	63,	80,	    100,	125,	160,	200},
   {5.6,   11.2,  0.2,	  0,	0,	 0,	     0,	 30,	38,	48,	      0,	  0,      0,      0},
   {5.6,   11.2, 0.25,	  0,	0,	 0,	    26,	 34,	42,	52,	      0,	  0,      0,      0},
   {5.6,   11.2, 0.35,	  0,	0,	24,	    30,	 38,	48,	60,	     75,	  0,      0,      0},
   {5.6,   11.2,  0.5,	  0,   22,	28,	    36,	 45,	56,	71,	     90,	112,	  0,      0},
   {5.6,   11.2, 0.75,	 21,   26,	34,	    42,	 53,	67,	85,	    106,	132,	170,	  0},
   {5.6,   11.2,	1,	 24,   30,	38,	    48,	 60,	75,	95,	    118,	150,	190,	236},
   {5.6,   11.2, 1.25,	 25,   32,	40,	    50,	 63,	80,	100,	125,	160,	200,	250},
   {5.6,   11.2,  1.5,	  0,	0,	 0,	     0,	  0,	0,	112,	140,	180,	224,	280},
   {11.2,  22.4, 0.35,	  0,   21,	26,	    34,	 42,	53,	67,	     85,      0,      0,      0},
   {11.2,  22.4,  0.5,	  0,   24,	30,	    38,	 48,	60,	75,	     90,	118,	  0,	  0},
   {11.2,  22.4, 0.75,   22,   28,	36,	    45,	 56,    71,	90,	    112,	140,	180,      0},
   {11.2,  22.4,	1,	 25,   32,	40,	    50,	 63,	80,	100,	125,	160,	200,	250},
   {11.2,  22.4, 1.25,	 28,   36, 	45,	    56,	 71,	90,	112,	140,	180,	224,	280},
   {11.2,  22.4,  1.5,	  0,	0,	 0,	     0,	  0,	 0,	118,	150,	190,	236,	300},
   {11.2,  22.4, 1.75,	  0,	0,	 0,	     0,	  0,	 0,	125,	160,	200,	250,	315},
   {11.2,  22.4,	2,	  0,	0,	 0,	     0,	  0,	 0,	132,	170,	212,	265,	335},
   {11.2,  22.4,  2.5,	  0,	0,	 0,	     0,	  0,	 0,	140,	180,	224,	280,	355},
   {22.4,	 45, 0.35,	  0,   22,	28,	    36,	 45,	56,	 71,	90,	      0,	  0,      0},
   {22.4,	 45,  0.5,	 20,   25,	32,	    40,	 50,	63,	 80,	100,	125,	  0,      0},
   {22.4,	 45, 0.75,	 24,   30,	38,	    48,	 60,	75,	 90,	118,	150,	190,	  0},
   {22.4,	 45,	1,	 26,   34,	42,	    53,	 67,	85,	106,	132,	170,	212,	  0},
   {22.4,	 45,  1.5,	  0,	0,	 0,	     0,	  0,	0,	125,	160,	200,	250,	315},
   {22.4,	 45,	2,	  0,	0,	 0,	     0,	  0,	0,	140,	180,	224,	280,	335},
   {22.4,	 45,	3,	  0,	0,	 0,	     0,	  0,	0,	170,	212,	265,	335,	425},
   {22.4,	 45,  3.5,	  0,	0,	 0,	     0,	  0,	0,	180,	224,	280,	355,	450},
   {22.4,	 45,	4,	  0,	0,	 0,	     0,	  0,	0,	190,	236,	300,	375,	475},
   {22.4,	 45,  4.5,	  0,	0,	 0,	     0,	  0,	0,	200,	250,	315,	400,	500},
   {45,      90, 0.35,	  0,   24,	 30,	38,	 48,	60,	 75,	0,	      0,	  0,	  0},
   {45,      90,  0.5,	 22,   28,	 36,	45,	 56,	71,	 90,    112,	  0,	  0,      0},
   {45,      90, 0.75,	 25,   32,	 40,	50,	 63,	80,	100,	125,	160,	  0,	  0},
   {45,      90,	1,	 30,   38,	 48,	60,	 75,	95,	118,	150,	180,	236,      0},
   {45,      90,  1.5,	  0,	0,	  0,	 0,	  0,	0,  132,	170,	212,	265,	335},
   {45,      90,	2,	  0,	0,	  0,	 0,	  0,	0,  150,	190,	236,	300,	375},
   {45,      90,	3,	  0,	0,	  0,	 0,	  0,	0,  180,	224,	280,	355,	450},
   {45,      90,	4,	  0,	0,	  0,	 0,	  0,	0,  200,	250,	315,	400,	500},
   {45,      90,	5,	  0,	0,	  0,	 0,	  0,	0,  212,	265,	335,	425,	530},
   {45,      90,  5.5,	  0,	0,	  0,	 0,	  0,	0,  224,	280,	355,	450,	560},
   {45,      90,	6,	  0,	0,	  0,	 0,	  0,	0,  236,	300,	375,	475,	600},
   {90,     180, 0.75,	 28,   36,	 45,	56,	 71,   90,	112,	140,	180,	  0,      0},
   {90,     180,	1,	 32,   40,	 50,	63,	 80,  100,	125,	160,	200,	250,	  0},
   {90,     180,  1.5,	  0,	0,	  0,	 0,	  0,	0,	140,	180,	224,	280,	  0},
   {90,     180,	2,	  0,	0,	  0,	 0,	  0,	0,	160,	200,	250,	315,	400},
   {90,     180,	3,	  0,	0,	  0,	 0,	  0,	0,	190,	236,	300,	375,	475},
   {90,     180,	4,	  0,	0,	  0,	 0,	  0,	0,	212,	265,	335,	425,	530},
   {90,     180,	6,	  0,	0,	  0,	 0,	  0,	0,	250,	315,	400,	500,	630},
   {90,     180,	8,	  0,	0,	  0,	 0,	  0,	0,	280,	355,	450,	560,	710},
   {180,	355,	1,	 34,   42,	 53,	67,	 85,  106,	132,	170,	212,	  0,      0},
   {180,	355,  1.5,    0,	0,	  0,	 0,	  0,	0,	150,	190,	236,	300,	  0},
   {180,	355,	2,	  0,	0,	  0,	 0,	  0,	0,	180,	224,	280,	355,	  0},
   {180,	355,	3,	  0,	0,	  0,	 0,	  0,	0,	212,	265,	335,	425,	530},
   {180,	355,	4,	  0,	0,	  0,	 0,	  0,	0,	236,	300,	375,	475,	600},
   {180,	355,	6,	  0,	0,	  0,	 0,	  0,	0,	265,	335,	425,	530,	670},
   {180,	355,	8,	  0,	0,	  0,	 0,	  0,	0,	300,	375,	475,	600,	750},
   {355,	500,	2,	  0,	0,	  0,	 0,	  0,	0,	180,	224,	280,	  0,	  0},
   {355,	500,	3,	  0,	0,	  0,	 0,	  0,	0,	212,	265,	335,	425,	530},
   {355,	500,	4,	  0,	0,	  0,	 0,	  0,	0,	236,	300,	375,	475,	600},
   {355,	500,	6,	  0,	0,	  0,	 0,	  0,	0,	280,	355,	450,	560,	710},
   {355,	500,	8,	  0,	0,	  0,	 0,	  0,	0,	315,	400,	500,	630,	800},
   {500,  1000,  	8,	  0,	0,	  0,	 0,	  0,	0,	  0,    425,	530,	670,	850}
   };

    for (slei = 0; slei < 76; slei++)
     {
      if ((da >= TD2[slei][0] ) && (da <= TD2[slei][1]) && (P == TD2[slei][2]))
       {
        zeile = slei;
        break;
       }
     }

   if(ITD2str.compare("02") == 0) spalte = 3;
   if(ITD2str.compare("01") == 0) spalte = 4;
   if(ITD2str.compare("0") == 0)  spalte = 5;
   if(ITD2str.compare("1") == 0)  spalte = 6;
   if(ITD2str.compare("2") == 0)  spalte = 7;
   if(ITD2str.compare("3") == 0)  spalte = 8;
   if(ITD2str.compare("4") == 0)  spalte = 9;
   if(ITD2str.compare("5") == 0)  spalte = 10;
   if(ITD2str.compare("6") == 0)  spalte = 11;
   if(ITD2str.compare("7") == 0)  spalte = 12;
   if(ITD2str.compare("8") == 0)  spalte = 13;


   TD2Wert = TD2[zeile][spalte];
   }


   void GewindeM::A0Fehlertest(void)
   {
    fehler = 0;
     QMessageBox *msgBox = new QMessageBox(this);
    // Fehlertest für A0-Wert
     if ((P >= 0.4) && (P <= 0.8))
      if ((GrndAbmassAussenD.compare("a") == 0) || (GrndAbmassAussenD.compare("b") == 0)) fehler = 1;
    if ((P >= 0.2) && (P <= 0.35))
      if ((GrndAbmassAussenD.compare("a") == 0) || (GrndAbmassAussenD.compare("b") == 0) || (GrndAbmassAussenD.compare("c") == 0) || (GrndAbmassAussenD.compare("d") == 0)) fehler = 2;
    // Fehlertest für Td-Wert
    if ((P >= 0.2) && (P <= 0.75) && (ITGradBolzenD.compare("8") == 0)) fehler = 3;
    // Fehlertest für Td2-Wert
    if (Td2Wert == 0) fehler = 4;
    if (Td3Wert == 0) fehler = 5;
    if (TD1Wert == 0) fehler = 6;
    if (TD2Wert == 0) fehler = 7;

    if (fehler == 1)
     {
      msgBox->setText("Fehler:\nBei dieser Steigung nur Toleranzlage Aussendurchmesser\n von c bis h erlaubt");
      msgBox->show();
     }
    if (fehler == 2)
     {
      msgBox->setText("Fehler:\nBei dieser Steigung nur Toleranzlage Aussendurchmesser\n von e bis h erlaubt");
      msgBox->show();
     }
    if (fehler == 3)
     {
      msgBox->setText("Fehler:\nBei dieser Steigung nur\nToleranzqualitaet Aussendurchmesser\nBolzengewinde\n von 4 und 6 erlaubt");
      msgBox->show();
     }
    if (fehler == 4)
     {
      msgBox->setText("Fehler:\nBei diesen Nenndurchmesser und Steigung\ndiese Toleranzqualitaet des Frankendurchmessers\nBolzengewinde\nnicht erlaubt");
      msgBox->show();
     }
    if (fehler == 5)
     {
      msgBox->setText("Fehler:\nBei diesen Nenndurchmesser und Steigung\ndiese Toleranzqualitaet des Kerndurchmessers\nBolzengewinde\nnicht erlaubt");
      msgBox->show();
     }
    if (fehler == 6)
     {
      msgBox->setText("Fehler:\nBei dieserSteigung\ndiese Toleranzqualitaet des Kerndurchmessers\nMuttergewinde\nnicht erlaubt");
      msgBox->show();
     }
    if (fehler == 7)
     {
      msgBox->setText("Fehler:\nBei diesen Nenndurchmesser und Steigung\ndiese Toleranzqualitaet des Flankendurchmessers\nMuttergewinde\nnicht erlaubt");
      msgBox->show();
     }
   }

    void GewindeM::SucheDMess(void)
     {
     int slei;

     double DMess[23][3]= {
      // P     dD     Faktor C
     {0.25,   0.17,   0.294},  // 0
     { 0.3,   0.17,   0.251},
     {0.35,   0.22,   0.358},
     { 0.4,   0.25,   0.405},
     {0.45,   0.29,   0.481},
     { 0.5,   0.29,   0.438}, // 5
     { 0.6,  0.335,   0.486},
     { 0.7,  0.455,    0.76},
     {0.75,  0.455,   0.717},
     { 0.8,  0.455,   0.673},
     {   1,   0.62,   0.996}, // 10
     {1.25,  0.725,   1.094},
     { 1.5,  0.895,   1.388},
     {1.75,    1.1,   1.787},
     {   2,   1.35,    2.32},
     { 2.5,   1.65,   2.788}, // 15
     {   3,   2.05,   3.555},
     { 3.5,   2.05,   3.121},
     {   4,   2.55,   4.189},
     { 4.5,   2.55,   3.755},
     {   5,    3.2,   5.273}, // 20
     { 5.5,    3.2,   4.839},
     {   6,      4,   6.807}
     };

            for (slei = 0; slei < 23; slei++)
              {
               if (P == DMess[slei][0])
                {
                 dD = DMess[slei][1];
                 C  = DMess[slei][2];
                 break;
                }
              }
             if ((P == 0.25) && (da >= 1.4)  && (da <= 10))  C = 0.294;
             if ((P == 0.35) && (da >= 2)    && (da <= 50))  C = 0.357;
             if ((P == 0.5)  && (da >= 3.5)  && (da <= 90))  C = 0.437;
             if ((P == 0.75) && (da >= 5)    && (da <= 110)) C = 0.716;
             if ((P == 1)    && (da >= 7.5)  && (da <= 10))  C = 0.995;
             if ((P == 1)    && (da >= 10.5) && (da <= 200)) C = 0.994;
             if ((P == 1.25) && (da >= 10)   && (da <= 12))  C = 0.994;
             if ((P == 1.5)  && (da >= 12)   && (da <= 17))  C = 1.387;
             if ((P == 1.5)  && (da >= 18)   && (da <= 300)) C = 1.386;
             if ((P == 2)    && (da >= 17)   && (da <= 28))  C = 2.319;
             if ((P == 2)    && (da >= 30)   && (da <= 300)) C = 2.318;
             if ((P == 3)    && (da >= 28)   && (da <= 50))  C = 3.553;
             if ((P == 3)    && (da >= 52)   && (da <= 300)) C = 3.552;

             //return rewer;
  }



double GewindeM::Bogenmass(double WinkelInGrad)
{
 double rewer = 0, pi = 3.141592654;

 rewer = (WinkelInGrad * pi)  / 180;
 return rewer;
}

double GewindeM::Sinus(double WinkelInGrad)
{
 double rewer = sin(Bogenmass(WinkelInGrad));

 return rewer;
}

double GewindeM::Cosinus(double WinkelInGrad)
{
 double rewer = cos(Bogenmass(WinkelInGrad));

 return rewer;
}

double GewindeM::Tangens(double WinkelInGrad)
{
 double rewer = tan(Bogenmass(WinkelInGrad));

 return rewer;
}

double GewindeM::Cotangens(double WinkelInGrad)
{
 double rewer = 1/ tan(Bogenmass(WinkelInGrad));

 return rewer;
}


void GewindeM::GetKorrC(void)
 {
  double pi = 3.141592654;
  Ccalc = (dD/Sinus(30)) - (P/ (2*Tangens(30))) + dD + (dD/2) * ((P * P) / (pi*pi)) *  ((Cosinus(30) * Cotangens(30)) / (d2atheo*d2atheo));
 }

void GewindeM::Regelgewindetest(void)
{
 int slei;
 QMessageBox *msgBox = new QMessageBox(this);
  double Reggew[37][2]
  {
   {1,     0.25},   // 0
   {1.2,   0.25},
   {1.4,   0.3},
   {1.7,   0.35},
   {2,     0.4},
   {2.3,   0.4},    // 5
   {2.6,   0.45},
   {3,     0.5},
   {3.5,   0.6},
   {4,     0.7},
   {5,     0.8},    // 10
   {6,     0.3},
   {8,     1.25},
   {10,    1.5},
   {12,    1.75},
   {14,    2},      // 15
   {16,    2},
   {18,    2.5},
   {20,    2.5},
   {22,    2.5},
   {24,    3},      // 20
   {27,    3},
   {30,    3.5},
   {33,    3.5},
   {36,    4},
   {39,    4},      // 25
   {42,    4.5},
   {45,    4.5},
   {48,    5},
   {52,    5},
   {56,    5.5},   // 30
   {60,    5.5},
   {64,    6},
   {68,    6},
   {72,    6},
   {76,    6},     // 35
   {80,    6}
  };

for (slei = 0; slei <= 37; slei++)
   if ((da == Reggew[slei][0]) && (P == Reggew[slei][1]))
    {
     msgBox->setText("Gewinde ist Regelgewinde");
     msgBox->show();
     break;
    }
}

void GewindeM::NennDSteigungsFehlertest(void)
{
QMessageBox *msgBox = new QMessageBox(this);
fehlernummer = 0;
if (da  > 1000) fehlernummer = 1;
if (da  < 0.99) fehlernummer = 2;
if (P  > 8) fehlernummer = 3;
if (P  < 0.2) fehlernummer = 4;
if ((da > 0.99) && (da <= 1.4) && (P >= 0.25)) fehlernummer = 5;
if ((da > 1.4) && (da <= 2.8) && (P != 0.2)  && (P != 0.25)  && (P != 0.35)  && (P != 0.4)  && (P != 0.45)) fehlernummer = 6;
if ((da > 2.8) && (da <= 5.6) && (P != 0.2)  && (P != 0.25)  && (P != 0.35)  && (P != 0.5)  && (P != 0.6) && (P != 0.7) && (P != 0.75) && (P != 0.8)) fehlernummer = 7;
if ((da > 5.6) && (da <= 11.2) && (P != 0.2)  && (P != 0.25)  && (P != 0.35) && (P != 0.5)  && (P != 0.75) && (P != 1) && (P != 1.25) && (P != 1.5)) fehlernummer = 8;
if ((da > 11.2) && (da <= 22.4) && (P != 0.35)  && (P != 0.5)  && (P != 0.75) && (P != 1)  && (P != 1.25) && (P != 1.5) && (P != 1.75) && (P != 2) && (P != 2.5)) fehlernummer = 9;
if ((da > 22.4) && (da <= 45) && (P != 0.35)  && (P != 0.5)  && (P != 0.75) && (P != 1)  && (P != 1.5) && (P != 2) && (P != 3) && (P != 3.5) && (P != 4) && (P != 4.5)) fehlernummer = 10;
if ((da > 45) && (da <= 90) && (P != 0.35)  && (P != 0.5)  && (P != 0.75) && (P != 1)  && (P != 1.5) && (P != 2) && (P != 3) && (P != 4) && (P != 5) && (P != 5.5) && (P != 6)) fehlernummer = 11;
if ((da > 90) && (da <= 180) && (P != 0.75)  && (P != 1)  && (P != 1.5) && (P != 2)  && (P != 3) && (P != 4) && (P != 6) && (P != 8)) fehlernummer = 12;
if ((da > 180) && (da <= 355) && (P != 1)  && (P != 1.5)  && (P != 2) && (P != 3)  && (P != 4) && (P != 6) && (P != 8)) fehlernummer = 13;
if ((da > 355) && (da <= 500) && (P != 2) && (P != 3)  && (P != 4) && (P != 6) && (P != 8)) fehlernummer = 14;
if ((da > 500) && (da <= 1000) && (P != 8)) fehlernummer = 15;

if (fehlernummer == 1)
 {
  msgBox->setText("Fehler: Nenndurchmesser > als 1000 mm");
  msgBox->show();
 }
if (fehlernummer == 2)
 {
  msgBox->setText("Fehler: Nenndurchmesser < als 0.99 mm");
  msgBox->show();
 }
if (fehlernummer == 3)
 {
  msgBox->setText("Fehler: Steigung > als 8 mm");
  msgBox->show();
 }
if (fehlernummer == 4)
 {
  msgBox->setText("Fehler: Steigung < als 0.2 mm");
  msgBox->show();
 }
if (fehlernummer == 5)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 0.99mm bis 1.4mm\n nur 0.2, 0.25, 0.3 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 6)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 1.4.mm bis 2.8mm\n nur 0.2, 0.25, 0.35, 0.4, 0.45 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 7)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 2.8mm bis 5.6mm\n nur 0.2, 0.25, 0.35, 0.5, 0.6, 0.7, 0.75, 0.8 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 8)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 5.6mm bis 11.2mm\n nur 0.2, 0.25, 0.35, 0.5, 0.75, 1, 1.25, 1.5 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 9)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 11.2mm bis 22.4mm\n nur 0.35, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2, 2.5 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 10)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 22.4mm bis 45mm\n nur 0.35, 0.5, 0.75, 1, 1.5, 2, 3, 3.5, 4, 4.5 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 11)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 45mm bis 90mm\n nur 0.35, 0.5, 0.75, 1, 1.5, 2, 3, 4, 5, 5.5, 6 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 12)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 90mm bis 180mm\n nur 0.75, 1, 1.5, 2, 3, 4, 6, 8 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 13)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 180mm bis 355mm\n nur 1, 1.5, 2, 3, 4, 6, 8 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 14)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 355mm bis 500mm\n nur 2, 3, 4, 6, 8 mm erlaubt");
  msgBox->show();
 }
if (fehlernummer == 15)
 {
  msgBox->setText("Fehler:\n Steigung bei Nenndurchmesser\n von > 500mm bis 1000mm\n nur 8 mm erlaubt");
  msgBox->show();
 }
}


void GewindeM::GewindeWerteAnzeigen(void)
{
//theoretische Werte anzeigen
ui->flankendtheo -> setText(QString("%1").arg(d2atheo,0,'f',7));
ui->d3ainp -> setText(QString("%1").arg(d3a,0,'f',7));
ui->D1i_inp -> setText(QString("%1").arg(D1i,0,'f',7));
ui->Rout -> setText(QString("%1").arg(R,0,'f',7));
ui->Sout -> setText(QString("%1").arg(S,0,'f',7));
ui->bohrerd_out -> setText(QString("%1").arg(bohrerd,0,'f',4));

ui->A0Wert_out -> setText(QString("%1").arg(A0Wert,0,'f',6));
ui->TdWert_out -> setText(QString("%1").arg(TdWert,0,'f',6));
ui->d2Wert_out -> setText(QString("%1").arg(Td2Wert,0,'f',6));
ui->Td3Wert_out -> setText(QString("%1").arg(Td3Wert,0,'f',6));

ui->damax_out -> setText(QString("%1").arg(damax,0,'f',7));
ui->damin_out -> setText(QString("%1").arg(damin,0,'f',7));
ui->d2max_out -> setText(QString("%1").arg(d2max,0,'f',7));
ui->d2min_out -> setText(QString("%1").arg(d2min,0,'f',7));
ui->d3max_out -> setText(QString("%1").arg(d3max,0,'f',7));
ui->d3min_out -> setText(QString("%1").arg(d3min,0,'f',7));
ui->Rmin_out -> setText(QString("%1").arg(Rmin,0,'f',5));

ui->AuWert_out -> setText(QString("%1").arg(AuWert,0,'f',7));
ui->TD1Wert_out -> setText(QString("%1").arg(TD1Wert,0,'f',7));
ui->TD2Wert_out -> setText(QString("%1").arg(TD2Wert,0,'f',7));
ui->D1imax_out -> setText(QString("%1").arg(D1imax,0,'f',7));
ui->D1imin_out -> setText(QString("%1").arg(D1imin,0,'f',7));
ui->D2Imax_out -> setText(QString("%1").arg(D2imax,0,'f',7));
ui->D2Imin_out -> setText(QString("%1").arg(D2imin,0,'f',7));

ui->dD_out -> setText(QString("%1").arg(dD,0,'f',6));
ui->C_out -> setText(QString("%1").arg(C,0,'f',6));
ui->Ccalc_out -> setText(QString("%1").arg(Ccalc,0,'f',6));
ui->PruefmassMmax_out -> setText(QString("%1").arg(PruefmassMmax,0,'f',7));
ui->PruefmassMmin_out -> setText(QString("%1").arg(PruefmassMmin,0,'f',7));
ui->AussenGtiefe_out -> setText(QString("%1").arg(AussenGtiefe,0,'f',6));
ui->InnenGtiefe_out -> setText(QString("%1").arg(InnenGtiefe,0,'f',6));

MKN = 0;
if(Nabpl.compare("0") == 0) MKN = 0;
if(Nabpl.compare("3.3") == 0) MKN = 1;
if(Nabpl.compare("2.1") == 0) MKN = 0.5;
if(Nabpl.compare("1.5") == 0) MKN = 0.3;

ui->MKN_out -> setText(QString("%1").arg(MKN,0,'f',4));

}

void GewindeM::berechnen(void)
{

 //Werte für Aussen- und Innengewinde einlesen
 GetGewindeWerte();
 Regelgewindetest();
 CalcGewindewerte();
 NennDSteigungsFehlertest();
 A0Fehlertest();

 if ((fehlernummer == 0) && (fehler == 0))
  {
   SucheDMess();
   GetKorrC();
   PruefmassMmax = d2max + C + (Nx / 1000);
   PruefmassMmin = d2min + C + (Nx/ 1000);
   AussenGtiefe = P * 0.6134;
   InnenGtiefe = P * 0.5413;
   GewindeWerteAnzeigen();
  }
}
