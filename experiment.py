from genome import test_genome
from worst_case import test_worst_case
import sys

def run_worst_case_test(interactive): 
    exec = './programs/kmp'
    file_path = './data/test.txt'
    results = './results/results_wc.csv'
    if interactive == 'i':
        exec = input("Unesite naziv izvrsive datoteke [<putanja>/exec]: ")
        file_path = input("Unesite putanju do podataka [<putanja>/<fajl>.txt]: ")
        results = input("Unesite putanju do datoteke za cuvanje rezultata [<putanja>/<fajl>.csv]: ")
    test_worst_case(exec, file_path, results)

def run_genome_test(interactive):
    exec_seq = './kmp'
    exec_omp = './kmpomp'
    exec_mpi = './kmpmpi'
    file_path = 'human_genome.txt'
    results = '/results_hg'
    
    if interactive == 'i':
        exec_seq = input("Unesite naziv izvrsive sekvencijalne datoteke <putanja>/exec: ")
        exec_omp = input("Unesite naziv izvrsive openmp datoteke <putanja>/exec: ")
        exec_mpi = input("Unesite naziv izvrsive mpi datoteke <putanja>/exec: ")
        file_path = input("Unesite putanju do podataka <putanja>/<fajl>.txt: ")
        results = input("Unesite putanju do datoteke za cuvanje rezultata: <putanja>/<fajl>.csv")
    test_genome(exec_seq, exec_omp, exec_mpi, file_path, results)

def main():
    # kmp_exec = './kmp'
    # naive_exec = './naive'
    # result_path_kmp = 'results_wc.csv'
    # result_path_naive = 'results_naive_omp.csv'
    # test_worst_case(naive_exec, result_path_naive)
    interactive = sys.argv[1]
    print("Izbor testa")
    print("1 - Worst case")
    print("2 - Human genome")
    choice = input("Unesite izbor: ")
    if choice == '1':
        run_worst_case_test(interactive)
    else:
        run_genome_test(interactive) 

if __name__ == "__main__":
    main()
