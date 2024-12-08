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

            // This takes the int obtained by the character map, then it appends it to the base64 string
            for (int i = 0; i < input.length(); i++) {
                base64 += bitset<6>(base64Maps.base64CharMap[input[i]]).to_string();
            }

            // This loop will add every 8 characters to an index of the base8 vector, it also adds the last characters of the string
            for (int i = 0; i < base64.length(); i++) {
                base8Tracking += base64[i];

                if ((i+1) % 8 == 0 || base64.length() - 1 == i) {

                    // Add the current set of 8 bits and then convert them to integers
                    base8.push_back(base8Tracking);

                    base8Tracking = "";
                }
            }

            // This adds zeros to the last index of the base8 vector till it is equal to 8 bits long
            while(base8[base8.size()-1].length() != 8) {
                base8[base8.size()-1] += "0";
            }

            // String to be returned
            string final;

            // This loop just gets the ascii value of each 8-bit index in the base8 vector
            for (int i = 0; i < base8.size(); i++) {
                bitset bits = bitset<8>(base8[i]);

                final += (char) bits.to_ulong();
            }

            return "```" + final + "```";
        }
};