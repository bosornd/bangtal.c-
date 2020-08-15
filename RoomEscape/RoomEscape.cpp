#include <bangtal.h>
using namespace bangtal;

int main()
{
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");

	auto key = Object::create("Images/열쇠.png", scene1, 600, 150);
	key->setScale(.2f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		object->pick();
		return true;
	});

	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (!flowerpot_moved) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				object->locate(scene1, 450, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				object->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}
		return true;
	});

	auto open1 = false;
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open1 == false) {
			if (key->isHanded()) {
				object->setImage("Images/문-오른쪽-열림.png");
				open1 = true;
			}
			else {
				showMessage("열쇠가 필요해!!!");
			}
		}
		else {
			scene2->enter();
		}
		return true;
	});

	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
	});

	auto open3 = false;
	auto unlocked3 = false;
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 900, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open3) {
			endGame();
		}
		else if (unlocked3) {
			object->setImage("Images/문-오른쪽-열림.png");
			open3 = true;
		}
		else {
			showMessage("문이 잠겨있다.");
		}

		return true;
	});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		unlocked3 = true;
		showMessage("철커덕!!!");

		return true;
	});

	auto password = Object::create("Images/암호.png", scene2, 400, 100, false);

	auto lighted = true;
	auto button = Object::create("Images/스위치.png", scene2, 880, 440);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {
			scene2->setLight(.2f);
			password->show();
			lighted = false;
		}
		else {
			scene2->setLight(1.f);
			password->hide();
			lighted = true;
		}
		return true;
	});


	auto keypad = Object::create("Images/키패드.png", scene2, 885, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", door3);
		return true;
	});

	// startGame(장면)으로 게임을 시작한다.
	startGame(scene1);

	return 0;
}
