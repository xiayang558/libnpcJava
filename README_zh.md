# libnpc Java

[![Version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com/xiayang558/libnpcJava)
[![Java](https://img.shields.io/badge/Java-11%2B-orange)](https://adoptium.net/)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey)]()

[English](README.md) | [中文](README_zh.md)

**libnpc 的 Java JNI 绑定** — 兼容 NumPy 风格的数值计算库。

`libnpc-java` 提供 20+ 个模块共 330+ 个函数，通过 JNI 调用成熟的 C 语言库 [libnpc](https://github.com/xiayang558/libnpc)，让 Java 程序能够进行高性能数值计算。

## 特性

- **NumPy 风格 API** — 函数命名风格与 NumPy 一致，采用 Java 驼峰命名规则
- **AutoCloseable 数组** — try-with-resources 自动管理原生内存
- **300+ 函数** — 涵盖数组创建、数学运算、统计、线性代数、FFT、随机数、I/O 等
- **广播机制** — 逐元素运算支持 NumPy 风格的形状广播
- **多维数组** — 完整支持带步长的 N 维数组
- **跨平台** — macOS (arm64/x86_64) 和 Linux

## 环境要求

- **JDK 11+**
- **CMake 3.16+**
- **libnpc** — 预编译的 C 库（静态链接库或动态链接库）
- **libnpcpp** — 仅头文件的 C++ 封装（只需头文件）
- **libzip**（可选，用于 `.npz` 文件 I/O）

## 快速开始

```java
import libnpc.Npc;
import libnpc.NpcArray;

// 使用 try-with-resources 创建数组
try (NpcArray a = Npc.ones(3, 4);
     NpcArray b = Npc.full(new int[]{3, 4}, 2.0)) {

    // 逐元素算术运算
    NpcArray c = Npc.add(a, b);       // [3.0, 3.0, ...]
    NpcArray d = Npc.sqrt(c);          // [1.732, 1.732, ...]

    // 聚合
    double total = d.sum().scalarDouble();

    // 线性代数
    NpcArray I = Npc.eye(3);
    SvdResult svd = Npc.svd(I);

    System.out.println(d);
}
// 数组在此处自动释放
```

## 从源码构建

```bash
# 1. 构建 libnpc（一次性）
cd /path/to/libnpc && make lib

# 2. 构建 JNI 原生库
cd libnpcJava
mkdir -p build && cd build
cmake .. \
    -DLIBNPC_ROOT=/path/to/libnpc \
    -DLIBNPCPP_ROOT=/path/to/npc++ \
    -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# 3. 构建 Java 并运行测试
cd ..
mvn compile
mvn test
```

## 模块总览

| 模块 | 函数 | 描述 |
|--------|-----------|-------------|
| **创建** | zeros, ones, full, empty, arange, linspace, eye, … | 数组工厂函数 |
| **数学** | abs, sqrt, exp, log, sin, cos, add, multiply, … | 逐元素数学运算 |
| **统计** | sum, mean, min, max, stddev, var, median, … | 聚合与统计 |
| **NaN 统计** | nanmax, nanmin, nanmean, isnan, isinf, … | NaN 感知操作 |
| **线性代数** | dot, matmul, inv, svd, qr, lu, eig, … | 矩阵运算 |
| **FFT** | fft, ifft, rfft, fft2, fftshift, fftfreq, … | 傅里叶变换 |
| **随机数** | rand, randn, uniform, normal, poisson, … | 随机数生成 |
| **形状** | reshape, transpose, concat, stack, split, vander, tri, trilIndices, block, … | 形状操作 |
| **比较** | equal, greater, less, isclose, … | 逐元素比较 |
| **逻辑** | logicalAnd, logicalOr, bitwiseAnd, … | 逻辑/位运算 |
| **多项式** | poly, roots, polyfit, polyval, … | 多项式代数 |
| **排序** | sort, argsort, argpartition, … | 数组排序 |
| **集合** | unique, intersect1d, setdiff1d, … | 集合运算 |
| **插值** | interp, diff, ediff1d, gradient, … | 插值与差分 |
| **窗函数** | bartlett, blackman, kaiser, hanning, hamming | 窗函数 |
| **直方图** | histogram, histogram2d, histogramdd | 分箱统计 |
| **I/O** | readtxt, savetxt, loadNpy, saveNpy, savez | 文件读写 |
| **原位** | place, put, putmask, fillDiagonal, … | 原位操作 |
| **杂项** | clip, convolve, trimZeros, einsum, einsumPath, asize, … | 其他 |

## API 结构

```
Npc          — 静态工具类（~300+ 方法）
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

NpcArray     — 核心数组类，实现 AutoCloseable
  ├── ndim(), size(), shape(), dtype(), ...
  ├── getDouble(), setDouble(), scalarDouble(), toDoubleArray(), ...
  ├── sum(), mean(), reshape(), transpose(), dot(), ...
  └── print(), info(), toString(), close()

结果类: SvdResult, QrResult, LuResult, EigResult,
        UniqueResult, HistogramResult, ...
```

## 许可证

MIT License — 详见 [LICENSE](LICENSE)。

## 相关项目

- [libnpc](https://github.com/xiayang558/libnpc) — C 语言数值计算库（兼容 NumPy）
- [libnpcpp](https://github.com/xiayang558/libnpcpp) — libnpc 的 C++17 RAII 封装
