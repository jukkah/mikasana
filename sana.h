/*
 * Sanan ja arvauksen tilaa kuvaavat vakiot
 */
#define SANA_TYHJA 6
#define SANA_ARVAUS_EI_KELPAA 5
#define SANA_KIRJAIN_EI_PEITETTY 4
#define SANA_VAARA_SANA 3
#define SANA_KIRJAINTA_EI_LOYTYNYT 2
#define SANA_KIRJAIN_LOYTYI 1
#define SANA_AVATTU 0

/*
 * Sanan maksimipituus (ml. loppumerkki)
 */
#define MAX_SANAN_PITUUS 256

/*
 * Yhden arvattavan sanan sisältävä rakenne
 */ 
typedef struct {
  char alkuperainen[MAX_SANAN_PITUUS];
  char peitetty[MAX_SANAN_PITUUS];
  int kirjaimia;
} Sana;

/*
 * seuraavaSana - lukee tiedostosta sattumanvaraisesti seuraavan sanan
 * 
 * Paluuarvo Sana - tiedostosta luettu sana
 * 
 * Lukee tiedostosta sattumanvaraisesti seuraavan sanan ja peittää sen
 * kirjaimista noin puolet.
 * 
 */
Sana seuraavaSana(void);

/*
 * arvaaKirjaimia - avaa annetun arvauksen perusteella kirjaimia sanasta
 * 
 * Sana *sana   - sana, jota pelaaja yrittää arvata
 * char *arvaus - yksi kirjain: avattava kirjain
 *                sana: sanan arvaus
 * 
 * Paluuarvo int: SANA_ARVAUS_EI_KELPAA arvaus on viallinen
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
int arvaaKirjaimia(Sana *sana, const char *arvaus);
