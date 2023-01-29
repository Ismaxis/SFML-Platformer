#pragma once
#include "../Game/Game.h"

class TestGame final : public Game
{
public:
    TestGame(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,
             const std::string& ip, bool moving);

    ~TestGame() override;

private:
    void poolInputs(const Inputs& input) override;

    int timeSinceDirectionChanged = 0;

    bool moving;
};
