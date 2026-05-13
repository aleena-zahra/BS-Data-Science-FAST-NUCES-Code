#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
// linked List
// it will store player pointer and game count
// it will be used to find top n players
struct PlayerGameCount
{
    string playerID;
    int gameCount;
    PlayerGameCount *next, *prev;
    PlayerGameCount(string playerID, int gameCount)
    {
        this->playerID = playerID;
        this->gameCount = gameCount;
        next = prev = NULL;
    }
};
// linked List
class List
{
    PlayerGameCount *head, *tail;

public:
    List()
    {
        head = tail = NULL;
    }
    void insertAtHead(string playerID, int gameCount)
    {
        PlayerGameCount *temp = new PlayerGameCount(playerID, gameCount);
        if (head == NULL)
        {
            head = tail = temp;
        }
        else if (head == tail)
        {
            head->next = temp;
            temp->prev = head;
            tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }
    void deleteNode(string player)
    {
        PlayerGameCount *temp = head;
        while (temp != NULL)
        {
            if (temp->playerID == player)
            {
                if (temp == head)
                {
                    head = head->next;
                    head->prev = NULL;
                    delete temp;
                    return;
                }
                else if (temp == tail)
                {
                    tail = tail->prev;
                    tail->next = NULL;
                    delete temp;
                    return;
                }
                else
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                    return;
                }
            }
            temp = temp->next;
        }
    }
    void printTopNPlayers(int n)
    {
        PlayerGameCount *temp = head;
        while (temp != NULL)
        {
            cout << temp->playerID << " " << temp->gameCount << endl;
            temp = temp->next;
        }
    }
    void sortDescending()
    {
        // use selection sort
        PlayerGameCount *temp = head;
        while (temp != NULL)
        {
            PlayerGameCount *max = temp;
            PlayerGameCount *temp2 = temp->next;
            while (temp2 != NULL)
            {
                if (temp2->gameCount > max->gameCount)
                {
                    max = temp2;
                }
                temp2 = temp2->next;
            }
            // swap
            int tempCount = temp->gameCount;
            string tempPlayerID = temp->playerID;
            temp->gameCount = max->gameCount;
            temp->playerID = max->playerID;
            max->gameCount = tempCount;
            max->playerID = tempPlayerID;
            temp = temp->next;

        }
    }
};
struct GamesPlayedNode
{
    string gameID;
    float hoursPlayed;
    int achievementsUnlocked;
    GamesPlayedNode *left, *right;

    GamesPlayedNode(string gameID, float hoursPlayed, int achievementsUnlocked)
        : gameID(gameID), hoursPlayed(hoursPlayed), achievementsUnlocked(achievementsUnlocked), left(nullptr), right(nullptr) {}
    void printGamesPlayedNode()
    {
        cout << "gameID: " << gameID;
        cout << " hours played: " << hoursPlayed;
        cout << " achievements unlocked: " << achievementsUnlocked;
        cout << endl;
    }
};

class GamesPlayedTree
{
public:
    GamesPlayedNode *root;

    GamesPlayedNode *insertReal(GamesPlayedNode *root, string gameID, float hoursPlayed, int achievementsUnlocked)
    {
        if (root == NULL)
        {
            return new GamesPlayedNode(gameID, hoursPlayed, achievementsUnlocked);
        }
        if (gameID < root->gameID)
        {
            root->left = insertReal(root->left, gameID, hoursPlayed, achievementsUnlocked);
        }
        else if (gameID > root->gameID)
        {
            root->right = insertReal(root->right, gameID, hoursPlayed, achievementsUnlocked);
        }
        else
        {
            cout << "Duplicate gameID, can't insert twice: " << gameID << endl;
        }

        return root;
    }
    GamesPlayedTree()
    {
        root = NULL;
    }

    void insert(string gameID, float hoursPlayed, int achievementsUnlocked)
    {
        root = insertReal(root, gameID, hoursPlayed, achievementsUnlocked);
    }

    GamesPlayedNode *findgamesPlayed(GamesPlayedNode *node, string gamesPlayedID)
    {
        if (node == NULL || node->gameID == gamesPlayedID)
        {
            return node;
        }
        if (gamesPlayedID < node->gameID)
        {
            return findgamesPlayed(node->left, gamesPlayedID);
        }
        return findgamesPlayed(node->right, gamesPlayedID);
    }
    GamesPlayedNode *getMinimum(GamesPlayedNode *&root)
    {
        GamesPlayedNode *temp = root;
        while (temp && temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    GamesPlayedNode *removeNode(GamesPlayedNode *&root, string value)
    {

        GamesPlayedNode *temp;
        temp = findgamesPlayed(root, value);
        if (temp == NULL)
        {
            cout << "Value not found";
            return NULL;
        }
        if (value < root->gameID)
        {
            removeNode(root->left, value);
        }
        else if (value > root->gameID)
        {
            removeNode(root->right, value);
        }
        else
        {
            // Node found

            // no children
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                root = NULL;
            }
            // one child
            else if (root->left == NULL)
            {
                GamesPlayedNode *temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == NULL)
            {
                GamesPlayedNode *temp = root;
                root = root->left;
                delete temp;
            }
            // two children
            else
            {
                GamesPlayedNode *temp = getMinimum(root->right);
                root->gameID = temp->gameID;
                removeNode(root->right, temp->gameID);
            }
        }
    }
    void printTree(GamesPlayedNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        printTree(root->left);
        root->printGamesPlayedNode();
        printTree(root->right);
    }
    void preOrderTraversal(GamesPlayedNode *root)
    {
        preOrderTraversal(root->left);
        root->printGamesPlayedNode();
        preOrderTraversal(root->right);
    }
    void saveGamesPlayedData(GamesPlayedNode *root, ofstream &file)
    {
        if (root == NULL)
        {
            return;
        }
        saveGamesPlayedData(root->left, file);
        file << root->gameID << "," << root->hoursPlayed << "," << root->achievementsUnlocked << ",";
        saveGamesPlayedData(root->right, file);
    }

    bool hasPlayed(GamesPlayedNode *root, string gameID)
    {
        if (root == NULL)
        {
            return false;
        }
        else if (root->gameID == gameID)
        {
            return true;
        }
        else if (root->gameID < gameID)
        {
            return hasPlayed(root->right, gameID);
        }
        else if (root->gameID > gameID)
        {
            return hasPlayed(root->left, gameID);
        }
    }
    void showNLayers(GamesPlayedNode *root, int n)
    {
        if (n < 0)
        {
            cout << "number of layers exceeded\n";
            return;
        }
        if (root == NULL)
        {
            return;
        }
        if (n == 0)
        {
            root->printGamesPlayedNode();
            return;
        }
        showNLayers(root->left, n - 1);
        showNLayers(root->right, n - 1);
    }
    void showLayerNumber(GamesPlayedNode *root, string gameID, int n = 0)
    {
        if (n < 0)
        {
            cout << "invalid layer number\n";
            return;
        }
        if (root == NULL)
        {
            return;
        }
        if (root->gameID == gameID)
        {
            cout << "Layer: " << n << " ";
            root->printGamesPlayedNode();
        }
        showLayerNumber(root->left, gameID, n + 1);
        showLayerNumber(root->right, gameID, n + 1);
    }
    // setters
    void setGameID(GamesPlayedNode *node, string gameID)
    {
        node->gameID = gameID;
        // balance tree
    }
    void setHoursPlayed(GamesPlayedNode *node, float hoursPlayed)
    {
        node->hoursPlayed = hoursPlayed;
    }
    void setAchievementsUnlocked(GamesPlayedNode *node, int achievementsUnlocked)
    {
        node->achievementsUnlocked = achievementsUnlocked;
    }
    int getTotalGamesPlayed(GamesPlayedNode *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return 1 + getTotalGamesPlayed(root->left) + getTotalGamesPlayed(root->right);
    }
};

struct PlayerNode
{
    string playerID;
    string name;
    string phoneNumber;
    string email;
    string password;
    GamesPlayedTree gamesPlayed;
    PlayerNode *left, *right;

    PlayerNode(string playerID, string name, string phoneNumber, string email, string password)
        : playerID(playerID), name(name), phoneNumber(phoneNumber), email(email), password(password), left(nullptr), right(nullptr) {}
    void printPlayer()
    {
        cout << " ID: " << this->playerID;
        cout << " Name: " << this->name;
        cout << " number: " << this->phoneNumber;
        cout << " email: " << this->email;
        cout << " password" << this->password;
        cout << "\nGames Played \n";
        this->gamesPlayed.printTree(this->gamesPlayed.root);
    }
};

class PlayersTree
{
    public:
    PlayerNode *root;


    PlayerNode *insertReal(PlayerNode *node, string playerID, string name, string phoneNumber, string email, string password)
    {
        if (node == nullptr)
        {
            return new PlayerNode(playerID, name, phoneNumber, email, password);
        }
        if (playerID < node->playerID)
        {
            node->left = insertReal(node->left, playerID, name, phoneNumber, email, password);
        }
        else if (playerID > node->playerID)
        {
            node->right = insertReal(node->right, playerID, name, phoneNumber, email, password);
        }
        else
        {
            cout << "Duplicate playerID, can't insert twice: " << playerID << endl;
        }
        return node;
    }
    PlayersTree()
    {
        root = NULL;
    }

    void insert(string playerID, string name, string phoneNumber, string email, string password)
    {
        root = insertReal(root, playerID, name, phoneNumber, email, password);
    }
    PlayerNode *getMinimum(PlayerNode *&root)
    {
        PlayerNode *temp = root;
        while (temp && temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    PlayerNode *removeNode(PlayerNode *&root, string value)
    {

        PlayerNode *temp;
        temp = findPlayer(root, value);
        if (temp == NULL)
        {
            cout << "Value not found";
            return NULL;
        }
        if (value < root->playerID)
        {
            removeNode(root->left, value);
        }
        else if (value > root->playerID)
        {
            removeNode(root->right, value);
        }
        else
        {
            // Node found

            // no children
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                root = NULL;
            }
            // one child
            else if (root->left == NULL)
            {
                PlayerNode *temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == NULL)
            {
                PlayerNode *temp = root;
                root = root->left;
                delete temp;
            }
            // two children
            else
            {
                PlayerNode *temp = getMinimum(root->right);
                root->playerID = temp->playerID;
                removeNode(root->right, temp->playerID);
            }
        }
    }
    PlayerNode *findPlayer(PlayerNode *node, string playerID)
    {
        if (node == NULL || node->playerID == playerID)
        {
            return node;
        }
        if (playerID < node->playerID)
        {
            return findPlayer(node->left, playerID);
        }
        return findPlayer(node->right, playerID);
    }

    PlayerNode *findPlayer(string playerID)
    {
        return findPlayer(root, playerID);
    }
    void printTree(PlayerNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        printTree(root->left);
        root->printPlayer();
        printTree(root->right);
    }
    void printTree()
    {
        cout << endl;
        printTree(root);
        cout << endl;
    }
    // save tree in csv file
    void savePlayersData()
    {
        ofstream file("PlayersNew.txt");
        savePlayersDataReal(root, file);
        file.close();
    }
    void savePlayersDataReal(PlayerNode *root, ofstream &file)
    {
        if (root == NULL)
        {
            return;
        }
        savePlayersDataReal(root->left, file);
        file << root->playerID << "," << root->name << "," << root->phoneNumber << "," << root->email << "," << root->password << ",";
        root->gamesPlayed.saveGamesPlayedData(root->gamesPlayed.root, file);
        file << "\n";
        savePlayersDataReal(root->right, file);
    }
    void showNLayers(PlayerNode *root, int n)
    {
        if (n < 0)
        {
            cout << "number of layers exceeded\n";
            return;
        }
        if (root == NULL)
        {
            return;
        }
        if (n == 0)
        {
            root->printPlayer();
            return;
        }
        showNLayers(root->left, n - 1);
        showNLayers(root->right, n - 1);
    }
    void showLayerNumber(PlayerNode *root, string playerID, int n = 0)
    {
        if (n < 0)
        {
            cout << "invalid layer number\n";
            return;
        }
        if (root == NULL)
        {
            return;
        }
        if (root->playerID == playerID)
        {
            cout << "Layer: " << n << " ";
            root->printPlayer();
        }
        showLayerNumber(root->left, playerID, n + 1);
        showLayerNumber(root->right, playerID, n + 1);
    }
    void showPlayersPath(PlayerNode *root, string playerID)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->playerID << " ";
        if (root->playerID == playerID)
        {
            return;
        }
        showPlayersPath(root->left, playerID);
        showPlayersPath(root->right, playerID);
    }
    void setPlayerName(PlayerNode *node, string name)
    {
        node->name = name;
    }
    void setPlayerPhoneNumber(PlayerNode *node, string phoneNumber)
    {
        node->phoneNumber = phoneNumber;
    }
    void setPlayerEmail(PlayerNode *node, string email)
    {
        node->email = email;
    }
    void setPlayerPassword(PlayerNode *node, string password)
    {
        node->password = password;
    }
    void setPlayerID(PlayerNode *node, string playerID)
    {
        node->playerID = playerID;
        // balance tree
    }

    // top n players: find players who play the most games
    bool hasPlayed(PlayerNode *root, string gameID)
    {
        if (root == NULL)
        {
            return false;
        }
        return root->gamesPlayed.hasPlayed(root->gamesPlayed.root, gameID);
    }
    void showPlayerDetails(string playerID)
    {
        PlayerNode *temp = findPlayer(playerID);
        if (temp != NULL)
        {
            temp->printPlayer();
        }
        else
            cout << "Not found";
    }
    void showTopNPlayers(PlayerNode *root, List *l, int n)
    {
        if (root == NULL)
        {
            return;
        }
        showTopNPlayers(root->left, l, n);
        int totalGamesPlayed = root->gamesPlayed.getTotalGamesPlayed(root->gamesPlayed.root);
        l->insertAtHead(root->playerID, totalGamesPlayed);

        showTopNPlayers(root->right, l, n);
    }
};

void loadPlayerData(PlayersTree &players)
{
    ifstream file("Players.txt");
    string line;
    int limitCheck = 0;
    int limit=5;
    int random = rand() % 1000;
    int threshold = 14*10+100;
    while (getline(file, line) && limitCheck < limit && random>threshold)
    {
        //generate random number
        random = rand() % 1000;
        stringstream ss(line);
        limitCheck++;
        // Load Player information
        string playerID, name, phoneNumber, email, password;
        getline(ss, playerID, ',');
        getline(ss, name, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        // Insert player node
        players.insert(playerID, name, phoneNumber, email, password);

        // Find the newly inserted player node
        PlayerNode *playerNode = players.findPlayer(playerID);
        // Load games for this player
        string gameID;
        string hoursPlayed;
        string achievementsUnlocked;
        while (getline(ss, gameID, ',') && getline(ss, hoursPlayed, ',') && getline(ss, achievementsUnlocked, ','))
        {
            float hoursPlayedfloat = stof(hoursPlayed);
            int achievementsUnlockedint = stoi(achievementsUnlocked);
            playerNode->gamesPlayed.insert(gameID, hoursPlayedfloat, achievementsUnlockedint);
        }
    }
    file.close();
}

struct GameNode
{
    string gameID;
    string name;
    string developer;
    string publisher;
    float fileSizeGBs;
    int downloads;
    GameNode *right, *left;
    GameNode(string gameID, string name, string developer, string publisher, float fileSizeGBs, int downloads)
    {
        this->gameID = gameID;
        this->name = name;
        this->developer = developer;
        this->publisher = publisher;
        this->fileSizeGBs = fileSizeGBs;
        this->downloads = downloads;
        right = left = NULL;
    }
    void printGame()
    {
        cout << "gameID: " << gameID;
        cout << " name: " << name;
        cout << " developer: " << developer;
        cout << " publisher: " << publisher;
        cout << " size in GB: " << fileSizeGBs;
        cout << " downloads: " << downloads;
        cout << endl;
    }
};
class GamesTree
{
public:
    GameNode *root;

    GamesTree()
    {
        root = NULL;
    }

    GameNode *insert(GameNode *root, string gameID, string name, string developer, string publisher, float fileSizeGBs, int downloads)
    {
        if (root == NULL)
        {
            return new GameNode(gameID, name, developer, publisher, fileSizeGBs, downloads);
        }
        if (gameID < root->gameID)
        {
            root->left = insert(root->left, gameID, name, developer, publisher, fileSizeGBs, downloads);
        }
        else if (gameID > root->gameID)
        {
            root->right = insert(root->right, gameID, name, developer, publisher, fileSizeGBs, downloads);
        }
        else
        {
            cout << "Duplicate gameID, can't insert twice: " << gameID << endl;
        }
        return root;
    }
    GameNode *find(GameNode *root, string gameID)
    {
        GameNode *current = root;
        while (current != NULL)
        {
            if (current->gameID == gameID)
            {
                return current;
            }
            else if (current->gameID < gameID)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return NULL;
    }
    GameNode *getMinimum(GameNode *&root)
    {
        GameNode *temp = root;
        while (temp && temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    GameNode *removeNode(GameNode *&root, string value)
    {

        GameNode *temp;
        temp = find(root, value);
        if (temp == NULL)
        {
            cout << "Value not found";
            return NULL;
        }
        if (value < root->gameID)
        {
            removeNode(root->left, value);
            return root;
        }
        else if (value > root->gameID)
        {
            removeNode(root->right, value);
            return root;
        }
        else
        {
            // Node found

            // no children
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                root = NULL;
                return root;
            }
            // one child
            else if (root->left == NULL)
            {
                GameNode *temp = root;
                root = root->right;
                delete temp;
                return root;
            }
            else if (root->right == NULL)
            {
                GameNode *temp = root;
                root = root->left;
                delete temp;
                return root;
            }
            // two children
            else
            {
                GameNode *temp = getMinimum(root->right);
                root->gameID = temp->gameID;
                removeNode(root->right, temp->gameID);
                return root;
            }
        }
        return NULL;
    }
    void printTree(GameNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        printTree(root->left);
        root->printGame();
        printTree(root->right);
    }
    void showNLayers(GameNode *root, int n)
    {
        if (n < 0)
        {
            cout << "number of layers exceeded\n";
            return;
        }
        if (root == NULL)
        {
            return;
        }
        if (n == 0)
        {
            root->printGame();
            return;
        }
        showNLayers(root->left, n - 1);
        showNLayers(root->right, n - 1);
    }
    void showLayerNumber(GameNode *root, string gameID, int n = 0)
    {
        if (n < 0)
        {
            cout << "invalid layer number\n";
            return;
        }
        if (root == NULL)
        {
            return;
        }
        if (root->gameID == gameID)
        {
            cout << "Layer: " << n << " ";
            root->printGame();
        }
        showLayerNumber(root->left, gameID, n + 1);
        showLayerNumber(root->right, gameID, n + 1);
    }
    void loadGamesData()
    {
        ifstream file("Games.txt");
        string line;
        int count = 0;
        while (getline(file, line) && count < 5)
        {
            stringstream ss(line);
            count++;

            // get txt info
            string gameID, name, developer, publisher, fileSizeGBs, downloads;
            getline(ss, gameID, ',');
            getline(ss, name, ',');
            getline(ss, developer, ',');
            getline(ss, publisher, ',');
            getline(ss, fileSizeGBs, ',');
            getline(ss, downloads, ',');
            float fileSizeGBsFloat = stof(fileSizeGBs);
            int downloadsInt = stoi(downloads);
            // Insert game node
            root = insert(root, gameID, name, developer, publisher, fileSizeGBsFloat, downloadsInt);
        }

        file.close();
    }
    // save tree in csv file
    void saveGamesData()
    {
        ofstream file("GamesNew.txt");
        saveGamesDataReal(root, file);
        file.close();
    }
    void saveGamesDataReal(GameNode *root, ofstream &file)
    {
        if (root == NULL)
        {
            return;
        }
        saveGamesDataReal(root->left, file);
        file << root->gameID << "," << root->name << "," << root->developer << "," << root->publisher << "," << root->fileSizeGBs << "," << root->downloads << endl;
        saveGamesDataReal(root->right, file);
    }
    // pre order traversal and print path
    void showGamePath(GameNode *root, string gameID)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->gameID << " ";
        if (root->gameID == gameID)
        {
            return;
        }
        showGamePath(root->left, gameID);
        showGamePath(root->right, gameID);
    }

    // setters for game
    void setGameName(GameNode *node, string name)
    {
        node->name = name;
    }
    void setGameDeveloper(GameNode *node, string developer)
    {
        node->developer = developer;
    }
    void setGamePublisher(GameNode *node, string publisher)
    {
        node->publisher = publisher;
    }
    void setGameFileSizeGBs(GameNode *node, float fileSizeGBs)
    {
        node->fileSizeGBs = fileSizeGBs;
    }
    void setGameDownloads(GameNode *node, int downloads)
    {
        node->downloads = downloads;
    }
    void setGameID(GameNode *node, string gameID)
    {
        node->gameID = gameID;
        // balance tree
    }
};

int main()
{
    int seed = 232514;

    // Seed the random number generator
    srand(seed);
    PlayersTree players;
    GamesTree games;
    // load data
    loadPlayerData(players);
    games.loadGamesData();

    // print data
    // players.printTree(players.root);
    // games.printTree(games.root);

    // find data
    GameNode *temp = games.find(games.root, "9410009774");
    if (temp != NULL)
    {
        cout << "found";
    }
    else
        cout << "Not found";
    cout << "the path is \n";
    games.showGamePath(games.root, "9410009774");
    cout << endl;
    games.showNLayers(games.root, 1);
    // delete data

    games.removeNode(games.root, "9410009774");

    temp = games.find(games.root, "9410009774");
    if (temp != NULL)
    {
        cout << "found";
        cout << temp->gameID;
    }
    else
        cout << "Not found";
    // make new csv files to save data
    players.savePlayersData();
    games.saveGamesData();
    //show output of other functions
    players.showNLayers(players.root, 1);
    players.showLayerNumber(players.root, "9410009774");
    players.showPlayerDetails("9410009774");
    List l;
    players.showTopNPlayers(players.root, &l, 5);
    l.sortDescending();
    l.printTopNPlayers(5);

    return 0;
}
