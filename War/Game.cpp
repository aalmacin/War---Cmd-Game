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
			i += 6;
			playWar(i);
			bool war = true;
			do {
				cout << "War time" << endl;
				war = false;
			} while (war);
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

	if (playerCard.number > computerCard.number) {
		return 'P';
	}
	else if (computerCard.number > playerCard.number) {
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
		cout << "You Win this round. 2 cards." << endl << endl;
		break;
	case 'C':
		computerCards += cardCount;
		cout << "Computer Win this round. 2 cards." << endl << endl;
		break;
	case 'W':
		cout << "War!!!" << endl << endl;
		cout << "Draw 3 cards each." << endl;
		break;
	}
}

void Game::playWar(int index) {

}

string Game::displayCard(Card card) {
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