#include "Application.h"

#include <vector>
#include <array>
#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>

#ifndef USE_EMSCRIPT
int main(){
	Application* app = new Application();
	
	app->searchBenchmark();
}
#endif

Guy* Application::createRandomGuy() {
	Guy* theGuy = new Guy();
	
	for(unsigned int propCount = 0; propCount < 50; propCount++){
		theGuy->insert({propCount, rand() % 50000 + 1});
		iterations++;
	}	
	
	return theGuy;
}

void Application::searchBenchmark() {

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	/*
		This is a code to do a huge array search on some data, similar to a SELECT QUERY on huge databases
	*/

	/* starting, we will fill up an array with 100k random items */
	
	std::clog << "Starting benchmark..." << std::endl;
	
	std::array<Guy*, 100000> myGuys;
	
	std::clog << "Filling up guys...";
	
	for(unsigned int guysCount = 0; guysCount < 100000; guysCount++){
		myGuys[guysCount] = createRandomGuy();
		iterations++;
	}
	
	std::clog << " Done" << std::endl;
	
	/* here we created the guys, and filled up it with data, now gonna do some search */ 
	/* for this we will randomize to be search, and when found we want take all properties and look it its there some
		prime numbers.*/
	
	std::vector<unsigned int> keysToBeFound;
	unsigned int propMax = rand() % 5 + 5;
	std::clog << "Preparing keys... (" << propMax << ")";
	for(unsigned int propCount = 0; propCount < propMax; propCount++){
		keysToBeFound.push_back(propCount);
		iterations++;
	}	
	std::clog << " Done" << std::endl;
	
	unsigned int primesFound = 0;

	std::cout << "Searching at " << myGuys.size() << std::endl;
	for(unsigned int guysToSearch = 0; guysToSearch < 20; guysToSearch++){
			
		for(Guy* theGuy : myGuys){
			for(unsigned int y : keysToBeFound){
				
				if(isPrime(theGuy->at(y))){		
					primesFound++;	
				}

				iterations++;
			}
		}
	}	

	std::cout << " Done" << std::endl;
	
	std::clog << "Total primes found: " << primesFound << std::endl;
	std::clog << "Iterations: " << iterations << std::endl;

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time_span = end - start;	
	
	#ifndef USE_EMSCRIPT
	std::clog << "Elapsed time: " << time_span.count() << "ms (C++ Native)" << std::endl;	
	#else
	std::clog << "Elapsed time: " << time_span.count() << "ms (C++ Web ASM)" << std::endl;	
	#endif
}

const bool Application::isPrime(unsigned num){
	
	const double s = std::sqrt(num);
    for(unsigned int i = 2; i <= s; i++){
		iterations++;
        if(num % i == 0) {
			return false; 
		}
	}
	
	bool isPrime = num > 1;	
    return isPrime;
}