#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

long long toDecimal(string num, int base);

vector<int> toBin(string decNum, int base);

int main() {
    string num;
    int base;
    cout << "Enter a number: " << endl;
    cin >> num;
    cout << "What is the base of this number? " << endl;
    cin >> base;
    vector<int> vec;
    vec = toBin(num, base);
    cout << "Result:" << endl;
    for (const int num1: vec) {
        cout << num1;
    }
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

vector<int> toBin(string num, int base) {
    int leftover;
    vector<int> result;
    switch (base) {
        case 2: {
            result.push_back(0);
            return result;
            break;
        }

        case 10: {
            int numb = stoi(num);
            do {
                leftover = numb % 2;
                numb /= 2;
                result.insert(result.begin(), leftover);
            } while (numb > 0);
            return result;
            break;
        }

        default: {
            long long decResult;
            decResult = 0;
            decResult = toDecimal(num, base);
            do {
                leftover = decResult % 2;
                decResult /= 2;
                result.insert(result.begin(), leftover);
            } while (decResult > 0);
            return result;
            break;
        }
    }
}