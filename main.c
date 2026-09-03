#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int valor_da_palavra(const char *palavra) {
    const char *unidades[] = {
        "zero", "um", "dois", "tres", "quatro", "cinco", "seis",
        "sete", "oito", "nove", "dez", "onze", "doze", "treze",
        "quatorze", "catorze", "quinze", "dezesseis", "dezessete",
        "dezoito", "dezenove"
    };
    const char *dezenas[] = {
        "", "", "vinte", "trinta", "quarenta", "cinquenta",
        "sessenta", "setenta", "oitenta", "noventa"
    };
    int indice;

    for (indice = 0; indice <= 20; indice++) {
        if (strcmp(palavra, unidades[indice]) == 0) {
            return indice;
        }
    }

    for (indice = 2; indice <= 9; indice++) {
        if (strcmp(palavra, dezenas[indice]) == 0) {
            return indice * 10;
        }
    }

    if (strcmp(palavra, "cem") == 0) {
        return 100;
    }

    return -1;
}

int converter_palpite(const char *entrada) {
    char copia[100];
    char *palavra;
    char *fim_numero;
    long numero;
    int total = 0;
    int valor;

    numero = strtol(entrada, &fim_numero, 10);
    while (*fim_numero == ' ' || *fim_numero == '\t' || *fim_numero == '\n') {
        fim_numero++;
    }
    if (*fim_numero == '\0') {
        return (int) numero;
    }

    strncpy(copia, entrada, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';
    copia[strcspn(copia, "\n")] = '\0';

    palavra = strtok(copia, " \t");
    while (palavra != NULL) {
        if (strcmp(palavra, "e") != 0) {
            valor = valor_da_palavra(palavra);
            if (valor < 0) {
                return -1;
            }
            total += valor;
        }
        palavra = strtok(NULL, " \t");
    }

    return total;
}

int main(void) {
    int palpite;
    int numero_sorteado;
    char entrada[100];

    printf("Digite um numero de 1 a 100 (em algarismos ou por extenso): ");

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        printf("Nao foi possivel ler a entrada.\n");
        return 1;
    }

    palpite = converter_palpite(entrada);
    if (palpite < 1 || palpite > 100) {
        printf("Entrada invalida. Digite um numero de 1 a 100.\n");
        return 1;
    }

    srand((unsigned int) time(NULL));
    numero_sorteado = rand() % 100 + 1;

    if (palpite == numero_sorteado) {
        printf("Acertou! O numero sorteado foi %d.\n", numero_sorteado);
    } else {
        printf("Errou! O numero sorteado foi %d.\n", numero_sorteado);
    }

    return 0;
}
