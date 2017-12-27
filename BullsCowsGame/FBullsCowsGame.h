#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all variables initialized to 0
enum class EGuessStatus {
	Invalid_status,
	OK,
	Not_isogram,
	Not_lowercase,
	Wrong_length,
};

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	FBullCowCount SubmitValidGuess(FString Guess);
	void SetMaxTries(int32);

	void Reset();	// TODO make a more rich return 
	EGuessStatus CheckGuessValidity(FString Guess) const;

private:
	//initialization is in the constructor
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};