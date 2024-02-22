# Huffman Archiver

The Huffman Archiver is a C++ project that implements file compression and decompression using the Huffman algorithm. The Huffman algorithm is a lossless data compression algorithm that assigns variable-length codes to different characters based on their frequency of occurrence in the input file.

## Features

-   Compression: The archiver can compress a given input file by replacing frequently occurring characters with shorter codes, resulting in a smaller output file size.
-   Decompression: The archiver can decompress a previously compressed file, restoring it to its original form.

## Usage

- `-c`: archiving
- `-u`: unzip
- `-f`, `--file <-path>`: input file name
- `-o`, `--output <-path>`: name of the result file

Compile project:
```bash
make
```

To compress a file:
```bash
./huffman -c -f path/to/input_file -o path/to/output_file
```

To decompress a file:
```bash
./huffman -u -f path/to/input_file -o path/to/output_file
```

The program displays compression/decompression statistics: the size of the source data, the size of the received data and the size that was used to store auxiliary data in the output file (e.g. tables). No additional text should be output, just the sizes. All sizes are in bytes.
