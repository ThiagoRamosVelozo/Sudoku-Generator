#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_values(char* matrix)
{
    char 
         i, j,
         box_offset, 
         box_start, 
         possible_value_count, 
         current_value,
         neighborhood[9],
         possible_values[9];

    for(char z = 0; z < 81; z++)
    {
        // Obter coordenadas I e J a partir de Z
        i = z / 9;
        j = z % 9;

        // Zerar a contagem de valores possíveis
        possible_value_count = 0;

        // Obter o início do quadro da célula
        box_start = 27 * (i/3) + 3 * (j/3);

        // Zerar cada valor na vizinhança e valores possíveis
        for(char w = 0; w < 9; w++)
        {
            neighborhood[w]     = 0;
            possible_values[w]  = 0;
        }

        // Loop de 0 a 8, para pegar cada item de linha, coluna e quadro do elemento
        for(char k = 0; k < 9; k++)
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
        }
        
        // Empilhar números no vetor de valores possíveis
        for(char q = 0; q < 9; q++)

            // Se o valor neighborhood[q] for 0, empilhe ele
            if(!neighborhood[q]) 
                possible_values[possible_value_count++] = q + 1;
        
        // Se houver qualquer valor possível, sorteie um dos valores possíveis para definir o da célula
        if(possible_value_count) 
            matrix[9 * i + j] = possible_values[rand() % possible_value_count];

        // Caso contrário, zerar a tabela e reiniciar
        else
        {
            z = -1;
            for(char k = 0; k < 81; k++)
                matrix[k] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    char* matrix = malloc(81);
    int   seed   = time(NULL);

    if(argc > 1) seed = atoi(argv[1]);

    srand(seed);
    
    generate_values(matrix);
    
    for(char k = 0; k < 81; k++)
        printf("%d %s", matrix[k], ((k%9) == 8) ? "\n" : "");
    
    return 0;

}