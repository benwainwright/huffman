# Huffman
Response to a C Programming assignment for the University of Bristol. Creates a [Huffman](https://en.wikipedia.org/wiki/Huffman_coding) tree based on a text file, then visualises it. Note that the 'autofree' repository is a later version of the `memory.c` file in this project. To build, you must have Cmake, SDL2, and Google Test installed.

# Build Steps
* `git clone https://github.com/benwainwright/huffman`
* `mkdir buildHuffman`
* `cd buildHuffman`
* `cmake ../huffman`
* `make check all`

This will build and run all tests, then create the `HuffmanSDL` binary. Execute with `./HuffmanSDL -f <textFileName>`. If you wish to see the text only tree visualisation, add the `-t` flag.

