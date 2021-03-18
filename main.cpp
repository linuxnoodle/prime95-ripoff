#include <thread>
#include <random>
#include <iostream>

// Checks if a random number is prime.
// Change this to any different algorithm if you want.
void threadStresser(){
    int randomNumber = rand();
    int factorCount = 0;
    for (int i = randomNumber - 1; i > 1; --i){
        if (randomNumber % i == 0){
            ++factorCount;
        }
    }
    std::cout << randomNumber << ": factor count? " << factorCount << "\n";
}

int main(){
    // Get thread count.
    unsigned int threadCount = std::thread::hardware_concurrency();
    if (!threadCount)
        ++threadCount;
    std::thread threads[threadCount];

    while (true){
        for (int i = 0; i < threadCount; ++i){
            threads[i] = std::thread(threadStresser);
            threads[i].detach();
        }
    }

    return 0;
}
