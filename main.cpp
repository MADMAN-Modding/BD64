#include <iostream>
#include <map>
#include <bitset>

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
            for (const auto& pair : base64CharMap) {
                std::cout << pair.first << " : " << pair.second << std::endl;
            }
        }
};

int main() {
    Main main;
}