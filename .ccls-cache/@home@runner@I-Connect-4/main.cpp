#include <iostream>
using namespace std;
class grid {

public:
  static const int row = 6;
  static const int columb = 7;
  char gridView[row][columb];
  int lastRow[columb];
  void InitializeGrid() {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < columb; j++) {
        gridView[i][j] = '0';
      }
    }
    for (int i = 0; i < columb; i++)
      lastRow[i] = row - 1;
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

private:
  bool checkHorizontal(int rowNo, int columbNo) {
    int count = 0;
    for (int i = rowNo; i >= 0; i--) {
      if (gridView[i][columbNo] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    for (int i = rowNo + 1; i < row; i++) {
      if (gridView[i][columbNo] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    return false;
  }
  bool checkVertical(int rowNo, int columbNo) {
    int count = 0;
    for (int i = columbNo; i >= 0; i--) {
      if (gridView[rowNo][i] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    for (int i = columbNo + 1; i < columb; i++) {
      if (gridView[rowNo][i] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    return false;
  }
  bool checkDiagonal(int rowNo, int columbNo) {
    int count = 0;
    for (int i = rowNo - 1, j = columbNo + 1; i >= 0 && j < columb; i--, j++) {
      if (gridView[i][j] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    for (int i = rowNo, j = columbNo; i < row && j >= 0; i++, j--) {
      if (gridView[i][j] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    count = 0;
    for (int i = rowNo - 1, j = columbNo - 1; i >= 0 && j >= 0; i--, j--) {
      if (gridView[i][j] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    for (int i = rowNo, j = columbNo; i < row && j < columb; i++, j++) {
      if (gridView[i][j] == gridView[rowNo][columbNo])
        count++;
      else
        break;
      if (count == 4)
        return true;
    }
    return false;
  }

public:
  bool GameOver(int columbNo) {
    int rowNo = lastRow[columbNo] + 1;
    if (checkHorizontal(rowNo, columbNo))
      return true;
    if (checkVertical(rowNo, columbNo))
      return true;
    if (checkDiagonal(rowNo, columbNo))
      return true;
    return false;
  }
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
    gameOver = Grid.GameOver(insertColumb);
    if (gameOver)
      playerWon = playerNo;
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
    if (gameOver) {
      cout << "Player " << playerWon << " won!";
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