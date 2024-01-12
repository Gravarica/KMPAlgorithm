from utils import run, run_mpi, run_omp, parse_output
import csv
import os

def test_genome_sequential(exec, patterns, file_path, result_path):
    print("Sekvencijalno testiranje pokrenuto.")
    with open('../results/' + result_path + '/seq.csv', 'w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(['Pattern', 'Pojavljivanja', 'Vreme(s)'])

        for pattern in patterns:
            output = run(exec, pattern, file_path)
            p, v = parse_output(output)
            
            writer.writerow([pattern, p, v])

    print("Sekvencijalno testiranje zavrseno.")

def test_genome_omp(exec_seq, exec, patterns, file_path, result_path):
    print("omp testiranje pokrenuto.")
    with open('../results/' + result_path + '/omp.csv', 'w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(['NP', 'Pattern', 'Pojavljivanja', 'Vreme(s)'])

        for pattern in patterns:
            output = run(exec_seq, pattern, file_path)
            p, v = parse_output(output)
            
            writer.writerow([1, pattern, p, v])
            for process_num in range(2, 18, 2):
                output = run_omp(exec, pattern, file_path, process_num)
                p, v = parse_output(output)
                
                writer.writerow([process_num, pattern, p, v])

    print("omp testiranje zavrseno.")

def test_genome_mpi(exec_seq, exec, patterns, file_path, result_path):

    print("mpi testiranje pokrenuto.")

    with open('../results/' + result_path + '/mpi.csv', 'w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(['NP', 'Pattern', 'Pojavljivanja', 'Vreme'])
        for pattern in patterns:
            output = run(exec_seq, pattern, file_path)
            p, v = parse_output(output)
            
            writer.writerow([1, pattern, p, v])
            for process_num in range (2,18,2):
                output = run_mpi(exec, pattern, file_path, process_num)
                p, v = parse_output(output)

                writer.writerow([process_num, pattern, p, v])

    print("mpi testiranje zavrseno.")

def test_genome(exec_seq, exec_omp, exec_mpi, file_path, result_path):
    print("Pokretanje testa za programe: ", exec_seq, exec_omp, exec_mpi)
    patterns =['ATCG', 'AAGTCA', 'GAATCATT', 'ATGCAGAGAT', 'ATGCTGATGATCAGTAGATCGA', 'ACGTS']
    print("Obrasci su: ", patterns)

    os.chdir("./programs")

    #test_genome_sequential(exec_seq, patterns, file_path, result_path)
    #test_genome_omp(exec_seq, exec_omp, patterns, file_path, result_path)
    test_genome_mpi(exec_seq, exec_mpi, patterns, file_path, result_path)

    print("Testiranje genoma zavrseno. Rezultati su smesteni na putanji:", result_path)