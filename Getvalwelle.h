#ifndef GETVALWELLE_H_INCLUDED
#define GETVALWELLE_H_INCLUDED

//#include "passungen.h"

void EingabeWelle(struct wellenwerte *ew);
void getRowofITArray(struct wellenwerte *ew, char ITBereich[22][5]);
void getITToleranz(struct wellenwerte *ew, double ITBreite[22][22]);
void getWelleSpalte(struct wellenwerte *ew, char Letterwelle[31][15]);
void getwellebeginn(struct wellenwerte *ew, short welle[41][33]);
void getcalcdirectionwelle(struct wellenwerte *ew);
void welleende(struct wellenwerte *ew);
void sortesei(struct wellenwerte *ew);
void getdeltabohrung(struct bohrungswerte *eb, double deltax[14][8]);
void Ausgabe( struct wellenwerte *ew);
void strupr(char ar[]);
void EingabeBohrung(struct bohrungswerte *eb);//double *nennmass, char grundabmass[10], char toleranzgrad[10])
void AusgabeBohrung( struct bohrungswerte *eb);//double nennmass, char grundabmass[10], char toleranzgrad[10])
void getRowofITArray(struct bohrungswerte *eb, char ITBereich[22][5]); //char toleranzgrad[], char ITBereich[22][5])
    // alt war: double nennmass, int itb
    // Sucht die Toleranzbreite
void getITToleranzbohrung(struct bohrungswerte *eb, double ITBreite[22][22]);
void getBohrungSpalte(struct bohrungswerte *eb, char Letterbohrung[32][15]);
void getbohrungbeginn(struct bohrungswerte *eb, short Bohrungen[41][34]);
void getcalcdirectionbohrung(struct bohrungswerte *eb); //char it[])
void bohrungende(struct bohrungswerte *eb);
void sortESEI(struct bohrungswerte *eb);

#endif // GETVALWELLE_H_INCLUDED
