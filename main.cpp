#ifdef __unix__
  #include <thread>
#elif defined(_WIN32) || defined(__WIN32)
  #include <windows.h>
#endif
#include <climits>
#include <iostream>
#include <random>
#include <chrono>

std::mt19937 generator(time(0));
std::uniform_int_distribution<std::mt19937::result_type> distribution(0, INT_MAX);

#ifdef __unix__
    // Checks if a random number is prime.
    // Change this to any different algorithm if you want.
    void threadStresser(){
        int randomNumber = distribution(generator);
        int factorCount = 0;
        for (int i = randomNumber - 1; i > 1; --i){
            if (randomNumber % i == 0){
                ++factorCount;
            }
        }
        std::cout << randomNumber << ": factor count? " << factorCount << "\n";
    }
#elif defined(_WIN32) || defined(__WIN32)
    // Checks if a random number is prime, but using windows.
    // Change this to any different algorithm if you want.
    DWORD WINAPI threadStresser(LPVOID lpParameter){
        int randomNumber = distribution(generator);
        int factorCount = 0;
        for (int i = randomNumber - 1; i > 1; --i){
            if (randomNumber % i == 0){
                ++factorCount;
            }
        }
        std::cout << randomNumber << ": factor count? " << factorCount << "\n";
    }
#endif

int main(){
    #ifdef __unix__
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
    #elif defined(_WIN32) || defined(__WIN32)
        // Get thread count.
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        unsigned int threadCount = sysinfo.dwNumberOfProcessors;
        
        HANDLE threads[threadCount];
        while (true){
            for (int i = 0; i < threadCount; ++i){
                threads[i] = CreateThread(NULL, 0, threadStresser, NULL, 0, NULL);
                if (threads[i] == NULL){
                    return -1;
                } else {
                    CloseHandle(threads[i]);
                }
            }
        }
    #endif
    return 0;
}
