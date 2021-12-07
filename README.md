# aocc
Advent of Code solutions in C

## Building

Should compile on Unix-like systems, though I have only tested Linux.

```shell
mkdir build && cd build
cmake ..
make
```

## Running tests

```shell
cd build
ctest
```

## Running solutions

```shell
cd build/src/aoc_cli
./aoc_cli <year> <day> <part> <path to input file>
```
