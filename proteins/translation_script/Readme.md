# DNA FASTA to mRNA, Protein Sequence, and Protein Name

This repository contains a Python script that takes a DNA gene sequence in FASTA format and converts it into:

1. mRNA sequence  
2. Protein sequence  
3. Likely protein name using online NCBI BLASTP, if requested  

The script uses Biopython, especially `Bio.Seq`, `Bio.SeqIO`, and optional NCBI BLAST tools.

<img width="1268" height="710" alt="image" src="https://github.com/user-attachments/assets/8dbf1a02-5ff0-4e5b-953b-61ad707e46bc" />

---

## Repository files

```text
DNA-to-RNA-Protein/
├── README.md
├── dna_to_mrna_protein.py
└── input.fasta
```

---

## 1. Install requirements

Install Biopython:

```bash
pip install biopython
```

---

## 2. Prepare your FASTA file

Create a FASTA file named `input.fasta`.

Example:

```fasta
>Example_gene
ATGGCCATTGTAATGGGCCGCTGAAAGGGTGCCCGATAG
```

The line beginning with `>` is the sequence name.  
The following line is the DNA sequence.

---

## 3. Run the script

Basic conversion:

```bash
python dna_to_mrna_protein.py input.fasta
```

Run conversion and identify likely protein name using NCBI BLASTP:

```bash
python dna_to_mrna_protein.py input.fasta --blast
```

If your DNA sequence is the template strand instead of the coding strand:

```bash
python dna_to_mrna_protein.py input.fasta --template-strand
```

Template strand plus BLAST protein-name search:

```bash
python dna_to_mrna_protein.py input.fasta --template-strand --blast
```

---

## 4. Example output

```text
======================================================================
DNA FASTA to mRNA and Protein Conversion Results
======================================================================

Sequence name:
Example_gene

FASTA description:
Example_gene

Input DNA sequence:
ATGGCCATTGTAATGGGCCGCTGAAAGGGTGCCCGATAG

DNA sequence used for translation:
ATGGCCATTGTAATGGGCCGCTGAAAGGGTGCCCGATAG

mRNA sequence:
AUGGCCAUUGUAAUGGGCCGCUGAAAGGGUGCCCGAUAG

Protein sequence:
MAIVMGR

Likely protein name:
Not searched. Run with --blast to identify likely protein name.

======================================================================
```

If you run with `--blast`, the final protein-name line will show the best matching protein hit from NCBI BLASTP.

---

## 5. How the script works

### Step 1: Read FASTA

The script reads the FASTA file using Biopython:

```python
record = SeqIO.read(fasta_file, "fasta")
```

It extracts:

- sequence name
- full FASTA description
- DNA sequence

---

### Step 2: Convert DNA to mRNA

For a coding DNA strand, transcription replaces:

```text
T → U
```

Example:

```text
DNA:  ATGGCC
mRNA: AUGGCC
```

The script performs this with:

```python
mrna_sequence = dna_for_translation.transcribe()
```

---

### Step 3: Translate mRNA to protein

mRNA is read in groups of three bases called codons.

Example:

```text
AUG GCC AUU GUA AUG GGC CGC UGA
```

Translation:

```text
AUG = M
GCC = A
AUU = I
GUA = V
AUG = M
GGC = G
CGC = R
UGA = Stop
```

Protein:

```text
MAIVMGR
```

The script performs this with:

```python
protein_sequence = mrna_sequence.translate(to_stop=True)
```

The argument `to_stop=True` means translation stops at the first stop codon.

---

### Step 4: Identify the likely protein name

When you use `--blast`, the script sends the translated protein sequence to NCBI BLASTP:

```python
NCBIWWW.qblast(
    program="blastp",
    database="nr",
    sequence=protein_sequence,
)
```

The best BLAST hit is returned as the likely protein name.

Internet connection is required for this step.

---

## 6. Important biological notes

### Coding strand vs template strand

This script assumes the input DNA is the coding strand by default.

Coding DNA example:

```text
DNA coding strand: ATGGCC
mRNA:              AUGGCC
```

If your sequence is the template strand, use:

```bash
python dna_to_mrna_protein.py input.fasta --template-strand
```

The script will reverse-complement the sequence before transcription.

---

### Reading frame matters

The script translates from the first base of the sequence. If your FASTA sequence does not begin at the correct coding frame, the protein sequence may be incorrect.

For best results, use a clean CDS sequence that starts with a start codon, usually `ATG`.

---

### Introns must be removed first

If your DNA sequence is genomic DNA with introns, translate the coding sequence/CDS instead. Protein translation should normally be done from spliced mRNA or CDS, not raw genomic DNA.

---

## 7. Limitations

- BLAST requires internet access.
- NCBI BLAST can take several minutes.
- Very short protein sequences may not give reliable protein names.
- Sequences with ambiguous bases such as `N` may translate into `X` or produce uncertain results.
- The script expects one FASTA record per file.

---

## 8. Citation / acknowledgement

This project uses Biopython.

Biopython website: https://biopython.org/
