# Minimal CMake-driven Emscripten project

The purpose of this project is to create a very basic minimal CMake project able to compile C++ program using emscripten with the following features enabled:
* Linking to external C++ library crosscompiled to JS file
* Using bindings created via Embind
* Preloading assets files

## How to use
1. Create build directory ```build``` and go there
2. Run cmake specifying toolchain file ```CMAKE_TOOLCHAIN_FILE=path/to/emscripten/emscripten/version/cmake/Modules/Platform/Emscripten.cmake```
3. Run ```make```

Compiled file called ```client.js``` along with the preloaded assets in file ```client.data``` will be put into ```build.emscripten``` directory. Check if it works by opening ```build.emscripten/index.html``` in browser.

# Benchmark results

Its a surprise but, pure Node/JS performs faster on this code than Web Assembly replica (about 80x faster).

More surprise is that even compilling it in pure C++ binary, the Node/JS version still runs about 4-5x faster, even when compiled with full perfomance build ```-O3```

I probably doing something very bad on C++ code replica.

## Update 1

After do a whole day of research and reading a lot, I figured out yes. My original C++ code had a lot of things to improve in perfomance.

I did the best I could and now C++/WASM is faster than JS v8. But not much faster... Only about 10%-15%. It definitively is not much as expected if you consider it took me whole day working on C++ code, to beat a JS that took me 5 minutes (was expecting something like 100x faster to worth all the time spent on it).

Anyway, good learning lesson. And good know the modern JS V8 engine is really very optimized to the point it can easily beat an C++ not very optimized, without any special effort. 

Final results:

```Elapsed time: 2727.1ms (C++ Web ASM)```

```Elapsed time: 2748.2ms (C++ Native)```

```Elapsed time: 3749ms (javascript)```
