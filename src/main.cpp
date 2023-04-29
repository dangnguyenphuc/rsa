#include "../headers/main.h"

using namespace std;
using namespace NTL;

#define ITERATION_NUM 10
typedef long long ll;

string byte_list[256] = {
"00","01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f", 
"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f", 
"20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f", 
"30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f", 
"40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f", 
"50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f", 
"60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f", 
"70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f", 
"80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f", 
"90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f", 
"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af", 
"b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf", 
"c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf", 
"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df", 
"e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef", 
"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
};

// ===============================================================================================
// AKS ===========================================================================================
vector<ll> coeffs(ll n) {
    vector<ll> c((n + 1), ll(1));
    for (ll i(1); i <= n; i++) {
        c[i] = c[i - 1] * (n - i + 1) / i;
    }
    return c;
}

bool AKS_primality_test(ll n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2 || n == 3 || n == 5) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {
        return false;
    }
    ll r(2);
    while (r <= n) {
        if (n % r == 0) {
            break;
        }
        r = r + 1;
    }
    if (r == n) {
        return true;
    }
    for (ll a(2); a <= min(r - 1, ll( sqrt(n) * log2(n) ) ); a++) {
        vector<ll> c = coeffs(n);
        c[0] = c[0] - 1;
        c[a] = c[a] - 1;
        for (ll i(1); i < n; i++) {
            for (ll j(n); j >= i; j--) {
                c[j] =  c[j] - c[j - i];
            }
        }
        if (c[n] % n != 0) {
            return false;
        }
    }
    return true;
}
// AKS ===========================================================================================
// ===============================================================================================


// ===============================================================================================
// File ==========================================================================================
void writeFile(string fileName, string message){
    std::ofstream outfile(fileName); // open the output file
    if (!outfile) {
        std::cerr << "\nError opening file." << std::endl;
        return;
    }
    outfile << message; // write the line to the output file
    outfile.close(); // close the output file
    }

string readFile(string fileName){
    std::ifstream infile(fileName); // open the input file
    if (!infile) {
        std::cerr << "\nError opening file." << std::endl;
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
// File ==========================================================================================
// ===============================================================================================


class RSA{
    long key_Bits;
    ZZ n;
    ZZ p;
    ZZ q;
    ZZ e;
    ZZ d;

    string message_String;
    ZZ cipher;
    ZZ message_ZZ;
    
public:
    // constructor
    RSA(){

    }
    RSA(ZZ p, ZZ q){
        this->p = p;
        this->q = q;
        this->n = p*q;
    }

    RSA(long key_Bits){
        this->key_Bits = key_Bits;
    }

    // destructor
    ~RSA(){

    }

    // setters
    void message_StringSetter(string message_String){
        this->message_String = message_String;
    }
    void pSetter(ZZ p){
        this->p = p;
    }
    void qSetter(ZZ q){
        this->q = q;
    }
    void nSetter(ZZ n){
        this->n = n;
    }
    void key_BitsSetter(long key_Bits){
        this->key_Bits = key_Bits;
    }
    void eSetter(ZZ e){
        this->e = e;
    }
    void dSetter(ZZ d){
        this->d = d;
    }


    // getters
    ZZ pGetter(){
        return this->p;
    }
    ZZ qGetter(){
        return this->q;
    }
    ZZ nGetter(){
        return this->n;
    }
    ZZ eGetter(){
        return this->e;
    }
    ZZ dGetter(){
        return this->d;
    }
    string messageGetter(){
        return this->message_String;
    }
    ZZ cipherGetter(){
        return this->cipher;
    }


    // trailing zeros:
    long trailing_zeroes(ZZ number) {
        long bits = 0;

        if (number!=0) {
            /* mask the 16 low order bits, add 16 and shift them out if they are all 0 */
            while ((number & 0x0000FFFF)==0) { bits += 16; number >>= 16;}
            /* mask the 8 low order bits, add 8 and shift them out if they are all 0 */
            while ((number & 0x000000FF)==0) { bits +=  8; number >>=  8; }
            /* mask the 4 low order bits, add 4 and shift them out if they are all 0 */
            while ((number & 0x0000000F)==0) { bits +=  4; number >>=  4; }
            /* mask the 2 low order bits, add 2 and shift them out if they are all 0 */
            while ((number & 0x00000003)==0) { bits +=  2; number >>=  2; }
            /* mask the low order bit and add 1 if it is 0 */
            if((number & 0x00000001)==0){ bits += 1; }
        }
        return bits;
    }

    // Stein"s GCD binary GCD
    ZZ S_gcd(ZZ number1, ZZ number2){
        if( number1 == 0 ) return number2;
        if (number2 == 0 ) return number1;


        long trail1;
        long trail2;
        long min_trail;

        trail1 = trailing_zeroes(number1);  number1 = number1>>trail1;                       
        trail2 = trailing_zeroes(number2);  number2 = number2>>trail2;
        min_trail = (trail1 > trail2)? trail2 : trail1;

        while (1)
        {
            assert(number1%2==1 && "Number1 is still even.");
            assert(number2%2==1 && "Number2 is still even.");

            if(number1 > number2){
                ZZ _swap;
                _swap = number1;
                number1 = number2;
                number2 = _swap;
            }

            number2 = number2 - number1;

            if( number2 == 0 )
            {
                return number1 << min_trail;
            }

            number2 = number2 >> trailing_zeroes(number2);
        }

    }

    // Euclide
    ZZ E_gcd(ZZ number1, ZZ number2){
        if (number1 == 0) return number2;
        return E_gcd(number2%number1 , number1);
    }

    // Extended Euclide to find invert number
    bool extendedEuclid(const ZZ& number1, const ZZ& number2, ZZ& t){
    /*
    Bézout"s identity asserts that "number1" and "number2" are coprime if and only if there exist integers s and t such that
        number2*s + number1*t = 1
        Reducing this identity modulo number2 give:
        number1*t = 1 mod number2     
        ===============> Phù hợp để tìm số nghịch đảo do Định nghĩa số nghịch đảo của w là w^(-1) với w^(-1) * w = 1
    */
        t = 0;
        ZZ newt(1);
        ZZ r;
        ZZ newr;
        ZZ quotient;

        r = number2;
        newr = number1;

        ZZ temp1, temp2;

        while (newr != 0)
        {
            quotient = r / newr;
            
            temp1 = t;
            t = newt;
            newt = temp1 - quotient*newt;

            temp2 = r;
            r = newr;
            newr = temp2 - quotient*newr;

        }

        if (r > 1) return 0;
        if (t < 0) t = t + number2;
        return 1;
    }

    long GetBits(ZZ number){
        return (long)NumBits(number);
    }

    ZZ modMul(const ZZ& number1, const ZZ& number2, const ZZ& mod){
        return (number1*number2) % mod;
    }

    ZZ modPow(ZZ number, ZZ power, ZZ mod){
        assert(power>= ZZ(0) && "Invalid power!");
        if(mod > 0){
            ZZ result(1);
            while ( power > ZZ(0) ){
                if( (power & 1) == 1){
                    result = modMul(result,number,mod);
                }
                number = modMul(number, number, mod);
                power = power >> 1;
            }
            return result;
        }else{
            ZZ result(1);
            while ( power > long(0) ){
                if( (power & 1) == 1){
                    result = result*number;
                }
                number = number*number;
                power = power >> 1;
            }
            return result;
        }
        
    }

    // Miller-Rabin primality test -> just determine probable prime number
    bool MillerTest(const ZZ& number, const ZZ& d, long r,const ZZ& ran){

        if (ran == 0) return 0;

        // loop variable
        long i = 0;
        ZZ x;
        ZZ y;

        // Compute: x = pow(ran, d) % number
        x = modPow(ran, d, number);

        if ( x == 1 ) return false;

        // Below loop mainly runs "r-1" times.
        do{
            y = x;
            x = (y*y) % number;
            i += 1;
        } while( i<r && x != 1 );

        return (x != 1) || (y != number-1);

    }


    // main Miller-Rabin test
    bool isPrime(const ZZ& number, long accurancy){
        if (number <= 1) return false;

        PrimeSeq seq;
        long check_num = seq.next();

        do{
            if(number % check_num == 0) return number == check_num;
            check_num = seq.next();
        }while( check_num && check_num < 2000);
        
        // if pass then Miller-Rabin check:
        ZZ d;
        long r;

        // number-1 = d* 2^r

        d = (number)/2;
        r = 1;

        while ( d % 2 == 0)
        {
            r += 1;
            d /= 2;    
        }

        // then we had d and r
        ZZ ran; // random number from 0 to number-1
        for(int i = 0; i < accurancy; i+=1){
            ran = RandomBnd(number);

            if( MillerTest(number, d, r, ran) ) return false;
        }

        return true;

    }

    ZZ generate_prime(long n_bits){
        ZZ res;
        bool found = false;
        while (!found)
        {
            res = RandomBits_ZZ(n_bits);
            if (res % 2 == 0) res++;
            found = isPrime(res, ITERATION_NUM);
        }
        
        return res;
    }

    ZZ generate_prime_with_bound(long n_bits){
        ZZ res;
        bool found = false;
        ZZ r;
        while (!found)
        {
            r = RandomBnd(5);
            res = RandomBits_ZZ(n_bits-NTL::conv<long>(r));
            if (res % 2 == 0) res++;
            found = isPrime(res, ITERATION_NUM);
        }
        
        return res;
    }

    ZZ generate_random_prime(ZZ lo, ZZ hi){
        ZZ res;
        bool found = false;
        while (!found)
        {
            res = lo + RandomBnd(hi - lo);
            if (res % 2 == 0) res++;
            found = isPrime(res, ITERATION_NUM);
        }
        
        return res;
    }

    ZZ generate_prime_with_gap(ZZ& p, long key_Bits){
        ZZ res;
        bool found = false;
        // ZZ _upper_bound(modPow(ZZ(2),ZZ(key_Bits/2)+ZZ(10),ZZ(0)));
        ZZ _lower_bound(modPow(ZZ(2),ZZ(key_Bits/2)-ZZ(5),ZZ(0)));
        // ZZ _middle_bound(modPow(ZZ(2),ZZ(key_Bits/2),ZZ(0)) - ZZ(1));

        long p_bits = NumBits(p);
        long q_bits = key_Bits - NumBits(p);

        bool compare = (p_bits > q_bits);       // true: p > q, false: p < q

        while (!found)
        {
            res = RandomBits_ZZ(q_bits);

            if (res % 2 == 0) res++;

            if(compare){
                if(p-res < _lower_bound) continue;
            }else{
                if(res-p < _lower_bound) continue;
            }

            
            found = isPrime(res, ITERATION_NUM); // && ( (NumBits(p) + NumBits(res) - 2) == key_Bits );
        }
        
        return res;
    }
    void p_and_q_Generate(){
        this->p = generate_prime_with_bound(this->key_Bits/2);
        this->q = generate_prime_with_gap( this->p, this->key_Bits);
    }

    void e_Generate(){
        assert(this->p != NULL && "Invalid p!");
        assert(this->q != NULL && "Invalid q!");
        ZZ phi;
        phi = (this->p - 1) * (this->q - 1);
        this->e = generate_prime(GetBits(phi)/2);
    }

    void e_Generate_with_Size(long _size){
        this->e = generate_prime(_size);
    }

    void e_random_Generate(ZZ lo, ZZ hi){
        this->e = generate_random_prime(lo, hi);
    }

    void d_Generate(){
        assert(this->p != NULL && "Invalid p!");
        assert(this->q != NULL && "Invalid q!");
        assert(this->e != NULL && "Invalid e!");
        ZZ phi;
        phi = (this->p - 1) * (this->q - 1);

        bool found = false;
        while (!found)
        {
            found = extendedEuclid(this->e, phi, this->d);
            if(!found){
                cout << "\ne doen not have an inverted number. Regenerate e ...";
                e_random_Generate(ZZ(3), phi);
            }
        }
    }
    // ===============================================================================================
    // string ========================================================================================
    int hex_2_int(char hex){
        switch (int(hex))
        {
        case 48:    // 0
            return 0;
            /* code */
            break;
        case 49:    // 1
            return 1;
            /* code */
            break;
        case 50:    // 2
            return 2;
            /* code */
            break;
        case 51:    // 3
            return 3;
            /* code */
            break;
        case 52:    // 4
            return 4;
            /* code */
            break;
        case 53:    // 5
            return 5;
            /* code */
            break;
        case 54:    // 6
            return 6;
            /* code */
            break;
        case 55:    // 7
            return 7;
            /* code */
            break;
        case 56:    // 8
            return 8;
            /* code */
            break;
        case 57:    // 9
            return 9;
            /* code */
            break;
        case 97:    // a
            return 10;
            break;
        case 98:    // b
            return 11;
            break;
        case 99:    // c
            return 12;
            break;
        case 100:    // d
            return 13;
            break;
        case 101:    // e
            return 14;
            break;
        default:    // f
            return 15;
            break;
        }
    }
    string String_2_Hex(string message){
        string encrypt = "";
        for(int i=0 ; i < message.length(); i++){
            encrypt += byte_list[(int)message[i]];
        }
        return encrypt;
    }

    string Hex_to_String(string message){
        string decrypt = "";
        int character;
        string two;
        for(int i=0 ; i < message.length(); i+=2){
            two = message.substr(i,2);
            character = stoi(two, 0, 16);
            decrypt += char(character);

        }
        return decrypt;
    }

    ZZ hex_2_ZZ(string message){
        ZZ res(0);
        int len = message.length();
        for (int i = message.length()-1; i >= 0; i-=1)
        {
            res += ZZ(hex_2_int(message[i]))*modPow(ZZ(16),ZZ(len-1-i),ZZ(0));
        }
        
        return res;
    }

    string ZZ_2_hex(ZZ message){
        long size = NTL::NumBytes(message); // get the number of bytes needed to represent the integer
        unsigned char* buffer = new unsigned char[size]; // allocate a buffer to hold the bytes
        NTL::BytesFromZZ(buffer, message, size); // convert the integer to bytes
        std::stringstream ss;
        ss << std::hex << std::setfill('0'); // set the output stream to output in hexadecimal format
        for (int i = size - 1; i >= 0; i--) {
        ss << std::setw(2) << static_cast<unsigned int>(buffer[i]); // output each byte as a two-digit hexadecimal number
        }
        std::string hex = ss.str(); // convert the output stream to a string
        delete[] buffer; // deallocate the buffer
        return hex;
    }

    string ZZ_to_String(ZZ message){
        return Hex_to_String(ZZ_2_hex(message));
    }

    ZZ String_to_ZZ(string message){
        return ZZ(hex_2_ZZ(String_2_Hex(message)));
    }
    // string ========================================================================================
    // ===============================================================================================

    void encryption(){
        ZZ message = String_to_ZZ(this->message_String);

        ZZ n( (this->p)*(this->q) );
        this->cipher = (modPow(message, this->e,n));
        
        string c = ZZ_to_String(this->cipher);

        // writeFile(cipherFile, c);
        cout << "\n\nMessage Encryption: " << c;
    }

    // void encryption(string fileName = "message/MyMessage.txt", string cipherFile = "cipher/encrypt.txt"){
    //     string mess = readFile(fileName);
    //     ZZ message = String_to_ZZ(mess);

    //     ZZ n( (this->p)*(this->q) );
    //     ZZ ci(modPow(message, this->e,n));
        
    //     string c = ZZ_to_String(ci);
    //     writeFile(cipherFile, c);
    //     cout << "\n\nMessage Encryption: " << c;
    // }

    void decryption(){
        ZZ n( (this->p)*(this->q) );
        ZZ message(modPow(this->cipher, this->d,n));

        string m = ZZ_to_String(message);
        // writeFile(decryptFile, m);
        cout << "\n\nMessage Decryption: " << m;
    }

    // void decryption(string cipherFile = "cipher/encrypt.txt", string decryptFile = "cipher/decrypt.txt"){
    //     string c = readFile(cipherFile);
    //     ZZ cipher = String_to_ZZ(c);

    //     ZZ n( (this->p)*(this->q) );
    //     ZZ message(modPow(cipher, this->d,n));

    //     string m = ZZ_to_String(message);
    //     writeFile(decryptFile, m);
    //     cout << "\n\nMessage Decryption: " << m;
    // }
};

int main()
{
    SetNumThreads(4); // Number of threads to use for parallelization
    RSA a;

    a.key_BitsSetter(1024);
    a.p_and_q_Generate();
    cout << "p: " << a.pGetter() << endl << "p Size: " << a.GetBits(a.pGetter());
    cout << "\nq: " << a.qGetter() << endl << "q Size: " << a.GetBits(a.qGetter());

    a.e_Generate();
    cout << "\ne: " << a.eGetter() << endl << "e Size: " << a.GetBits(a.eGetter());
    a.d_Generate();
    cout << "\nd: "<< a.dGetter() << endl << "d Size: " << a.GetBits(a.dGetter());
    a.message_StringSetter(readFile("message/MyMessage.txt"));

    a.encryption();
    a.decryption();

    return 0;
}