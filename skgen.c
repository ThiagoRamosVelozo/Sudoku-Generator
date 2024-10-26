#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_values(char* matrix)
{
    char 
         i, j, k, z = 0,
         box_offset, 
         box_start, 
         possible_value_count, 
         error_count = 0,
         current_value,
         neighborhood[9],      // Aproveitamento de 1/8 bits por endereço :(
         possible_values[9];

    while(z < 81)
    {

        k = 0;

        // Obter coordenadas I e J a partir de Z
        i = z / 9;
        j = z % 9;

        // Zerar a contagem de valores possíveis
        possible_value_count = 0;

        // Obter o início do quadro da célula
        box_start = 27 * (i/3) + 3 * (j/3);

        // Zerar cada valor na vizinhança e valores possíveis
        while(k < 9)
        {
            neighborhood[k]       = 0;
            possible_values[k++]  = 0;
        }

        k = 0;

        // Loop de 0 a 8, para pegar cada item de linha, coluna e quadro do elemento
        while(k < 9)
        {
            // Obter a coluna no quadro
            box_offset = k % 3;

            // Obtendo valores existentes na linha
            if(current_value = matrix[9 * i + k]) 
                neighborhood[current_value - 1] = 1;

            // Obtendo valores existentes na coluna
            if(current_value = matrix[k * 9 + j]) 
                neighborhood[current_value - 1] = 1;

            // Obtendo valores existentes no quadro
            if(current_value = matrix[box_start + box_offset]) 
                neighborhood[current_value - 1] = 1;

            // Caso a coluna no quadro for igual a 2, pular para a próxima linha do quadro
            if(box_offset == 2) 
                box_start += 9;

            k++;
        }

        k = 0;
        
        // Empilhar números no vetor de valores possíveis
        while(k < 9)

            // Se o valor neighborhood[q] for 0, empilhe ele
            if(!neighborhood[k++]) 
                possible_values[possible_value_count++] = k;

        k = 0;
        
        // Se houver qualquer valor possível, sorteie um dos valores possíveis para definir o da célula
        if(possible_value_count)
            matrix[z++] = possible_values[rand() % possible_value_count];

        // Caso contrário, zerar os 9 anteriores e recomeçar
        else
        {
            error_count++;
            while((z > 0) & (k < 9))
            {
                matrix[z--] = 0;
                k--;
            }
        }

        // Se bater o máximo de erros, reiniciar tudo
        if (error_count > 50) {
            error_count = 0;
            while(z > 0)
                matrix[z--] = 0; 
        }
    }
}

int main(int argc, char *argv[])
{
    char  matrix[81] = {0};
    int   seed       = time(NULL);

    if(argc > 1) 
        seed = atoi(argv[1]);

    srand(seed);
    
    generate_values(matrix);
    
    for(char k = 0; k < 81; k++)
        printf("%d %s", matrix[k], ((k%9) == 8) ? "\n" : "");
    
    return 0;

}