# Aimo

A Didactic Bitboard Chess Engine

![Aimo Koivunen -- Finnish Soldier and the first documented case of a soldier overdosing on methamphetamine during combat.](https://github.com/OmuW/Aimo/blob/main/aimo.jpeg)

## What is this?

A chess engine is a program that plays chess. It takes as input a chess position and outputs a move. This project is a chess engine written in C++. It is not meant to be a strong chess engine, but rather a didactic one. It is meant to be easy to understand and modify.

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
