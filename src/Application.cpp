#include "Application.h"

#include <vector>
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

Guy Application::createRandomGuy() {
	Guy theGuy;
	
	for(unsigned int propCount = 0; propCount < 50; propCount++){
		theGuy[propCount] = rand() % 50000 + 1;
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
	
	std::vector<Guy> myGuys;
	myGuys.reserve(100000);
	
	std::clog << "Filling up guys...";
	
	for(unsigned int guysCount = 0; guysCount < 100000; guysCount++){
		myGuys.push_back(createRandomGuy());
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
			
		
		for(unsigned int guy_id = 0; guy_id < 100000; guy_id++){
			
			Guy theGuy = myGuys[guy_id];
			for(unsigned int y : keysToBeFound){
				
				if(isPrime(theGuy[y])){
					
					primesFound++;
					
				}
				
				iterations++;
			}	
		}		
	}	
	std::cout << " Done" << std::endl;
	
	std::clog << "Total primes found: " << primesFound << std::endl;
	
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time_span = end - start;	
	
	std::clog << "Elapsed time: " << time_span.count() << "ms (C++)" << std::endl;
	std::clog << "Iterations: " << iterations << std::endl;
	std::clog << "Cached primes length: " << primesCache.size() << std::endl;
	std::clog << "Cached primes used: " << primesCacheUsed << std::endl;
	std::clog << "Uncached primes used: " << uncachedPrimesUsed << std::endl;
}

bool Application::isPrime(unsigned num){
	
	return true;
	
	//auto search = primesCache.find(num);
	if(primesCache[num]){
		primesCacheUsed++;
		return primesCache[num];
	}
	
	double s = std::sqrt(num);
    for(unsigned int i = 2; i <= s; i++){
		iterations++;
        if(num % i == 0) {
			primesCache[num] = false;
			uncachedPrimesUsed++;
			return false; 
		}
		else{
			primesCache[num] = true;
		}
	}
	
	bool isPrime = num > 1;
	primesCache[num] = isPrime;
	uncachedPrimesUsed++;
	
    return isPrime;
}