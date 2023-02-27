const min = 10, max = 100;
const prNum = Math.floor(Math.random() * (max - min) + min);
let attempts = Math.round(Math.log2(max - min + 1));
let flagWin = false;

document.getElementById('attempts').innerHTML = "Attempts: " + attempts;

let inputNum = document.getElementById('input-num');
inputNum.min = min;
inputNum.max = max;

let out = document.getElementById('out');

document.getElementById('form').onsubmit = function () {
    if (flagWin) {
        return false;
    }

    const num = inputNum.value;
    if (attempts > 0) {
        document.getElementById('attempts').innerHTML = "Attempts: " + (attempts -= 1);

        if (num == prNum) {
            out.innerHTML = "You won!";
            flagWin = true;
        } else if (attempts === 0) {
            out.innerHTML = "You lose";
        } else if (num > prNum) {
            out.innerHTML = "Less";
        } else if (num < prNum) {
            out.innerHTML = "More";
        } else {
            out.innerHTML = "Error";
        }
    }
    return false;
}

document.getElementById('outNum').innerHTML = prNum;
document.getElementById('min').innerHTML = min;
document.getElementById('max').innerHTML = max;
document.getElementById('attempts1').innerHTML = attempts;
document.getElementById('attempts2').innerHTML = attempts;