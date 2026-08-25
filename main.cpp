#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string toDecimal(string num, int base, vector<char>& output);

string toBin(string decNum, int base, vector<char>& output);

string toHex(string num, int base, vector<char>& output);

string toAnyNumber(string num, int base, vector<char>& output);

bool checkBase(string num, int base);
//TODO:
// to hex converter and to any base
// handle too big numbers
// handle out of base numbers

int main() {
    string num;
    vector<char> result;
    int base;
    int baseOut;
    cout << "Enter a number: " << endl;
    cin >> num;
    cout << "What is the base of this number? " << endl;
    cin >> base;
    
    bool numValid = checkBase(num, base);
    if(numValid == false) {
        cout << "This number does not belong to the " << base << " base. Please try again." << endl;
        return 0;
    } 

    cout << "Convert to which base? (2-36): " << endl;
    cin >> baseOut;

    if (baseOut < 2 || baseOut > 36) {
        cout << "Choose a number between 2 and 36. This base is not supported or do not exist." << endl;
    }
    else {
        switch (baseOut) {
            case 2: {
                string msg = toBin(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for (int i = 0; i < result.size(); ++i) {
                        cout << result[i] + '0' - 48;
                    }
                    cout << endl;
                } else if (msg == "BINARY"){
                    cout << "Can't convert binary to binary." << endl;
                }
                break;
            }

            case 10: {
                string msg = toDecimal(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for (int i = 0; i < result.size(); i++) {
                        cout << result[i];
                    }
                }
                else if (msg == "TOO BIG") {
                    cout << "Number is too big." << endl;
                }
                break;
            }

            case 16: {
                string msg = toHex(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for(int i = 0; i < result.size(); i++) {
                        cout << result[i];
                    }
                    cout << endl;
                }
                else if (msg == "HEXADECIMAL") {
                    cout << "Cant convert a hex number to another hex number." << endl;                
                }
                break;
            }

            default: {
                string msg = toAnyNumber(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for(int i = 0; i < result.size(); i++) {
                        cout << result[i];
                    }
                    cout << endl;
                }
                break;
            }
        }
    }
}

bool checkBase(string num, int base){
    bool valid = true;
    for(char c : num) {
        if(isdigit(c)){
            int numLetter = c - '0';
            if (numLetter > base) {
                valid = false;
            }
        }
        else {
            int numLetter = (c - 'A') + 10;
            if(numLetter > base) {
                valid = false;
            }
        }
    }
    return valid;
}

string toDecimal(string num, int base, vector<char>& output) {
    long long decResult = 0;
    long long pow = 1;
    for (int i = num.length() - 1; i >= 0; i--) {
        long long numb;
        if (isdigit(num[i])) {
            numb = num[i] - '0';
        } else {
            numb = (num[i] - 'A') + 10;
        }
        cout << "numb: " << numb << " char: " << num[i];
        decResult += numb * pow;
        // cout << "num: " << numb << " pow: " << pow << " base: " << base << " value: " << numb * pow << endl;
        cout << " pow: " << pow << " base: " << base << " value: " << numb * pow << endl;
        pow *= base;
        if (pow >= 9223372036854775807LL || pow <= -9223372036854775808LL) {
            return "TOO BIG";
        }
    }
    string outNumb = to_string(decResult);
    for (char n : outNumb) {
        output.push_back(n);
    }
    return "SUCCESS";
}

string toBin(string num, int base, vector<char>& output) {
    long long leftover;
    switch (base) {
        case 2: {
            return "BINARY";
            break;
        }

        case 10: {
            //cout << num << endl;
            long long numb = stoll(num);
            //cout << numb << endl;
            do {
                leftover = numb % 2;
                numb /= 2;
                output.insert(output.begin(), leftover);
                //cout << leftover << endl;
            } while (numb > 0);
            return "SUCCESS";
            break;
        }

        default: {
            long long decResult;
            vector<char> outputDec;
            toDecimal(num, base, outputDec);
            string decNumb(outputDec.begin(), outputDec.end());
            decResult = stoll(decNumb);
            //cout << "decResult: " << decResult << endl;
            do {
                leftover = decResult % 2;
                decResult /= 2;
                output.insert(output.begin(), leftover + '0');
                // cout << leftover << endl;
            } while (decResult > 0);
            return "SUCCESS";
            break;
        }
    }
}

string toHex(string num, int base, vector<char>& output) {    
    switch(base) {
        case 16: {
            return "HEXADECIMAL";
            break;
        }

        case 10: {
            long long decResult;
            int leftover;
            decResult = stoll(num);
            do {
                leftover = decResult % 16;
                decResult /= 16;
                //cout << "number: " << leftover << endl;
                if (leftover >= 10) {
                    char chr = (leftover + 55);
                    cout << "letra: " << chr << endl;
                    output.insert(output.begin(), chr);
                }
                else {
                    output.insert(output.begin(), leftover + '0');
                }
            } while(decResult > 0);
            return "SUCCESS";
        }

        default: {
            long long decResult;
            int leftover;
            vector<char> outputDec;
            toDecimal(num, base, outputDec);
            string decNumb(outputDec.begin(), outputDec.end());
            decResult = stoll(decNumb);            
            do {
                leftover = decResult % 16;
                decResult /= 16;
                //cout << "number: " << leftover << endl;
                if (leftover >= 10) {
                    char chr = (leftover + 55);
                    //cout << "letter: " << chr << endl;
                    output.insert(output.begin(), chr);
                }
                else {
                    output.insert(output.begin(), leftover + '0');
                }
            } while(decResult > 0);
            return "SUCCESS";
        }
    }
}

string toAnyNumber(string num, int base, vector<char>& output) {
    switch(base) {
        case 10: {
            long long decResult;
            int leftover;
            decResult = stoll(num);
            do {
                leftover = decResult % base;
                decResult /= base;
                if (leftover >= 10) {
                    char chr = (leftover + 55);
                    //cout << "letter: " << chr << endl;
                    output.insert(output.begin(), chr);
                }
                else {
                    output.insert(output.begin(), leftover + '0');
                }
            } while(decResult > 0);
            return "SUCCESS";
        }

        default: {
            long long decResult;
            int leftover;
            vector<char> outputDec;
            toDecimal(num, base, outputDec);
            string decNumb(outputDec.begin(), outputDec.end());
            decResult = stoll(decNumb);            
            do {
                leftover = decResult % base;
                decResult /= base;
                //cout << "number: " << leftover << endl;
                if (leftover >= 10) {
                    char chr = (leftover + 55);
                    //cout << "letter: " << chr << endl;
                    output.insert(output.begin(), chr);
                }
                else {
                    output.insert(output.begin(), leftover + '0');
                }
            } while(decResult > 0);
            return "SUCCESS";
        }        
    }
}