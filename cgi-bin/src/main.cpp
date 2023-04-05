//C++ 23
//#include <cgicc>
#include <iostream>
#include <random>
#include <tr1/unordered_map>
#include "utils.h"
#include "index.h"

const int min = 100, max = 140;

int main() {
    std::cout << "content-type:text/HTML\n\n\n";

    int strLen = 0;
    try {
        strLen = std::stoi(getenv("CONTENT_LENGTH")) + 1;
    } catch (std::exception& ex) {}
    std::string inputString(strLen, ' ');
    fgets(&inputString[0], strLen, stdin);

    //TestCases:
    //inputString = "input-num=&prNum=&attempts=&sum=";
    //inputString = "";
    //inputString = "input-num=120&prNum=kikjmcljk&attempts=6&sum=wlnmlchjihwblijhkbjb"; //key = ZZZ
    //inputString = "input-num=120&prNum=hbolkjjjj&attempts=6&sum=wiojcnkkbnwcmkiiiiml";

    std::tr1::unordered_map<std::string, std::string> param;
    param["input-num"] = getInputVal(inputString, "input-num=");
    param["prNum"] = getInputVal(inputString, "prNum=");
    param["attempts"] = getInputVal(inputString, "attempts=");
    param["sum"] = getInputVal(inputString, "sum=");

    std::string outText;
    int decryptPrNum;
    int attempts;
    bool stopGame = false;

    if (param["attempts"].empty() || param["prNum"].empty()) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
        decryptPrNum = (int)dist6(rng);
        param["prNum"] = encrypt(decryptPrNum);

        attempts = (int)ceil(log2(max - min + 1));
        param["attempts"] = std::to_string(attempts);
        param["sum"] = formSum(decryptPrNum, std::stoi(param["attempts"]));
    } else {
        decryptPrNum = decrypt(param["prNum"]);
        attempts = std::stoi(param["attempts"]);
        int inputNum = std::stoi(param["input-num"]);

        /*std::cout << param["sum"] << std::endl;
        std::cout << param["prNum"] << std::endl;
        std::cout << decryptPrNum << std::endl;
        std::cout << formSum(decrypt(param["prNum"]), 6) << std::endl;*/

        if (!checkSum(decryptPrNum, attempts, param["sum"])) {
            stopGame = true;
            outText = "You lose. Let's play fair.";
        } else if (!param["input-num"].empty()) {
            attempts -= 1;
            param["attempts"] = std::to_string(attempts);

            if (decryptPrNum == inputNum) {
                stopGame = true;
                outText = "You won!";
            } else if (attempts == 0) {
                stopGame = true;
                outText = "You lose!";
            } else if (decryptPrNum > inputNum) {
                outText = "Guess number is more";
            } else if (decryptPrNum < inputNum) {
                outText = "Guess number is less";
            } else {
                stopGame = true;
                outText = "Error";
            }
        }
    }
    //std::cout << inputString << std::endl << decryptPrNum << std::endl;

    std::string htmlPage = getIndex();
    htmlPage = replaceMask(htmlPage, "%prNum%", param["prNum"]);
    htmlPage = replaceMask(htmlPage, "%attempts%", param["attempts"]);
    htmlPage = replaceMask(htmlPage, "%sum%", formSum(decryptPrNum, attempts));
    htmlPage = replaceMask(htmlPage, "%stopGame%",  std::to_string(stopGame));
    htmlPage = replaceMask(htmlPage, "%totalAttempts%", std::to_string((int)ceil(log2(max - min + 1))));
    htmlPage = replaceMask(htmlPage, "%outText%", outText);
    htmlPage = replaceMask(htmlPage, "%inputNumDisabled%", (stopGame ? "disabled" : ""));
    htmlPage = replaceMask(htmlPage, "%guessBtnDisabled%", (stopGame ? "disabled" : ""));
    htmlPage = replaceMask(htmlPage, "%min%", std::to_string(min));
    htmlPage = replaceMask(htmlPage, "%max%", std::to_string(max));

    std::cout << htmlPage;
    return 0;
}