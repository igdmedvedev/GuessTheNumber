#ifndef CHECKTHENUM_UTILS_H
#define CHECKTHENUM_UTILS_H

std::string getInputVal(std::string argv, const std::string& paramName) {
    std::string res;
    for (size_t j = argv.find(paramName) + paramName.length(); argv.contains(paramName) && argv[j] != '&' && argv[j] != '\0'; j++) {
        res += argv[j];
    }
    return res;
}

const char key[3] = {'Z', 'Z', 'Z'};
std::string encrypt(int toEncrypt) {
    std::string output = std::to_string(toEncrypt * toEncrypt * toEncrypt * toEncrypt);

    for (int i = 0; i < output.size(); i++)
        output[i] = output[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return output;
}

int decrypt(std::string toDecrypt) {
    std::string output = toDecrypt;

    for (int i = 0; i < output.size(); i++)
        output[i] = output[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return sqrt(sqrt((double)std::stoi(output)));
}

std::string replaceMask(std::string str, const std::string& mask, const std::string& text) {
    while (str.contains(mask)) {
        str = replaceMask(str.replace(str.find(mask), mask.length(), text), mask, text);
    }
    return str;
}

std::string formSum(int prNum, int attempts) {
    return encrypt(prNum * attempts * 2) + encrypt(prNum * attempts * 3);
}

bool checkSum(int prNum, int attempts, std::string sum) {
    return sum == formSum(prNum, attempts);
}

#endif //CHECKTHENUM_UTILS_H
