/**
 * @file mecanizacao.c
 * @author Danilo Fróes
 * 
 * @brief Código no qual faço operações matemáticas sem operadores aritméticos,
 * utilizando apenas operações bitwise, o que é conhecido como mecanização.
 * O conceito é estudar o cálculo em hardware, assim como a ULA faz no processador.
 */

#include <stdio.h>

/**
 * @brief Soma dois números usando operações bitwise (mecanização)
 */
int soma_mecanizada(int a, int b) {
    while (b != 0) {
        int carry = a & b;

        a = a ^ b;

        b = carry << 1;
    }

    return a;
}

int main() {
    int num1 = 200;
    int num2 = 54;

    printf("Operacao feita com bitwise: %d + %d = %d\n", num1, num2, soma_mecanizada(num1, num2));

    return 0;
}