#include <iostream>
#include <string>

class Dice {
public:
    Dice() {}
    ~Dice() {}
};

class Player {
private:
    std::string name;
    int money;
    int position;

public:
    Player(const std::string& name, int money = 7, int position = 0)
        : name(name), money(money), position(position) {}

    ~Player() {}

    // Getters
    std::string getName() const {
        return name;
    }

    int getMoney() const {
        return money;
    }

    int getPosition() const {
        return position;
    }

    // Setters
    void setName(const std::string& name) {
        this->name = name;
    }

    void setMoney(int money) {
        this->money = money;
    }

    void setPosition(int position) {
        this->position = position;
    }
};


class Square {
public:
    Square() {}
    virtual ~Square() {}

    virtual void land(Player& player){}
};

class LotterySquare : public Square {
public:
    LotterySquare() {}
    ~LotterySquare() {}

    void land(Player& player) override {
        // Specific behavior for LotterySquare
    }
};

class BadInvestmentSquare : public Square {
public:
    BadInvestmentSquare() {}
    ~BadInvestmentSquare() {}

    void land(Player& player) override {
        // Specific behavior for BadInvestmentSquare
    }
};

class GameBoard {
private:
    Square* squares[40];

public:
    GameBoard() {
        for (int i = 0; i < 40; ++i) {
            squares[i] = nullptr;
        }
    }

    ~GameBoard() {
        for (int i = 0; i < 40; ++i) {
            if (squares[i] != nullptr) {
                delete squares[i];
            }
        }
    }

    Square* getSquare(int index) const {
        return squares[index];
    }

    void setSquare(int index, Square* square) {
        squares[index] = square;
    }
};
int main() {
    // Creating instances
    Player player1("Alice");
    Player player2("Bob");

    Dice dice;

    GameBoard board;
    board.setSquare(9, new LotterySquare());
    board.setSquare(4, new BadInvestmentSquare());

    // Sample usage of setters and getters
    player1.setMoney(10);
    std::cout << player1.getName() << " has " << player1.getMoney() << " cents." << std::endl;

    // Clean up dynamically allocated memory
    return 0;
}
