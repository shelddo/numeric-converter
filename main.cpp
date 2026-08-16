#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

long long toDecimal(string num, int base);

string toBin(string decNum, int base, vector<char>& output);

int main() {
    string num;
    vector<char> result;
    int base;
    int baseOut;
    cout << "Enter a number: " << endl;
    cin >> num;
    cout << "What is the base of this number? " << endl;
    cin >> base;
    cout << "Convert to which base? (2-36): " << endl;
    cin >> baseOut;

    switch (baseOut) {
        case 2: {
            string msg = toBin(num, base, result);
            if (msg == "SUCCESS") {
                cout << "Result: " << endl;
                for (int i = 0; i < result.size(); ++i) {
                    cout << result[i];
                }
                cout << endl;
            } else if (msg == "BINARY"){
                cout << "Can't convert binary to binary." << endl;
            }
            break;
        }

        default: {
            cout << "Base not supported yet." << endl;
            break;
        }
    }

    // result = toBin(num, base);
    // cout << "Result:" << endl;
    // for (const int num1: result) {
    //     cout << num1;
    // }
}

long long toDecimal(string num, int base) {
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
    }
    return decResult;
}

string toBin(string num, int base, vector<char>& output) {
    int leftover;
    switch (base) {
        case 2: {
            return "BINARY";
            break;
        }

        case 10: {
            long long numb = stoi(num);
            do {
                leftover = numb % 2;
                numb /= 2;
                output.insert(output.begin(), leftover);
            } while (numb > 0);
            return "SUCCESS";
            break;
        }

        default: {
            long long decResult;
            decResult = 0;
            decResult = toDecimal(num, base);
            cout << "decResult: " << decResult << endl;
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