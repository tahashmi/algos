# fasta_to_rna_protein.py

from Bio import SeqIO
from Bio.Seq import Seq
import sys

def convert_fasta(input_fasta, output_file="converted_sequences.txt"):
    with open(output_file, "w") as out:
        for record in SeqIO.parse(input_fasta, "fasta"):
            gene_name = record.id
            dna_seq = Seq(str(record.seq).upper())

            # DNA -> mRNA
            mrna_seq = dna_seq.transcribe()

            # mRNA/DNA -> Protein
            protein_seq = dna_seq.translate(to_stop=True)

            out.write(f"Gene/Sequence name: {gene_name}\n")
            out.write(f"DNA sequence:\n{dna_seq}\n")
            out.write(f"mRNA sequence:\n{mrna_seq}\n")
            out.write(f"Protein sequence:\n{protein_seq}\n")
            out.write("-" * 60 + "\n")

    print(f"Done. Results saved to {output_file}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python fasta_to_rna_protein.py input.fasta")
    else:
        convert_fasta(sys.argv[1])
