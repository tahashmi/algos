#!/usr/bin/env python3
"""
Convert a DNA FASTA sequence into mRNA and protein sequence, then optionally
identify the likely protein name using NCBI BLASTP.

Requirements:
    pip install biopython

Usage:
    python dna_to_mrna_protein.py input.fasta
    python dna_to_mrna_protein.py input.fasta --blast
    python dna_to_mrna_protein.py input.fasta --template-strand --blast
"""

import argparse
from pathlib import Path
from typing import Dict, Any

from Bio import SeqIO
from Bio.Seq import Seq
from Bio.Blast import NCBIWWW, NCBIXML


def get_best_protein_name(protein_sequence: str) -> str:
    """
    Identify the likely protein name using online NCBI BLASTP.

    Internet connection is required. Very short protein sequences may not
    produce reliable matches.
    """
    if not protein_sequence:
        return "No protein sequence generated."

    try:
        print("Running BLASTP search on NCBI. This may take several minutes...")
        result_handle = NCBIWWW.qblast(
            program="blastp",
            database="nr",
            sequence=protein_sequence,
        )

        blast_record = NCBIXML.read(result_handle)

        if blast_record.alignments:
            best_hit = blast_record.alignments[0]
            return best_hit.hit_def

        return "No significant protein match found."

    except Exception as error:
        return f"BLAST search failed: {error}"


def convert_sequence(
    fasta_file: str,
    template_strand: bool = False,
    run_blast: bool = False,
) -> Dict[str, Any]:
    """
    Read a FASTA file, convert DNA to mRNA, translate mRNA to protein,
    and optionally identify likely protein name using NCBI BLAST.
    """
    record = SeqIO.read(fasta_file, "fasta")

    sequence_name = record.id
    full_description = record.description
    dna_sequence = record.seq.upper()

    # Validate sequence characters.
    allowed_bases = set("ATGCN")
    observed_bases = set(str(dna_sequence))
    invalid_bases = observed_bases - allowed_bases
    if invalid_bases:
        raise ValueError(
            f"Invalid DNA bases found: {sorted(invalid_bases)}. "
            "Expected only A, T, G, C, or N."
        )

    # If the FASTA is the template strand, use reverse complement first.
    if template_strand:
        dna_for_translation = dna_sequence.reverse_complement()
    else:
        dna_for_translation = dna_sequence

    # DNA coding strand -> mRNA.
    mrna_sequence = dna_for_translation.transcribe()

    # mRNA -> protein. Translation stops at first stop codon.
    protein_sequence = mrna_sequence.translate(to_stop=True)

    if run_blast:
        protein_name = get_best_protein_name(str(protein_sequence))
    else:
        protein_name = "Not searched. Run with --blast to identify likely protein name."

    return {
        "sequence_name": sequence_name,
        "description": full_description,
        "input_dna_sequence": dna_sequence,
        "dna_used_for_translation": dna_for_translation,
        "mrna_sequence": mrna_sequence,
        "protein_sequence": protein_sequence,
        "protein_name": protein_name,
    }


def print_results(results: Dict[str, Any]) -> None:
    """Print conversion results clearly."""
    print("\n" + "=" * 70)
    print("DNA FASTA to mRNA and Protein Conversion Results")
    print("=" * 70)

    print("\nSequence name:")
    print(results["sequence_name"])

    print("\nFASTA description:")
    print(results["description"])

    print("\nInput DNA sequence:")
    print(results["input_dna_sequence"])

    print("\nDNA sequence used for translation:")
    print(results["dna_used_for_translation"])

    print("\nmRNA sequence:")
    print(results["mrna_sequence"])

    print("\nProtein sequence:")
    print(results["protein_sequence"])

    print("\nLikely protein name:")
    print(results["protein_name"])

    print("\n" + "=" * 70)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Convert a DNA FASTA sequence to mRNA and protein sequence."
    )
    parser.add_argument(
        "fasta_file",
        help="Path to input FASTA file containing one DNA sequence.",
    )
    parser.add_argument(
        "--template-strand",
        action="store_true",
        help="Use this option if the input DNA is the template strand. The script will reverse-complement it before transcription.",
    )
    parser.add_argument(
        "--blast",
        action="store_true",
        help="Run online NCBI BLASTP to identify the likely protein name.",
    )

    args = parser.parse_args()

    if not Path(args.fasta_file).exists():
        raise FileNotFoundError(f"FASTA file not found: {args.fasta_file}")

    results = convert_sequence(
        fasta_file=args.fasta_file,
        template_strand=args.template_strand,
        run_blast=args.blast,
    )
    print_results(results)


if __name__ == "__main__":
    main()
