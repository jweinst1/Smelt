# smelt

*A single header CSV library in C*

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/jweinst1/Smelt/blob/master/LICENSE.md)
![language button](https://img.shields.io/badge/Language-C-orange.svg)
![build button](https://img.shields.io/badge/Build-passing-green.svg)

## Intro

Smelt is a C-library for parsing and saving CSV files and data. Smelt is a compact, single header library under 500 lines of code. It's cross platform, and easier to include in almost any project. Smelt also comes as a shared library with a different header for linking into projects. With `LibSmelt`, the shared library version of Smelt, it can also be called from other languages like Python.

## Building

If you just want to use the header version of `Smelt`, feel free to drop `include/Smelt.h` into your project.

To build the `/build` directory, on unix, you can run the shell script at `scripts/build.sh`. This will build the shared library of Smelt as well as copy the single header and shared library header to the `/build` directory.

Instead, you can also build directly with cmake

```
$ mkdir -p build
$ cmake ..
$ make
```


### Running Tests

The `Smelt` library is throughly tested to ensure maximum quality. If you would like to run the unit tests, run the shell script at `scripts/testrun.sh`. Alternatively, you can follow the steps below

```
$ mkdir -p build
$ cmake ..
$ make
$ ./SmeltHeaderTests
$ ./SmeltLibTests
```

The lib tests contain tests for the functions exposed via the shared library and the header tests contain tests for all the smaller, lower level functions in the single header distribution.

## Usage

`Smelt` is a straight forward, easy to use CSV library for the C language. For performance critical tasks, you can also call `Smelt` functions from languages like Python. Smelt contains a public API, functions that are exposed to the shared library and start with `Smelt_`, as well as a full API which includes smaller, `static` functions. Overall, the public API is more simplified and good for general use cases.

### Parsing a string:

This functions parses a c string into a `smelt_table_t*`:

```c
smelt_table_t*
Smelt_parse_string(const char* csv);
```

### Parsing a file:

This function parses the file content at a specified path into a `smelt_table_t*`:

```c
smelt_table_t*
Smelt_parse_file(const char* path);
```

### Saving to file:

This function writes the table to a file at `path`. It accepts a C file mode, so you can append to an existing CSV file or write to the beginning of a file.

```c
int
Smelt_to_file(smelt_table_t* table, const char* path, const char* mode);
```

### Setting and Getting Data

The following functions allow you to access and change data anywhere in the `smelt_table_t*` structure capsule.

```c
smelt_row_t*
Smelt_get_row(smelt_table_t* table, size_t index);

smelt_item_t*
Smelt_get_item(smelt_table_t* table, size_t row, size_t col);

int
Smelt_set_item_str(smelt_table_t* table, 
	               size_t x, 
	               size_t y, 
	               const char* value,
	               size_t slice);

int
Smelt_set_item_int(smelt_table_t* table, 
	               size_t x, 
	               size_t y, 
	               const int value);
```

### Printing

You can print your smelt parsed table with this function:

```c
void
Smelt_print_table(smelt_table_t* table);
```

## License

`Smelt` is fully MIT licensed. Please maintain a copy of the MIT license of the repo in any distribution you intend to use it in.