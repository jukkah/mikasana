/*
 * Pelaajien maksimimäärä ja pelaajan nimen maksimipituus (ml. lopetusmerkki)
 */
#define MAX_PELAAJIA 4
#define PELAAJAN_NIMEN_MAX_PITUUS 256

/*
 * Yhden pelaajan tiedot sisältävä rakenne
 */
typedef struct {
  char nimi[PELAAJAN_NIMEN_MAX_PITUUS];
  int pisteet;
} Pelaaja;

/*
 * Kaikkien pelaajien tiedot sekä pelivuoron sisältävä rakenne
 */
struct {
  Pelaaja pelaajat[MAX_PELAAJIA];
  int pelaajia;
  Pelaaja *nykyinenPelaaja;
} pelaajienTiedot;

/*
 * alustaPelaajat - alustaa pelaajien tiedot
 * 
 * Alustaa pelaajien tiedot.
 */
void alustaPelaajat(void);

/*
 * seuraavaPelaaja - siirtää pelivuoron seuraavalle pelaajalle
 * 
 * Paluuarvo Pelaaja * - pelaaja, joka saa pelivuoron
 * 
 * Siirtää pelivuoron seuraavalle pelaajalle.
 */
Pelaaja *seuraavaPelaaja(void);

/*
 * lajittelePelaajat - lajittelee pelaajat paremmuusjärjestykseen
 * 
 * Lajittelee pelaajat paremmuusjärjestykseen pisteiden mukaan.
 */
void lajittelePelaajat(void);
