# Raiders Of All Pyramids

Final C implementation of the `RAIDERS OF ALL PYRAMIDS` project from `RoaP.pdf`.

The program reads a maze description from a `.in` file and writes the corresponding `.sol` file with:

- the minimum total cost
- the number of walls that must be broken
- the ordered sequence of broken walls in the chosen optimal path

## Project Structure

- `src/`
  - source code and `makefile`
- `tests/`
  - final project test files and reference outputs
- `RoaP.pdf`
  - original project statement

## How It Works

The solver compresses the maze into rooms of connected white cells, builds a graph between rooms through breakable gray walls, and then runs Dijkstra’s algorithm on that graph to obtain a minimum-cost path.

## Build

From `src/`:

```sh
make
```

This generates the executable `roap`.

## Usage

From `src/`:

```sh
./roap ../tests/enunciado104.in
```

This creates:

```sh
../tests/enunciado104.sol
```

The program expects a final-phase input file with extension `.in`.

## Test Files

The `tests/` folder contains bundled final-phase inputs and reference outputs, including:

- `enunciado101.in` to `enunciado116.in`
- `chess094.in`
- `chess10.in`

Reference outputs are provided as `.sol` files, and some `enunciado` cases also include `.check` files.

## Verified

This workspace version was compiled from `src/` and checked against bundled final sample pairs, including:

- `enunciado104.in`
- `enunciado116.in`
- `chess094.in`
- `chess10.in`

Those tested cases matched the expected `.sol` outputs.
