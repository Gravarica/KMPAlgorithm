#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to create the longest prefix suffix (LPS) array
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Modified KMP search algorithm to count pattern occurrences
int KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];
    computeLPSArray(pat, M, lps);
    int i = 0;
    int j = 0;
    int count = 0;

    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            count++;
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    return count;
}

// Function to read the contents of a file into a string
char* readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening filez");
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

    char* pat = argv[1];
    char* filename = argv[2];

    char* txt = readFile(filename); 

    if (txt == NULL) {
        return 1;
    }

    clock_t start, end;

    start = clock();
    int count = KMPSearch(pat, txt);
    end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Pojavljivanja:%d\n", count);
    printf("Vreme:%f\n", cpu_time_used);

    free(txt);
    return 0;
}
