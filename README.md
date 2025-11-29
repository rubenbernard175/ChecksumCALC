# ChecksumCALC
C program that computes 8/16/32-bit checksums using big-endian grouped summation with X-padding when data is misaligned. Reads files, prints them in 80-width format, calculates masked hex output, and reports full processed byte count on completion.
# pa02-Checksum-Calculator

C program that computes 8, 16, or 32-bit checksums for an input file. Reads raw ASCII data, prints it in 80-character rows, pads with 'X' when length is incomplete, and prints checksum masked to correct size. Accepts filename + checksum size via command-line arguments.

---

## Resume Entry

**Checksum Calculator — C (CIS3360)**  
• Implemented 8, 16, and 32-bit checksums using bit-masked summation  
• Output processed input in 80-column formatting with LF included  
• Added padding logic for incomplete data blocks (mod-2 / mod-4)  
• Supports command-line execution with STDOUT checksum reporting

---

## How to Compile & Run

```bash
gcc -o pa02 pa02.c
./pa02 inputFile.txt 8
./pa02 inputFile.txt 16
./pa02 inputFile.txt 32
