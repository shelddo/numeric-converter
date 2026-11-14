#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string toDecimal(const string &num, int base, vector<char> &output);

string toBin(const string &num, int base, vector<char> &output);

string toHex(const string &num, int base, vector<char> &output);

string toAnyNumber(const string &num, int inBase, int outBase, vector<char> &output);

static bool checkBase(const string &num, int base);

//TODO
// handle unexpected digits (special characters)

int main() {
    vector<char> validChars = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
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

        for (char &c: num) {
            c = static_cast<char>(std::toupper(c));
        }

        bool special = false;
        for (const char c: num) {
            if (c < '0' || c > '9' && c < 'A' || c > 'Z') {
                cout << "Please do not enter special characters. Use only numbers and letters of the alphabet,"
                        << " since this converter does not support any bases beyond base 36. Try again.\n" << endl;
                special = true;
            }
        }
        if (special) {continue;}

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

        // check if the input number is already on the ouput desired base
        if (baseOut == base) {
            cout << "Can't convert a base " << base
                    << " number to the same base. Please inform another output base to convert." << endl;
            continue;
        }

        string msg = toAnyNumber(num, base, baseOut, result);
        if (msg == "SUCCESS") {
            cout << "Result: " << endl;
            for (const char i: result) {
                cout << i;
            }
            cout << endl;
        } else if (msg == "LARGE NUMBER") {
            cout << "This number is too large, not supported." << endl;
        }

        bool valid = false;
        do {
            cout << endl;
            cout << "Do you want to convert another number?" << endl;
            cout << "1 - Yes" << endl;
            cout << "2 - No" << endl;
            cin >> option;
            if (option != 1 && option != 2) {
                cout << "Invalid option. Please try again." << endl;
                continue;
            }
            valid = true;
        } while (valid == false);
        result.clear();
    }

    cout << "Thanks for using our converter!" << endl;
}

bool checkBase(const string &num, const int base) {
    bool valid = true;
    for (const char c: num) {
        if (isdigit(c)) {
            if (const int numLetter = c - '0'; numLetter >= base) {
                valid = false;
            }
        } else {
            if (const int numLetter = (c - 'A') + 10; numLetter >= base) {
                valid = false;
            }
        }
    }
    return valid;
}

/// \brief Converts a number from any base to decimal.
/// \param num The number to be converted.
/// \param base The source base of the number.
/// \param output Output vector that will be stored the converted digits.
/// \returns A message indicating whether the operation was succesful or an error occurred.
string toDecimal(const string &num, const int base, vector<char> &output) {
    long long decResult = 0;
    long long pow = 1;
    for (size_t i = num.length(); i-- > 0;) {
        long long numb;
        if (isdigit(num[i])) {
            numb = num[i] - '0';
        } else {
            numb = (num[i] - 'A') + 10;
        }
        const long long value = numb * pow;
        if (numb != 0) {
            if (pow > LLONG_MAX / numb || decResult > LLONG_MAX - value) {
                return "LARGE NUMBER";
            }
        }
        decResult += value;
        cout << "num: " << numb << " char: " << num[i] << " pow: " << pow << " base: " << base << " value: " << value <<
                endl;
        pow *= base;
    }
    string outNumb = to_string(decResult);
    cout << "decNumb: " << outNumb << "/" << LLONG_MAX << endl;
    for (char n: outNumb) {
        output.push_back(n);
    }
    return "SUCCESS";
}

/// \brief Converts a number from any base to another base.
/// \param num The number to be converted.
/// \param inBase The source base of the number.
/// \param outBase The target base.
/// \param output The vector where the result digits will be stored.
/// \return A message indicating whether the operation was successful or an error occurred.
string toAnyNumber(const string &num, const int inBase, const int outBase, vector<char> &output) {
    long long leftover;
    vector<char> outputDec;
    string decMsg = toDecimal(num, inBase, outputDec);
    if (decMsg == "LARGE NUMBER") {
        return "LARGE NUMBER";
    }
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
