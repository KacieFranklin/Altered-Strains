#pragma once

class Player
{
public:

	Player();
	
 void takeDamage();
 void regenHealth();
 void useItems();
 void getItems();
 void getSerums();


private:

	int health;
	int selectedSerums[5];





};
