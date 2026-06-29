# libnpc Java

[![Version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com/xiayang558/libnpcJava)
[![Java](https://img.shields.io/badge/Java-11%2B-orange)](https://adoptium.net/)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey)]()

[English](README.md) | [中文](README_zh.md)

**Java JNI binding for libnpc** — a NumPy-compatible numerical computing library.

`libnpc-java` provides ~330+ functions across 20+ modules, enabling Java applications to perform high-performance numerical computation using the mature C library [libnpc](https://github.com/xiayang558/libnpc) via JNI.

## Features

- **NumPy-compatible API** — mirrors NumPy function names with Java camelCase conventions
- **AutoCloseable arrays** — try-with-resources for automatic native memory management
- **330+ functions** — creation, math, statistics, linear algebra, FFT, random, I/O, and more
- **Broadcasting** — element-wise operations with numpy-style shape broadcasting
- **Multi-dimensional arrays** — full support for n-dimensional arrays with strides
- **Cross-platform** — macOS (arm64/x86_64) and Linux

## Prerequisites

- **JDK 11+**
- **CMake 3.16+**
- **libnpc** — pre-built C library (static or shared)
- **libnpcpp** — header-only C++ wrapper (headers only)
- **libzip** (optional, for `.npz` file I/O)

## Quick Start

```java
import libnpc.Npc;
import libnpc.NpcArray;

// Create arrays with try-with-resources
try (NpcArray a = Npc.ones(3, 4);
     NpcArray b = Npc.full(new int[]{3, 4}, 2.0)) {

    // Element-wise arithmetic
    NpcArray c = Npc.add(a, b);       // [3.0, 3.0, ...]
    NpcArray d = Npc.sqrt(c);          // [1.732, 1.732, ...]

    // Aggregation
    double total = d.sum().scalarDouble();

    // Linear algebra
    NpcArray I = Npc.eye(3);
    SvdResult svd = Npc.svd(I);

    System.out.println(d);
}
// Arrays auto-closed here
```

## Building from Source

```bash
# 1. Build libnpc (one-time)
cd /path/to/libnpc && make lib

# 2. Build JNI native library
cd libnpcJava
mkdir -p build && cd build
cmake .. \
    -DLIBNPC_ROOT=/path/to/libnpc \
    -DLIBNPCPP_ROOT=/path/to/npc++ \
    -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# 3. Build Java + run tests
cd ..
mvn compile
mvn test
```

## Module Overview

| Module | Functions | Description |
|--------|-----------|-------------|
| **Creation** | zeros, ones, full, empty, arange, linspace, eye, … | Array factory functions |
| **Math** | abs, sqrt, exp, log, sin, cos, add, multiply, … | Element-wise math |
| **Statistics** | sum, mean, min, max, stddev, var, median, … | Aggregation & statistics |
| **NaN Stats** | nanmax, nanmin, nanmean, isnan, isinf, … | NaN-aware operations |
| **Linear Algebra** | dot, matmul, inv, svd, qr, lu, eig, … | Matrix operations |
| **FFT** | fft, ifft, rfft, fft2, fftshift, fftfreq, … | Fourier transforms |
| **Random** | rand, randn, uniform, normal, poisson, … | Random number generation |
| **Shape** | reshape, transpose, concat, stack, split, vander, tri, trilIndices, block, … | Shape manipulation |
| **Comparison** | equal, greater, less, isclose, … | Element-wise comparison |
| **Logic** | logicalAnd, logicalOr, bitwiseAnd, … | Logical/bitwise |
| **Polynomial** | poly, roots, polyfit, polyval, … | Polynomial algebra |
| **Sorting** | sort, argsort, argpartition, … | Array sorting |
| **Set Ops** | unique, intersect1d, setdiff1d, … | Set operations |
| **Interpolation** | interp, diff, ediff1d, gradient, … | Interpolation & diff |
| **Window** | bartlett, blackman, kaiser, hanning, hamming | Window functions |
| **Histogram** | histogram, histogram2d, histogramdd | Binning |
| **I/O** | readtxt, savetxt, loadNpy, saveNpy, savez | File I/O |
| **Mutation** | place, put, putmask, fillDiagonal, … | In-place ops |
| **Misc** | clip, convolve, trimZeros, einsum, einsumPath, asize, … | Miscellaneous |

## API Structure

```
Npc          — Static utility class (~300+ methods)
  ├── zeros(), ones(), full(), arange(), linspace(), eye(), ...
  ├── add(), subtract(), multiply(), divide(), power(), ...
  ├── sin(), cos(), exp(), log(), abs(), sqrt(), ...
  ├── sum(), mean(), min(), max(), stddev(), var(), median(), ...
  ├── dot(), matmul(), inv(), svd(), qr(), lu(), eig(), ...
  ├── fft(), ifft(), rfft(), fft2(), fftshift(), ...
  ├── rand(), randn(), uniform(), normal(), choice(), ...
  ├── vander(), tri(), trilIndices(), block(), bmat(), ...
  ├── einsum(), einsumPath(), asize(), typenameStr(), ...
  └── ...

NpcArray     — Core array class, implements AutoCloseable
  ├── ndim(), size(), shape(), dtype(), ...
  ├── getDouble(), setDouble(), scalarDouble(), toDoubleArray(), ...
  ├── sum(), mean(), reshape(), transpose(), dot(), ...
  └── print(), info(), toString(), close()

Result classes: SvdResult, QrResult, LuResult, EigResult,
                UniqueResult, HistogramResult, ...
```

## License

MIT License — see [LICENSE](LICENSE) for details.

## Related Projects

- [libnpc](https://github.com/xiayang558/libnpc) — C numerical computing library (NumPy-compatible)
- [libnpcpp](https://github.com/xiayang558/libnpcpp) — C++17 RAII wrapper for libnpc
