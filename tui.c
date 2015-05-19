#include <string.h>
#include "tui.h"
#include "pelaaja.h"
#include "sana.h"
#include "utils.h" // #include <stdio.h>

/*
 * __tulostaYlaosa - tulostaa logon ja ohjeet pelin alussa
 * 
 *  __  __ _ _    _  _    _____                   
 * |  \/  (_) |  (_)(_)  / ____|                  
 * | \  / |_| | ____ _  | (___   __ _ _ __   __ _ 
 * | |\/| | | |/ / _` |  \___ \ / _` | '_ \ / _` |
 * | |  | | |   < (_| |  ____) | (_| | | | | (_| |
 * |_|  |_|_|_|\_\__,_| |_____/ \__,_|_| |_|\__,_|
 *                                                
 *            (c) Jukka Hyytiälä 2015             
 * 
 * Mika Sana on sananarvauspeli 1-4 pelaajalle. Kukin pelaaja saa
 * 5 osittain peitettya sanaa ratkaistavakseen. Sanaa voi avata kirjain
 * kerralla tai vaihtoehtoisesti yrittaa arvata koko sanan. Arvauksia on
 * rajaton maara, mutta kustakin sanasta saa pisteita seuraavasti:
 *    1  arvaus   = 100 p
 *    2  arvausta =  80 p
 *    3  arvausta =  60 p
 *    4  arvausta =  40 p
 *    5  arvausta =  20 p
 *    6+ arvausta =   0 p.
 * Eniten pisteita saanut pelaaja voittaa. Onnea peliin!
 * 
 */
void __tulostaYlaosa(void) {
  printf("\n");
  
  printf("  __  __ _ _    _  _      _____                    \n");
  printf(" |  \\/  (_) |  (_)(_)    / ____|                  \n");
  printf(" | \\  / |_| | ____ _    | (___   __ _ _ __   __ _ \n");
  printf(" | |\\/| | | |/ / _` |    \\___ \\ / _` | '_ \\ / _` |\n");
  printf(" | |  | | |   < (_| |    ____) | (_| | | | | (_| |\n");
  printf(" |_|  |_|_|_|\\_\\__,_|   |_____/ \\__,_|_| |_|\\__,_|\n");
  printf("\n");
  printf("            (c) Jukka Hyytiala 2015             \n");

  printf("\n");
  printf("Mika Sana on sananarvauspeli 1-4 pelaajalle. Kukin pelaaja saa\n5 osittain peitettya sanaa ratkaistavakseen. Sanaa voi avata kirjain\nkerralla tai vaihtoehtoisesti yrittaa arvata koko sanan. Arvauksia on\nrajaton maara, mutta kustakin sanasta saa pisteita seuraavasti:\n   1  arvaus   = 100 p\n   2  arvausta =  80 p\n   3  arvausta =  60 p\n   4  arvausta =  40 p\n   5  arvausta =  20 p\n   6+ arvausta =   0 p.\nEniten pisteita saanut pelaaja voittaa. Onnea peliin!\n\n");
}

/*
 * __tulostaPelaajalista - tulostaa pelaajalistan
 * 
 * int tulostaPisteet - lippu, joka määrää, tulostetaanko pelaajien pisteet vai ei
 * int lainausmerkit  - lippu, joka määrää, tulostetaanko pelaajien nimet lainausmerkeissä vai ei
 * 
 * Tulostaa pelaajien tiedot listan mukaisessa järjestyksessä. Pelaajien nimet
 * voidaan kääriä puolilainausmerkkeihin ja nimen perään voidaan myös tulostaa
 * sulkuihin pelaajan pistemäärä.
 * 
 */
void __tulostaPelaajalista(int tulostaPisteet, int lainausmerkit) {
  int i;
  for (i = 0; i < pelaajienTiedot.pelaajia; i++) {
    if (lainausmerkit) {
      printf("'%s'", pelaajienTiedot.pelaajat[i].nimi);
    } else {
      printf("%s", pelaajienTiedot.pelaajat[i].nimi);
    }
    
    if (tulostaPisteet) {
      printf(" (%d)", pelaajienTiedot.pelaajat[i].pisteet);
    }
    
    if (i + 2 < pelaajienTiedot.pelaajia) {
      printf(", ");
    } else if (i + 1 < pelaajienTiedot.pelaajia) {
      printf(" ja ");
    }
  }
}

/*
 * __vahvistaPelaajienNimet - kysyy käyttäjältä vahvistuksen luetuille pelaajien nimille
 * 
 * Paluuarvo int - 1: myöntävä vastaus
 *                 0: kieltävä vastaus
 * 
 * Kertoo käyttäjälle luetut pelaajien nimet ja kysyy, ovatko ne oikein.
 * 
 */
int __vahvistaPelaajienNimet(void) {
  if (pelaajienTiedot.pelaajia < 1) {
    printf("Pelaajia taytyy olla vahintaan 1 kpl. Ole hyva, ja yrita uudelleen.\n");
    return 0;
  }
  
  if (pelaajienTiedot.pelaajia == 1) {
    printf("Pelaajan nimi on ");
  } else {
    printf("Pelaajien nimet (%d kpl) ovat ", pelaajienTiedot.pelaajia);
  }
  
  __tulostaPelaajalista(0, 1);
  
  printf(". ");
  return ymmarsinkoOikein(KYLLA) == KYLLA;
}

/*
 * __luePelaajat - lukee pelaajien nimet
 * 
 * Kysyy käyttäjältä pelaajien nimet ja tallentaa ne pelaajien tietoihin.
 * 
 */
void __luePelaajat(void) {
  printf("Anna pelaajien nimet (1-4 kpl)> ");
  
  int i = 0, loppu = 0;
  while (i < MAX_PELAAJIA && !loppu) {
    char sana[PELAAJAN_NIMEN_MAX_PITUUS];
    lueSana(stdin, sana, PELAAJAN_NIMEN_MAX_PITUUS, hyvaksyKaikki);
    loppu = lueRoskat(stdin, SEURAAVAN_SANAN_ALKUUN);
      
    if(sana[0] != '\0' && strcmp(sana, "ja") != 0) {
      strcpy(pelaajienTiedot.pelaajat[i].nimi, sana);
      
      i++;
    }
  }
  
  if (!loppu) {
    lueRoskat(stdin, RIVIN_LOPPUUN);
  }
  
  pelaajienTiedot.pelaajia = i;
}

/*
 * __alustaPeli - alustaa pelin, jotta se voidaan käynnistää
 * 
 * Alustaa satunnailukugeneraattorin sekä lukee ja vahvistuttaa pelaajien
 * nimet käyttäjällä. Pelaajien nimet voidaan joutua lukemaan useampaan kertaan.
 * 
 */
void __alustaPeli(void) {
  alustaSatunnaislukugeneraattori();
  
  do {
    alustaPelaajat();
    __luePelaajat();
  } while (!__vahvistaPelaajienNimet());
  
  printf("\n");
}

/*
 * __pisteet - laskee arvausten määrää vastaavan pistemäärän
 * 
 * int arvauksia - arvausten lukumäärä
 * 
 * Paluuarvo int: arvausten määrää vastaava pistemäärä
 * 
 * Laskee arvausten määrää vastaavan pistemäärän.
 * 
 */
int __pisteet(int arvauksia) {
  int pisteet;
  switch (arvauksia) {
    case 1:
      pisteet = 100;
      break;
    case 2:
      pisteet = 80;
      break;
    case 3:
      pisteet = 60;
      break;
    case 4:
      pisteet = 40;
      break;
    case 5:
      pisteet = 20;
      break;
    default:
      pisteet = 0;
      break;
  }
  
  return pisteet;
}

/*
 * __pelaaPelivuoro - pelaa yhden pelivuoron
 * 
 * Muodostaa uuden arvattavan sanan ja antaa pelaajan arvata sen.
 * 
 */
void __pelaaPelivuoro(void) {
  Sana sana = seuraavaSana();
  
  int arvauksia = 0, tulos;
  char arvaus[MAX_SANAN_PITUUS];
  do {
    arvauksia++;
    
    printf("%s: %d. arvaus sanalle '%s' (sis. %d eri merkkia)> ", pelaajienTiedot.nykyinenPelaaja->nimi, arvauksia, sana.peitetty, sana.kirjaimia);
    
    
    lueSana(stdin, arvaus, MAX_SANAN_PITUUS, hyvaksyKaikki);
    lueRoskat(stdin, RIVIN_LOPPUUN);
    
    tulos = arvaaKirjaimia(&sana, arvaus);
    
    switch (tulos) {
      case SANA_AVATTU:
        printf("Hienoa! Arvasti sanan '%s'.\n", sana.alkuperainen);
        break;
      case SANA_KIRJAIN_LOYTYI:
        printf("Hienoa! Jatka samaan malliin.\n");
        break;
      case SANA_KIRJAINTA_EI_LOYTYNYT:
        printf("Kirjaita '%c' ei ollut sanassa.\n", arvaus[0]);  
        break;
      case SANA_KIRJAIN_EI_PEITETTY:
        printf("Krhm... kirjain '%c' on jo nakyvilla.\n", arvaus[0]);
        arvauksia--;
        break;
      case SANA_TYHJA:
        printf("Ala luovuta, kylla sina sen arvaat viela.\n");
        arvauksia--;
        break;
      case SANA_VAARA_SANA:
      case SANA_ARVAUS_EI_KELPAA:
        printf("Sana ei ole '%s'. Yrita uudelleen.\n", arvaus);
        break;
    }
  } while(tulos != SANA_AVATTU);
  
  int pisteet = __pisteet(arvauksia);
  pelaajienTiedot.nykyinenPelaaja->pisteet += pisteet;
  
  printf("Sait arvatusta sanasta %d pistetta ja nyt sinulla on yhteensa %d pistetta.\n\n", pisteet, pelaajienTiedot.nykyinenPelaaja->pisteet);
}

/*
 * __pelaaPeli - pelaa yhden pelin kaikki peivuorot läpi
 */
void __pelaaPeli(void) {
  int i;
  for (i = 0; i < pelaajienTiedot.pelaajia * 5; i++) {
    seuraavaPelaaja();
    __pelaaPelivuoro();
  }
}

/*
 * __tulostaTulokset - tulostaa tulostaulukon pelin päätyttyä
 */
void __tulostaTulokset(void) {
  printf("Onnittelut! Ratkaisitte yhdessa yhteensa %d sanaa. Alla naette pisteenne.\n", pelaajienTiedot.pelaajia * 5);
  
  lajittelePelaajat();
  __tulostaPelaajalista(1, 0);
  
  printf(".");
}

/*
 * kaynnistaPeli - käynnistää pelin
 */
void kaynnistaPeli(void) {
  do {
    __tulostaYlaosa();
    __alustaPeli();
    __pelaaPeli();
    __tulostaTulokset();
  } while (kysyKyllaEi("\n\nPelataanko uudestaan?", EI) == KYLLA);
  
}
