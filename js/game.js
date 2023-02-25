const min = 10, max = 100;
const prNum = Math.floor(Math.random() * (max - min) + min);
let attempts = Math.round(Math.log2(max - min + 1));
let flagWin = false;

document.getElementById('outNum').innerHTML = prNum;
document.getElementById('min').innerHTML = min;
document.getElementById('max').innerHTML = max;
document.getElementById('attempts').innerHTML = attempts;

document.getElementById('btn').onclick = function () {
    var out = document.getElementById('out');
    if (flagWin) {
        return;
    }

    let num = document.getElementById('mynum').value;
    if (attempts > 0 && /( )*\d+( )*/.exec(num)) {
        attempts -= 1
        document.getElementById('attempts').innerHTML = attempts;

        if (num == prNum) {
            out.innerHTML = "You won!";
            flagWin = true;
        } else if (attempts == 0) {
            out.innerHTML = "You lose";
        } else if (num > prNum) {
            out.innerHTML = "Less";
        } else {
            out.innerHTML = "More";
        }
    }
}