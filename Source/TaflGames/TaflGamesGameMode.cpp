#include "TaflGamesGameMode.h"
#include "TaflGamesPlayerController.h"
#include "TaflGamesPawn.h"

ATaflGamesGameMode::ATaflGamesGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATaflGamesPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATaflGamesPlayerController::StaticClass();

	spawn->Add(3); spawn->Add(4); spawn->Add(5); spawn->Add(13);
	spawn->Add(27); spawn->Add(35); spawn->Add(36); spawn->Add(37);
	spawn->Add(43); spawn->Add(44); spawn->Add(45); spawn->Add(53);
	spawn->Add(67); spawn->Add(75); spawn->Add(76); spawn->Add(77);
}
