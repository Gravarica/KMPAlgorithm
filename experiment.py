import subprocess
import csv

def run_kmp_search(pattern, file_path):
    result = subprocess.run(['./kmp', pattern, file_path], capture_output=True, text=True)
    return result.stdout

def parse_output(output):
    lines = output.strip().split('\n')
    pojavljivanja = lines[0].split(':')[1]
    vreme = lines[1].split(':')[1]

    return pojavljivanja, vreme

def main():
    file_path = 'test.txt'  
    patterns = ['AAAAAAAAAAAA', 'AAAAAAAAAAA', 'AAAAAA', 'AAB','AB', 'A', 'B', 'C']

    with open('results.csv', 'w', newline='') as file:
        writer = csv.writer(file)

        writer.writerow(['Pattern', 'Pojavljivanja', 'Vreme(s)'])

        for pattern in patterns:
            output = run_kmp_search(pattern, file_path)
            p, v = parse_output(output)
            
            writer.writerow([pattern, p, v])

if __name__ == "__main__":
    main()
