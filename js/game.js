const min = 100, max = 140;
const prNum = Math.floor(Math.random() * (max - min) + min);
let attempts = Math.ceil(Math.log2(max - min + 1));
let flagWin = false;

document.getElementById('attempts').innerHTML = "Attempts: " + attempts;

let inputNum = document.getElementById('input-num');
inputNum.min = min;
inputNum.max = max;
inputNum.focus();

let out = document.getElementById('out');

document.getElementById('form').onsubmit = function () {
    if (flagWin) {
        return false;
    }

    if (attempts > 0) {
        document.getElementById('attempts').innerHTML = "Attempts: " + (attempts -= 1);

        const num = inputNum.value;
        if (num == prNum) {
            out.innerHTML = "You won!";
            flagWin = true;
            disableGame();
        } else if (attempts === 0) {
            out.innerHTML = "You lose";
            disableGame();
        } else if (num > prNum) {
            out.innerHTML = "Less";
        } else if (num < prNum) {
            out.innerHTML = "More";
        } else {
            out.innerHTML = "Error";
            disableGame();
        }
    }
    return false;
}

function disableGame() {
    document.getElementById('input-num').disabled = true;
    document.getElementById('guess-btn').disabled = true;
    document.getElementById('new-game-btn').focus();
}

document.getElementById('new-game-btn').onclick = function () {
    location.reload();
}

//document.getElementById('outNum').innerHTML = prNum;
document.getElementById('min').innerHTML = min;
document.getElementById('max').innerHTML = max;
document.getElementById('attempts1').innerHTML = attempts;
document.getElementById('attempts2').innerHTML = attempts;