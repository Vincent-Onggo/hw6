#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0}; // Stores base-36 converted values
        int len = k.length();
        int numChunks = (len + 5) / 6;  // Calculate the number of chunks

        for (int i = 0; i < numChunks; ++i) {
            int start = std::max(0, len - 6 * (i + 1)); // Starting index of chunk
            int end = len - 6 * i; // Ending index of chunk
            unsigned long long base36Number = 0;
            unsigned long long power = 1;

            for (int j = end - 1; j >= start; --j) {
                base36Number += letterDigitToNumber(k[j]) * power;
                power *= 36;
            }

            w[4 - i] = base36Number; // Store the base-36 number in w from w[4] to w[0]
        }

        // Compute the final hash using the formula provided
        HASH_INDEX_T hash = 0;
        for (int i = 0; i < 5; ++i) {
            hash += rValues[i] * w[i];
        }
        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (isdigit(letter)) {
            return 26 + (letter - '0'); // '0' to '9' -> 26 to 35
        } else {
            return std::tolower(letter) - 'a'; // 'a' to 'z' -> 0 to 25
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
