#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Represents a room in the game
struct Room {
    string name;
    string description;
    map<string, int> exits;
    vector<string> items;
};

// Represents the player in the game
struct Player {
    string currentRoom;
    vector<string> inventory;
};

// Function to initialize the game rooms
void initializeRooms(map<string, Room>& rooms) {
    Room livingRoom;
    livingRoom.name = "Living Room";
    livingRoom.description = "You are in a cozy living room.";
    livingRoom.exits["kitchen"] = 1;
    livingRoom.exits["bedroom"] = 2;
    livingRoom.items.push_back("key");

    Room kitchen;
    kitchen.name = "Kitchen";
    kitchen.description = "You are in a bright kitchen.";
    kitchen.exits["livingroom"] = 0;
    kitchen.items.push_back("apple");

    Room bedroom;
    bedroom.name = "Bedroom";
    bedroom.description = "You are in a comfortable bedroom.";
    bedroom.exits["livingroom"] = 0;
    bedroom.items.push_back("book");

    rooms["livingroom"] = livingRoom;
    rooms["kitchen"] = kitchen;
    rooms["bedroom"] = bedroom;
}

// Function to handle player movement
void movePlayer(Player& player, const string& direction, const map<string, Room>& rooms) {
    int roomIndex = rooms.at(player.currentRoom).exits.at(direction);
    if (roomIndex >= 0) {
        player.currentRoom = rooms.at(player.currentRoom).exits.at(direction);
        cout << "You are now in the " << rooms.at(player.currentRoom).name << "." << endl;
        cout << rooms.at(player.currentRoom).description << endl;
    } else {
        cout << "You cannot go that way." << endl;
    }
}

// Function to handle item collection
void collectItem(Player& player, const map<string, Room>& rooms) {
    Room currentRoom = rooms.at(player.currentRoom);
    for (const string& item : currentRoom.items) {
        player.inventory.push_back(item);
        cout << "You picked up a " << item << "." << endl;
    }
    currentRoom.items.clear();
}

// Main game loop
void playGame() {
    map<string, Room> rooms;
    initializeRooms(rooms);

    Player player;
    player.currentRoom = "livingroom";

    cout << "Welcome to the Adventure Game!" << endl;
    cout << rooms.at(player.currentRoom).description << endl;

    string command;
    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "quit") {
            cout << "Thanks for playing! Goodbye!" << endl;
            break;
        } else if (command == "look") {
            cout << rooms.at(player.currentRoom).description << endl;
        } else if (command.substr(0, 4) == "go to") {
            string direction = command.substr(5);
            movePlayer(player, direction, rooms);
        } else if (command == "pickup") {
            collectItem(player, rooms);
        } else if (command == "inventory") {
            cout << "You are carrying:";
            for (const string& item : player.inventory) {
                cout << " " << item;
            }
            cout << endl;
        } else {
            cout << "Invalid command. Type 'quit' to exit." << endl;
        }
    }
}

// Entry point of the program
int main() {
    playGame();
    return 0;
}
