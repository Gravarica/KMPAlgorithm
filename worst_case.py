from utils import run, parse_output
import csv

def test_worst_case(exec, file_path, result_path):
    patterns = ['AAAAAAAAAAAA', 'AAAAAAAAAAA', 'AAAAAA', 'AAB','AB', 'A', 'B', 'C']

    with open(result_path, 'w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(['Pattern', 'Pojavljivanja', 'Vreme(s)'])

        for pattern in patterns: 
            output = run(exec, pattern, file_path)
            print(output)
            p, v = parse_output(output)
            
            writer.writerow([pattern, p, v])
