package com.demo.springmvctest.common;

public class GameContext {
    private int curAttempts;
    private int guessNum;
    private GameStatus gameStatus;
    private String gameInfo;

    public GameContext(int curAttempts, int guessNum) {
        this.curAttempts = curAttempts;
        this.guessNum = guessNum;
        gameStatus = GameStatus.START_GAME;
        gameInfo = "";
    }

    public int getCurAttempts() {
        return curAttempts;
    }
    public void setCurAttempts(int curAttempts) {
        this.curAttempts = curAttempts;
    }

    public void decreaseAttempts() {
        this.curAttempts--;
    }

    public int getGuessNum() {
        return guessNum;
    }

    public void setGuessNum(int guessNum) {
        this.guessNum = guessNum;
    }

    public GameStatus getGameStatus() {
        return gameStatus;
    }

    public void setGameStatus(GameStatus gameStatus) {
        this.gameStatus = gameStatus;
    }

    public String getGameInfo() {
        return gameInfo;
    }

    public void setGameInfo(String gameInfo) {
        this.gameInfo = gameInfo;
    }
}
