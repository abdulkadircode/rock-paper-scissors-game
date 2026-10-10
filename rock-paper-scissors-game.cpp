#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

enum enChoice{ Stone = 1, Paper = 2, Scissor = 3};

enum enWinner{ Player1 = 1, Computer = 2, Draw = 3};

struct stRoundInfo{
    
    short roundNumber = 0;
    enChoice player1Choice;
    enChoice computerChoice;
    enWinner roundWinner;
    string roundWinnerName= "";

};

struct stGameResults{

    short gameRounds = 0;
    short player1WinTimes = 0;
    short computerWinTimes = 0;
    short drawTimes = 0;
    enWinner gameWinner;
    string GameWinnerName = "";

};

int ReadNumberInRange(string message, int from, int to){
    int number;

    do{
        cout << message << endl;
        cin >> number;
    }while(number < from || number > to);

    return number;
}

int RandomNumberInRange(int from, int to){

    int randNum = rand() % (to - from + 1) + from;
    return randNum;

}

enWinner WhoWonTheRound(stRoundInfo RoundInfo){

    if(RoundInfo.player1Choice == RoundInfo.computerChoice)
        return enWinner::Draw;

    switch(RoundInfo.player1Choice){
        case enChoice::Stone:
            if(RoundInfo.computerChoice == enChoice::Scissor)
                return enWinner::Player1;

            break;

        case enChoice::Paper:
            if(RoundInfo.computerChoice == enChoice::Stone) 
                return enWinner::Player1;
        
            break;
    
        case enChoice::Scissor:
            if(RoundInfo.computerChoice == enChoice::Paper)
                return enWinner::Player1;

            break;
    
    }

    return enWinner::Computer;

}

string WinnerName(enWinner winner){

    string winnerNames[] = {"Player1", "Computer", "No Winner"};
    return winnerNames[winner - 1];

}

string ChoiceName(enChoice choice){

    string ChoiseNames[] = {"Stone", "Paper", "Scissor"};
    return ChoiseNames[choice - 1];

}

void PrintColor(enWinner winner){

    switch(winner){

        case enWinner::Computer:
            system("color 47");
            MessageBeep(MB_ICONERROR);
            break;
    
        case enWinner::Player1:
            system("color 20");
            break;
    
        default:
            system("color 60");

    }

}

void PrintRoundResults(stRoundInfo RoundInfo){

    PrintColor(RoundInfo.roundWinner);
    cout << "\n____________ Round [" << RoundInfo.roundNumber << "] ____________\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.player1Choice) << endl;     
    cout << "Computer Choice: " << ChoiceName(RoundInfo.computerChoice) << endl;   
    cout << "Raund Winner   : [" << RoundInfo.roundWinnerName << "]" << endl;
    cout << "_________________________________________________________\n";

}

enWinner WhoWonTheGame(stGameResults gameResults){

    if(gameResults.player1WinTimes > gameResults.computerWinTimes)
        return enWinner::Player1;

    else if(gameResults.computerWinTimes > gameResults.player1WinTimes)
        return enWinner::Computer;

    else 
        return enWinner::Draw;

}

stGameResults FillGameResults(short howManyRounds, short player1WinTimes, short computerWinTimes, short drawTimes){

    stGameResults gameResults;

    gameResults.gameRounds = howManyRounds;
    gameResults.player1WinTimes = player1WinTimes;
    gameResults.computerWinTimes = computerWinTimes;
    gameResults.drawTimes = drawTimes;
    gameResults.gameWinner = WhoWonTheGame(gameResults);
    gameResults.GameWinnerName = WinnerName(gameResults.gameWinner);

    return gameResults;
}

stGameResults PlayGame(short howManyRounds){
    
    stRoundInfo RoundInfo;
    short player1WinTimes = 0, computerWinTimes = 0, drawTimes = 0;

    for(short roundNumber = 1 ; roundNumber <= howManyRounds ; roundNumber++){

        cout << "\n\nRound [" << roundNumber << "] begins : \n";
        RoundInfo.roundNumber = roundNumber;
        RoundInfo.player1Choice = (enChoice)ReadNumberInRange("\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ", 1, 3);
        RoundInfo.computerChoice = (enChoice)RandomNumberInRange(1,3);
        RoundInfo.roundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.roundWinnerName = WinnerName(RoundInfo.roundWinner);

        if(RoundInfo.roundWinner == enWinner::Player1)
            player1WinTimes++;

        else if(RoundInfo.roundWinner == enWinner::Computer)
            computerWinTimes++;

        else 
            drawTimes++;

        
        PrintRoundResults(RoundInfo);

    }

    return FillGameResults(howManyRounds, player1WinTimes, computerWinTimes, drawTimes);

}

void ClearScreen(){
    system("cls");
    system("color 0F");
}

void ShowGameOverScreen(){

    cout << "                _________________________________________________________\n\n";

    cout << "                                 +++ G a m e  O v e r +++\n";
    cout << "                _________________________________________________________\n\n";

}

void ShowFinalGameResults(const stGameResults GameResult){

    cout << "                _____________________ [Game Results ] ____________________\n\n";

    cout << "                Game Rounds         : " << GameResult.gameRounds << endl;
    cout << "                Player1 won times   : " << GameResult.player1WinTimes << endl;
    cout << "                Computer won times  : " << GameResult.computerWinTimes << endl;
    cout << "                Draw times          : " << GameResult.drawTimes << endl;
    cout << "                Final Winner        : " << GameResult.GameWinnerName << endl;
    cout << "                _________________________________________________________\n";

}

void StartGame(){
    char playAgain = 'Y';

    do{

        ClearScreen();
        stGameResults GameResults = PlayGame(ReadNumberInRange("How many raunds 1 to 10 ? ", 1, 10));
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);


        cout << "Do you want to play again? Y/N? ";
        cin >> playAgain;

    }while(playAgain == 'Y' || playAgain == 'y');

}

int main(){

    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}