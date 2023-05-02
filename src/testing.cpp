#include <iostream>
#include <fstream>

using namespace std;

void writeFile(string fileName, string message){
   std::ofstream outfile(fileName); // open the output file
   if (!outfile) {
      std::cerr << "Error opening file." << std::endl;
      return;
   }
   outfile << message << std::endl; // write the line to the output file
   outfile.close(); // close the output file
}

string readFile(string fileName){
   std::ifstream infile("key/example.txt"); // open the input file
    if (!infile) {
        std::cerr << "Error opening file." << std::endl;
        return "-1";
    }
    string res = "";
    char c;
    while (infile.get(c)) { // read each character of the file
        res += c; // output the character to the console
    }
    infile.close(); // close the input file
    return res;
}



int main()
{
   string a;
   cin >> a;
   cout << a.length();
   return 0;
}