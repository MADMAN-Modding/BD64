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
        }

        string encode(string input) {
            string base64;
            vector <string> base6;

            // Keeps track of the currently watched 8 bits
            string base6Tracking;

            for (int i = 0; i < input.length(); i++)
            {
                base64 += bitset<8>(int(input[i])).to_string();
            }



            for (int i = 0; i < base64.length(); i++) {
                base6Tracking += base64[i];

                if ((i+1) % 6 == 0 || base64.length() - 1 == i) {

                    // Add the current set of 8 bits and then convert them to integers
                    base6.push_back(base6Tracking);

                    base6Tracking = "";
                }
            }

            // Adds zeros to the end until it is 6 characters long
            while(base6[base6.size()-1].length() != 6) {
                base6[base6.size()-1] += "0";
            }
            
            string final;
            
            for (int i = 0; i < base6.size(); i++) {

                bitset bits = bitset<6>(base6[i]);

                final += base64CharMapRev[(int) bits.to_ulong()];
                
            }
            
            return final;
        };

        string decode(string input) {
            string base64;
            vector <string> base8;

            // Keeps track of the currently watched 8 bits
            string base8Tracking;


            for (int i = 0; i < input.length(); i++) {
                base64 += bitset<6>(base64CharMap[input[i]]).to_string();
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

int main() {
    Main main;

    int input;

    main.clearScreen();

    cout << "----------------------------------------------\n";

    cout << "Please choose one of the following options:\n[1] String Encoding\n[2] String Decoding\n";

    cin >> input;

    main.clearScreen();

    string text;


    switch (input)
    {
    case 1:
        cout << "Input a string to encode please: ";

        cin >> text;

        cout << main.encode(text);
        break;
    case 2:
        cout << "Input a string to decode please: ";

        cin >> text;    

        cout << main.decode(text);
        break;
    default:
        cout << "That's not an option!";
        break;
    };


}