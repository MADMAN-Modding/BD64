#include <iostream>
#include <map>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Encode {
    public:
       string encode(string input) {
            string base64;
            vector <string> base6;

            // Keeps track of the currently watched 8 bits
            string base6Tracking;

            for (int i = 0; i < input.length(); i++)
            {
                // For each of the characters in the string it will get their int value, convert that to 8-bit binary, and then append it to the base64 string
                base64 += bitset<8>(int(input[i])).to_string();
            }



            for (int i = 0; i < base64.length(); i++) {
                base6Tracking += base64[i];

                // For every 6 characters and them to the base6 vector, or if its the end of the string
                if ((i+1) % 6 == 0 || base64.length() - 1 == i) {

                    // Add the current set of 8 bits and then convert them to integers
                    base6.push_back(base6Tracking);

                    // Reset the tracker
                    base6Tracking = "";
                }
            }

            // Adds zeros to the end until it is 6 characters long
            while(base6[base6.size()-1].length() != 6) {
                base6[base6.size()-1] += "0";
            }
            
            // String to be returned
            string final;
            
            // This loop converts all the base6 string to their respective character on the base64 map, then it appends them to the final string
            for (int i = 0; i < base6.size(); i++) {

                bitset bits = bitset<6>(base6[i]);

                final += base64Maps.base64CharMapRev[(int) bits.to_ulong()];
                
            }
            
            return final;
        };
};