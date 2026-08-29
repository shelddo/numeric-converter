#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string toDecimal(const string &num, int base, vector<char> &output);

string toBin(const string &num, int base, vector<char> &output);

string toHex(const string &num, int base, vector<char> &output);

string toAnyNumber(const string &num, int base, int outBase, vector<char> &output);

static bool checkBase(const string &num, int base);

int main() {
    string num;
    vector<char> result;
    int base;
    int baseOut;

    int option = 0;
    while (option != 2) {
        cout
                << "===================================" << endl
                << "====     Numeric converter     ====" << endl
                << "====      (Up to base 36)      ====" << endl
                << "===================================" << endl;

        cout << "Enter a number: " << endl;
        cin >> num;
        cout << "What is the base of this number? " << endl;
        cin >> base;

        bool numValid = checkBase(num, base);
        if (numValid == false) {
            cout << "This number is not in base " << base << ". Please try again." << endl;
            cout << endl;
            continue;
        }

        cout << "Convert to which base? (2-36): " << endl;
        cin >> baseOut;

        if (baseOut < 2 || baseOut > 36) {
            cout << "Invalid base. Please choose a base between 2 and 36." << endl;
            cout << endl;
            continue;
        }
        switch (baseOut) {
            case 2: {
                string msg = toBin(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for (const char i: result) {
                        cout << i;
                    }
                    cout << endl;
                } else if (msg == "BINARY") {
                    cout << "Can't convert binary to binary." << endl;
                }
                break;
            }

            case 10: {
                string msg = toDecimal(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for (const char i: result) {
                        cout << i;
                    }
                } else if (msg == "TOO BIG") {
                    cout << "Number is too big." << endl;
                }
                break;
            }

            case 16: {
                string msg = toHex(num, base, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for (const char i: result) {
                        cout << i;
                    }
                    cout << endl;
                } else if (msg == "HEXADECIMAL") {
                    cout << "Cant convert a hex number to another hex number." << endl;
                }
                break;
            }

            default: {
                string msg = toAnyNumber(num, base, baseOut, result);
                if (msg == "SUCCESS") {
                    cout << "Result: " << endl;
                    for (const char i: result) {
                        cout << i;
                    }
                    cout << endl;
                }
                break;
            }
        }

        cout << endl;
        cout << "Do you want to convert another number?" << endl;
        cout << "1 - Yes" << endl;
        cout << "2 - No" << endl;
        cin >> option;
    }

    cout << "Thanks for using our converter!" << endl;
}

bool checkBase(const string &num, const int base) {
    bool valid = true;
    for (const char c: num) {
        if (isdigit(c)) {
            if (const int numLetter = c - '0'; numLetter > base) {
                valid = false;
            }
        } else {
            if (const int numLetter = (c - 'A') + 10; numLetter > base) {
                valid = false;
            }
        }
    }
    return valid;
}

string toDecimal(const string &num, const int base, vector<char> &output) {
    long long decResult = 0;
    long long pow = 1;
    for (size_t i = num.length(); i-- > 0; ) {
        long long numb;
        if (isdigit(num[i])) {
            numb = num[i] - '0';
        } else {
            numb = (num[i] - 'A') + 10;
        }
        //cout << "numb: " << numb << " char: " << num[i];
        decResult += numb * pow;
        // cout << "num: " << numb << " pow: " << pow << " base: " << base << " value: " << numb * pow << endl;
        //cout << " pow: " << pow << " base: " << base << " value: " << numb * pow << endl;
        pow *= base;
        if (pow < 0) {
            return "TOO BIG";
        }
    }
    string outNumb = to_string(decResult);
    cout << "decNumb: " << outNumb << endl;
    for (char n: outNumb) {
        output.push_back(n);
    }
    return "SUCCESS";
}


/// \brief Converts a number from any base to binary.
/// \param num The number to be converted.
/// \param base The base which the number to be converted is.
/// \param output The output list where the final result will be inserted to.
/// \return A string message to identify if the process went well or something went wrong.
string toBin(const string &num, const int base, vector<char> &output) {
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
                output.insert(output.begin(), static_cast<char>('0' + leftover));
                //cout << leftover << endl;
            } while (numb > 0);
            return "SUCCESS";
            break;
        }

        default: {
            // TODO:
            // - DEAL WITH NUMBERS BIGGER THAN LONG LONG LIMITS
            vector<char> outputDec;
            toDecimal(num, base, outputDec);
            string decNumb(outputDec.begin(), outputDec.end());
            long long decResult = stoll(decNumb);
            //cout << "decResult: " << decResult << endl;
            do {
                leftover = decResult % 2;
                decResult /= 2;
                output.insert(output.begin(), static_cast<char>('0' + leftover));
                // cout << leftover << endl;
            } while (decResult > 0);
            return "SUCCESS";
            break;
        }
    }
}

string toHex(const string &num, const int base, vector<char> &output) {
    switch (base) {
        case 16: {
            return "HEXADECIMAL";
            break;
        }

        case 10: {
            long long leftover;
            long long decResult = stoll(num);
            do {
                leftover = decResult % 16;
                decResult /= 16;
                //cout << "number: " << leftover << endl;
                if (leftover >= 10) {
                    char chr = static_cast<char>(leftover + 55);
                    cout << "letra: " << chr << endl;
                    output.insert(output.begin(), chr);
                } else {
                    output.insert(output.begin(),  static_cast<char>(leftover + '0'));
                }
            } while (decResult > 0);
            return "SUCCESS";
        }

        default: {
            long long leftover;
            vector<char> outputDec;
            toDecimal(num, base, outputDec);
            const string decNumb(outputDec.begin(), outputDec.end());
            long long decResult = stoll(decNumb);
            do {
                leftover = decResult % 16;
                decResult /= 16;
                //cout << "number: " << leftover << endl;
                if (leftover >= 10) {
                    char chr = static_cast<char>(leftover + 55);
                    //cout << "letter: " << chr << endl;
                    output.insert(output.begin(), chr);
                } else {
                    output.insert(output.begin(),  static_cast<char>(leftover + '0'));
                }
            } while (decResult > 0);
            return "SUCCESS";
        }
    }
}

string toAnyNumber(const string &num, const int base, const int outBase, vector<char> &output) {
    long long leftover;
    vector<char> outputDec;
    toDecimal(num, base, outputDec);
    const string decNumb(outputDec.begin(), outputDec.end());
    long long decResult = stoll(decNumb);
    do {
        leftover = decResult % outBase;
        decResult /= outBase;
        //cout << "number: " << leftover << endl;
        if (leftover >= 10) {
            char chr = static_cast<char>(leftover + 55);
            //cout << "letter: " << chr << endl;
            output.insert(output.begin(), chr);
        } else {
            output.insert(output.begin(), static_cast<char>(leftover + '0'));
        }
    } while (decResult > 0);
    return "SUCCESS";
}
