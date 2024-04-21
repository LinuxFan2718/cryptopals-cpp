#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
  string hexToBase64(string hexString) {
    const string base64lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string base64String = "";
    const int stride = 6;
    const int masks[4] = {0b111111000000000000000000, 0b111111000000000000, 0b111111000000, 0b111111};
    int shift;
    int octet_int;
    string octets;
    for (int i = 0; i < hexString.length()/6; i++) {
      octets = hexString.substr(i*stride, stride);
      octet_int = 0;
      for (char& c : octets) {
        int value;
        if (c >= '0' && c <= '9') {
          value = c - '0';
        } else if (c >= 'A' && c <= 'F') {
          value = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
          value = c - 'a' + 10;
        } else {
          string error = "Non-hex digit ";
          error.append(&c);
          std::cout << error << std::endl;
          throw(error);
        }
        octet_int <<= 4;
        octet_int += value;
        //std::cout << c << " " << value << std::endl;

      }
      shift = 18;
      for (const int mask : masks) {
        int sextet = octet_int & mask;
        sextet >>= shift;
        shift -= 6;
        std::cout << sextet << " ";
        char charToAdd = base64lookup[sextet];
        base64String += charToAdd;
      }
      std::cout << octets << " = " << octet_int << std::endl;
      // std::cout << "left= " << i*stride << " right= " << (i+1)*stride << std::endl;
      // std::cout << octets << std::endl;
      // std::cout << " length= " << octets.length() << std::endl;
    }
    
    return base64String;
  }
};

int main() {
  Solution solution;
  string hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  string base64String = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  string ans = solution.hexToBase64(hexString);
  std::cout << std::endl;
  string correct = "fail";
  if (ans == base64String) {
    correct = "pass";
  }
  std::cout << ans << std::endl;
  std::cout << base64String << " " << correct << std::endl;

  return 0;
}