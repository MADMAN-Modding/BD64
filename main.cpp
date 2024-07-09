#include <iostream>
#include <map>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
class Main {
    public:
        map<char, int> base64CharMap;
        
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

            // Output the map for verification
            // for (const auto& pair : base64CharMap) {
            //     std::cout << pair.first << " : " << pair.second << std::endl;
            // }
        }

        string encode(string input) {
            string base64;
            vector <int> base8;

            // Keeps track of the currently watched 8 bits
            string base8Tracking;

            for (int i = 0; i < input.length(); i++)
            {
                base64 += bitset<6>(base64CharMap[input[i]]).to_string();
            }



            for (int i = 1; i <= base64.length(); i++) {
                // cout << base64[i];

                // base64 = i % 8 == 0? base64.replace(i, 8, "") : base64;
                base8Tracking += base64[i];

                if (i % 8 == 0) {
                    // cout << "\n";
                    // Add the current set of 8 bits and then convert them to integers
                    base8.push_back(stoi(base8Tracking));
                    base8Tracking = "";
                }

                // cout << "New: " << base64;
            }
            
            for (int i = 0; i < base8.size(); i++) {

                cout << bitset<8>(base8[i]).to_ulong() << "\n";

            }
            

            return base64;
        };
};

int main() {
    Main main;

    string input;

    cout << "Input a string please: ";

    cin >> input;

    main.encode(input);

}