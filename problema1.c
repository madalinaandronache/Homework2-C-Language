#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functia returneaza 1 daca sirul *s contine cel putin un spatiu
// si 0 in caz contrar
int verif_spatiu(char *s, int lg_s) {
    int i, ok = 0;

    for (i = 0; i < lg_s; i++) {
        if (s[i] == ' ') ok = 1;
    }

    return ok;
}

// funtia parcurge fiecare sir *s (linie) si modifica textul conform cerintei
void parcurgere(char *s, int lg_s, char (*a)[50]) {
    int i, j, k = 0, p, ok = 0, q;
    char *cuvant, *aux, *aux2, *cuvant2;

    aux = (char *)calloc(201, sizeof(char));
    strcpy(aux, s);

    while (k < lg_s) {
        // in variabila cuvant se salveaza primul cuvant nou gasit
        cuvant = (char *)calloc(201, sizeof(char));
        p = 0;
        ok = 0;
        while (aux[p] != ' ' && p < strlen(aux)) {
            p++;
            k++;
        }
        strncpy(cuvant, aux, p);
        cuvant[p + 1] = '\0';
        int lg_cuv = p;

        // in variabila cuvant2 se salveaza prima secventa de 2 cuvinte gasite
        // memorand insa doar un spatiu intre cele 2 cuvinte
        cuvant2 = (char *)calloc(201, sizeof(char));
        strcpy(cuvant2, cuvant);
        strcat(cuvant2, " ");
        int prim = p;
        while (aux[prim] == ' ') {
            prim++;
        }
        q = prim;
        while (aux[q] != ' ' && q < strlen(aux)) {
            q++;
        }
        aux2 = (char *)calloc(201, sizeof(char));
        strncpy(aux2, aux + prim, q - prim + 1);
        aux2[q - prim] = '\0';
        strcat(cuvant2, aux2);
        cuvant2[strlen(cuvant2)] = '\0';

        // lg_inlocuit pastreaza cate caractere sunt intre inceputul
        // primului cuvant din secventa si finalul celui de-al doilea cuvant
        // din secventa (incluzant toate spatiile)
        int lg_inlocuit = strlen(cuvant2) + prim - p - 1;


        // verificam pentru fiecare secventa memorata in *a, daca corespunde
        // cu un nou cuvant gasit
        for (i = 0; i <= 14; i++) {
            if ((verif_spatiu(a[i], strlen(a[i])) == 0) &&
                (strcmp(cuvant, a[i]) == 0)) {
                for (j = 0; j < strlen(cuvant); j++) {
                    printf("_");
                    ok = 1;
                }
                break;
            } else if ((verif_spatiu(a[i], strlen(a[i])) == 1) &&
                       (strcmp(cuvant2, a[i]) == 0)) {
                for (i = 0; i < lg_inlocuit; i++) {
                    printf("_");
                    ok = 1;
                }
                p = q;
                k = k + q - lg_cuv;
                aux2 = (char *)calloc(201, sizeof(char));
                strcpy(aux2, aux + p);
                aux = (char *)calloc(201, sizeof(char));
                strcpy(aux, aux2);
                p = 0;
                break;
            }
        }

        if (ok == 0) {
            for (j = 0; j < strlen(cuvant); j++) {
                printf(" ");
            }
        }

        while (aux[p] == ' ') {
            printf(" ");
            p++;
            k++;
        }
        aux2 = (char *)calloc(201, sizeof(char));
        strcpy(aux2, aux + p);
        aux = (char *)calloc(201, sizeof(char));
        strcpy(aux, aux2);
        aux[strlen(aux)] = '\0';
    }

    free(aux);
    free(aux2);
    free(cuvant);
    free(cuvant2);
}

// functia intializeaza in vectorul *a cuvintele sau secvenetele de cuvinte
// care trebuie cautate
void initializare(char (*a)[50]) {
    int i;

    for (i = 0; i < 15; i++) {
        a[i][0] = '\0';
    }

    strcpy(a[0], "first of");
    strcpy(a[1], "for each");
    strcpy(a[2], "for");
    strcpy(a[3], "from");
    strcpy(a[4], "in");
    strcpy(a[5], "is a");
    strcpy(a[6], "is");
    strcpy(a[7], "list of");
    strcpy(a[8], "unit");
    strcpy(a[9], "or");
    strcpy(a[10], "while");
    strcpy(a[11], "int");
    strcpy(a[12], "float");
    strcpy(a[13], "double");
    strcpy(a[14], "string");
}

int main() {
    int n, i;
    char s[201], a[16][50];

    scanf("%d", &n);
    getchar();

    initializare(a);

    char **v = (char **)calloc(n, sizeof(char *));

    for (i = 0; i < n; i++) {
        fgets(s, 200, stdin);
        v[i] = (char *)calloc((strlen(s) + 1), sizeof(char));
        strcpy(v[i], s);
        v[i][strlen(v[i]) - 1] = '\0';
        printf("%s\n", v[i]);
        parcurgere(v[i], strlen(v[i]), a);
        printf("\n");
    }

    free(v);
    return 0;
}
