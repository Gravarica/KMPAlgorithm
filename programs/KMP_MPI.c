#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(const char* pat, int M, int* lps) {
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

void KMPSearch(const char* pat, char* txt, int *matches) {
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
    *matches = count;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (argc < 2) {
        if (world_rank == 0) {
            printf("Usage: %s [pattern] [filepath] \n", argv[0]);
        }

        MPI_Finalize();
        return 1;
    }

    MPI_File fh;
    MPI_Status status;
    const char* pattern = argv[1];
    const char* file_path = argv[2];

    char fullFilePath[100];

    double start_time = MPI_Wtime();

    MPI_File_open(MPI_COMM_WORLD, file_path, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

    MPI_Offset file_size;
    MPI_File_get_size(fh, &file_size);
    
    MPI_Offset chunk_size = file_size / world_size;
    MPI_Offset start = world_rank * chunk_size;
    MPI_Offset end = (world_rank == world_size - 1) ? file_size : start + chunk_size;

    char *buffer = (char *)malloc((end - start + 1) * sizeof(char));

    MPI_File_read_at(fh, start, buffer, end - start, MPI_CHAR, &status);
    buffer[end - start] = '\0';

    int num_matches = 0;
    KMPSearch(pattern, buffer, &num_matches);

    int total_matches;
    MPI_Reduce(&num_matches, &total_matches, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    free(buffer);
    MPI_File_close(&fh);

    double end_time = MPI_Wtime();
    if (world_rank == 0) {
        printf("Pojavljivanja:%d\n", total_matches);
        printf("Vreme:%f\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
