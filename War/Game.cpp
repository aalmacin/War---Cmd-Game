#include "Game.h"

Game::Game() :playerCards(0), computerCards(0)
{
}


Game::~Game()
{
}

void Game::start() 
{
	createCards();
	bool play = true;
	do {
		playerCards = 0;
		computerCards = 0;

		string key;

		cout << "Play War? (1 to play, any key to exit): ";
		cin >> key;

		play = (key == "1");

		if (play) {
			Game::play();
		}

	} while (play);
}

void Game::play() 
{
	shuffleCards();

	cout << endl << "-------------------- WAR GAME --------------------" << endl << endl;

	for (int i = 0; i < CARD_MAX * 4; i += 2) {

		cout << endl << "------------------------ START -----------------------" << endl;

		char winner = checkWar(i);

		assignWin(winner);

		if (winner == 'W') {
			bool war = true;
			const int CARD_COUNT = 6;
			int cardCount = 2;
			do {
				i += CARD_COUNT;
				cardCount += CARD_COUNT;

				winner = playWar(i);
				assignWin(winner, cardCount);
			} while (winner == 'W');
		}


		cout << "TOTAL CARDS" << endl;
		cout << "-------------" << endl;
		cout << "Player Cards:\t" << playerCards << endl;
		cout << "Computer Cards:\t" << computerCards << endl << endl;

		cin.ignore(256, '\n');
		cout << "Next Round?" << endl;

		cin.get();
	}
}

char Game::checkWar(int index) {
	Card playerCard = cards[index];
	Card computerCard = cards[index + 1];

	string formattedPlayerCard = displayCard(playerCard);
	string formattedComputerCard = displayCard(computerCard);

	cout << "Your Card \t" << "Computer's Card" << endl;
	cout << formattedPlayerCard << "\t" << formattedComputerCard << endl << endl;

	if (playerCard > computerCard) {
		return 'P';
	}
	else if (playerCard < computerCard) {
		return 'C';
	}
	else {
		return 'W';
	}
}

void Game::assignWin(char winner, int cardCount) {
	switch (winner) {
	case 'P':
		playerCards += cardCount;
		cout << "You Win this round. " << cardCount << " cards." << endl << endl;
		break;
	case 'C':
		computerCards += cardCount;
		cout << "Computer Win this round. " << cardCount << " cards." << endl << endl;
		break;
	case 'W':
		cout << "War!!!" << endl << endl;
		cout << "Draw 3 cards each." << endl;
		cin.get();
		break;
	}
}

char Game::playWar(int index) {
	char winner = checkWar(index);
	return winner;
}

string Game::displayCard(const Card card) {
	return getSpecial(card.number) + " of " + getSuit(card.suit);
}

void Game::createCards() 
{
	int counter = 0;
	for (int i = 1; i <= CARD_MAX; i++) {
		for (int suit = HEART; suit <= SPADE; suit++) {
			cards[counter] = { i, static_cast<Suit>(suit)};
			counter++;
		}
	}
}

void Game::shuffleCards() 
{
	random_shuffle(begin(cards), end(cards));
}

string Game::getSpecial(int num) 
{
	switch (num) {
	case 1:
		return "Ace";
		break;
	case 11:
		return "Jack";
		break;
	case 12:
		return "Queen";
		break;
	case 13:
		return "King";
		break;
	default:
		return to_string(num);
		break;
	}
}

string Game::getSuit(int num)
{
	switch (num) {
	case HEART:
		return "Hearts";
		break;
	case DIAMOND:
		return "Diamonds";
		break;
	case SPADE:
		return "Spades";
		break;
	case CLUB:
		return "Clubs";
		break;
	}
}

bool Card::operator < (const Card &f) const { 
	return number < f.number; 
}

bool Card::operator > (const Card &f) const { 
	return number > f.number; 
}

bool Card::operator == (const Card &f) const { 
	return number == f.number; 
}