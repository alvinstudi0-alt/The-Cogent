// DDNPPROJECT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// DDNPPROJECT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
#include <cstdio>
using namespace std;
string location = "Maintenance Room";
string direction;
int row;
int column;
char UserName[20]{};
int health;
int firewall;
int attack;
int defense;
int enemyDamage;
int movesavailable = 4;
bool gameRunning = true;
bool northCleared = false;
bool southCleared = false;
bool eastCleared = false;
bool westCleared = false;
bool legalCleared = false;
int progress = 0;
bool LoadGameData();
void initialize();
void MainMenu();
void showMap();
void navigate();
void startBattle();
void SaveGame();
void showStats();
void ResetGame();
void RestartGame();
void checkVictory();
void showMonster();
void pauseGame();
void startBiochemistryTask();
void startFinanceTask();
void startMathTask();
void StartLegalTask();
void end();

int main() {
	srand(static_cast<unsigned int>(std::time(nullptr)));
	MainMenu();
	while (gameRunning) {
		pauseGame();
		showMap();
		navigate();
		checkVictory();
	}
	SaveGame(); end();
	return 0;
}

static void slowline(const char text[])
{
	cout << text << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void MainMenu() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11); // Set text color to light cyan
	slowline("The year is 2045.");
	SetConsoleTextAttribute(hConsole, 14); // Set text color to yellow
	slowline("A highly advanced AI named The Oracle-");
	SetConsoleTextAttribute(hConsole, 10); // Set text color to light green
	slowline("designed to manage global legal disputes and secure financial datasets-");
	SetConsoleTextAttribute(hConsole, 12); // Set text color to light red
	slowline("has been compromised.");
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE)); // Ensure we're writing to the console
	SetConsoleTextAttribute(hConsole, 9); // Set text color to light blue
	slowline("You are the last Cyber Auditor in this world.");
	slowline("Your job is to dive into the text-based mainframe-");
	slowline("and navigate corrupted server notes to find the source of the breach and stop it!");
	SetConsoleTextAttribute(hConsole, 5); // Set text color to purple
	std::this_thread::sleep_for(std::chrono::milliseconds(1200));
	cout << "Stay...\n";
	cout << "_________                              __\n";
	cout << "\\_   ___ \\  ____   ____   ____   _____/  |_\n";
	cout << "/    \\  \\/ /  _\\ / ___\\_/ __  \\ /    \\   __\\\n";
	cout << "\\     \\___(  <_> ) /_/  >  ___/|   |  \\  |\n";
	cout << " \\______  /\\____/\\___  / \\___  >___|  /__| \n";
	cout << "        \\/      /_____/      \\/     \\/      \n";
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	cout << "1. Start New Game\n";
	cout << "2. Load Game\n";
	cout << "3. Reset Game\n";
	cout << "4. Exit\n";
	int choice;
	cin >> choice;
	cin.ignore();
	switch (choice) {
	case 1:
		initialize();
		break;
	case 2:
		if (LoadGameData()) {
			showStats();
			cout << "Game loaded successfully!\n";
			cout << "Welcome back, " << UserName << "! Resuming your mission to secure The Oracle.\n";
		}
		else if (!LoadGameData()) {
			initialize();
		}
		else {
			cout << "No save file found. Starting a new game.\n";
			initialize();
		}
		break;
	case 3:
		ResetGame();
		break;
	case 4:
		gameRunning = false;
		break;
	default:
		MainMenu();
		break;
	}
}

void initialize() {
	while (true) {
		cout << "Enter your Cyber Auditor username (max. 20 char): ";

		if (cin.getline(UserName, 20)) {
			break;
		}
		if (!cin.getline(UserName, 20)) {
			cout << "Input error! Please try again.\n";
			cin.clear();
			while (cin.get() != '\n');
		}

		cout << "Input error! Please try again.\n";
		cin.clear();
		while (cin.get() != '\n');
	}
	cout << "Welcome, " << UserName << "! Your mission is to secure The Oracle and stop the breach.\n";
	cout << "Press Enter to initialize your cyber avatar...";
	cin.get();
	cout << "Initializing your cyber avatar...\n";
	health = 100;
	firewall = 50;
	attack = 20;
	defense = 15;
	progress = 0;
	movesavailable = 4;
	northCleared = southCleared = eastCleared = westCleared = false;
	cout << "Initialization complete! Your stats:\n";
	showStats();
}
void pauseGame() {
	cout << "\nPress Enter to continue...";
	cin.ignore(100, '\n');  // clear leftover input
	cin.get();               // wait for Enter
}
void showMap() {
	cout << "                        _____________\n";
	cout << "                        |            |\n";
	cout << "                        |  North     |\n";
	cout << "                        |  Server    |\n";
	cout << "                        |  Room      |\n";
	cout << "                        |____________|\n";
	cout << "                              ||\n";
	cout << "                              ||\n";
	cout << " _____________      __________||___________     _____________\n";
	cout << "|             |    |                       |   |             |\n";
	cout << "|  West       |    |     Maintenance       |   |  East       |\n";
	cout << "|  Server     |====|     Room              |===|  Server     |\n";
	cout << "|  Room       |    |                       |   |  Room       |\n";
	cout << "|_____________|    |_______________________|   |_____________|\n";
	cout << "                              ||\n";
	cout << "                              ||\n";
	cout << "                        ______||_____\n";
	cout << "                        |            |\n";
	cout << "                        |  South     |\n";
	cout << "                        |  Server    |\n";
	cout << "                        |  Room      |\n";
	cout << "                        |____________|\n";
	cout << "\nCurrent Location: " << location << endl;
	cout << "Map: [N] North Server Room | [S] South Server Room | [E] East Server Room | [W] West Server Room\n";
	cout << "Each server room may contain corrupted data nodes. Be prepared!\n";
	cout << "Navigate through the server rooms to find and secure The Oracle.\n";
	cout << "Good luck, Cyber Auditor!\n";
	cout << "---------------------------------------------\n";
	if (northCleared) cout << "North Server Room: Secured\n";
	else cout << "North Server Room: Corrupted\n";
	if (southCleared) cout << "South Server Room: Secured\n";
	else cout << "South Server Room: Corrupted\n";
	if (eastCleared) cout << "East Server Room: Secured\n";
	else cout << "East Server Room: Corrupted\n";
	if (westCleared) cout << "West Server Room: Secured\n";
	else cout << "West Server Room: Corrupted\n";
	cout << "Moves Available: " << movesavailable << endl;
	cout << "Progress: " << progress << "/4 server rooms cleared\n";
}
void navigate() {
	if (movesavailable <= 0) {
		cout << "No moves remaining\n";
		gameRunning = false;
		return;
	}
	if (location == "Maintenance Room") {
		cout << "You are in the Maintenance Room. You can access any server room from here.\n";
	}
	cout << "Enter direction to navigate (";
	bool first = true;
	if (!northCleared) {
		cout << "N";
		first = false;
	}
	if (!southCleared) {
		if (!first) cout << "/";
		cout << "S";
		first = false;
	}
	if (!eastCleared) {
		if (!first) cout << "/";
		cout << "E";
		first = false;
	}
	if (!westCleared) {
		if (!first) cout << "/";
		cout << "W";
	}
	cout << ") or type 'exit' to quit: ";	// Read full line to allow 'exit'
	getline(cin, direction);

	if (direction == "N" || direction == "n") {
		location = "North Server Room";
		if (!northCleared) startBattle();
		else cout << "This server room is already secured.\n";
	}
	else if (direction == "S" || direction == "s") {
		location = "South Server Room";
		if (!southCleared) startBiochemistryTask();
		else cout << "This server room is already secured.\n";
	}
	else if (direction == "E" || direction == "e") {
		location = "East Server Room";
		if (!eastCleared) startFinanceTask();
		else cout << "This server room is already secured.\n";
	}
	else if (direction == "W" || direction == "w") {
		location = "West Server Room";
		if (!westCleared) startMathTask();
		else cout << "This server room is already secured.\n";
	}
	else if (direction == "exit" || direction == "EXIT" || direction == "Exit") {
		gameRunning = false;
		return;
	}
	else {
		cout << "Invalid direction! Try again.\n";
		return;
	}
}
void showMonster() {
	SetConsoleOutputCP(CP_UTF8); //function used to change the active output code page for the current console to UTF-8.
	cout << "     ███████████████████████\n";
	cout << "  ███░░░░░░░░░░░░░░░░░░░░░███\n";
	cout << " ██░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░██\n";
	cout << "██░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░██\n";
	cout << "██░▒▓▓██████▓▓▓▓▓▓██████▓▓▒▒░░██\n";
	cout << "██░▒▓▓██████▓▓▓▓▓▓██████▓▓▒▒░░██\n";
	cout << "██░▒▓▓███  ███▓▓▓▓▓███  ███▓▒▒░░██\n";
	cout << "██░▒▓▓███  ███▓▓▓▓▓███  ███▓▒▒░░██\n";
	cout << "▒▒▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▒▒\n";
	cout << "▒▒▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▒▒\n";
	cout << "   ▒▒▒▓▓███▓▓▓▓▓▓▓▓▓▓▓▓███▓▓▒▒▒\n";
	cout << "     ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n";
	cout << "     ███████████████████████\n";
}
void startBattle() {
	system("cls");            // Clear console for better readability at start of battle
	cout << "Entering " << location << "...\n";
	cout << "Scanning for corrupted data nodes...\n";
	showMonster();
	cout << "Warning: Corrupted data nodes detected in this server room!\n";

	// Initialize enemy health
	int enemyHealth = 50 + rand() % 51; // Random health between 50 and 100
	cout << "You encounter a corrupted data node with " << enemyHealth << " health!\n";

	// Battle loop; supports iterative restart on player death
	while (true) {
		// Loop the combat until either the player or enemy is defeated
		while (health > 0 && enemyHealth > 0) {
			int block = 0; // resets each round
			cout << "Choose an action: (1) Attack (2) Defend (3) Firewall\n";
			int action;
			if (!(cin >> action)) {
				// invalid (non-numeric) input
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input! Enter 1, 2, or 3.\n";
				continue;
			}
			cin.ignore(1000, '\n'); // clear rest of line

			if (action == 1) {
				int damage = attack + rand() % 11; // Random damage between attack and attack+10
				enemyHealth -= damage;
				if (enemyHealth < 0) enemyHealth = 0;
				cout << "You deal " << damage << " damage to the data node. It has " << enemyHealth << " health left.\n";
				if (enemyHealth <= 0) {
					cout << "You have defeated the corrupted data node!\n";
					// Only mark north cleared if this battle corresponds to that room
					if (location == "North Server Room" && !northCleared) {
						northCleared = true;
						progress++;
						movesavailable--;
					}
					// Exit the battle function after victory
					return;
				}
			}
			else if (action == 2) {
				block = defense + rand() % 6; // Random block between defense and defense+5
				cout << "You prepare to block. You will block up to " << block << " damage on the next attack.\n";
			}
			else if (action == 3) {
				if (firewall > 0) {
					block = firewall + rand() % 11; // Random block between firewall and firewall+10
					firewall -= 10; // Firewall can be used a limited number of times
					if (firewall < 0) firewall = 0;
					cout << "You activate your firewall! You will block up to " << block << " damage on the next attack. Firewall strength is now " << firewall << ".\n";
				}
				else {
					cout << "Your firewall is depleted! You cannot use it.\n";
					block = 0;
				}
			}
			// Enemy attack
			enemyDamage = 15 + rand() % 36; // Random enemy damage between 15 and 50
			enemyDamage -= block;
			if (enemyDamage <= 0) enemyDamage = 0;
			health -= enemyDamage;
			if (health <= 0) {
				health = 0;
				system("cls");            // Clear console for better readability on defeat
				system("color 4F");      // Change text color to red on defeat
				cout << "The data node attacks you for " << enemyDamage << " damage. You have " << health << " health left.\n";
				cout << "You have been defeated by the corrupted data node...\n";
				// break to handle retry prompt outside inner combat loop
				break;
			}
			else {
				cout << "The data node attacks you for " << enemyDamage << " damage. You have " << health << " health left.\n";
			}
		}

		// If enemy was defeated inside inner loop, function already returned.
		// If player died, offer retry
		if (health <= 0) {
			cout << "Try again? (Y/N): ";
			char retry;
			if (!(cin >> retry)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Exiting battle.\n";
				gameRunning = false;
				return;
			}
			cin.ignore(1000, '\n');

			if (retry == 'Y' || retry == 'y') {
				RestartGame();
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 5); // Set text color to purple
				cout << "System rebooting...\n";
				showMonster();
				enemyHealth = 50 + rand() % 51;
				cout << "Re-entering " << location << "...\n";
				cout << "You encounter a corrupted data node with " << enemyHealth << " health!\n";
				// continue outer while(true) to re-enter combat
				continue;
			}
			else {
				gameRunning = false;
				return;
			}
		}
		else {
			// health > 0 but loop ended (shouldn't normally happen), exit
			return;
		}
	}
}

void startBiochemistryTask() {
	system("cls");            // Clear console for better readability at start of task
	cout << "Entering South Server Room...\n";
	location = "South Server Room";
	cout << "\nYou are now in the " << location << endl;
	cout << "Accessing Biochemical Data Storage...\n";
	cout << "This server room contains the genetic data storage for The Oracle.\n";
	cout << "Scanning for corrupted biochemical data...\n";
	cout << "Biochemical Subsystem Corrupted.\n";
	cout << "Repair DNA Encoding using complementary base pairing.\n";
	cout << "Rules: A-T and G-C\n\n";

	string dna = "ATGCGTAC";
	string answer;

	// Outer loop lets us restart the task iteratively if the player chooses to reboot
	for (;;) {
		while (health > 0) {
			cout << "Corrupted DNA Strand: " << dna << endl;
			cout << "Enter the correct complementary strand: ";

			if (!(cin >> answer)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter a DNA string using A, T, G, C.\n";
				continue;
			}
			cin.ignore(1000, '\n');

			string correct = "";
			for (char base : dna) {
				if (base == 'A') correct += 'T';
				else if (base == 'T') correct += 'A';
				else if (base == 'G') correct += 'C';
				else if (base == 'C') correct += 'G';
				else correct += '?'; // unexpected char
			}

			if (answer == correct) {
				cout << "Correct! Genetic sequence restored.\n";
				if (!southCleared) {
					southCleared = true;
					progress++;
					movesavailable--;
				}
				return;
			}
			else {
				cout << "Incorrect sequence. The subsystem remains corrupted.\n";
				// apply penalty
				health -= 10;
				if (health < 0) health = 0;
				cout << "\nSystem penalty applied. You have " << health << " health left.\n";
			}
		}
		system("cls");            // Clear console for better readability on defeat
		system("color 4F");      // Change text color to red on defeat
		cout << "Your health has dropped to zero. You have been overwhelmed by the corrupted data...\n";
		cout << "Try again? (Y/N): ";
		char retry;
		if (!(cin >> retry)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Exiting task.\n";
			gameRunning = false;
			return;
		}
		cin.ignore(1000, '\n');

		if (retry == 'Y' || retry == 'y') {
			RestartGame();
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 5); // Set text color to purple
			cout << "System rebooting...\n";
			// Loop will restart the task with reset health
			continue;
		}
		else {
			gameRunning = false;
			return;
		}
	}
}

void startFinanceTask() {
	system("cls");            // Clear console for better readability at start of task
	cout << "Entering East Server Room...\n";
	location = "East Server Room";
	cout << "\nYou are now in the " << location << endl;
	cout << "Accessing Financial Data Storage...\n";
	cout << "This server room contains the financial forecasting models for The Oracle.\n";
	cout << "Scanning for corrupted financial data...\n";
	cout << "Global Financial Forecast System Corrupted.\n";
	while (health > 0) {
		int price = rand() % 51 + 50;         // Random price between 50 - 100
		int inflationPercent = rand() % 6 + 5; // Random inflation between 5% - 10%
		int answer;
		cout << "Original asset value: $" << price << endl;
		cout << "Inflation rate: " << inflationPercent << "%\n";
		cout << "After one year, what is the new value?\n";
		cout << "Enter your answer: ";
		cin >> answer;

		int increase = price * inflationPercent / 100;
		int correct = price + increase;

		if (answer == correct) {
			cout << "Correct. Inflation model restored.\n";
			if (!eastCleared) {
				eastCleared = true;
				progress++;
				movesavailable--;
			}
			break;
		}
		else {
			cout << "Incorrect. The economic forecast remains unstable.\n";
			health -= 9;
			health--;
			cout << "\nSystem penalty applied. You have " << health << " health left.\n";
		}
	}
	if (health <= 0) {
		health = 0; // fix: ensure health is set to zero when it falls below 0
		system("cls");            // Clear console for better readability on defeat
		system("color 4F");      // Change text color to red on defeat
		cout << "Your health has dropped to zero. You have been overwhelmed by the corrupted data...\n";
		cout << "Try again? (Y/N): ";
		char retry;
		cin >> retry;
		cin.ignore(1000, '\n');
		if (retry == 'Y' || retry == 'y') {
			RestartGame();
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 5); // Set text color to purple
			cout << "System rebooting...\n";
			startFinanceTask(); // Restart the finance task immediately after rebooting
		}
		else {
			gameRunning = false;
		}
	}
}
void startMathTask() {
	system("cls");            // Clear console for better readability at start of task
	cout << "Entering West Server Room...\n";
	cout << "Core Encryption Algorithm Corrupted.\n";
	cout << "You must solve the logic sequence to unlock the system.\n\n";
	while (health > 0) {
		int a = rand() % 10 + 5;   // 5–14
		int b = rand() % 5 + 2;    // 2–6
		int c = rand() % 20 + 10;  // 10–29

		int answer;

		cout << "Security Equation:\n";
		cout << "(" << a << " + " << b << ") * 2 - " << c << " = ?\n";
		cout << "Decrypt the final access code: ";
		cin >> answer;
		cin.ignore();

		int correct = (a + b) * 2 - c;

		if (answer == correct) {
			cout << "Access code accepted.\n";
			cout << "Mathematical engine restored.\n";
			if (!westCleared) {
				westCleared = true;
				progress++;
				movesavailable--;
			}
			break;
		}
		else {
			cout << "Access denied.\n";
			cout << "The encryption remains active.\n";
			health -= 9;
			health--;
			cout << "\nSystem penalty applied. You have " << health << " health left.\n";
		}
	}
	if (health <= 0) {
		health = 0; // fix: ensure health is set to zero when it falls below 0
		system("cls");            // Clear console for better readability on defeat
		system("color 4F");      // Change text color to red on defeat
		cout << "Your health has dropped to zero. You have been overwhelmed by the corrupted data...\n";
		cout << "Try again? (Y/N): ";
		char retry;
		cin >> retry;
		cin.ignore(1000, '\n');
		if (retry == 'Y' || retry == 'y') {
			RestartGame();
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 5); // Set text color to purple
			cout << "System rebooting...\n";
			startMathTask(); // Restart the math task immediately after rebooting
		}
		else {
			gameRunning = false;
		}
	}
}

void StartLegalTask() {
	cout << "Entering Legal Arbitration Core...\n";
	cout << "The Oracle's legal dispute engine is corrupted.\n";
	cout << "Analyze the case and choose the correct ruling.\n";

	cout << "Case:\n";
	cout << "A supplier agreed to deliver 100 processors in 30 days.\n";
	cout << "They delivered all 100 in 45 days.\n";
	cout << "The contract states: 'Time is of the essence.'\n\n";

	cout << "What is the correct legal outcome?\n";
	cout << "1) No breach\n";
	cout << "2) Minor breach\n";
	cout << "3) Material breach\n";
	cout << "4) Criminal violation\n";

	int answer;
	cin >> answer;
	cin.ignore();

	if (answer == 3) {
		system("cls");            // Clear console for better readability at start of task
		cout << "Correct. Legal engine restored.\n";
		cout << "\nAll server rooms secured.\n";
		cout << "The Oracle has been restored\n";
		legalCleared = true;
	}
	else {
		cout << "Incorrect ruling. Judicial logic unstable.\n";
		health -= 9;
		health--;
		cout << "\nSystem penalty applied. You have " << health << " health left.\n";
	}
	if (health < 0) {
		health = 0; // fix: ensure health is set to zero when it falls below 0
		system("cls");            // Clear console for better readability on defeat
		system("color 4F");      // Change text color to red on defeat
		cout << "Your health has dropped to zero. You have been overwhelmed by the corrupted data...\n";
		cout << "Try again? (Y/N): ";
		char retry;
		cin >> retry;
		cin.ignore(1000, '\n');
		if (retry == 'Y' || retry == 'y') {
			RestartGame();
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 5); // Set text color to purple
			cout << "System rebooting...\n";
		}
		else {
			gameRunning = false;
		}
	}
}
void SaveGame() {
	ofstream saveFile("savegame.txt");
	if (saveFile.is_open()) {
		// Write one item per line in a fixed order
		saveFile << UserName << '\n';
		saveFile << location << '\n';
		saveFile << health << '\n';
		saveFile << firewall << '\n';
		saveFile << attack << '\n';
		saveFile << defense << '\n';
		saveFile << progress << '\n';
		saveFile << movesavailable << '\n';
		// Write booleans as integers for portability
		saveFile << (northCleared ? 1 : 0) << '\n';
		saveFile << (southCleared ? 1 : 0) << '\n';
		saveFile << (eastCleared ? 1 : 0) << '\n';
		saveFile << (westCleared ? 1 : 0) << '\n';
		saveFile << (legalCleared ? 1 : 0) << '\n';
		saveFile.close();
	}
	else {
		cout << "Unable to save game.\n";
	}
}

bool LoadGameData() {
	ifstream loadFile("savegame.txt");
	if (!loadFile.is_open())
		return false;

	loadFile.getline(UserName, 20);
	getline(loadFile, location);

	loadFile >> health;
	loadFile >> firewall;
	loadFile >> attack;
	loadFile >> defense;
	loadFile >> progress;
	loadFile >> movesavailable;

	int val;
	loadFile >> val; northCleared = val;
	loadFile >> val; southCleared = val;
	loadFile >> val; eastCleared = val;
	loadFile >> val; westCleared = val;
	loadFile >> val; legalCleared = val;

	loadFile.close();
	return true;
}
void ResetGame() {
	if (remove("savegame.txt") == 0) {
		cout << "Save file deleted successfully.\n";
		initialize();
	}
	else {
		cout << "No save file found to delete.\n";
		initialize();
	}
}

void RestartGame() {
	system("color 07");  // reset to default
	system("cls");       // clear console
	health = 100;
	firewall = 50;
	attack = 20;
	defense = 15;
	progress = 0;
	movesavailable = 4;
	northCleared = southCleared = eastCleared = westCleared = false;
}

void showStats() {
	cout << "Username: " << UserName << endl;
	cout << "Health: " << health << endl;
	cout << "Firewall: " << firewall << endl;
	cout << "Attack: " << attack << endl;
	cout << "Defense: " << defense << endl;
}

void checkVictory() {
	if (progress == 4) {
		cout << "\nCongratulations, " << UserName << "! You have secured all server rooms and restored The Oracle!\n";
		cout << "However, there is one last issue...\n";
		SaveGame();
		gameRunning = false;
		pauseGame();
		system("cls");            // Clear console for better readability at start of task
		showMonster();
		cout << "!Urgent System Alert!\n";
		cout << "\nThe Oracle's legal subsystem is still corrupted.\n";
		cout << "there is a Legal Arbitration task to complete!.\n";
		StartLegalTask();
	}
}

void end() {
	cout << "\nThank you for playing!\n";
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

