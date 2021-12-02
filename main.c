// Ohjelmointi 1 -kurssin kotitehtävä
// Tekijä: Niko Heikkilä

#include <stdio.h>
#include <time.h>
#include <string.h>


// Globaalit muuttujat
int saldo = 5000;

struct Tapahtuma {          // tietorakenne tilitapahtumalle
    char pvm[11];
    int summa;
} tapahtumat[5];            // tallennetaan viisi viimeistä tilitapahtumaa
// Tapahtumien pitäminen oikeassa järjestyksessä perustuu jonoon.
// Tässä muuttujat jonon käsittelyä varten.
int tHead = 0, tTail = 0, tSize = 0;

typedef struct Setelit {    // tietorakenne noston seteleille
    int s20;                // 50 setelien määrä
    int s50;                // 20 setelien määrä
} setelit;

// Funktiot apuohjelmat.c-tiedostosta.
int lueKokonaisluku(void);
void lueRoskat(void);

// Omat funktiot
int kysyPin(int oikeapin);
void kysyToiminto(int *toim);
void nostaRahaa(void);
void naytaSaldo(void);
void naytaTapahtumat(void);
void lataaPuheaikaa(void);
int tarkastaNosto(int nosto);
void odotaJatkoa(void);
void lisaaTapahtuma(int summa);
setelit laskeSetelit(int nosto);
int kysyTili(void);


int main(void) {
    int toiminto, suorita, oikeapin;

    // anna tili
    oikeapin = kysyTili();
    suorita = kysyPin(oikeapin);

    while (suorita) {
        kysyToiminto(&toiminto);

        switch (toiminto) {
                case 0:
                    printf("Poistutaan ohjelmasta...");
                    suorita = 0;
                    break;
                
                case 1:
                    nostaRahaa();
                    break;
                
                case 2:
                    naytaSaldo();
                    break;
                
                case 3:
                    naytaTapahtumat();
                    break;
                
                case 4: 
                    lataaPuheaikaa();
                    break;
        }
    }
    return 0;
}



// Lukee kokonaisluvun. Kopioitu kurssilla jaetusta apuohjelmia.c -tiedostosta.
// return: luku (int) - luettu kokonaisluku
int lueKokonaisluku(void){

   int luku;
   char mki;
   int status;

   while (((status = scanf("%d%c", &luku, &mki)) == 0)  || (2 == status && mki != '\n')){
      lueRoskat();
      printf("Et syottanyt kokonaislukua. Yrita uudestaan:\n");
   }
   return luku;
}

// Tyhjentää stdin-puskurin. Kopioitu kurssilla jaetusta apuohjelmia.c -tiedostosta.
void lueRoskat(void){

   // Tyhjennetään puskuri
   while( fgetc(stdin) != '\n');
}

// Lukee merkkijonon. Kopioitu kurssilla jaetusta apuohjelmia.c -tiedostosta.
// TODO this
void lueMerkkijono(char merkkijono[], int pituus) {

   fgets( merkkijono, pituus, stdin );

   // Jos merkkijonon lopussa, ennen lopetusmerkkiä on ylimääräinen
   // rivinvaihto korvataan se lopetusmerkillä
   if( merkkijono[ strlen(merkkijono)-1 ] == '\n')
      merkkijono[ strlen(merkkijono)-1 ] = '\0';
   else
      lueRoskat();
}



// Kysyy pin-koodin käyttäjältä ja vertaa sitä oikeaan pin-koodiin kolme kertaa.
// return: 0 tai 1 (int), riippuen oliko pin oikein.
int kysyPin(int oikeapin) {
    
    int pin;

    for (int i = 1; ; i++) {
        printf("Syota PIN:\n");
        pin = lueKokonaisluku();

        if (pin == oikeapin) {
            return 1;
        }
        else if (i == 3) {
            printf("Vaara PIN. Suljetaan ohjelma...");
            return 0;
        }
        else {
            printf("Vaara PIN. Yrityksia jaljella: %d\n", 3 - i);
        }
    }
}

// Tulostaa saatavilla olevat toiminnot ja kysyy mikä toiminnon käyttäjä haluaa.
// toim (int *) - osoitin muistipaikkaan, johon valittu toiminto tallennetaan kokonaislukuna.
void kysyToiminto(int *toim) {

    do {
        printf("\nToiminnot:\nSulje (0)\nNosto (1)\nSaldo (2)\nTapahtumat (3)\nLataa puheaikaa (4)\n");
        printf("Valitse toiminto:\n");
        *toim = lueKokonaisluku();
        printf("\n");
    } while (*toim < 0 || 4 < *toim);
}

// Tämä funktio sisältää rahojen nosto -toiminnon.
// Se kysyy noston määrän, tarkastaa onko nosto mahdollinen
// ja lisää noston tapahtumiin.
void nostaRahaa(void) {

    int nosto;
    setelit set;
    while (1) {
        printf("Valitse noston maara:\n");
        nosto = lueKokonaisluku();

        if (nosto < 40 || 1000 < nosto)
            printf("Noston on oltava vahintaan 40 e ja enintaan 1000 e.\n\n");

        else if (nosto % 10) 
            printf("Noston on oltava jaollinen kymmenella.\n\n");

        else
            break;
    }
    
    if (tarkastaNosto(nosto))
        saldo -= nosto;
    else 
        return;

    lisaaTapahtuma(-nosto);
    set = laskeSetelit(nosto);

    printf("Setelit ovat\n50 e: %d kpl\n20 e: %d kpl\n", set.s50, set.s20);
    printf("Nosto valmis. Saldo nyt %d euroa.\n\n", saldo);
    odotaJatkoa();
}

// Tämä funktio tarkastaa ja tulostaa saldon.
void naytaSaldo(void) {

    printf("Tilisi saldo on: %d euroa\n", saldo);
    odotaJatkoa();
}

// Tämä funktio tulostaa tapahtumat.
// Tulostaa tapahtumat läpi vanhimmasta uusimpaan.
// Käyttää globaaleja muuttujia tTail, tHead ja tSize.
void naytaTapahtumat(void) {
    
    if (tSize == 0) {
        printf("Ei tapahtumia tililla\n");
    }
    else {
        int i = tHead;
        do {
            printf("%10s%8d e\n", tapahtumat[i].pvm, tapahtumat[i].summa);
            i = (i + 1) % 5;
        } while (i != tTail);
    }
    odotaJatkoa();
}

// Tämä funktio kysyy puhelinnumeron ja latauksen määrän, 
// joka ladataan liittymälle. Tarkastaa ja lisää latauksen
// tapahtumiin.
void lataaPuheaikaa(void) {

    int puh, lataus;
    printf("Syota puhelinnumero:\n");
    puh = lueKokonaisluku();
    printf("Syota latauksen maara:\n");
    lataus = lueKokonaisluku();
    
    if (tarkastaNosto(lataus))
        saldo -= lataus;
    else 
        return;
    
    lisaaTapahtuma(-lataus);

    printf("Ladattu puheaikaa %d eurolla numerolle %d.\n", lataus, puh);
    odotaJatkoa();
}

// Tarkastaa, onko tilillä tarpeeksi rahaa nostoon.
// nosto (int) - noston määrä euroina.
// return: 0 tai 1 (int), riippuen oliko tarpeeksi rahaa.
int tarkastaNosto(int nosto) {

    if (nosto > saldo) {
        printf("Tililla ole tarpeeksi rahaa. Toiminto keskeytetaan\n");
        odotaJatkoa();
        return 0;
    }
    return 1;
}

// Odottaa, että käyttäjä painaa enter jatkaakseen.
void odotaJatkoa(void) {

    printf("Paina enteria jatkaaksesi\n");
    getchar();
}

// Lisää lisää uuden tapahtuman ja poistaa tarvittaessa vanhimman tapahtuman.
// Hakee nykyisen ajan ja muuntaa sen muotoon DD.MM.YYYY.
// Vain viisi tapahtumaa säilytetään. Käyttää globaaleja muuttujia 
// tTail, tHead ja tSize.
// summa (int) - Saldon muutoksen määrä.
void lisaaTapahtuma(int summa) {

    time_t aika = time(NULL);
    struct tm *pAika = localtime(&aika);

    strftime(tapahtumat[tTail].pvm, 11, "%d.%m.%Y", pAika);
    tapahtumat[tTail].summa = summa;
    
    tTail = (tTail + 1) % 5;
    if (tSize == 5)
        tHead = (tHead + 1) % 5;
    else
        tSize++;
}

// Laskee montako 50 ja 20 seteliä tarvitaan nostoon.
// Laskee ensin 50 setelien määrän jakolaskulla ja sitten 20.
// Jos ei mene tasan eli jää 10, niin vähentää yhden 50 setelin
// ja lisää kolme 20 seteliä.
// nosto (int) - Noston määrä.
// return: set (setelit) - Tietorakenne, joka sisältää setelien määrät.
setelit laskeSetelit(int nosto) {
    
    setelit set;
    set.s50 = nosto / 50;
    set.s20 = (nosto - set.s50 * 50) / 20;

    if (set.s20 * 20 + set.s50 * 50 != nosto) {
        set.s50--;
        set.s20 += 3;
    }
    return set;
}

//
//
int kysyTili(void) {
    char tilinumero[100];
    int pin;
    FILE *tili;

    do {
        printf("Anna tilinumero:\n");
        lueMerkkijono(tilinumero, 100);
        strcat(tilinumero, ".acc");
        
        tili = fopen(tilinumero, "r");
        if (tili == NULL)
            printf("Tilia ei loydy. Yrita uudestaan.\n");

    } while (tili == NULL);
    
    fscanf(tili, "%d", &pin);
    return pin;

}

