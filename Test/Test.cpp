#include <bangtal>
#include <iostream>

#include "Item.h"
#include "Door.h"

using namespace bangtal;
using namespace std;

int main()
{
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");

	scene1->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		std::cout << (int)key << pressed << std::endl;
		return true;
	});

	auto door1 = Door::create("Images/문-오른쪽-열림.png", scene1, 800, 270, scene2, true, "Images/문-오른쪽-닫힘.png");
	if (door1->getClosed())
		showMessage("문이 닫혀있습니다.");

	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		auto door = std::dynamic_pointer_cast<Door>(object);
		showMessage(door->getClosed() ? "닫힘 --> 열림" : "열림 --> 장면 연결");
		return false;
	});

	auto door2 = Door::create("Images/문-왼쪽-열림.png", scene2, 320, 270, scene1);
	auto door3 = Door::create("Images/문-오른쪽-열림.png", scene2, 900, 270, nullptr, true, "Images/문-오른쪽-닫힘.png");

	auto arm = Item::create("Images/bear_arm.png", scene1, 320, 170);
	auto leg = Item::create("Images/bear_leg.png", scene1, 920, 170);
	auto body = Item::create("Images/bear_body.png", scene1, 520, 120);
	auto head = Item::create("Images/bear_head.png", scene1, 720, 120);

	auto noleg = Item::create("Images/bear_noleg.png");
	noleg->defineCombination(arm, body);
	auto nohead = Item::create("Images/bear_nohead.png");
	nohead->defineCombination(noleg, leg);
	auto bear = Item::create("Images/bear.png");
	bear->defineCombination(nohead, head);

	startGame(scene1);
}

