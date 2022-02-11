#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef USE_EMSCRIPT
#include <emscripten/html5.h>
#include <emscripten/bind.h>

using namespace emscripten;
#endif

#include <map>
#include <utility>

typedef std::map<unsigned int, unsigned int> Guy;
typedef std::map<unsigned int, bool> Primes;

class Application {
public:
    void searchBenchmark();
	Guy createRandomGuy();
	bool isPrime(unsigned int num);
	
	unsigned int iterations = 0;
	Primes primesCache;
	int primesCacheUsed = 0;
	int uncachedPrimesUsed = 0;
	
};

#ifdef USE_EMSCRIPT
// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
  class_<Application>("Application")
    .constructor()
    .function("searchBenchmark", &Application::searchBenchmark)
    ;
}
#endif

#endif
