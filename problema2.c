#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dictionary_entry {
    char *word;
    int priority;
} dictionar;

// adaugam un nou cuvant in dictionar
void adaugare_cuvant(dictionar *v, int n, char *cuvant, int lg_cuv) {
    v[n - 1].word = (char *)calloc((lg_cuv + 1) , sizeof(char));
    strcpy(v[n - 1].word, cuvant);
    v[n - 1].priority = 1;
}

// functia cauta un cuvant in dictionar, in functie de cum este introdus
// cuvantul. Daca cuvantul nu este gasit, acesta este adaugat in dictionar.
void cautare_cuvant(dictionar **v, int *n, char *cuvant, int lg_cuv) {
    int ok = 0, i, nr, poz, prior_crt;
    char *s, aux[25];

    if (cuvant[lg_cuv - 1] == '*') {
        ok = 0;

        for (i = 0; i < lg_cuv - 1; i++) {
            printf("%c", cuvant[i]);
        }

        strncpy(aux, cuvant, lg_cuv - 1);
        aux[lg_cuv - 1] = '\0';

        for (i = 0; i < *n; i++) {
            if (strcmp((*v)[i].word, aux) == 0) {
                ok = 1;
                ((*v)[i].priority)++;
                break;
            }
        }
        if (ok == 0) {
            *n = *n + 1;
            nr = *n;
            *v = (dictionar *)realloc(*v, nr * sizeof(dictionar));
            adaugare_cuvant(*v, nr, aux, lg_cuv);
        }

    } else {
        ok = 0;

        for (i = 0; i < *n; i++) {
            s = (char *)calloc(25, sizeof(char));
            strncpy(s, (*v)[i].word, lg_cuv);
            s[strlen(s)] = '\0';
            if (strcmp(s, cuvant) == 0) {
                if (ok == 0) {
                    ok = 1;
                    poz = i;
                    prior_crt = (*v)[i].priority;
                }
                if ((*v)[i].priority > prior_crt) {
                    poz = i;
                    prior_crt = (*v)[i].priority;
                }
                if ((*v)[i].priority == prior_crt && strcmp((*v)[poz].word, (*v)[i].word) > 0) {
                    poz = i;
                    prior_crt = (*v)[i].priority;
                }
            }
        }

        if (ok == 1) {
            printf("%s", (*v)[poz].word);
            ((*v)[poz].priority)++;
        }

        if (ok == 0) {
            *n = *n + 1;
            nr = *n;
            printf("%s", cuvant);
            *v = (dictionar *)realloc(*v, nr * sizeof(dictionar));
            adaugare_cuvant(*v, nr, cuvant, lg_cuv);
        }

        free(s);
    }
}

int main() {
    int n, i, m;
    char cuvant[25];
    dictionar *v;

    scanf("%d", &n);
    v = (dictionar *)calloc(n, sizeof(dictionar));

    for (i = 0; i < n; i++) {
        scanf("%s", cuvant);
        v[i].word = (char *)calloc((strlen(cuvant) + 1) , sizeof(char));
        strcpy(v[i].word, cuvant);
        v[i].priority = 0;
        getchar();
    }

    scanf("%d", &m);

    for (i = 0; i < m; i++) {
        scanf("%s", cuvant);
        if (strcmp(cuvant, ",") == 0 || strcmp(cuvant, ".") == 0 ||
            strcmp(cuvant, ":") == 0 || strcmp(cuvant, "!") == 0 ||
            strcmp(cuvant, "?") == 0) {
                printf("%s", cuvant);
            } else {
            cautare_cuvant(&v, &n, cuvant, strlen(cuvant));
        }
        printf(" ");
    }

    free(v);

    return 0;
}
