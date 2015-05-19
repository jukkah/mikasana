#include <stdlib.h>
#include <string.h>
#include "utils.h"  // #include <stdio.h>

/*
 * GetCurrentDir - järjestelmäfunktio työhakemiston saamiseksi
 */
#ifdef WINDOWS
  #include <direct.h>
  #define GetCurrentDir _getcwd
#else
  #include <unistd.h>
  #define GetCurrentDir getcwd
#endif

/*
 * satunnaisluku - arpoo satunnaisluvun annetulta väliltä
 *
 * int min - alaraja (sisältyy)
 * int max - yläraja (sisältyy)
 *
 * Paluuarvo int - satunnailuku x väliltä [min, max]. Jos max < min, tulos on
 * määrittelemätön.
 *
 */
int satunnaisluku(int min, int max) {
  double kerroin = rand() / (double) RAND_MAX;

  return min + (int) ((max - min) * kerroin);
}

/*
 * alustaSatunnaislukugeneraattori - alustaa satunnaislukugeneraattorin
 */
void alustaSatunnaislukugeneraattori(void) {
  time_t t;
  srand((unsigned) time(&t));
}


/*
 * __rivinvaihto - tarkistaa ja lukee rivinvaihdon
 *
 * FILE *tiedosto - syöte, josta luetaan tarvittaessa
 * char c         - syötteestä luettu viimeinen merkki
 * int alaLue     - lippu, joka määrää, luetaanko syötettä vai ei.
 *
 * Paluuarvo int - rivinvaihtoon kuuluvien merkkien määrä.
 *
 * Tarkistaa, onko syötteestä luettu merkki c rivinvaihdon alottava merkki.
 * Luetaan myös tarvittaessa CRLF-rivinvaihdon toinenkin merkki.
 *
 */
int __rivinvaihto(FILE *tiedosto, char c, int alaLue) {
  int pituus = 0;

  if (c == '\r') {
    pituus = 1;

    // katsotaan, onko kyseessä CR vai CRLF
    c = getc(tiedosto);
    if (c != '\n' || alaLue) ungetc(c, tiedosto);
    else pituus = 2;
  } else if (c == '\n') {
    pituus = 1;
  }

  return pituus;
}

/*
 * hyvaksyKaikki - hyväksyy kaikki merkit
 * 
 * char c - tarkasteltava merkki
 * 
 * Paluuarvo int - 1
 * 
 */
int hyvaksyKaikki(char c) {
  return 1;
}

/*
 * lueSana - lukee yhden sanan annetusta syötteestä
 * 
 * FILE *tiedosto - syöte, josta luetaan
 * char mjono[]   - merkkijono, johon luettu sana tallennetaan
 * int pituus     - mjonon pituus tavuina
 * fn suodatin    - funktio, jonka perusteella päätetään, sisällytetäänko merkki mjonoon
 * 
 * Paluuarvo int - 1: sana loppuu rivinvaihtomerkkiin
 *                 0: sana ei lopu rivinvaihtomerkkiin
 * 
 * Lukee annetusta syötteestä yhden sanan. Sanan katsotaan loppuvan
 * rivinvaihtoon, välilyöntiin tai pilkkuun. Nämä merkit jätetään lukematta.
 * Mikäli luettava sana on pidempi kuin mitä mjonoon mahtuu, sana luetaan
 * loppuun, mutta yli meneviä tai suodattimen hylkäämiä merkkejä ei tallenneta
 * mjonoon.
 * 
 * 
 * suodatin - hyväksyy tai hylkää merkin
 * 
 * char c - tarkasteltava merkki
 * 
 * Paluuarvo int - 1: merkki hyväksytään
 *                 0: merkkiä ei hyväksytä
 * 
 */
int lueSana(FILE *tiedosto, char mjono[], int pituus, int suodatin(char c)) {
  int rivinvaihto = 0;
  int lopeta = 0;

  char c;
  int i = 0;
  while (!lopeta) {
    c = fgetc(tiedosto);

    rivinvaihto = __rivinvaihto(tiedosto, c, 1);

    if (rivinvaihto || feof(tiedosto) || c == ' ' || c == ',') {
      // merkki c on ensimmäinen merkki, joka ei kuulu sanaan.
      ungetc(c, tiedosto);

      lopeta = 1;
      if (feof(tiedosto)) rivinvaihto = 1;
    } else if (i < pituus - 1 && suodatin(c)) {
      mjono[i] = c;
      i++;
    }
  }

  // Lisätään vielä loppuun lopetusmerkki.
  mjono[i] = '\0';

  return rivinvaihto != 0;
}

/*
 * kysyKyllaEi - kysyy varmistuksen käyttäjältä
 *
 * char kysymys[] - käyttäjälle näytettävä kysymys
 * int oletus     - oletusvastaus on KYLLA tai EI
 *
 * Paluuarvo int - 1: myöntävä vastaus
 *                 0: epäselvä vastaus
 *                -1: kieltävä vastaus
 *
 * Tulostaa stdoutiin kysymyksen ja "(k/e)>" ja odottaa myöntäväksi
 * vastaukseksi kirjaimia K tai k. Vastaavasti kieltäväksi vastaukseksi
 * odotetaan kirjaimia E tai e. Toinen vastauksista määritellään
 * oletusvastaukseksi, joka aktivoidaan antamalla tyhjä vastaus. Jos käyttäjä
 * antaa vastauksen, jota ei voida tulkita myöntäväksi eikä kieltäväksi,
 * kyseessä on epäselvä vastaus.
 *
 */
int kysyKyllaEi(char kysymys[], int oletus) {
  if (oletus == KYLLA) {
    printf("%s (K/e)> ", kysymys);
  } else {
    printf("%s (k/E)> ", kysymys);
  }

  char c[2];
  lueSana(stdin, c, sizeof(c), hyvaksyKaikki);
  lueRoskat(stdin, RIVIN_LOPPUUN);

  int vastaus = 0;
  if (c[0] == 'K' || c[0] == 'k') vastaus = KYLLA;
  if (c[0] == 'E' || c[0] == 'e') vastaus = EI;
  if (c[0] == '\0') vastaus = oletus;

  return vastaus;
}

/*
 * ymmarsinkoOikein - kysyy varmistuksen käyttäjältä
 *
 * int oletus - oletusvastaus on KYLA tai EI
 *
 * Paluuarvo int - 1: myöntävä vastaus
 *                 0: epäselvä vastaus
 *                -1: kieltävä vastaus
 *
 * Tulostaa stdoutiin kysymyksen "Ymmarsinko oikein (k/e)>" ja odottaa
 * myöntäväksi vastaukseksi kirjaimia K tai k. Vastaavasti kieltäväksi
 * vastaukseksi odotetaan kirjaimia E tai e. Toinen vastauksista määritellään
 * oletusvastaukseksi, joka aktivoidaan antamalla tyhjä vastaus. Jos käyttäjä
 * antaa vastauksen, jota ei voida tulkita myöntäväksi eikä kieltäväksi,
 * kyseessä on epäselvä vastaus.
 *
 */
int ymmarsinkoOikein(int oletus) {
  return kysyKyllaEi("Ymmarsinko oikein", oletus);
}

/*
 * lueRoskat - lukee annetusta syötteestä ylimääräiset merkit pois
 *
 * FILE *tiedosto   - syöte, josta luetaan
 * int rivinLoppuun - RIVIN_LOPPUUN: lukee rivin loppuun asti
 *                    SEURAAVAN_SANAN_ALKUUN: lukee seuraavan sanan alkuun asti
 *
 * Paluuarvo int: 1: rivi loppui
 *                0: rivi ei loppunut vielä
 *
 * Lukee annetusta syötteestä ylimääräiset merkit pois, jotta seuraava sana
 * voitaisiin lukea. Jos syötteessä tulee vastaan jokin muu merkki kuin
 * rivinvaihto, välilyönti tai pilkku, siitä kohdasta alkaa seuraava sana.
 * Syötettä voidaan lukea joko seuraavan sanan alkuun tai rivin loppuun asti.
 *
 */
int lueRoskat(FILE *tiedosto, int rivinLoppuun) {
  int rivinvaihto = 0;
  int lopeta = 0;

  char c;
  while (!lopeta) {
    c = fgetc(tiedosto);

    rivinvaihto = __rivinvaihto(tiedosto, c, 0);

    if (rivinvaihto || feof(tiedosto)) {
      // merkki c lopettaa rivin
      lopeta = 1;
      rivinvaihto = 1;
    } else if (!rivinLoppuun && c != ' ' && c != ',') {
      // merkki c lopettaa sanan
      ungetc(c, tiedosto);
      lopeta = 1;
    }
  }

  return rivinvaihto;
}

/*
 * muodostaTiedostopolku - muodostaa tiedostpolun työhakemistoon
 *
 * char *polku      - tiedostopolku, joka toimii myös paluuarvona. Sen pituuden tulisi olla vähintään FILENAME_MAX
 * char *tiedosto   - tiedoston nimi
 *
 * Paluuarvo char * - tiedoston polku työhakemistossa
 *
 * Muodostaa tiedostolle polun nykyiseen työhakemistoon seuraavalla kaavalla:
 * Windows: <työhakemisto>\tiedosto
 * Linux:   <työhakemisto>/tiedosto
 *
 */
void muodostaTiedostopolku(char *polku, char *tiedosto) {
  GetCurrentDir(polku, FILENAME_MAX);

  // Linuxissa polku alkaa /-merkillä. Valitaan sen avulla sopiva erotinmerkki.
  char erotin = '\\';
  if (polku[0] == '/') erotin = '/';

  // Tallennetaan tiedostopolkuun <polku><erotin><tiedosto>
  sprintf(polku, "%s%c%s", polku, erotin, tiedosto);
}
