#include <iostream>
using namespace std;
class grid {

public:
  static const int row = 6;
  static const int columb = 7;
  char gridView[row][columb];
  int lastRow[columb] = {5, 5, 5, 5, 5, 5, 5};
  void InitializeGrid() {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < columb; j++) {
        gridView[i][j] = '0';
      }
    }
  }
  void PrintGrid() {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < columb; j++) {
        cout << gridView[i][j] << " ";
      }
      cout << endl;
    }
  }
  bool BoardFull() {
    for (int i = 0; i < columb; i++) {
      if (lastRow[i] != -1)
        return false;
    }
    return true;
  }
  void InsertElement(char colour, int columbNo) {
    int rowNo = lastRow[columbNo];
    gridView[rowNo][columbNo] = colour;
    lastRow[columbNo]--;
  }
  bool GameOver() { return false; }
};
class gameplay : grid {
  grid Grid;
  bool boardFull = false;
  bool gameOver = false;
  char player1 = 'R';
  char player2 = 'B';
  int playerWon;

  void playerTurn(char colour) {
    int playerNo;
    if (colour == 'R')
      playerNo = 1;
    else
      playerNo = 2;
    int insertColumb;
    cout << "Player " << playerNo << "- " << colour << " enter column number: ";
    cin >> insertColumb;
    while (Grid.lastRow[insertColumb - 1] == -1 || insertColumb < 1 ||
           insertColumb > Grid.columb) {
      cout << "Columb Full or Wrong input select other:\n";
      cin >> insertColumb;
    }
    insertColumb--;
    Grid.InsertElement(colour, insertColumb);
    Grid.PrintGrid();
    boardFull = Grid.BoardFull();
    gameOver = Grid.GameOver();
  }
  void gameLoop() {
    while (!boardFull && !gameOver) {
      playerTurn(player1);
      if (boardFull || gameOver)
        break;
      playerTurn(player2);
    }
    if (boardFull) {
      cout << "Its a draw\n";
      return;
    }
  }

public:
  void Play() {
    Grid.InitializeGrid();
    Grid.PrintGrid();
    gameLoop();
  }
};
int main() {
  gameplay game;
  game.Play();
}