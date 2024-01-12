import subprocess

def run(exec, pattern, file_path):
    print("Running search for: ", pattern)
    command = [exec, pattern, file_path]
    result = subprocess.run(command, capture_output=True, text=True)
    return result.stdout

def run_mpi(exec, pattern, filepath, process_num):
    print("Running mpi for: (pattern, np) = (", pattern, process_num, ")")
    command = ['mpiexec', '-n', str(process_num), exec, pattern, filepath]
    result = subprocess.run(command, capture_output=True, text=True)
    return result.stdout

def run_omp(exec, pattern, filepath, process_num):
    print("Running omp for: (pattern, np) = (", pattern, ", ", process_num, ")")
    command = [exec, pattern, filepath, str(process_num)]
    result = subprocess.run(command, capture_output=True, text=True)
    print(result.stdout)
    print(result.stderr)
    return result.stdout

def parse_output(output):
    lines = output.strip().split('\n')
    pojavljivanja = lines[0].split(':')[1]
    vreme = lines[1].split(':')[1]

    return pojavljivanja, vreme