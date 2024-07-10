#include <iostream>
#include <map>

class Base64Maps {
    public:
        std::map<char, int> base64CharMap;
        std::map<ulong, char> base64CharMapRev;
        
        Base64Maps() {
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
        };
};

Base64Maps base64Maps;