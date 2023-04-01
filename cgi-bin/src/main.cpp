//C++ 23
//#include <cgicc>
#include <iostream>
#include <random>
#include <tr1/unordered_map>

std::string getInputVal(std::string, const std::string&);
std::string encryptDecrypt(std::string);
std::string replaceMask(std::string, const std::string&, const std::string&);

std::string htmlPage = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Document</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="../css/bootstrap.css" rel="stylesheet">
</head>
<body>
<header></header>
<main>
    <form action="../cgi-bin/CheckTheNum.cgi" method="POST" class="form-inline" id="form">
        <div class="container">
            <h1 class="mt-0">
                <span class="col-sm-auto">
                    <label for="input-num" class="col-sm-auto">Your number:</label>
                </span>
            </h1>
            <div class="input-group mb-3">
                <input type="number" id="input-num" name="input-num" class="form-control" required %inputNumDisabled%>
                <button class="btn btn-outline-secondary" id="guess-btn" %guessBtnDisabled%>Guess</button>
                <button type="button" class="btn btn-outline-secondary" id="new-game-btn">New game</button>
                <!-- Hidden fields -->
                <input type="hidden" id="prNum" name="prNum" class="form-control" value="%prNum%">
                <input type="hidden" id="attempts" name="attempts" class="form-control" value="%encryptAttempts%">
                <input type="hidden" id="sum" name="sum" class="form-control" value="%sum%">
                <input type="hidden" id="end-game-flag" class="form-control" value="%stopGame%" disable>
            </div>
            <div class="lead">Attempts: %attempts%</div>
            <p class="lead">%outText%</p>
        </div>
    </form>
    <hr>
</main>
<footer class="container">
    <div>
        The thinker thinks of a number from %min% to %max% inclusive.
        The guesser has %totalAttempts% guesses to guess the number. If they take more than %totalAttempts% guesses to guess the number, they lose.
        <div>
            Every time the guesser guesses, the thinker must give one of three responses:
        </div>
        <div class="ms-3">your guess is too big,</div>
        <div class="ms-3">your guess is too small,</div>
        <div class="ms-3">or your guess is the correct number.</div>
        If the number is correct, the guesser wins.
    </div>
</footer>
</body>
<script type="text/javascript" src="../js/game.js" defer></script>
</html>
)";

int main() {
    std::cout << "content-type:text/HTML\n\n\n";

    std::string inputString;
    try {
        char* buf = new char[std::stoi(getenv("CONTENT_LENGTH")) + 1];
        fgets(buf, std::stoi(getenv("CONTENT_LENGTH")) + 1, stdin);
        inputString = buf;
        delete[] buf;
    } catch (std::exception& ex) {}
    //inputString = "input-num=120&min=100&max=140&prNum=ptt&attempts=w&sum=pttw";

    std::tr1::unordered_map<std::string, std::string> param;

    param["input-num"] = getInputVal(inputString, "input-num=");
    param["min"] = "100";
    param["max"] = "140";
    param["prNum"] = getInputVal(inputString, "prNum=");
    param["attempts"] = getInputVal(inputString, "attempts=");
    param["sum"] = getInputVal(inputString, "sum=");

    std::string outText;
    bool stopGame = false;

    if (param["attempts"].empty() || param["prNum"].empty()) {
        param["attempts"] = encryptDecrypt(std::to_string((int)ceil(log2(std::stoi(param["max"]) - std::stoi(param["min"]) + 1))));

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(std::stoi(param["min"]), std::stoi(param["max"]));
        param["prNum"] = encryptDecrypt(std::to_string((int)dist6(rng)));
        param["sum"] = param["prNum"] + param["attempts"];
    }

    param["attempts"] = encryptDecrypt(param["attempts"]);
    if (param["prNum"] + encryptDecrypt(param["attempts"]) != param["sum"]) {
        stopGame = true;
        outText = "You lose. Let's play fair.";
    } else if (!param["input-num"].empty()) {
        param["attempts"] = std::to_string(std::stoi(param["attempts"]) - 1);
        if (encryptDecrypt(param["prNum"]) == param["input-num"]) {
            stopGame = true;
            outText = "You won!";
        } else if (param["attempts"] == "0") {
            stopGame = true;
            outText = "You lose!";
        } else if (std::stoi(encryptDecrypt(param["prNum"])) > std::stoi(param["input-num"])) {
            outText = "Your number is less";
        } else if (std::stoi(encryptDecrypt(param["prNum"])) < std::stoi(param["input-num"])) {
            outText = "Your number is more";
        } else {
            stopGame = true;
            outText = "Error";
        }
    }

    htmlPage = replaceMask(htmlPage, "%prNum%", param["prNum"]);
    htmlPage = replaceMask(htmlPage, "%encryptAttempts%", encryptDecrypt(param["attempts"]));
    htmlPage = replaceMask(htmlPage, "%sum%", param["prNum"] + encryptDecrypt(param["attempts"]));
    htmlPage = replaceMask(htmlPage, "%stopGame%",  std::to_string(stopGame));
    htmlPage = replaceMask(htmlPage, "%attempts%", param["attempts"]);
    htmlPage = replaceMask(htmlPage, "%totalAttempts%", std::to_string((int)ceil(log2(std::stoi(param["max"]) - std::stoi(param["min"]) + 1))));
    htmlPage = replaceMask(htmlPage, "%outText%", outText);
    htmlPage = replaceMask(htmlPage, "%min%", param["min"]);
    htmlPage = replaceMask(htmlPage, "%max%", param["max"]);
    htmlPage = replaceMask(htmlPage, "%inputNumDisabled%", (stopGame ? "disabled" : ""));
    htmlPage = replaceMask(htmlPage, "%guessBtnDisabled%", (stopGame ? "disabled" : ""));

    std::cout << htmlPage;
    return 0;
}

std::string getInputVal(std::string argv, const std::string& paramName) {
    std::string res;
    for (size_t j = argv.find(paramName) + paramName.length(); argv.contains(paramName) && argv[j] != '&' && argv[j] != '\0'; j++) {
        res += argv[j];
    }
    return res;
}

std::string encryptDecrypt(std::string toEncrypt) {
    char key[3] = {'A', 'D', 'F'};
    std::string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

    return output;
}

std::string replaceMask(std::string str, const std::string& mask, const std::string& text) {
    while (str.contains(mask)) {
        str = replaceMask(str.replace(str.find(mask), mask.length(), text), mask, text);
    }
    return str;
}