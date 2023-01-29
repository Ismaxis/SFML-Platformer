#include "TestGame.h"

TestGame::TestGame(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,
                   const std::string& ip, const bool moving)
    : Game(mapPath, mapSheetPath, playerTexturePath, ip), moving(moving)
{}

TestGame::~TestGame() = default;

void TestGame::poolInputs(const Inputs& input)
{
    if (moving)
    {
        ++timeSinceDirectionChanged;
        if (timeSinceDirectionChanged > 20)
        {
            controls.isJump = rand() % 10 == 0;
            controls.grabDirection = rand() % 2 == 0 ? 1 : -1;
            controls.walkDirection = rand() % 2 == 0 ? 1 : -1;
            timeSinceDirectionChanged = 0;
        }
    }
}
