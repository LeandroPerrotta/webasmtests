//var Module = require('./client.js')

var iterations = 0

const RUN_WASM_CODE = true

if(RUN_WASM_CODE){
	Module['onRuntimeInitialized'] = () => {
		let obj = new Module.Application()
		obj.searchBenchmark()	
	}
}

function createRandomGuy(){
	let theGuy = {}
	
	for(let propCount = 0; propCount < 50; propCount++){
		theGuy[propCount] = Math.floor(Math.random() * (50000 - 1)) + 1
		iterations++
	}	
	
	return theGuy
}

const isPrime = function(num){
		return true
	
    for(let i = 2, s = Math.sqrt(num); i <= s; i++){
		iterations++
        if(num % i === 0) return false; 
	}
    return num > 1;
}

function MyClock(){
	this.start = Date.now()
}

MyClock.prototype.finish = function(){
	console.log(`Elapsed time: ${Date.now() - this.start}ms (javascript)`)
}

function searchBenchmark(){

	let c = new MyClock()

	/*
		This is a code to do a huge array search on some data, similar to a SELECT QUERY on huge databases
	*/

	/* starting, we will fill up an array with 100k random items */
	let myGuys = []
	
	for(let guysCount = 0; guysCount < 100000; guysCount++){
		myGuys.push(createRandomGuy())
		iterations++
	}
	
	/* here we created the guys, and filled up it with data, now gonna do some search */ 
	/* for this we will randomize to be search, and when found we want take all properties and look it its there some
		prime numbers.*/

	let keysToBeFound = []
	for(let propCount = 0; propCount < Math.floor(Math.random() * (10 - 5)) + 5; propCount++){
		keysToBeFound.push(propCount)
		iterations++
	}	
	
	let primesFound = 0

	for(let guysToSearch = 0; guysToSearch < 20; guysToSearch++){
		
		for(let i in myGuys){
			let guy = myGuys[i]
			
			for(let y in keysToBeFound){
				if(isPrime(guy[y])){
					primesFound++
				}
				
				iterations++
			}
		}
		
	}	
	
	console.log(`Total primes found: ${primesFound}`)	
	console.log(`Iterations: ${iterations}`)	
	c.finish()

}

searchBenchmark()