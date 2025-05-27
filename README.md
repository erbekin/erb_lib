<p align="center">
  <img src="icon.png" width="200" alt="erb_lib icon">
</p>

<h1 align="center">erb_lib</h1>

<p align="center">
  Modern, multiplatform, modular C++ library for everything.
</p>

<p align="center">
  <a href="https://cmake.org/"><img src="https://img.shields.io/badge/CMake-3.16+-blue.svg" alt="CMake Badge"></a>
  <a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License"></a>
  <img src="https://img.shields.io/badge/language-C++20-blue.svg" alt="Language Badge">
  <img src="https://img.shields.io/badge/status-alpha-orange.svg" alt="Status Badge">
</p>

---

## 📦 About

**erb_lib** is an open-source C++ library designed to be your flexible, plug-and-play toolkit.  
Built using modern C++ standards (17/20/23), it’s optimized for clarity, portability, and extensibility.

Use it for anything — from scripting runtimes to game engines or systems programming.  
It doesn’t tell you how to build, but it builds with you.

---

## ⚙️ Integration

You can easily pull `erb_lib` into your own project via [CMake FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):

```cmake
include(FetchContent)

FetchContent_Declare(
    erb_lib
    GIT_REPOSITORY https://github.com/erbekin/erb_lib.git
    GIT_TAG v0.0.7
)

FetchContent_MakeAvailable(erb_lib)

target_link_libraries(Playground PRIVATE erb::erb)
```

