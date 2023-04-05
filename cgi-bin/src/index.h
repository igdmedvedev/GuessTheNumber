#ifndef CHECKTHENUM_INDEX_H
#define CHECKTHENUM_INDEX_H
#include <iostream>

const std::string getIndex() { return R"(
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
                <input type="number" id="input-num" name="input-num" class="form-control" required min=%min% max=%max% %inputNumDisabled%>
                <button class="btn btn-outline-secondary" id="guess-btn" %guessBtnDisabled%>Guess</button>
                <button type="button" class="btn btn-outline-secondary" id="new-game-btn">New game</button>
                <!-- Hidden fields -->
                <input type="hidden" id="prNum" name="prNum" class="form-control" value="%prNum%">
                <input type="hidden" id="attempts" name="attempts" class="form-control" value="%attempts%">
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
)";}
#endif //CHECKTHENUM_INDEX_H
