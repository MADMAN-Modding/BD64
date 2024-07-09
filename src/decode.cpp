#include <iostream>
#include <map>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
class Decode {
    public:
        string decode(string input) {
            string base64;
            vector <string> base8;

            // Keeps track of the currently watched 8 bits
            string base8Tracking;

            for (int i = 0; i < input.length(); i++) {
                base64 += bitset<6>(Base64Maps::base64CharMap[input[i]]).to_string();
            }

            for (int i = 0; i < base64.length(); i++) {
                base8Tracking += base64[i];

                if ((i+1) % 8 == 0 || base64.length() - 1 == i) {

                    // Add the current set of 8 bits and then convert them to integers
                    base8.push_back(base8Tracking);

                    base8Tracking = "";
                }
            }

            while(base8[base8.size()-1].length() != 8) {
                base8[base8.size()-1] += "0";
            }

            string final;

            for (int i = 0; i < base8.size(); i++) {
                bitset bits = bitset<8>(base8[i]);

                final += (char) bits.to_ulong();
            }

            return final;
        }

        void clearScreen() {
            cout << "\033[2J\033[1;1H";
        }
};