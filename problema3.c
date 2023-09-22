#include <stdio.h>

// implementeaza operatia de interschimbare
int interschimb(int a, int b) {
    int poz1, poz2;
    unsigned int bit1, bit2;

    poz2 = (b & ((1<<2) - 1));
    poz1 = ((b >> 2) & ((1 << 2) - 1));
    poz1 = 3 - poz1;
    poz2 = 3 - poz2;
    bit1 = ((a >> poz1) & 1);
    bit2 = ((a >> poz2) & 1);

    if (bit1 ^ bit2) {
        a = a ^ (1 << poz1);
        a = a ^ (1 << poz2);
    }

    return a;
}

// implementeaza operatia xor
int opxor(int a, int b) {
    unsigned int nr;

    nr = (a | b);
    nr = nr & (~a | ~b);
    a = nr;

    return a;
}

// implementeaza operatia de rotire
int rotire(int a, int b) {
    int i = 0;
    unsigned int bit1;

    b = b % 4;
    while (i < b) {
        bit1 = (a >> 3) & 1;
        a = (a << 1);
        a = (a & ((1 << 4) - 1));
        a = (a & ~1) | bit1;
        i++;
    }

    return a;
}

// implementeaza operatia de adunare
int adunare(int a, int b) {
    unsigned int transp;

    while (b != 0) {
        transp = a & b;
        a = opxor(a, b);
        b = transp << 1;
    }
    a = (a & ((1 << 4) - 1));
    return a;
}

int main() {
    int m, p, i, n, a, b;
    unsigned int v[6], op[6];

    scanf("%d", &n);
    scanf("%d", &m);
    p = 0;
    for (i = n; i >= 0; i--) {
        v[i] = ((m >> p) & ((1 << 4) - 1));
        if (i != n) {
            op[i] = (m >> (p - 2) & ((1 << 2) - 1));
        }
        p = p + 6;
    }

    int (*operatie[5])(int a, int b) = {adunare, interschimb, rotire, opxor};

    i = 0;
    a = v[0];
    while (i < n) {
        b = v[i + 1];
        a = operatie[op[i]](a, b);
        i++;
    }

    printf("%d", a);

    return 0;
}
