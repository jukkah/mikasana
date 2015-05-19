#include <stdio.h>

/*
 * satunnaisluku - arpoo satunnaisluvun annetulta väliltä
 * 
 * int min - alaraja (sisältyy)
 * int max - yläraja (sisältyy)
 * 
 * Paluuarvo int - satunnailuku x väliltä [min, max]
 * 
 */
int satunnaisluku(int min, int max);

/*
 * alustaSatunnaislukugeneraattori - alustaa satunnaislukugeneraattorin
 */
void alustaSatunnaislukugeneraattori(void);

/*
 * hyvaksyKaikki - hyväksyy kaikki merkit
 * 
 * char c - tarkasteltava merkki
 * 
 * Paluuarvo int - 1
 * 
 */
int hyvaksyKaikki(char c);

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
int lueSana(FILE *tiedosto, char mjono[], int pituus, int suodatin(char c));

/*
 * Bool-arvoja vastaavat vakiot, joita käytetään seuraavissa funktioissa
 */
#define KYLLA 1
#define EI 0

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
int kysyKyllaEi(char kysymys[], int oletus);

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
int ymmarsinkoOikein(int oletus);

/*
 * Liput, joita käytetään roskien lukemisessa
 */
#define RIVIN_LOPPUUN 1
#define SEURAAVAN_SANAN_ALKUUN 0

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
int lueRoskat(FILE *tiedosto, int rivinLoppuun);

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
 * Linux  : <työhakemisto>/tiedosto
 * 
 */
void muodostaTiedostopolku(char *polku, char *tiedosto);
