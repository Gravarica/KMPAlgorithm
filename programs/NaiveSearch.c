#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int naiveSearch(char* txt, char* pat) {
    int M = strlen(pat);
    int N = strlen(txt);
    int count = 0;

    #pragma omp parallel for reduction(+:count) 
    for (int i = 0; i <= N - M; i++) {
        int j;

        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M)
            count++;
    }

    return count;
}

char* readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    char *content = (char*)malloc(sizeof(char) * (size + 1));
    if (content == NULL) {
        perror("Error allocating memory for file content");
        fclose(file);
        return NULL;
    }

    fread(content, sizeof(char), size, file);
    content[size] = '\0';

    fclose(file);
    return content;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s [pattern] [file] \n", argv[0]);
        return 1;
    }

    double start = omp_get_wtime();
    char* pat = argv[1];
    char* filename = argv[2];
    char* txt = readFile(filename); 

    if (txt == NULL) {
        return 1;
    }

    int count = naiveSearch(txt, pat);
    double end = omp_get_wtime();

    double cpu_time_used = end - start;

    printf("Pojavljivanja:%d\n", count);
    printf("Vreme:%f\n", cpu_time_used);

    free(txt);
    return 0;
}
