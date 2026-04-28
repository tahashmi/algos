# fasta_to_rna_protein.py

from Bio import SeqIO
from Bio.Seq import Seq
import sys
import io # Import io for StringIO

def convert_fasta(input_fasta, output_file="converted_sequences.txt"):
    # SeqIO.parse can accept a file path string or a file-like object
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
    input_source = None
    # Check if a valid command-line argument for the FASTA file is provided
    # In Colab, sys.argv can contain elements like '-f' which are not actual filenames
    if len(sys.argv) > 1 and sys.argv[1] != '-f':
        input_source = sys.argv[1]
    else:
        # If no valid file argument is found, use a default sample FASTA content
        print("No valid FASTA input file path provided. Using a sample FASTA sequence.")
        sample_fasta_content = """>gene_1\nATGCGTAATGCGT\n>gene_2\nCGTAGCTAGCT\n>gene_3\nGATTACAGA\n"""
        input_source = io.StringIO(sample_fasta_content)

    convert_fasta(input_source)
