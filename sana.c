#include <string.h>
#include <stdlib.h>
#include "sana.h"
#include "utils.h" // #include <stdio.h>

/*
 * __peitaKirjain - peittää sanasta kirjaimen
 *
 * Sana *sana - muokattava sana
 *
 * Valitsee sanasta sattumanvaraisesti jonkun kirjaimen ja peittää sen kaikki
 * esiintymät annetusta sanasta. Kyseinen kirjain voi olla jo peitetty, jolloin
 * ei tapahdu mitään.
 *
 */
void __peitaKirjain(Sana *sana) {
  int pituus = strlen(sana->peitetty);
  int indeksi = satunnaisluku(0, pituus);
  char alkuperainen = sana->alkuperainen[indeksi];

  if (sana->peitetty[indeksi] != '*') {
    int i;
    for (i = 0; i < pituus; i++) {
      if (sana->alkuperainen[i] == alkuperainen) {
        sana->peitetty[i] = '*';
      }
    }
  }
}

/*
 * __avaaKirjain - poistaa peitteen sanan yhdeltä kirjaimelta
 *
 * Sana *sana - muokattava sana
 *
 * Valitsee sanasta sattumanvaraisesti jonkun kirjaimen ja poistaa peitteen sen
 * kaikista esiintymistä annetussa sanassa. Kyseinen kirjain ei ole välttämättä
 * peitetty, jolloin ei tapahdu mitään.
 *
 */
void __avaaKirjain(Sana *sana) {
  int pituus = strlen(sana->peitetty);
  int indeksi = satunnaisluku(0, pituus);
  char alkuperainen = sana->alkuperainen[indeksi];

  if (sana->peitetty[indeksi] == '*') {
    int i;
    for (i = 0; i < pituus; i++) {
      if (sana->alkuperainen[i] == alkuperainen) {
        sana->peitetty[i] = sana->alkuperainen[i];
      }
    }
  }
}

/*
 * __tahtia - laskee tähtien määrän peitetystä sanasta
 *
 * Sana *sana - sana, josta tähdet lasketaan
 *
 * Paluuarvo int - tähtien lukumäärä
 *
 * Laskee tähtien lukumäärän annetusta sanasta.
 *
 */
int __tahtia(Sana *sana) {
  int pituus = strlen(sana->peitetty);
  int tahtia = 0;

  int i;
  for (i = 0; i < pituus; i++) {
    if (sana->peitetty[i] == '*') {
      tahtia++;
    }
  }

  return tahtia;
}

/*
 * __peitaSana - peittää annetun sanan
 *
 * Sana *sana - muokattava sana
 *
 * Peittää sanasta sattumanvaraisesti 50 % ± > 10 %. Jos sanan kaikkien
 * kirjainten joukosta K ei voida valita osajoukkoa K', joiden esiintymien
 * yhteenlaskettu määrä on 50 % ± > 10 % sanan kokonaispituudesta, funktio jää
 * ikuiseen silmukkaan. Esimerkki tällaisesta on sana 'aaaa'.
 *
 */
void __peitaSana(Sana *sana) {
  // alustetaan peitetty sana
  strcpy(sana->peitetty, sana->alkuperainen);

  double pituus = (double) strlen(sana->peitetty);

  double peitetty = 0;
  while (peitetty < 0.4 || peitetty > 0.6) {
    if (peitetty < 0.5) {
      __peitaKirjain(sana);
    } else {
      __avaaKirjain(sana);
    }

    peitetty = __tahtia(sana) / pituus;
  }
}

/*
 * __laskeKirjaimet - laskee sanan eri kirjainten määrän
 *
 * Sana *sana - sana, jonka kirjaimet lasketaan
 *
 * Laskee annetusta sanasta eri kirjainten määrän.
 *
 */
void __laskeKirjaimet(Sana *sana) {
  int pituus = strlen(sana->alkuperainen);
  int kirjaimet[256] = { 0 };

  int i;
  for (i = 0; i < pituus; i++) {
    kirjaimet[sana->alkuperainen[i]] = 1;
  }

  for (i = 0; i < 256; i++) {
    sana->kirjaimia += kirjaimet[i];
  }
}

/*
 * __suodatin - hyväksyy sanassa sallitut merkit
 *
 * char c - tarkasteltava merkki
 *
 * Paluuarvo int - 1: a-z tai -
 *                 0: kaikissa muissa tapauksissa
 *
 */
int __suodatin(char c) {
  return ('a' <= c && c <= 'z') || c == '-';
}

/*
 * seuraavaSana - lukee tiedostosta sattumanvaraisesti seuraavan sanan
 *
 * Paluuarvo Sana - tiedostosta luettu sana
 *
 * Lukee tiedostosta sattumanvaraisesti seuraavan sanan ja peittää sen
 * kirjaimista noin puolet.
 *
 */
Sana seuraavaSana(void) {
  Sana sana = { "", "", 0 };

  // muodostetaan tiedostopolku ja avataan tiedosto
  char polku[FILENAME_MAX + strlen("/tiedosto.txt")];
  muodostaTiedostopolku(polku, "sanalista.txt");
  FILE *tiedosto = fopen(polku, "r");

  if (tiedosto != NULL) {
    // lasketaan tiedoston pituus ilman EOF-merkkiä
    fseek(tiedosto, 0, SEEK_END);
    int pituus = ftell(tiedosto) - 1;
    fseek(tiedosto, 0, SEEK_SET);

    // arvotaan kohta, josta lähdetään lukemaan.
    int indeksi = satunnaisluku(0, pituus);
    fseek(tiedosto, indeksi, SEEK_SET);

    int loppuOhitettu = 0;
    do {
      // luetaan seuraavan sanan alkuun
      lueRoskat(tiedosto, RIVIN_LOPPUUN);

      // jos tiedosto loppui kesken, jatketaan alusta
      if (feof(tiedosto) || ftell(tiedosto) >= pituus) {
        fseek(tiedosto, 0, SEEK_SET);
        loppuOhitettu++;
      }

      lueSana(tiedosto, sana.alkuperainen, MAX_SANAN_PITUUS, __suodatin);
      
      // lopetetaan, jos tiedostossa ei ollut yhtään kelvollista sanaa
      if(loppuOhitettu > 1 || (sana.alkuperainen[0] == '\0' && loppuOhitettu && ftell(tiedosto) >= indeksi)) {
        printf("Tiedostossa '%s' ei ollut yhtaan hyvaksyttavaa sanaa. Peli keskeytetaan.\n", polku);
        exit(1);
      }
    } while (sana.alkuperainen[0] == '\0');

    fclose(tiedosto);
  } else {
    printf("Tiedostoa '%s' ei voitu lukea. Peli keskeytetaan.\n", polku);
    exit(1);
  }

  __peitaSana(&sana);
  __laskeKirjaimet(&sana);

  return sana;
}

/*
 * __arvaaYksiKirjain - suorittaa arvauksen, kun arvaus koostuu yhdestä kirjaimesta
 *
 * Sana *sana - arvattava sana
 * char c     - arvaus
 *
 * Paluuarvo int: SANA_KIRJAIN_EI_PEITETTY arvattu kirjain on sanassa, mutta ei peitetty
 *                SANA_KIRJAINTA_EI_LOYTYNYT kirjainta ei löytynyt
 *                SANA_KIRJAIN_LOYTYI kirjain löytyi, mutta sana ei ole vielä kokonaan arvattu
 *                SANA_AVATTU sana on kokonaan arvattu
 *
 * Yrittää avata sanasta annetun kirjaimen. Kirjain voi löytyä tai olla
 * löytymättä sekä käyttäjän syöttövirheestä johtuen jokin sellainen kirjain,
 * joka on jo näkyvillä (esim. kirjain 't' sanassa 'ti*t*k*n*').
 *
 */
int __arvaaYksiKirjain(Sana *sana, char c) {
  int tulos = SANA_KIRJAINTA_EI_LOYTYNYT;

  int pituus = strlen(sana->alkuperainen);
  int lopeta = 0;

  int i = 0;
  while (i < pituus && !lopeta) {
    if (sana->alkuperainen[i] == c) {
      if (sana->peitetty[i] == '*') {
        sana->peitetty[i] = sana->alkuperainen[i];

        if (strcmp(sana->alkuperainen, sana->peitetty) == 0) {
          tulos = SANA_AVATTU;
        } else {
          tulos = SANA_KIRJAIN_LOYTYI;
        }
      } else {
        tulos = SANA_KIRJAIN_EI_PEITETTY;
        lopeta = 1;
      }
    }

    i++;
  }

  return tulos;
}

/*
 * arvaaKirjaimia - avaa annetun arvauksen perusteella kirjaimia sanasta
 *
 * Sana *sana   - sana, jota pelaaja yrittää arvata
 * char *arvaus - yksi kirjain: avattava kirjain
 *                sana: sanan arvaus
 *
 * Paluuarvo int: SANA_ARVAUS_EI_KELPAA arvaus on viallinen
 *                TYHJA_SANA arvaus oli tyhjä
 *                SANA_KIRJAIN_EI_PEITETTY arvattu kirjain on sanassa, mutta ei peitetty
 *                SANA_VAARA_SANA sanan arvaus oli väärä
 *                SANA_KIRJAINTA_EI_LOYTYNYT kirjainta ei löytynyt
 *                SANA_KIRJAIN_LOYTYI kirjain löytyi, mutta sana ei ole vielä kokonaan arvattu
 *                SANA_AVATTU sana on kokonaan arvattu
 *
 * Jos arvaus sisältää yhden kirjaimen, sanasta yritetään avata kyseinen
 * kirjain. Kirjain voi löytyä tai olla löytymättä sekä käyttäjän syöttövirheestä
 * johtuen jokin sellainen kirjain, joka on jo näkyvillä (esim. kirjain 't'
 * sanassa 'ti*t*k*n*').
 *
 * Jos taas arvaus sisältää kokonaisen sanan, käyttäjän oletetaan yrittävän
 * arvata sanaa kerralla. Arvaus voi pitää paikkansa tai sitten ei sekä
 * käyttäjän syöttövirheestä johtuen olla eri pituinen kuin arvattava sana.
 *
 */
int arvaaKirjaimia(Sana *sana, const char *arvaus) {
  int tulos = SANA_ARVAUS_EI_KELPAA;

  if (strlen(arvaus) == 0) {
    tulos = SANA_TYHJA;
  } else if (strlen(arvaus) == 1) {
    tulos = __arvaaYksiKirjain(sana, arvaus[0]);
  } else if (strlen(arvaus) == strlen(sana->alkuperainen)) {
    if (strcmp(sana->alkuperainen, arvaus) == 0) {
      strcpy(sana->peitetty, sana->alkuperainen);

      tulos = SANA_AVATTU;
    } else {
      tulos = SANA_VAARA_SANA;
    }
  }

  return tulos;
}
