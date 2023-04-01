let inputNum = document.getElementById('input-num');
let newGameBtn = document.getElementById('new-game-btn')

if (document.getElementById('end-game-flag').value !== "1") {
    inputNum.focus();
} else {
    newGameBtn.focus();
}


newGameBtn.onclick = function () {
	inputNum.value = null;
    document.getElementById('attempts').value = null;
	document.getElementById('prNum').value = null;
	document.getElementById('sum').value = null;
    document.getElementById('form').submit();
}