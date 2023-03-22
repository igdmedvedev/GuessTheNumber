const min = 100, max = 140;
let attempts = Math.ceil(Math.log2(max - min + 1));

let inputNum = document.getElementById('input-num');
inputNum.min = min;
inputNum.max = max;

let newGameBtn = document.getElementById('new-game-btn')

if (document.getElementById('end-game-flag').value !== "1") {
    inputNum.focus();
} else {
    newGameBtn.focus();
    inputNum.disabled = true;
	document.getElementById('guess-btn').disabled = true;
}


newGameBtn.onclick = function () {
	inputNum.value = null;
    document.getElementById('attempts').value = null;
	document.getElementById('prNum').value = null;
	document.getElementById('sum').value = null;
    document.getElementById('form').submit();
}

document.getElementById('min').innerHTML = min;
document.getElementById('max').innerHTML = max;
document.getElementById('formMin').value = min;
document.getElementById('formMax').value = max;
document.getElementById('attempts1').innerHTML = attempts;
document.getElementById('attempts2').innerHTML = attempts;