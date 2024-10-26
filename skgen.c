#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_values(char* matrix)
{
    char box_offset, 
         box_start, 
         possible_value_count, 
         current_value,
         error_count        = 0, 
         *neighborhood       = malloc(9),
         *possible_values    = malloc(9);
    
    start:
    for(char i = 0; i < 9; i++) for(char j = 0; j < 9; j++)
    {
        possible_value_count = 0;
        box_start = 27 * (i/3) + 3 * (j/3);

        for(char w = 0; w < 9; w++)
        {
            neighborhood[w]     = 0;
            possible_values[w]  = 0;
        }

        for(char k = 0; k < 9; k++)
        {
            box_offset = k%3;
            if(current_value = matrix[9*i+k]) neighborhood[current_value - 1] = 1;
            if(current_value = matrix[k*9+j]) neighborhood[current_value - 1] = 1;
            if(current_value = matrix[box_start + box_offset]) neighborhood[current_value - 1] = 1;
            if(box_offset == 2) box_start += 9;
        }
        
        for(char q = 0; q < 9; q++)
            if(!neighborhood[q]) possible_values[possible_value_count++] = q + 1;
        
        if(possible_value_count) matrix[9*i+j] = possible_values[rand() % (possible_value_count)];
        else
        {
            for(char p = 0; p < j; p++)
                matrix[9*i+p] = 0;

            j = -1;
            error_count++;
        }
        
        if(error_count > 50)
        {
            error_count = 0;
            for(char k = 0; k < 81; k++)
                matrix[k] = 0;

            goto start;
        }
    }
    
    free(neighborhood);
    free(possible_values);
}

int main(int argc, char *argv[])
{
    char*   matrix  = malloc(81);
    int     seed    = time(NULL);

    if(argc > 1) seed = atoi(argv[1]);

    srand(seed);
    
    generate_values(matrix);
    
    for(char k = 0; k < 81; k++)
        printf("%d %s", matrix[k], ((k%9) == 8) ? "\n" : "");
    
    return 0;

}