#include <SFML/Graphics.hpp>

using namespace sf;

// Function to determine the winner
char checkWin(const char board[3][3]) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    
    return '\0';
}

// Function to check if the game is a draw
bool checkDraw(const char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false; // There is an empty cell, so the game is not a draw
            }
        }
    }
    return true; // All cells are filled, so the game is a draw
}


int main() {
    RenderWindow window(VideoMode(300, 300), "Tic Tac Toe");
    
    char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char currentPlayer = 'X';
    bool gameOver = false;  // Track if the game is over

    Font font;
    font.loadFromFile("CaviarDreams_Bold.ttf"); // Change this path to your font file
    
    Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(Color::Black);
    
    RectangleShape playAgainButton(Vector2f(200, 50));
    playAgainButton.setPosition(50, 220);
    playAgainButton.setOutlineThickness(2);
    playAgainButton.setOutlineColor(Color::Black);
    
    Text playAgainText;
    playAgainText.setFont(font);
    playAgainText.setCharacterSize(30);
    playAgainText.setFillColor(Color::Black);
    playAgainText.setString("Play Again");
    playAgainText.setPosition(75, 225);
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            
            if (!gameOver && event.type == Event::MouseButtonPressed) {
                int x = event.mouseButton.x / 100;
                int y = event.mouseButton.y / 100;
                
                if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[y][x] == ' ') {
                    board[y][x] = currentPlayer;
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
                
                char winner = checkWin(board);
                if (winner != '\0' || checkDraw(board)) {
                    gameOver = true;
                }
            }
            
            if (gameOver && event.type == Event::MouseButtonPressed) {
                // Check if the "Play Again" button is clicked
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                
                if (x >= 50 && x <= 250 && y >= 220 && y <= 270) {
                    // Reset the game state
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            board[i][j] = ' ';
                        }
                    }
                    currentPlayer = 'X';
                    gameOver = false;
                }
            }
        }
        
        window.clear();
        
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                RectangleShape cell(Vector2f(100, 100));
                cell.setPosition(j * 100, i * 100);
                cell.setOutlineThickness(2);
                cell.setOutlineColor(Color::Black);
                window.draw(cell);
                
                text.setString(board[i][j]);
                text.setPosition(j * 100 + 30, i * 100 + 30);
                window.draw(text);
            }
        }
        
        char winner = checkWin(board);
        if (winner != '\0') {
            text.setString("Player " + std::string(1, winner) + " wins!");
            text.setPosition(10, 100);
            text.setFillColor(Color::Green);
            text.setCharacterSize(43);
            window.draw(text);
        } else if (checkDraw(board)) {
            text.setString("It's a draw!");
            text.setPosition(60, 160);
            text.setFillColor(Color::Red);
            text.setCharacterSize(30);
            window.draw(text);
        }

        
        if (gameOver) {
            window.draw(playAgainButton);
            window.draw(playAgainText);
        }
        
        window.display();
    }
    
    return 0;
}

