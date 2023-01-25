#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
clear: puhdistaa bufferin, jos sinne on jäänyt käyttäjän inputista jotakin.
*/
void clear (void) {    
    while ( getchar() != '\n' );
}

/*
Nosto, jossa kysytään paljonko käyttäjä haluaa nostaa ja miinustetaan se saldosta
Tarkistetaan, että nostettava summa on nollan ja käyttäjän saldon välillä. Nosto voi olla 20 euroa, 40 euroa tai enemmän,
kymmenen euron välein (esim. 50, 60, 70, 80, 90, 100, 110, 120, 130 jne.) 1000 asti.
Parametrit: saldo0 (* double), josta miinustetaan käyttäjän syöttämä luku, nostolkm, joka lisää yhden kerran nostojen lukumäärään, 
jos nosto onnistuu.
Paluuarvo: maara (int), määrä, jonka käyttäjä haluaa nostaa tai 0 jos se ei ole nollan ja saldon välillä tai jos automaatti ei voi
antaa sen suuruista summaa.
*/
int nosto(double * saldo0, int *nostolkm) {
    int maara, i, vitoset=0, kakoset=0, summa;
    clear();
    printf("Paaset takaisin painamalla jotain kirjainta ja enteria\n");
    printf("Desimaaleja ei oteta huomioon\n");
    printf("Voit nostaa 20 euroa tai 40:sta eurosta eteenpain 10 euron valeilla 1000 saakka.\nKuinka paljon haluat nostaa?\n: ");
    scanf("%d",&maara);
    if (maara <= *saldo0 && maara > 0) {
        for (i=0; 40+i<=1000;i+=10) {
            if (maara == 20 || maara == 40+i) {
                summa = maara;
                *saldo0 -= maara;
                do {
                    if (maara%50 == 0) {
                        vitoset += 1;
                        maara = maara - 50;
                    } else {
                        kakoset += 1;
                        maara = maara - 20;
                    }
                }while (maara != 0);
                printf("Otto onnistui. %d kpl 50 euron seteleita, %d kpl 20 euron seteleita\n", vitoset, kakoset);
                printf("Tilin saldo on: %.2lf\n", *saldo0);
                *nostolkm += 1;
                clear();
                return(summa);
            }
        }
    }
    printf("otto ei onnistunut.\nOtto-automaatista voi nostaa vain 20 ja 50 euron seteleita.\n");
    printf("Suurin kertanosto voi olla enintaan 1000 euroa.\n");
    printf("Tilin saldo on: %.2lf\n", *saldo0);
    clear();
    return(0);
}

/*
Saldo, joka printtaa tilin tiedot eli omistaja, saldo ja tilinumero
Jos halutaan näyttää kuinka paljon käyttäjä voi nostaa sitä pitäisi kysyä erikseen, joten jätetään se tulostamatta.
Parametrit: tili0 (int), joka on annettu tilinumero, saldo(0), käyttäjän saldo ja nimi0, käyttäjän nimi.
Ei palauta mitään.
*/
void tilin_saldo(char tili0[], double saldo0, char nimi0[]) {
    if (strlen(tili0) >= 4) {
        tili0[strlen(tili0)-4] = 0;
    }
    printf("Tilin omistaja: %s", nimi0);
    printf("\nTilin numero: %s\nTilin saldo: %.2lf\n", tili0, saldo0);
    clear();
}

/*
Tapahtumat, joka näyttäisi pankkitilin tiedot eli mihin rahaa on käytetty, mistä saatu ja paljonko
Koska näitä tietoja ei saa mistään vaan käyttäjän pitäisi antaa ne käsin, kerrotaan vain mitä käyttäjä on tehnyt ohjelmaa pyörittäessä,
eli kuinka monta kertaa tililtä on nostettu rahaa ja paljonko ja kuinka monta kertaa puheaikaa on lisätty ja paljonko.
Tiedot voi saada printattua näytölle tai kuitille.
Parametrit: nostolkm0 (int) nostojen lukumäärä, kokonosto0 (int) nostettu rahamäärä yhteensä, puhelkm0 (int) kuinka monta kertaa
puheaikaa on lisätty, kokopuhe0 (int) kuinka paljon rahaa puheajan lisäämiseen käytetty.
Ei palauta mitään.
*/
void tapahtumat(int nostolkm0, int kokonosto0, int puhelkm0, int kokopuhe0) {
    char valinta;
    clear();
    printf("Haluatko tapahtumat naytolle (n) vai kuitille (k)?\n: ");
    scanf(" %c", &valinta);
    if (valinta == 'n') {
        printf("Ottoja tehty yhteensa: %d. Nostettu yhteensa: %.2d euroa.\n", nostolkm0, kokonosto0);
        printf("Puheaikaa on ladattu %d kertaa. Ladattu yhteensa: %.2d euron edesta\n", puhelkm0, kokopuhe0);
        clear();
    } else {
        if (valinta == 'k') {
            printf("Kuittia tulostetaan...\nOta kuitti\n");
            clear();
        } else {
            printf("Valitse joko 'n' tai 'k'.\n");
            clear();
        }
    }
}

/*
Puheajan lisääminen,jossa kysytään käyttäjältä paljonko hän haluaa lisätä ja miinustetaan se saldosta
Tarkistetaan, että puheaikaan lisättävä summa on nollan ja käyttäjän saldon välillä. Puheaikaa voi lisätä 10 euroa tai enemmän,
kymmenen euron välein (esim. 10, 20, 30, 40 jne.) 100 asti.
Parametrit: saldo0 (* double), josta miinustetaan käyttäjän syöttämä luku, puhelkm, joka lisää yhden kerran puheajan lisäämisen
lukumäärään, jos lisääminen onnistuu.
Paluuarvo: maara (int), määrä, jonka käyttäjä haluaa lisätä puheaikaan tai 0 jos se ei ole nollan ja saldon välillä.
*/
int puheaika(double * saldo0, int *puhelkm) {
    int maara=0, i;
    clear();
    printf("Paaset takaisin painamalla jotain kirjainta ja enteria\n");
    printf("Desimaaleja ei oteta huomioon\n");
    printf("Voit ladata 10 euroa tai enemman 10 euron valeilla 100 saakka.\nKuinka paljon haluat lisata puheaikaa?\n: ");
    scanf("%d",&maara);
    if (maara <= *saldo0 && maara > 0) {
        for (i=0; 10+i<=100;i+=10) {
            if (maara == 10+i) {
                *saldo0 -= maara;
                printf("Puheajan lisaaminen onnistui. Latasit %d euron edesta\n", maara);
                printf("Tilin saldo on: %.2lf\n", *saldo0);
                *puhelkm += 1;
                clear();
                return (maara);
            }
        }
    }
    printf("Puheajan lisaaminen ei onnistunut. Voit ladata 10, 20, 30, 40, jne. euroa\n");
    printf("Voit ladata enintaan 100 euroa kerralla.\n");
    printf("Tilin saldo on: %.2lf\n", *saldo0);
    clear();
    return(0);
}


int main(void) {
    int  nostolkm =0, puhelkm=0, kokonosto=0, kokopuhe=0;
    char nimi[30]; //rajoituksena ettei nimi voi olla yli 29 merkkiä pitkä
    char pin[256], filepin[256], tili[256];
    double saldo;
    char vastaus; //käytetään kun kysytään kuinka paljon käyttäjä haluaa nostaa tai lisätä puheaikaan rahaa
    FILE *pfile;
    //Koska tämä on automaattia mallintava koodi pitää kysyä tilin nimeä ja rahasummaa joka tilillä on kortin ja koodin sijaan
    printf("Anna tilin omistajan nimi (ei skandeja): ");
    fgets(nimi, sizeof(nimi), stdin); //ei käytetä scanf jotta voi olla välimerkit
    nimi[strcspn(nimi, "\n")] = 0; //poistaa nimen perässä olevan \n, joka olisi tietoja printatessa ongelma
    printf("Anna tilin numero: ");
    fgets(tili, 256, stdin);
    tili[strcspn(tili, "\n")] = 0;
    strcat(tili, ".txt");
    
    while (1) {
        if ((pfile = fopen(tili, "r")) == NULL) {
            pfile = fopen(tili, "w+");
            fputs("0000", pfile); //testausta varten tehdaan koodi, jos tiedosto on tyhjä, niinkuin se testatessa aina onkin
            fclose(pfile);
        }
        pfile = fopen(tili, "r");
        printf("Anna tilin PIN-koodi: ");
        fgets(pin, 256, stdin);
        pin[strcspn(pin, "\n")] = 0; //poistaa \n koodin perästä
        fgets(filepin, 256, pfile);
        filepin[strcspn(filepin, "\n")] = 0; //poistaa \n tiedostosta saadun koodin perästä
        filepin[strcspn(filepin, "\r")] = 0; //poistaa \r tiedostosta saadun koodin perästä
        if (strcmp(pin, filepin) == 0) {
            printf("PIN-koodi oikein\n");

            while(1) {
                printf("Anna tilin saldo (ilman valimerkkeja): ");
                if (scanf("%lf", &saldo) == 1) {
                    if (saldo <= 0) {
                        printf("Saldon tulee olla positiivinen luku.\n");
                        continue;
                    }
                    break;
                } else {
                    printf("Saldon tulee olla positiivinen luku.\n");
                    clear();
                }
            }
            clear();
            break;
        } else {
            printf("PIN-koodi vaarin yrita uudelleen\n");
            continue;
        }
    }
    fclose(pfile);

    while (1) {
        printf("\nHaluatko:\nnostaa kateista (n)\nnahda saldon (s)\nnahda tapahtumat (t)\nlisata puheaikaa liittymaan (p)\nlopettaaksesi paina (l)\n: ");
        scanf(" %c", &vastaus);

        if (vastaus == 'n') {
            kokonosto += nosto(&saldo, &nostolkm);
            continue;
        }

        if (vastaus == 's') {
            tilin_saldo(tili, saldo, nimi);
            continue;
        }

        if (vastaus == 't') {
            tapahtumat(nostolkm, kokonosto, puhelkm, kokopuhe);
            continue;
        }

        if (vastaus == 'p') {
            kokopuhe += puheaika(&saldo, &puhelkm);
            continue;
        }
        /*
        lopetus, joka lopettaa while loopin ja sitä kautta ohjelman pyörittämisen
        */
        if (vastaus == 'l') {
            break;
        }
        else {
            printf("Valitse jokin annetuista vaihtoehdoista\n");
            clear();
        }
    }return (0);
}