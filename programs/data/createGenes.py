import random

def create_genome_like_file(file_path, target_size_bytes):
    nucleotides = ['A', 'C', 'G', 'T']
    written_bytes = 0

    with open(file_path, "w") as file: 
        while written_bytes < target_size_bytes:
            gene_length = random.randint(76, 10**6)
            gene = ''.join(random.choices(nucleotides, k=gene_length))

            file.write(gene + '\n')
            written_bytes += gene_length + 1

file_path = 'human_genome.txt'
target_size_bytes = 10**9 

create_genome_like_file(file_path, target_size_bytes)
print("File created:", file_path)
