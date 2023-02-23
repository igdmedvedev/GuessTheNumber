const min = 10, max = 100;
const prNum = Math.floor(Math.random() * (max - min) + min);
let attempts = Math.round(Math.log2(max - min + 1));
let flagWin = false;

document.getElementById('outNum').innerHTML = prNum;
document.getElementById('min').innerHTML = min;
document.getElementById('max').innerHTML = max;
document.getElementById('attempts').innerHTML = attempts;

function checkNum() {
	var out = document.getElementById('out');
	if (flagWin) {
		return;
	}
	if (attempts > 0) {
		attempts -= 1
		let num = document.getElementById('mynum').value;
		document.getElementById('attempts').innerHTML = attempts;

		if (attempts > 0) {
			if (num == prNum) {
				out.innerHTML = "You won!";
				flagWin = true;
			} else if (num > prNum) {
				out.innerHTML = "Less";
			} else {
				out.innerHTML = "More";
			}
		} else {
			if (num == prNum) {
				out.innerHTML = "You won!";
			} else {
				out.innerHTML = "You lose";
			}
		}
	}
}