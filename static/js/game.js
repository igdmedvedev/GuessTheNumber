let inputNum = document.getElementById('input-num');

if (inputNum.disabled === true) {
    document.getElementById('new-game-btn').focus();
} else {
    inputNum.focus();
}