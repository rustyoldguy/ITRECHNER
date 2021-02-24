#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::Dialog)
{
  ui->setupUi(this);
   this->setWindowTitle("Dialog");

  /*
  ///Bohrungswerte uebertragen
  QD_bohrnennmass = (reinterpret_cast<FitDimensions *>(parent))->bohrnennmass;
  QD_bohrgrundabmass = (reinterpret_cast<FitDimensions *>(parent))->bohrgrundabmass;
  QD_bohrtoleranzgrad = (reinterpret_cast<FitDimensions *>(parent))->bohrtoleranzgrad;
  QD_bohrtolerbreite = (reinterpret_cast<FitDimensions *>(parent))->bohrtolerbreite;
  QD_ESbore = (reinterpret_cast<FitDimensions *>(parent))->bohrbeginn;
  QD_EIbore = (reinterpret_cast<FitDimensions *>(parent))->bohrende;
  QD_bohrgob = (reinterpret_cast<FitDimensions *>(parent))->bohrgob;
  QD_bohrgub  = (reinterpret_cast<FitDimensions *>(parent))->bohrgub;
  QD_deltawert = (reinterpret_cast<FitDimensions *>(parent))->deltawert;
  QD_bohrinttolergrad =   QD_bohrtoleranzgrad.toInt();

  ///Wellenwerte uebertragen
  ///wellebeginn = es;
  ///masswelleende = ei;
  ///GoW -> setText(QString("%1").arg(shaftgow,0,'f',5));
  ///GuW -> setText(QString("%1").arg(shaftguw,0,'f',5));

  QD_nennmass = (reinterpret_cast<FitDimensions *>(parent))->nennmass;
  QD_grundabmass = (reinterpret_cast<FitDimensions *>(parent))->grundabmass;
  QD_inttolergrad = (reinterpret_cast<FitDimensions *>(parent))->inttoleranzgrad;
  QD_tolerbreite = (reinterpret_cast<FitDimensions *>(parent))->tolerbreite;
  QD_wellebeginn = (reinterpret_cast<FitDimensions *>(parent))->wellebeginn;
  QD_masswelleende = (reinterpret_cast<FitDimensions *>(parent))->masswelleende;
  QD_rechenrichtung = (reinterpret_cast<FitDimensions *>(parent))->rechenrichtung;
  QD_shaftgow= (reinterpret_cast<FitDimensions *>(parent))->shaftgow;
  QD_shaftguw = (reinterpret_cast<FitDimensions *>(parent))->shaftguw;
*/
  copyvalues(parent);

  //Nachricht= QString("Beginn dialog");
  //ui->textEdit->append(Nachricht);

  /// Berechne Werte fuer Massverkoerperungen
  getTfeld();        /// Werte fuer Grenzlehrdorne
  getWelleTFeld();   /// Werte fuer Grenzrachenlehren


  /// Zeige Werte für Massverkoerperungen von Innenmassen
  showborevalues();

  ///Ausgabe der Werte fuer Einheitswelle
  showshaftvalues();


  QD_diffmax = QD_bohrgob - QD_shaftguw;
  QD_diffmin = QD_bohrgub - QD_shaftgow;

  if((QD_diffmax >= 0)&&(QD_diffmin >= 0))
   {
    Nachricht= QString("Spielpassung");
    ui->textEdit->append(Nachricht);
   }

  if((QD_diffmax >= 0) && (QD_diffmin <= 0))
   {
    Nachricht= QString("Uebergangspassung");
    ui->textEdit->append(Nachricht);
   }

  if((QD_diffmax <= 0) && (QD_diffmin <= 0))
   {
    Nachricht= QString("Uebermasspassung");
    ui->textEdit->append(Nachricht);
   }
  Nachricht= QString("Maxdiff: %1 mm").arg(QD_diffmax,0,'f',6);
  ui->textEdit->append(Nachricht);
  Nachricht= QString("mindiff: %1 mm").arg(QD_diffmin,0,'f',6);
  ui->textEdit->append(Nachricht);

  connect(ui->pB_kopieren,    SIGNAL (clicked()),  this, SLOT(kopieren() ) );
  connect(ui->pB_Ende,        SIGNAL (clicked()),  this, SLOT(close() ) );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getTfeld()
{
int i, spalte = 0;

/// Werte fuer Grenzlehrdorne
short B_t_feld[13][14]=
{
//0 1       2   3     4     5     6    7     8      9    10    11    12    13
{1,   3,    6,  10,   18,   18,   30,   50,   80,  120,  180,  250,  315,  400},   // von, Zeile 0
{3,   6,   10,  18,   30,   30,   50,   80,  120,  180,  250,  315,  400,  500},   // bis, Zeile 1
{6,	  6,    8,   9,	  11,   13,	  16,   19,	  22,   25,	  29,   32,	  36,   40},   // ab Qualität 6, Zeile 2
{7,	 10,   12,  15,	  18,   21,	  25,   30,	  35,   40,	  46,   52,	  57,   63},   // 3
{8,	 14,   18,  22,	  27,   33,	  39,   46,	  54,   63,	  72,   81,	  89,   97},   // 4
{9,	 25,   30,  36,	  43,   52,	  62,   74,	  87,  100,  115,  130,  140,  115},   // 5
{10, 40,   48,  58,   70,   84,  100,  120,  140,  160,  185,  210,  230,  250},   // 6
{11, 60,   75,  90,	 110,  130,  160,  190,  220,  250,  290,  320,  360,  400},   // 7
{12, 100,  20,  50,	 180,  210,  250,  300,  350,  400,  460,  520,  570,  630},   // 8
{13, 140, 180, 220,  270,  330,  390,  460,  540,  630,  720,  810,  890,  970},   // 9
{14, 250, 300, 360,  430,  520,  620,  740,  870, 1000, 1150, 1300, 1400, 1150},   // 10
{15, 400, 480, 580,  700,  840, 1000, 1200, 1400, 1600, 1850, 2100, 2300, 2500},   // 11
{16, 600, 750, 900, 1100, 1300, 1600, 1900, 2200, 2500, 2900, 3200, 3600, 4000}};  // bis Qualität 16

double B_z_feld[13][14]= {
{0,   1,   3,     6,   10,   18,   30,    50,   80,  120,  180,  250,  315, 400},   // von
{0,   3,   6,    10,   18,   30,   50,    80,  120,  180,  250,  315,  400, 500},   // bis
{6,   1, 1.5,   1.5,    2,	  2,  2.5,	 2.5,	 3,	   4,	 5,	   6,	7,	  8},   // ab Qualität 6
{7, 1.5,   2,     2,  2.5,	  3,  3.5,	   4,	 5,	   6,	 7,	   8,   10,	 11},
{8,	  2,   3,     3,    4,	  5,    6,     7,	 8,	   9,   12,	  14,   16,	 18},
{9,	  5,   6,     7,    8,	  9,   11,	  13,   15,	  18,	 2,   24,   28,	 32},
{10,  5,   6,     7,    8,	  9,   11,	  13,   15,	  18,   24,	  27,   32,	 37},
{11, 10,  12,    14,   16,	 19,   22,	  25,   26,	  32,   40,	  45,   50,	 55},
{12, 10,  12,    14,   16, 	 19,   22,	  25,   26,	  32,   45,	  50,   65,	 70},
{13, 20,  24,    28,   32,	 36,   42,	  48,   54,	  60,   80,	  90,  100, 110},
{14, 20,  24,    28,   32,	 36,   42,	  48,   54,	  60,  100,	 110,  125, 145},
{15, 40,  48,    56,   64,	 72,   80,	  90,  100,	 110,  170,	 190,  210, 240},
{16, 40,  48,    56,   64,   72,   80,	  90,  100,  110,  210,	 240,  280, 320}};

double B_hh_feld[13][14]= {
{0,    1,     3,     6,   10,   18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
{0,    3,     6,    10,   18,   30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
{6,	 0.6,  0.75,  0.75,	   1, 1.25,	 1.25,	 1.5,	 2,	 2.5,  3.5,	   4,  4.5,	    5},
{7,	   1,  1.25,  1.25,  1.5,    2,	    2,	 2.5,	 3,	   4,	5,	   6,  7.5,	  7.5},
{8,	   1,  1.25,  1.25,  1.5,    2,	    2,	 2.5,	 3,	   4,	5,	   6,  6.5,	  7.5},
{9,	   1,  1.25,  1.25,  1.5,    2,	    2,	 2.5,	 3,	   4,	5,	   6,  6.5,	  7.5},
{10,   1,  1.25,  1.25,  1.5,    2,	    2,	 2.5,	 3,	   4,	5,	   6,  6.5,	  7.5},
{11,   2,   2.5,     3,	   4,  4.5,	  5.5,	 6.5,  7.5,	   9,   10, 11.5, 12.5,	 13.5},
{12,   2,   2.5,     3,	   4,  4.5,	  5.5,	 6.5,  7.5,	   9,   10, 11.5, 12.5,	 13.5},
{13,   5,	  6,   7.5,	   9, 10.5,	 12.5,	  15, 17.5,	  20,   23,	  26, 28.5,	 31.5},
{14,   5,	  6,   7.5,	   9, 10.5,	 12.5,	  15, 17.5,	  20,   23,	  26, 28.5,	 31.5},
{15,   5,	  6,   7.5,	   9, 10.5,	 12.5,	  15, 17.5,	  20,   23,	  26, 28.5,	 31.5},
{16,   5,	  6,   7.5,	   9, 10.5,	 12.5,	  15, 17.5,	  20,   23,	  26, 28.5,	 31.5}};

double B_y_feld[13][14]= {
{0,   1,    3,      6,   10,    18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
{0,   3,    6,     10,   18,    30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
{6,	  1,	1,	   1,  1.5,	  1.5,	   2,     2,	3,	  3,	4,	  5,	6,	   7},
{7,	1.5,  1.5,	 1.5,	 2,	    3,	   3,	  3,	4,	  4,	6,	  7,	8, 	   9},
{8,	  3,	3,	   3,	 4,	    4,	   5,	  5,	6,	  6,	7,	  9,	9,	  11},
{9,	  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{10,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{11,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{12,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{13,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{14,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{15,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0},
{16,  0,	0,	   0,	 0,	    0,	   0,	  0,	0,	  0,	0,	  0,	0,	   0}};

double B_a_feld[13][14]= {
{0,    1,    3,     6,   10,    18,    30,    50,   80,  120,   180, 250,  315,   400},   // von
{0,    3,    6,    10,   18,    30,    50,    80,  120,  180,   250, 315,  400,   500},   // bis
{6,    0,    0,     0,    0,     0,     0,     0,    0,    0,     0,   6,    7,	    8},
{7,    0,    0,     0,    0,     0,     0,     0,    0,    0,     0,   8,   10,	   11},
{8,    0,    0,     0,    0,     0,     0,     0,    0,    0,     0,  14,   16,	   18},
{9,    0,    0,     0,    0,     0,     0,     0,    0,    0,     0,  24,   28,    32},
{10,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0,  27,   32,    37},
{11,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0,  45,   50,    55},
{12,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0,  50,   65,	   70},
{13,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0,  90,  100,   110},
{14,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0, 110,  125,   145},
{15,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0, 190,  210,	  240},
{16,   0,    0,     0,    0,     0,     0,     0,    0,    0,     0, 240,  280,   320}};

double B_hsh_feld[13][14]= {
{0,    1,    3,     6,   10,    18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
{0,    3,    6,    10,   18,    30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
{6,    0,    0,  0.75,	 1,	  1.25,	 1.25,	 1.5,	 2,	 2.5,  3.5,	   4,  4.5,	    5},
{7,    0,    0,  0.75,	 1,	  1.25,	 1.25,	 1.5,	 2,	 2.5,  3.5,    4,  4.5,	    5},
{8,    0,    0,  0.75, 	 1,	  1.25,	 1.25,	 1.5,	 2,	 2.5,  3.5,	   4,  4.5,	    5},
{9,    0,    0,  0.75,	 1,   1.25,	 1.25,	 1.5,	 2,	 2.5,  3.5,	   4,  4.5,	    5},
{10,   0,    0,  0.75,	 1,   1.25,	 1.25,	 1.5,	 2,	 2.5,  3.5,	   4,  4.5,	    5},
{11,   0,    0,     2,  2.5,     3,	  3.5,	   4,	 5,	   6,	 7,	   8,	 9,	   10},
{12,   0,    0,     2,  2.5,     3,	  3.5,	   4,	 5,	   6,	 7,	   8,	 9,	   10},
{13,   0,    0,   4.5,  5.5,   6.5,	    8,	 9.5,   11, 12.5, 14.5,	  16,   18,	   20},
{14,   0,    0,   4.5,  5.5,   6.5,	    8,	 9.5,   11, 12.5, 14.5,	  16,   18,	   20},
{15,   0,    0,   4.5,  5.5,   6.5,	    8,	 9.5,   11, 12.5, 14.5,	  16,   18,	   20},
{16,   0,    0,   4.5,  5.5,   6.5,	    8,	 9.5,   11, 12.5, 14.5,	  16,   18,	   20}};



// Suche Spalte zum auslesen des T-Wertes
  for (i = 0; i < 14; i++)
    if((QD_bohrnennmass >=  B_t_feld[0][i]) && (QD_bohrnennmass <=  B_t_feld[1][i]))
     {
      spalte = i;
      break;
     }

  for (i = 2; i < 13; i++)
      if(QD_bohrinttolergrad ==  B_t_feld[i][0])
       {
        T_Wert =  B_t_feld[i][spalte];
        z_Wert =  B_z_feld[i][spalte];
        hh_Wert = B_hh_feld[i][spalte];
        y_Wert = B_y_feld[i][spalte];
        a_Wert = B_a_feld[i][spalte];
        hsh_Wert = B_hsh_feld[i][spalte];
        break;
       }
  ///Berechnung der Werte fuer Grenzlehrdorne
  /// nOberes Abmaß..: " << eb.bohrbeginn
  ///  Unteres Abmaß.: " << eb.bohrende;
    QD_bohrbeginn = QD_ESbore;
    QD_bohrende = QD_EIbore;
    GLD_EI_neu_max = QD_bohrnennmass + QD_bohrende + (z_Wert * 0.001) + (hh_Wert * 0.001);
    GLD_EI_neu_min = QD_bohrnennmass + QD_bohrende + (z_Wert * 0.001) - (hh_Wert * 0.001);
    /// aplha-Werte sind erst an 180mm Nennmass vorhanden
    GLD_EI_alt = QD_bohrnennmass - (y_Wert / 1000) + (a_Wert / 1000);
    GLD_ES_max = QD_bohrnennmass + QD_bohrbeginn + (hh_Wert / 1000);
    GLD_ES_min = QD_bohrnennmass + QD_bohrbeginn - (hh_Wert / 1000);

    /// Berechnung der Werte fuer Kugelendmasse
    GLS_EI_neu_max = QD_bohrnennmass + QD_bohrende + (z_Wert / 1000) + (hsh_Wert / 1000);
    GLS_EI_neu_min = QD_bohrnennmass + QD_bohrende + (z_Wert / 1000) - (hsh_Wert / 1000);
      /// aplha-Werte sind erst an 180mm Nennmass vorhanden
    GLS_EI_alt = QD_bohrnennmass - (y_Wert / 1000) + (a_Wert / 1000);
    GLS_ES_max = QD_bohrnennmass + QD_bohrbeginn + (hsh_Wert / 1000);
    GLS_ES_min =  QD_bohrnennmass + QD_bohrbeginn - (hsh_Wert / 1000);

}
//-------------Ende von getTfeld-------------------

void Dialog::getWelleTFeld(void)
{
 int i, spalte = 0;

 z1_Wert = 0;
 y1_Wert = 0;
 hp2_Wert = 0;
 h12_Wert = 0;
 Tw_Wert = 0;
 a1_Wert = 0;

    ///Werte fuer Grenzrachenlehren
    double W_z1_Feld[14][14] = {
    {0,    1,     3,     6,   10,    18,   30,    50,    80,  120,  180,  250,  315,    400},   // von
    {0,    3,     6,    10,   18,    30,   50,    80,   120,  180,  250,  315,  400,    500},   // bis
    {5,	   1,	  1,     1,	 1.5,   1.5,    2,     2,   2.5,    3,	  4,    4,	  6,	 7},
    {6,	 1.5,	  2,     2,	 2.5,	  3,  3.5,	   4,	  5,    6,	  7,    8,	 10,	11},
    {7,	 1.5,	  2,     2,	 2.5,	  3,  3.5,	   4,	  5,    6,	  7,    8,	 10,	11},
    {8,	   2,	  3,     3,	   4,	  5,    6,	   7,	  8,    9,	 12,   14,	 16,	18},
    {9,	   5,	  6,     7,	   8,	  9,   11,	  13,	 15,   18,	 21,   24,	 28,	32},
    {10,   5,	  6,     7,	   8,	  9,   11,	  13,	 15,   18,	 24,   27,	 32,	37},
    {11,  10,	 12,    14,	  16,	 19,   22,	  25,	 28,   32,	 40,   45,	 50,	55},
    {12,  10,	 12,    14,	  16,	 19,   22,	  25,	 28,   32,	 45,   50,	 65,	70},
    {13,  20,	 24,    28,	  32,	 36,   42,	  48,	 54,   60,	 80,   90,	100,   110},
    {14,  20,	 24,    28,	  32,	 36,   42,	  48,	 54,   60,	100,  110,	125,   145},
    {15,  40,	 48,    56,	  64,	 72,   80,	  90,   100,  110,	170,  190,	210,   240},
    {16,  40,	 48,    56,	  64,	 72,   80,	  90,   100, 110,	210,  240,	280,   320}};

    double W_y1_Feld[14][14]= {
    {0,    1,    3,      6,   10,    18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
    {0,    3,    6,     10,   18,    30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
    {5,	   1,	 1,	     1,	 1.5,	  2,     2,	    2,	  3,	3,	  3,    3,	 4,	     4},
    {6,	 1.5,  1.5,	   1.5,	   2,	  3,     3,	    3,	  4,	4,	  5,    6,	 6,	     7},
    {7,	 1.5,  1.5,	   1.5,	   2,	  3,	 3,	    3,	  4,	4,	  6,    7,	 8,	     9},
    {8,	   3,	 3,	     3,	   4,	  4,	 5,	    5,	  6,	6,	  7,    9,	 9,	    11},
    {9,	   0,	 0,	     0,	   0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {10,   0, 	 0,	     0,	   0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {11,   0,	 0,	     0,	   0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {12,   0,	 0,	     0,    0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {13,   0,	 0,	     0,	   0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {14,   0,	 0,	     0,    0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {15,   0,	 0,	     0,	   0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,	     0},
    {16,   0,	 0,	     0,    0,	  0,	 0,	    0,	  0,	0,	  0,    0,	 0,   	 0}};
    double W_hp2_Feld[14][14]= {
    {0,    1,     3,     6,   10,    18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
    {0,    3,     6,    10,   18,    30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
    {5,	 0.4,   0.5,   0.5,	 0.6,  0.75,  0.75,	    1, 1.25, 1.75, 2.25,    3,	3.5,	 4},
    {6,  0.4,   0.5,   0.5,	 0.6,  0.75,  0.75,	    1, 1.25, 1.75, 2.25,    3,	3.5,	 4},
    {7,	 0.4,   0.5,   0.5,	 0.6,  0.75,  0.75,	    1, 1.25, 1.75, 2.25,    3,	3.5,	 4},
    {8,	 0.6,  0.75,  0.75,	   1,  1.25,  1.25,	  1.5,	  2,  2.5,  3.5,    4,	4.5,	 5},
    {9,	 0.6,  0.75,  0.75,	   1,  1.25,  1.25,   1.5,    2,  2.5,  3.5,    4,	4.5,	 5},
    {10, 0.6,  0.75,  0.75,	   1,  1.25,  1.25,	  1.5,	  2,  2.5,  3.5,    4,	4.5,     5},
    {11, 0.6,  0.75,  0.75,	   1,  1.25,  1.25,	  1.5,	  2,  2.5,  3.5,    4,	4.5,	 5},
    {12, 0.6,  0.75,  0.75,	   1,  1.25,  1.25,	  1.5,	  2,  2.5,  3.5,    4,	4.5,	 5},
    {13,   1,  1.25,  1.25,	 1.5,     2,     2,	  2.5,	  3,    4,	  5,    6,	6.5,   7.5},
    {14,   1,  1.25,  1.25,	 1.5,     2,     2,	  2.5,	  3,    4,	  5,    6,	6.5,   7.5},
    {15,   1,  1.25,  1.25,	 1.5,     2,     2,	  2.5,	  3,    4,	  5,    6,	6.5,   7.5},
    {16,   1,  1.25,  1.25,	 1.5,     2,     2,	  2.5,	  3,    4,	  5,    6,	6.5,   7.5}};

    double W_h12_Feld[14][14]= {
    {0,    1,     3,     6,   10,    18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
    {0,    3,     6,    10,   18,    30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
    {5,	 0.6,  0.75,  0.75,	   1,  1.25,  1.25,	  1.5,	  2,  2.5,  3.5,    4,  4.5,     5},
    {6,	   1,  1.25,  1.25,	 1.5,     2,  	2,	 2.5,	  3,    4,	  5,	6,  6.5,   7.5},
    {7,	   1,  1.25,  1.25,	 1.5, 	  2,     2,	 2.5,	  3,    4,	  5,	6,  6.5,   7.5},
    {8,	 1.5,	  2,     2,	 2.5,	  3,   3.5,	   4,	  5,    6,	  7,    8, 	  9,    10},
    {9,	 1.5,	  2,     2,	 2.5,	  3,   3.5,	   4,	  5,    6,	  7,    8, 	  9,    10},
    {10, 1.5,     2,     2,	 2.5,	  3,   3.5,	   4,	  5,    6,	  7,    8,	  9,    10},
    {11,   2,   2.5,     3,	   4,   4.5,   5.5,	 6.5,   7.5,    9,	 10, 11.5, 12.5,  13.5},
    {12,   2,   2.5,     3,	   4,   4.5,   5.5,	 6.5,   7.5,    9,	 10, 11.5, 12.5,  13.5},
    {13,   5,	  6,   7.5,	   9,  10.5,  12.5,	  15,  17.5,   20,	 23,   26, 28.5,  31.5},
    {14,   5,	  6,   7.5,	   9,  10.5,  12.5,	  15,  17.5,   20,	 23,   26, 28.5,  31.5},
    {15,   5,	  6,   7.5,	   9,  10.5,  12.5,	  15,  17.5,   20,	 23,   26, 28.5,  31.5},
    {16,   5,	  6,   7.5,	   9,  10.5,  12.5,	  15,  17.5,   20,	 23,   26, 28.5,  31.5}};

    short W_Tw_Feld[14][14]= {
    {0,    1,     3,     6,   10,    18,    30,    50,   80,  120,  180,  250,  315,    400},   // von
    {0,    3,     6,    10,   18,    30,    50,    80,  120,  180,  250,  315,  400,    500},   // bis
    {5,	   4,	  5,     6,    8,	  9,    11,	   13,	 15,   18,   20,   23,	 25,     27},
    {6,	   6,	  8,     9,	  11,	 13,    16,	   19,	 22,   25,   29,   32,	 36,     40},
    {7,	  10,	 12,    15,	  18,	 21,    25,	   30,	 35,   40,	 46,   52,	 57,     63},
    {8,	  14,	 18,    22,	  27,	 33,    39,	   46,	 54,   63,	 72,   81,	 89,     97},
    {9,	  25,	 30,    36,	  43,	 52,    62,	   74,	 87,  100,  115,  130,  140,    155},
    {10,  40,	 48,    58,	  70,	 84,   100,	  120,	140,  160,  185,  210,	230,	250},
    {11,  60,	 75,    90,	 110,   130,   160,	  190,	220,  250,  290,  320,	360,	400},
    {12, 100,   120,   150,	 180,   210,   250,	  300,	350,  400,	460,  520,	570,	630},
    {13, 140,   180,   220,  270,   330,   390,	  460,	540,  630,  720,  810,	890,	970},
    {14, 250,   300,   360,	 430,   520,   620,	  740,	870, 1000, 1150, 1300, 1400,   1550},
    {15, 400,   480,   580,	 700,   840,  1000,	 1200, 1400, 1600, 1850, 2100, 2300,   2500},
    {16, 600,   750,   900, 1100,  1300,  1600,	 1900, 2200, 2500, 2900, 3200, 3600,   4000}};

    double W_a1_Feld[14][14] = {
    {0,    1,    3,    6,    10,    18,    30,    50,   80,  120,  180,  250,  315,   400},   // von
    {0,    3,    6,   10,    18,    30,    50,    80,  120,  180,  250,  315,  400,   500},   // bis
    {5,	   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,	 1,	 1.5,  2.5,	    3},
    {6,	   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,	 2,	   3,	 4,	    5},
    {7,	   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,	 3,	   4,	 6,	    7},
    {8,	   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,	 4,	   6,	 7,	    9},
    {9,	   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,	 4,	   6,	 7,	    9},
    {10,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,	 7,	   9,   11,	   14},
    {11,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,   10,	  15,   15,	   20},
    {12,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,   15,	  20,   30,	   35},
    {13,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,   25,	  35,   45,	   55},
    {14,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,   45,	  55,   70,	   90},
    {15,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,   70,	  90,  110,	  140},
    {16,   0,	 0,	   0,	  0,     0,	    0,	   0,	 0,	   0,  110,	 140,  180,	  220}};



       /// Suche Spalte zum auslesen des T-Wertes per Nennmass
      for (i = 0; i < 14; i++)
        if((QD_nennmass >=  W_Tw_Feld[0][i]) && (QD_nennmass <=  W_Tw_Feld[1][i])) //Zeile 0 und 1
         {
          //std::cout << "\nNennmassbereich: "<< Welle_Tw_Feld[0][i] << "  bis " <<  Welle_Tw_Feld[1][i] << std::endl;
          spalte = i;
          break;
         }

      /// Suche Zeile per Toleranzgrad
        for (i = 2; i < 14; i++)
         {
          //QString	arg(double a,    int fieldWidth = 0, char format = 'g', int precision = -1,               QChar fillChar = QLatin1Char( ' ' )) const
          //QString	arg(short int a, int fieldWidth = 0, int base = 10,     QChar fillChar = QLatin1Char( ' ' )) const
            //Nachricht = (QString("QD_inttolergrad %1").arg(QD_inttolergrad,0,'f',5));
            //Nachricht = (QString("QD_inttolergrad %1").arg(QD_inttolergrad));
           // ui->textEdit->append(Nachricht);

          if(QD_inttolergrad ==  W_Tw_Feld[i][0]) // Zeile i und Spalte 0
           {
            //std::cout << "\nZeile: "<< Welle_Tw_Feld[0][i] << "  bis " <<  Welle_Tw_Feld[1][i] << std::endl;
            z1_Wert =  W_z1_Feld[i][spalte];
            y1_Wert = W_y1_Feld[i][spalte];
            hp2_Wert = W_hp2_Feld[i][spalte];
            h12_Wert = W_h12_Feld[i][spalte];
            Tw_Wert =  W_Tw_Feld[i][spalte];
            a1_Wert =  W_a1_Feld[i][spalte];

            Nachricht= QString("Suche Zeile per Toleranzgrad");
            ui->textEdit->append(Nachricht);
            break;
           }
         }
        ///Berechnung der Werte fuer GrenzRachenlehren
         GRL_es_neu_max = QD_nennmass + QD_beginn - (z1_Wert / 1000) + (h12_Wert / 1000);
         GRL_es_neu_min = QD_nennmass + QD_beginn - (z1_Wert / 1000) - (h12_Wert / 1000);
         GRL_es_alt = QD_nennmass + QD_beginn + (y1_Wert / 1000) - (a1_Wert / 1000);
         GRL_ei_max = QD_nennmass + QD_ende + (h12_Wert / 1000) + (a1_Wert / 1000);
         GRL_ei_min = QD_nennmass + QD_ende - (h12_Wert / 1000) + (a1_Wert / 1000);

}
//-------------Ende von getWelleTfeld-------------------

// Ermoeglicht das Kopieren von Text aus dem Textfenster in andere Applikationen
void Dialog::kopieren(void)
{
QTextCursor cursor = ui->textEdit->textCursor();
cursor.select(QTextCursor::BlockUnderCursor);
ui->textEdit->copy();
//textEdit2->paste();
}

void Dialog::showshaftvalues(void)
{


    if(QD_nennmass > 0.001)
    {
    ///Ausgabe der Werte fuer Einheitswelle
    Nachricht= QString("\nWerte fuer Einheitswelle");
    ui->textEdit->append(Nachricht);
    Nachricht = QString("Nennmass: %1 mm").arg(QD_nennmass,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht = QString("Grundabmass: ") + QD_grundabmass;
    ui->textEdit->append(Nachricht);
    //  Nachricht = QString("Toleranzgrad: %1").arg(QD_inttolergrad,0,'f',5);
    Nachricht = QString("Toleranzgrad: ").append(QString::number(QD_inttolergrad));
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Toleranzbreite: %1 mm").arg(QD_tolerbreite,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("es %1 mm").arg(QD_wellebeginn,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("es: %1 mm").arg(QD_masswelleende,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("GoW: %1 mm").arg(QD_shaftgow,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("GuW: %1 mm").arg(QD_shaftguw,0,'f',5);
    ui->textEdit->append(Nachricht);

    ///Ausgabe der Werte fuer Grenzrachenlehren
    Nachricht= QString("QD-beginn: %1 µm").arg(QD_beginn,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("QD-ende: %1 µm").arg(QD_ende,0,'f',5);
    ui->textEdit->append(Nachricht);

    Nachricht= QString("z1-Wert: %1 µm").arg(z1_Wert,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("h1/2-Wert: %1 µm").arg(h12_Wert,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("y1-Wert: %1 µm").arg(y1_Wert,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("alpha-Werte sind erst ab 180mm Nennmass vorhanden");
    ui->textEdit->append(Nachricht);
    Nachricht= QString("a1-Wert: %1 µm").arg(a1_Wert,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Gut-Seite neu: %1 mm").arg(GRL_es_neu_max,0,'f',5) +  QString(" bis: %1 mm").arg(GRL_es_neu_min,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Gut-Seite abgenutzt: %1 µm").arg(GRL_es_alt,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Ausschuss-Seite: %1 mm").arg(GRL_ei_max,0,'f',5) +  QString(" bis: %1 mm").arg(GRL_ei_min,0,'f',5);
    ui->textEdit->append(Nachricht);
    }
}

void Dialog::showborevalues(void)
{
    /// Werte fuer Einheitsbohrung  ausgeben
   if(QD_bohrnennmass > 0.001)
    {
     Nachricht= QString("Werte fuer Einheitsbohrung");
    ui->textEdit->append(Nachricht);

    //Nennmass);
    Nachricht = QString("Nennmass: %1 mm").arg(QD_bohrnennmass,0,'f',5);
    ui->textEdit->append(Nachricht);

    Nachricht = QString("Grundabmass: ") + QD_bohrgrundabmass;
    ui->textEdit->append(Nachricht);

    Nachricht = QString("Toleranzgrad: ") + QD_bohrtoleranzgrad;
    ui->textEdit->append(Nachricht);

    Nachricht= QString("Toleranzbreite: %1 mm").arg(QD_bohrtolerbreite,0,'f',5);
    ui->textEdit->append(Nachricht);

    Nachricht= QString("ES %1 mm").arg(QD_ESbore,0,'f',5);
    ui->textEdit->append(Nachricht);

    Nachricht= QString("EI: %1 mm").arg(QD_EIbore,0,'f',5);
    ui->textEdit->append(Nachricht);

    Nachricht= QString("GoB: %1 mm").arg(QD_bohrgob,0,'f',5);
    ui->textEdit->append(Nachricht);

    Nachricht= QString("GuB: %1 mm").arg(QD_bohrgub,0,'f',5);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Deltawert: %1 mm").arg(QD_deltawert,0,'f',5);
    ui->textEdit->append(Nachricht);



    Nachricht= QString("T-Wert: %1 µm").arg(T_Wert,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("z-Wert: %1 µm").arg(z_Wert,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("hh-Wert: %1 µm").arg(hh_Wert,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("y-Wert: %1 µm").arg(y_Wert,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Gut-Seite neu...........: %1 mm").arg(GLD_EI_neu_max,0,'f',6) + QString(" bis %1 mm").arg(GLD_EI_neu_min,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Gut-Seite abgenutzt.....: %1 mm").arg(GLD_EI_alt,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Ausschuß-Seite abgenutzt: %1 mm").arg(GLD_ES_max,0,'f',6) + QString(" bis %1 mm").arg(GLD_ES_min,0,'f',6) ;
    ui->textEdit->append(Nachricht);

    ///Ausgabe der Werte fuer Kugelendmasse
    Nachricht= QString("Werte fuer Kugelendmasse:");
    ui->textEdit->append(Nachricht);
    Nachricht= QString("hsh-Wert: %1 µm").arg(hsh_Wert,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Gut-Seite neu...........: %1 mm").arg(GLS_EI_neu_max,0,'f',6) + QString(" bis %1 mm").arg(GLS_EI_neu_min,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Gut-Seite abgenutzt.....: %1 mm").arg(GLS_EI_alt,0,'f',6);
    ui->textEdit->append(Nachricht);
    Nachricht= QString("Ausschuß-Seite abgenutzt: %1 mm").arg(GLS_ES_max,0,'f',6) + QString(" bis %1 mm").arg(GLS_ES_min,0,'f',6) ;
    ui->textEdit->append(Nachricht);
    }
}

void Dialog::copyvalues(QWidget *parent)
{
    ///Bohrungswerte uebertragen
    QD_bohrnennmass = (reinterpret_cast<FitDimensions *>(parent))->bohrnennmass;
    QD_bohrgrundabmass = (reinterpret_cast<FitDimensions *>(parent))->bohrgrundabmass;
    QD_bohrtoleranzgrad = (reinterpret_cast<FitDimensions *>(parent))->bohrtoleranzgrad;
    QD_bohrtolerbreite = (reinterpret_cast<FitDimensions *>(parent))->bohrtolerbreite;
    QD_ESbore = (reinterpret_cast<FitDimensions *>(parent))->bohrbeginn;
    QD_EIbore = (reinterpret_cast<FitDimensions *>(parent))->bohrende;
    QD_bohrgob = (reinterpret_cast<FitDimensions *>(parent))->bohrgob;
    QD_bohrgub  = (reinterpret_cast<FitDimensions *>(parent))->bohrgub;
    QD_deltawert = (reinterpret_cast<FitDimensions *>(parent))->deltawert;
    QD_bohrinttolergrad =   QD_bohrtoleranzgrad.toInt();

    ///Wellenwerte uebertragen
    ///wellebeginn = es;
    ///masswelleende = ei;
    ///GoW -> setText(QString("%1").arg(shaftgow,0,'f',5));
    ///GuW -> setText(QString("%1").arg(shaftguw,0,'f',5));

    QD_nennmass = (reinterpret_cast<FitDimensions *>(parent))->nennmass;
    QD_grundabmass = (reinterpret_cast<FitDimensions *>(parent))->grundabmass;
    QD_inttolergrad = (reinterpret_cast<FitDimensions *>(parent))->inttoleranzgrad;
    QD_tolerbreite = (reinterpret_cast<FitDimensions *>(parent))->tolerbreite;
    QD_wellebeginn = (reinterpret_cast<FitDimensions *>(parent))->wellebeginn;
    QD_masswelleende = (reinterpret_cast<FitDimensions *>(parent))->masswelleende;
    QD_rechenrichtung = (reinterpret_cast<FitDimensions *>(parent))->rechenrichtung;
    QD_shaftgow= (reinterpret_cast<FitDimensions *>(parent))->shaftgow;
    QD_shaftguw = (reinterpret_cast<FitDimensions *>(parent))->shaftguw;
    QD_beginn = (reinterpret_cast<FitDimensions *>(parent))->wellebeginn;
    QD_ende = (reinterpret_cast<FitDimensions *>(parent))->masswelleende;

   // Nachricht= QString("*******QD-beginn: %1 µm").arg(QD_beginn,0,'f',5);
   // ui->textEdit->append(Nachricht);
   // Nachricht= QString("*******QD-ende: %1 µm").arg(QD_ende,0,'f',5);
   // ui->textEdit->append(Nachricht);
}
