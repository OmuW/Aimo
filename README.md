# Aimo

Bitboard Chess Engine

## How to build

first, ensure you have the following dependencies installed:

- cmake
- make
- Catch2 (for tests)

then, run the following commands (from the main project directory):

```bash
mkdir build
cd build
cmake ..
make
```

Note: the build directory is ignored by git, so you can safely delete it at any time.

## How to run

To run the engine, run the following command (from the build directory):

```bash
./aimo
```

## How to run tests

To run the tests, run the following command (from the build directory):

```bash
./tests/tests
```
