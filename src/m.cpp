#include <iostream>

using namespace std;

// Define a function to calculate the greatest common divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Define a function to calculate the least common multiple
int lcm(int a, int b) {
    return (a*b)/gcd(a, b);
}

void option(){    
    int option;
    int num_bits;
    int p, q, d, n, e;
    string plaintext;
    string ciphertext;

while ( true ) {
    
        // Print the options for the user
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "Select an option:" << endl;
        cout << "\t1. Find the large prime number given the number of bits of the large prime to be found." << endl;
        cout << "\t2. Calculate the largest divisor when given two large integers." << endl;
        cout << "\t3. Calculate the decryption key d given the encryption key e and two large primes." << endl;
        cout << "\t4. Generate random key set when given 2 large prime numbers." << endl;
        cout << "\t5. Encryption given the message and encryption key e and n." << endl;
        cout << "\t6. Decrypt when given encrypted message and decryption key d and n." << endl;
        cout << "\t0. Exit" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    
    // Get the user's choice
    
    cin >> option;

    cout << "\nYour choice is: " << option << endl;
    cout << "===================================================================================" << endl;

    // Get the user's numbers
    switch (option) {
        case 0:
            cout << "Exited!";
            exit(0);
            break;

        case 1:
            cout << "Enter the number of bits of the large prime to be found: ";
            cin >> num_bits;
            //function
            cout << "The large prime number is: " << num_bits << endl;
            cout << "===================================================================================" << endl;
            break;

        case 2:
            cout << "Enter the two large integers: \n";
            cout << "\tNumber 1:";
            cin >> p;
            cout << "\tNumber 2:";
            cin >> q;
            //function
            cout << "The largest divisor is: " << "result function" << endl;
            cout << "===================================================================================" << endl;
            break;
        
        case 3:
            cout << "Enter the encryption key e: ";
            cin >> e;
            cout << "Enter the first large prime p: ";
            cin >> p;
            cout << "Enter the second large prime q: ";
            cin >> q;
            //function
            cout << "The decryption key d is: " << "//result function" << endl;
            cout << "===================================================================================" << endl;
            break;

        case 4:
            cout << "Enter the first large prime p: ";
            cin >> p;
            cout << "Enter the second large prime q: ";
            cin >> q;
            //random key function (tinh d), n
            cout << "The encryption key e is: " << e << endl;
            cout << "The decryption key d is: " << "d" << endl;
            cout << "The modulus n is: " << "n" << endl;
            cout << "===================================================================================" << endl;
            break;

        // case 5:
        //     cout << "Enter the message to be encrypted: ";
        //     cin >> message;
        //     cout << "Enter the encryption key e: ";
        //     cin >> e;
        //     cout << "Enter the modulus n: ";
        //     cin >> n;
        //     encrypted_message = 0; //encrypt_message(message, e, n)
        //     cout << "The encrypted message is: " << encrypted_message << endl;
            cout << "===================================================================================" << endl;
        //     break;
        
        // case 6:
        //     cout << "Enter the encrypted message: ";
        //     cin >> encrypted_message;
        //     cout << "Enter the decryption key d: ";
        //     cin >> d;
        //     cout << "Enter the modulus n: ";
        //     cin >> n;
        //     decrypted_message = 0; //call function decrypt_message(encrypted_message, d, n)
        //     cout << "The decrypted message is: " << decrypted_message << endl;
        cout << "===================================================================================" << endl;
        //     break;

        default:
            cout << "Invalid option. Please select a valid option." << endl;
            break;
    }
}
}

int main() {
    option();
    return 0;
}
