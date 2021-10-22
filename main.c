// Ohjelmointi 1 -kurssin kotitehtävä
// Tekijä: Niko Heikkilä

#include <stdio.h>

// Funktiot apuohjelmat.c-tiedostosta.
int lueKokonaisluku(void);
void lueRoskat(void);

// Omat funktiot
int kysyPin(int oikeaPin);
void kysyToiminto(int *toim);
void nostaRahaa(void);
void naytaSaldo(void);
void naytaTapahtumat(void);
void lataaPuheaikaa(void);


int main(void) {
    int const OIKEAPIN = 1234;
    int toiminto, suorita;

    suorita = kysyPin(OIKEAPIN);

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
      printf("Et syottanyt kokonaislukua > ");
   }
   return luku;
}

// Tyhjentää stdin-puskurin. Kopioitu kurssilla jaetusta apuohjelmia.c -tiedostosta.
void lueRoskat(void){

   // Tyhjennet��n puskuri
   while( fgetc(stdin) != '\n');
}



// Kysyy pin-koodin käyttäjältä ja vertaa sitä oikeaan pin-koodiin kolme kertaa.
// oikeaPin (int) - oikea pin-koodi
// return: 0 tai 1 (int), riippuen oliko pin oikein.
int kysyPin(int oikeaPin) {
    
    int pin;

    for (int i = 1; ; i++) {
        printf("Syota PIN: ");
        pin = lueKokonaisluku();

        if (pin == oikeaPin) {
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
        printf("Valitse toiminto: ");
        *toim = lueKokonaisluku();
        printf("\n");
    } while (*toim < 0 || 4 < *toim);
    
}

// Tämä funktio sisältää rahojen nosto -toiminnon myöhemmin.
// Nyt vain tulostaa jotain.
void nostaRahaa(void) {

    printf("Nosto valmis. Ota rahat.\n");
}

// Tämä funktio tarkastaa ja tulostaa saldon myöhemmin.
// Nyt vain tulostaa jotain.
void naytaSaldo(void) {

    printf("Tilisi saldo on: 2000e\n");
}

// Tämä funktio tulostaa tapahtumat myöhemmin.
// Nyt vain tulostaa jotain.
void naytaTapahtumat(void) {

    printf("10.06.2021    -200e\n");
    printf("16.03.2021    -50e\n");
    printf("26.10.2020    +1000e\n");
    printf("05.07.2019    +10e\n");
}

// Tämä funktio lataa puheaikaa liittymälle myöhemmin.
// Nyt vain tulostaa jotain.
void lataaPuheaikaa(void) {
    
    printf("Puheajan lataus valmis.\n");
}
