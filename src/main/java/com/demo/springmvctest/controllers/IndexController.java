package com.demo.springmvctest.controllers;

import com.demo.springmvctest.common.GameContext;
import com.demo.springmvctest.common.GameStatus;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import static java.lang.Math.*;

@Controller
@SessionAttributes("gameContext")
public class IndexController {
    private final int min = 100;
    private final int max = 140;
    private final int diff = max - min;
    private final int totalAttempts = (int)ceil(log(diff + 1) / log(2));

    @GetMapping("/")
    public String startGame(Model model,
                            @ModelAttribute("gameContext") GameContext gameContext) {

        if (gameContext.getGameStatus() == GameStatus.END_GAME) {
            model.addAttribute("end_game", true);
            gameContext.setGameStatus(GameStatus.START_GAME);
        } else if (gameContext.getGameStatus()  == GameStatus.START_GAME) {
            gameContext.setGuessNum((int)ceil(random() * diff + 100));
            gameContext.setCurAttempts(totalAttempts);
            gameContext.setGameInfo("");
            gameContext.setGameStatus(GameStatus.CONTINUES_GAME);
        }

        model.addAttribute("attempts", gameContext.getCurAttempts());
        model.addAttribute("game_info", gameContext.getGameInfo());
        model.addAttribute("min", min);
        model.addAttribute("max", max);
        model.addAttribute("total_attempts", totalAttempts);

        return "index";
    }

    @PostMapping("/")
    //Redirect on GET-request. Using pattern Post-Redirect-Get (PRG).
    public String checkNum(@RequestParam("input-num") int inputNum,
                           @ModelAttribute("gameContext") GameContext gameContext) {
        gameContext.decreaseAttempts();
        if (inputNum == gameContext.getGuessNum()) {
            gameContext.setGameStatus(GameStatus.END_GAME);
            gameContext.setGameInfo("You won!");
        } else if (gameContext.getCurAttempts() == 0) {
            gameContext.setGameStatus(GameStatus.END_GAME);
            gameContext.setGameInfo("You lose");
        } else if (inputNum < gameContext.getGuessNum()) {
            gameContext.setGameInfo("Guess number is more");
        } else {
            gameContext.setGameInfo("Guess number is less");
        }

        return "redirect:/";
    }

    @ModelAttribute("gameContext")
    public GameContext getGameContext() {
        return new GameContext(totalAttempts, (int)ceil(random() * diff + 100));
    }
}
