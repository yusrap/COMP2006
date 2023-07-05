#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Generates 100 random customers for c_file.txt*/
int generate_c_file(){
    int i, index;
    char letters[] = {'W','I','D'};
    srand(time(NULL));  

    FILE *file = fopen("c_file.txt", "w");    

    if (file == NULL){
        printf("Error: could not open file\n");
        return 1;
    }

    for (i = 1; i <= 100; i++) {    
        index = rand() % 3;    
        fprintf(file, "%d: %c\n", i, letters[index]); 
    }

    fclose(file);
    return 0;
}

