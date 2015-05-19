#include <stdlib.h>
#include <stdio.h>
#include "pelaaja.h"

/*
 * alustaPelaajat - alustaa pelaajien tiedot
 * 
 * Alustaa pelaajien tiedot.
 */
void alustaPelaajat(void) {
  int i;
  for (i = 0; i < MAX_PELAAJIA; i++) {
    pelaajienTiedot.pelaajat[i].nimi[0] = '\0';
    pelaajienTiedot.pelaajat[i].pisteet = 0;
  }
  pelaajienTiedot.pelaajia = 0;
  pelaajienTiedot.nykyinenPelaaja = 0;
}

/*
 * seuraavaPelaaja - siirtää pelivuoron seuraavalle pelaajalle
 * 
 * Paluuarvo Pelaaja * - pelaaja, joka saa pelivuoron
 * 
 * Siirtää pelivuoron seuraavalle pelaajalle.
 */
Pelaaja *seuraavaPelaaja(void) {
  Pelaaja *viimeinen = &pelaajienTiedot.pelaajat[pelaajienTiedot.pelaajia - 1];
  
  if (pelaajienTiedot.nykyinenPelaaja == 0 || pelaajienTiedot.pelaajia < 1) {
    pelaajienTiedot.nykyinenPelaaja = &pelaajienTiedot.pelaajat[0];
  } else if (pelaajienTiedot.nykyinenPelaaja == viimeinen) {
    pelaajienTiedot.nykyinenPelaaja = &pelaajienTiedot.pelaajat[0];
  } else {
    pelaajienTiedot.nykyinenPelaaja++; 
  }
  
  return pelaajienTiedot.nykyinenPelaaja;
}

/*
 * __vertaaPelaajia - vertaa pelaajien pisteitä
 *
 * const void *v1 - 1. pelaaja
 * const void *v2 - 2. pelaaja
 *
 * Pelaajat lajitellaan ensisijaisesti pisteiden mukaan laskevaan
 * järjestykseen ja toissijaisesti nimen perusteella nousevaan
 * järjestykseen.
 *
 */
int __vertaaPelaajia(const void *v1, const void *v2) {
  Pelaaja *p1 = (Pelaaja *)v1;
  Pelaaja *p2 = (Pelaaja *)v2;
  
  int tulos = p2->pisteet - p1->pisteet;
  
  if (tulos == 0) {
    tulos = strcmp(p1->nimi, p2->nimi);
  }
  
  return tulos;
}

/*
 * lajittelePelaajat - lajittelee pelaajat paremmuusjärjestykseen
 * 
 * Lajittelee pelaajat paremmuusjärjestykseen pisteiden mukaan.
 */
void lajittelePelaajat(void) {
  qsort(pelaajienTiedot.pelaajat, pelaajienTiedot.pelaajia, sizeof(Pelaaja), __vertaaPelaajia);
  
  pelaajienTiedot.nykyinenPelaaja = 0;
}
