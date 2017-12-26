#include "FBullsCowsGame.h"
#include <iostream>
#include <string>
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;

}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();					//assuming submitted Guess length is equal to Hidden Word length (this is checked in GetValidGuess in main.cpp)

	for (int32 i = 0; i < WordLength; i++)						//iterate through letters in a Guess word
	{
		for (int32 j = 0; j < WordLength; j++)					//iterate through all letters in a Hidden word
		{														//compare letter at [i] from a Guess word with every letter in Hidden word
			if ((Guess[i] == MyHiddenWord[j]) && (i == j)) {
				BullCowCount.Bulls++;
			}
			if ((Guess[i] == MyHiddenWord[j]) && (i != j)) {
				BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) {			//check if the game is won and set the Win variable accordingly
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bGameIsWon = false;
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_length;
	}
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)	{ return true; }

	TMap<char, bool> SeenLetters;

	for (auto Letter : Guess) {

		Letter = tolower(Letter);
		if (SeenLetters[Letter]) { return false; }
		else {
			SeenLetters[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		if (!islower(Letter)) { return false; }
	}

	return true;
}

