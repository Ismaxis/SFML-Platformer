#pragma once
struct PlayerControls
{
	int walkDirection = 0; // Directions: -1 - left, 1 - right
	int grabDirection = 0; // Directions: -1 - up, 1 - down

	bool isJump = false;
};