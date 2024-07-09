#include <iostream>
#include <map>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
class Main {
    public:
        map<char, int> base64CharMap;
        map<ulong, char> base64CharMapRev;
        
        Main() {
            // Map 'A' to 'Z' (0-25)
            for (char ch = 'A'; ch <= 'Z'; ++ch) {
                // Subtracts the value of A so that it reads right for base64
                base64CharMap[ch] = ch - 'A';
            }

            // Map 'a' to 'z' (26-51)
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                // Subtracts the value of a so that it reads right for base64
                base64CharMap[ch] = ch - 'a' + 26;
            }

            // Map '0' to '9' (52-61)
            for (char ch = '0'; ch <= '9'; ++ch) {
                base64CharMap[ch] = ch - '0' + 52;
            }

            // Map '+' to 62
            base64CharMap['+'] = 62;

            // Map '/' to 63
            base64CharMap['/'] = 63;


            for (const auto &key : base64CharMap) {
                // This reverses the map for encoding stuff, wahoo
                base64CharMapRev[base64CharMap[key.first]] = key.first;
            }

            // Output the map for verification
            for (const auto& key : base64CharMap) {
                std::cout << key.first << " : " << key.second << std::endl;
            }

            for (const auto& key : base64CharMapRev) {
                std::cout << key.first << " : " << key.second << std::endl;
            }
        }

        string encode(string input) {
            string base64;
            vector <string> base6;

            // Keeps track of the currently watched 8 bits
            string base6Tracking;

            for (int i = 0; i < input.length(); i++)
            {
                base64 += bitset<8>(int(input[i])).to_string();
                cout << int(input[i]) << ": " << base64 << "\n";
            }



            for (int i = 0; i < base64.length(); i++) {
                // cout << base64[i];

                // base64 = i % 8 == 0? base64.replace(i, 8, "") : base64;
                base6Tracking += base64[i];

                if ((i+1) % 6 == 0 || base64.length() - 1 == i) {
                    // cout << "\n";
                    // Add the current set of 8 bits and then convert them to integers
                    base6.push_back(base6Tracking);
                    cout << "tracking: " << base6Tracking << "\n";

                    base6Tracking = "";
                }
            }

            string final;
            
            for (int i = 0; i < base6.size(); i++) {
                cout << "base6: " << base6[i] << "\n";

                bitset bits = bitset<6>(base6[i]);

                cout << bits.to_ulong() << "\n";

                final += base64CharMapRev[(int) bits.to_ulong()];
                
            }
            

            return final;
        };
};

int main() {
    Main main;



    string input;

    cout << "Input a string please: ";

    cin >> input;

    cout << main.encode(input);

}