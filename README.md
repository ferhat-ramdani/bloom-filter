# Bloom Filter Implementation in C

This repository contains an implementation of a Bloom Filter data structure written in C. It provides functionalities to create filters, add entries, and test for set membership with a focus on analyzing space and time efficiency. The project also includes comparative tests against Hashmaps and Binary Search Trees.

## Project Structure

- `bin/`: Contains the compiled executable binary.
- `data/`: Contains input data files (e.g., word banks and generated words) used for testing the filter.
- `doc/`: Contains project documentation, including the final report.
- `include/`: Contains C header files (`.h`).
- `obj/`: Contains compiled object files (`.o`).
- `src/`: Contains C source files (`.c`).
- `stats/`: Stores generated statistical data from false positive tests.

## Build Instructions

This project uses `make` for compilation. A GCC compiler is required.

To build the project, run the following command from the root directory:

```sh
make
```

This will compile the source code and place the executable `bloom_filter` inside the `bin/` directory.

To clean the compiled object files and the binary, run:

```sh
make clean
```

## Running the Application

After a successful build, you can run the interactive menu using:

```sh
./bin/bloom_filter
```

Once the application is running, it will present a menu with several basic commands to interact with the Bloom Filter (e.g., create a filter, insert an entry, read from a file, run statistical tests).

## Documentation and Results

For a detailed analysis, theoretical background, and the results of the performance comparisons, please refer to the project report located at:

[doc/rapport.pdf](doc/rapport.pdf)
