# RSA

Cryptography and Network Security - 222

- Authors:
  - Ung Van Hung - 2013401
  - Nguyen Phuc Dang - 2012968
  - Le Trung Duc - 2012995
 

HCMUT - Ho Chi Minh University of Technology.


## Abstract:

In this assignment, we will implement a simple RSA encryption/decryption by C++.

## Getting Started

In "NTL Testing" commit, I had pushed a testing NTL library program by C++.

- First, we need to install NTL. Docs: https://libntl.org/doc/tour-win.html
- After setting up the env then compile the main.cpp file:
  ![Testing program](/img/testing.png "testing in terminal")

## Compile these files
- Old version: 
  Compile file in __src/__ and export binary file to __debug/__
  ```bash
  g++ -g -O2 -std=c++11 -pthread -march=native src/main.cpp -o debug/main -lntl -lgmp -lm
  ```
- New version: 
  - ```make main```: to compile and run main.cpp and its executed file.
  - ```make test```: to compile and run testing.cpp and its executed file.
  - ```make clean```: to remove all executed files in debug folder.


## Update 

### Update 1:
* Adding NTL library and Miller-Rabin algorithm.

### Update 2:
* Adding "Euclide", "Extended Euclide" and "Square and Multiply" Algorithms.

### Update 3:
* Adding "Stein's GCD" - or Binary GCD" algorithm.

### Update 4:
* Adding "Prime number Generaters":
  1) Generate prime number with given Size.
  2) Generate prime number with a Key Size and another prime number .
  ![Testing program](/img/test2.png "2 primes p and q")

### Update 5:
* Capture all to 1 class "RSA"
![Testing program](/img/update5.png "Using RSA class")

### Update 6:
* Encrypt and Decrypt message
![Testing program](/img/update6.png "Encryption and Decryption")

### Update 7:
* Add makefile