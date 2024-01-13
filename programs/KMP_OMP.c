#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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

int KMPSearch(char* pat, char* txt, int start, int end) {
    int M = strlen(pat);
    int count = 0;

    int lps[M];
    computeLPSArray(pat, M, lps);
    int i = start;
    int j = 0;

    while (i < end) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            count++;
            j = lps[j - 1];
        } else if (i < end && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
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
        printf("Usage: %s [pattern] [file] [threads]\n", argv[0]);
        return 1;
    }

    char* pat = argv[1];
    char* filename = argv[2];
    int num_threads = atoi(argv[3]);
    omp_set_num_threads(num_threads);

    double start = omp_get_wtime();
    char* txt = readFile(filename); 

    if (txt == NULL) {
        return 1;
    }

    int N = strlen(txt);
    int segment_size = N / num_threads;
    int overlap = strlen(pat) - 1;
    int total_count = 0;

    #pragma omp parallel reduction(+:total_count)
    {
        int t = omp_get_thread_num(); 
        int segment_start = t * segment_size; 
        int segment_end = (t + 1) * segment_size + overlap;

        if (t == num_threads - 1) {
            segment_end = N;
        }

        total_count = KMPSearch(pat, txt, segment_start, segment_end);
    }

    double end = omp_get_wtime();

    double cpu_time_used = end - start;

    printf("Pojavljivanja:%d\n", total_count);
    printf("Vreme:%f\n", cpu_time_used);

    free(txt);
    return 0;
}
