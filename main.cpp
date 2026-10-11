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
    string num;
    vector<char> result;
    int base;
    int baseOut;

    int option = 0;
    while (option != 2) {
        cout
                << "===================================" << endl
                << "====    Conversor de bases     ====" << endl
                << "====      (Ate a base 36)      ====" << endl
                << "===================================" << endl;

        cout << "Digite um numero: " << endl;
        cin >> num;
        cout << "Digite a base de origem: " << endl;
        cin >> base;

        for (char &c: num) {
            c = static_cast<char>(std::toupper(c));
        }

        bool numValid = checkBase(num, base);
        if (numValid == false) {
            cout << "Esse numero nao pertence a base " << base << ". Tente novamente." << endl;
            cout << endl;
            continue;
        }

        cout << "Digite a base de destino (2-36): " << endl;
        cin >> baseOut;

        // checa se a base de destino está entre 2 e 36 para evitar cálculos incorretos.
        // da base 37 em diante, os caracteres de são diferentes, o que exige um cálculo mais complexo.
        if (baseOut < 2 || baseOut > 36) {
            cout << "Base invalida. Digite um numero entre 2 e 36." << endl;
            cout << endl;
            continue;
        }

        // checa se o número de origem é da mesma base de destino
        if (baseOut == base) {
            cout << "Não é possível converter um numero de base " << base
            << " para a mesma base. Digite outra base a de destino." << endl;
            continue;
        }

        // porção do código que realiza a conversão
        string msg = toAnyNumber(num, base, baseOut, result);
        if (msg == "SUCCESS") {
            cout << "Resultado: " << endl;
            for (const char i: result) {
                cout << i;
            }
            cout << endl;
        } else if (msg == "LARGE NUMBER") {
            cout << "Esse numero e muito grande e nao e suportado. Tente novamente." << endl;
        }

        bool valid = false;
        do {
            cout << endl;
            cout << "Voce quer converter outro numero?" << endl;
            cout << "1 - Sim" << endl;
            cout << "2 - Nao" << endl;
            cin >> option;
            if (option != 1 && option != 2) {
                cout << "Opcao invalida, tente novamente." << endl;
                continue;
            }
            valid = true;
        } while (valid == false);
        result.clear();
    }

    cout << "Obrigado por utilizar nosso conversor!" << endl;
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

/// \brief Realiza a conversão de um número de qualquer base para decimal.
/// \param num O número a ser convertido.
/// \param base A base de origem.
/// \param output Vetor em que será armazenado o resultado da conversão
/// \returns Uma mensagem informando se a operação foi um sucesso ou ocorreu algum erro.
string toDecimal(const string &num, const int base, vector<char> &output) {
    long long decResult = 0;
    long long pow = 1;

    // loopa entre os dígitos do número de origem, começando do final
    for (size_t i = num.length(); i-- > 0; ) {
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
        //cout << "num: " << numb << " char: " << num[i] << " pow: " << pow << " base: " << base << " value: " << value << endl;
        pow *= base;
    }
    string outNumb = to_string(decResult);

    //cout << "decNumb: " << outNumb << "/" << LLONG_MAX << endl; // debug para aferição da

    for (char n: outNumb) {
        output.push_back(n);
    }
    return "SUCCESS";
}


/// \brief Converte um número de qualquer base para outra base.
/// \param num O número a ser convertido.
/// \param inBase A base de origem do número.
/// \param outBase A base de destino do número
/// \param output O vetor em que será armazenado os dígitos do resultado.
/// \return Uma mensagem informando se a operação foi um sucesso ou ocorreu algum erro.
string toAnyNumber(const string &num, const int inBase, const int outBase, vector<char> &output) {
    long long leftover;
    vector<char> outputDec;

    string decMsg = toDecimal(num, inBase, outputDec); // realiza a conversão do número de origem para decimal

    // se a conversão para decimal resultar em um número maior que a variável do tipo long long pode armazenar,
    // resulta em um erro que impede a continuação do cálculo, pois o resultado seria incorreto
    if (decMsg == "LARGE NUMBER") {return "LARGE NUMBER";}

    const string decNumb(outputDec.begin(), outputDec.end()); // extrai os dígitos do número em uma string
    long long decResult = stoll(decNumb); // transforma a string em um long long (numeral)

    // realiza os cálculos de conversão, que consiste em dividir o número pela base destino até que o resultado
    // seja zero e armazenar o resto das operações em um vetor (output), que conferirá o resultado final
    do {
        leftover = decResult % outBase;
        decResult /= outBase;

        if (leftover >= 10) {
            // identifica se o resto é maior que 10 e o transforma em letras, no caso é aplicado para bases 11 em diante
            char chr = static_cast<char>(leftover + 55);
            output.insert(output.begin(), chr);
        } else {
            // caso o resto não seja maior que 10, é mantido o número normalmente, mas é convertido em char
            // para que seja armazenado no vetor output e posteriormente seja descrito no terminal
            output.insert(output.begin(), static_cast<char>(leftover + '0'));
        }
    } while (decResult > 0);
    return "SUCCESS";
}
