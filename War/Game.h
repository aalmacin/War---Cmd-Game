#pragma once
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

enum Suit {
	HEART,
	DIAMOND,
	CLUB,
	SPADE
};

struct Card
{
	int number;
	Suit suit;
};

class Game
{
public:
	Game();
	~Game();

	void start();

private:
	const int CARD_MAX = 13;
	const int PLAYERS = 2;
	const int WAR_CARDS = 3;

	Card cards[52];

	int playerCards;
	int computerCards;

	void createCards();
	string getSpecial(int);
	string getSuit(int);
	void shuffleCards();
	string displayCard(Card);
	void play();
	char checkWar(int);
	void assignWin(char, int=2);
	char playWar(int);
};

