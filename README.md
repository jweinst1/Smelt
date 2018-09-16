# smelt

*A single header CSV library in C*

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

## License

`Smelt` is fully MIT licensed. Please maintain a copy of the MIT license of the repo in any distribution you intend to use it in.