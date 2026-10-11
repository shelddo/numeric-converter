#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// declaração dos métodos/funções
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

        // verifica se o número pertence à base informada
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

    // loopa para cada dígito no número
    // como recebe uma string, loopa entre os caracteres dela e os transforma o dígito em número e confere se é
    // maior ou igual à base informada, caso seja, invalida a base
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
    long long pow = 1; // inicia como 1 pois todo número elevado a 0 é 1

    // loopa entre os dígitos do número de origem, começando do final.
    // por se tratar do cálculo padrão, onde é: num * (base ^ posição), é necessário começar do final,
    // pois facilita o cálculo, visto que a contagem da posição começa no final do número.
    for (size_t i = num.length(); i-- > 0;) {
        long long numb; // variável que armazenará o digito atualmente percorrido no número

        // transforma o dígito em número
        if (isdigit(num[i])) {
            numb = num[i] - '0'; // conversão de char para long long
        } else {
            numb = (num[i] - 'A') + 10; // mesma conversão, mas adiciona 10, por se tratar de uma letra
        }


        /* Checa se o valor do cálculo não ultrapassará o límite de armazenamento do long long, evitando que ocorra um
         * overflow.
         *
         * Como funciona:
         * O programa verificará duas condições:
         * - A primeira verifica se o valor da potência (pow) é maior que o limite de long long dividido pelo
         * dígito (numb) sendo calculado.
         * - A segunda verifica se o valor atual da soma dos digitos anteriores (decResult) é maior que o limite de
         * long long menos o valor calculado do dígito atual (value).
         *
         * Por exemplo:
         * Digamos que o limite seja 100, o dígito atual (numb) seja 5 e a potência seja 21. 100 / 5 é 20, e não pode
         * ultrapassar esse valor, então, como o valor da potência é 21, ele resultaria em um erro, pois é maior
         * que o que podemos armazenar naquele momento.
         *
         * Outro exemplo:
         * Ainda presumindo que o limite seja 100, se o valor do cálculo do digito atual (value) for 30, quer dizer
         * que o máximo que poderia ser somado é 70 (100 - 30 = 70). Portanto, se o valor da soma dos dígitos
         * anteriores (decResult) for 80, por exemplo, resultaria no mesmo erro, não permitindo que o programa
         * continuasse.
         */
        // primeira condição
        if (numb != 0 && pow > LLONG_MAX / numb) {
            return "LARGE NUMBER";
        }

        // calcula o valor do dígito
        const long long value = numb * pow;

        // segunda condição
        if (decResult > LLONG_MAX - value) {
            return "LARGE NUMBER";
        }

        decResult += value; // adiciona o valor do dígito no resultado final

        // debug para aferição do cálculo dígito por dígito
        //cout << "num: " << numb << " char: " << num[i] << " pow: " << pow
        //<< " base: " << base << " value: " << value << endl;

        pow *= base; // prepara o valor da potência para o próximo dígito
    }

    string outNumb = to_string(decResult); // transforma o resultado long long em string

    // debug para aferição do quanto o resultado se aproximou do limite
    //cout << "decNumb: " << outNumb << "/" << LLONG_MAX << endl;

    // pega cada char da string convertida e adiciona no vetor de saída (foreach)
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
    if (decMsg == "LARGE NUMBER") { return "LARGE NUMBER"; }

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
