#include <iostream>
#include <random>
#include <tr1/unordered_map>

std::string getInputVal(std::string, const std::string&);
std::string encryptDecrypt(std::string);

int main() {
    const std::string inputString = std::string(getenv("QUERY_STRING"));
    //std::string inputString = "input-num=120&min=100&max=140&prNum=pu%7F&attempts=w&sum=pu%7Fw";

    std::tr1::unordered_map<std::string, std::string> param;

    param["input-num"] = getInputVal(inputString, "input-num=");
    param["min"] = getInputVal(inputString, "min=");
    param["max"] = getInputVal(inputString, "max=");
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


    std::cout << "content-type:text/HTML\n\n" << std::endl;
    std::cout
    <<  "<!DOCTYPE html>"
    <<  "<html lang=\"en\">"
    <<  "<head>"
        <<  "<meta charset=\"UTF-8\">"
        <<  "<title>Document</title>"
        <<  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
        <<  "<link href=\"../css/bootstrap.css\" rel=\"stylesheet\">\n"
    <<  "</head>"
    <<  "<body>"
    <<  "<header></header>"
    <<  "<main>"
        <<  "<form action=\"../cgi-bin/test.cgi\" method=\"GET\" class=\"form-inline\" id=\"form\">\n"
            <<  "<div class=\"container\">\n"
                <<  "<h1 class=\"mt-0\">\n"
                    <<  "<span class=\"col-sm-auto\">\n"
                        <<  "<label for=\"input-num\" class=\"col-sm-auto\">Your number:</label>\n"
                    <<  "</span>\n"
                <<  "</h1>\n"
                <<  "<div class=\"input-group mb-3\">\n"
                    <<  "<input type=\"number\" id=\"input-num\" name=\"input-num\" class=\"form-control\" required>\n"
                    <<  "<button class=\"btn btn-outline-secondary\" id=\"guess-btn\")>Guess</button>\n"
                    <<  "<button type=\"button\" class=\"btn btn-outline-secondary\" id=\"new-game-btn\">New game</button>\n"
                    <<  "<!-- Hidden fields -->\n"
                    <<  "<input type=\"hidden\" id=\"formMin\" name=\"min\" class=\"form-control\">\n"
                    <<  "<input type=\"hidden\" id=\"formMax\" name=\"max\" class=\"form-control\">\n"
                    <<  R"(<input type="hidden" id="prNum" name="prNum" class="form-control" value=)" + param["prNum"] + ">\n"
                    <<  R"(<input type="hidden" id="attempts" name="attempts" class="form-control" value=)" + encryptDecrypt(param["attempts"]) + ">\n"
                    <<  R"(<input type="hidden" id="sum" name="sum" class="form-control" value=)" + param["prNum"] + encryptDecrypt(param["attempts"]) + ">\n"
                    <<  R"(<input type="hidden" id="end-game-flag" class="form-control" value=)" + std::to_string(stopGame) + " disable>\n"
                <<  "</div>\n"
                <<  "<div class=\"lead\">Attempts: " + param["attempts"] + "</div>\n"
                <<  "<p class=\"lead\">" + outText + "</p>\n"
            <<  "</div>\n"
        <<  "</form>\n"
        <<  "<hr>"
    <<  "</main>"
    <<  "<footer class=\"container\">\n"
        <<  "<div>\n"
            <<  "The thinker thinks of a number from <span id=\"min\"></span> to <span id=\"max\"></span> inclusive.\n"
            <<  "The guesser has <span id=\"attempts1\"></span> guesses to guess the number. If they take more than <span id=\"attempts2\"></span> guesses to guess the number, they lose.\n"
            <<  "<div>\n"
                <<  "Every time the guesser guesses, the thinker must give one of three responses:\n"
            <<  "</div>\n"
            <<  "<div class=\"ms-3\">your guess is too big,</div>\n"
            <<  "<div class=\"ms-3\">your guess is too small,</div>\n"
            <<  "<div class=\"ms-3\">or your guess is the correct number.</div>\n"
            <<  "If the number is correct, the guesser wins.\n"
        <<  "</div>\n"
    <<  "</footer>"
    <<  "</body>"
    <<  "<script type=\"text/javascript\" src=\"../js/game.js\" defer></script>\n"
    <<  "</html>";

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