#include <bangtal>
using namespace bangtal;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	auto scene = Scene::create("산타 레이스", "Images/background.png");

	auto timer = Timer::create(10.f);
	showTimer(timer);

	int santaX = 0, santaY = 500;
	auto santa = Object::create("Images/santa.png", scene, santaX, santaY);

	auto startButton = Object::create("Images/start.png", scene, 590, 70);
	auto endButton = Object::create("Images/end.png", scene, 590, 20);
	auto playButton = Object::create("Images/play.png", scene, 610, 30, false);

	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// start game
		startButton->hide();
		endButton->hide();
		playButton->show();

		santaX = 0;
		santa->locate(scene, santaX, santaY);

		timer->set(10.f);
		timer->start();

		return true;
	});

	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
	});

	playButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		santaX = santaX + 30;
		santa->locate(scene, santaX, santaY);

		if (santaX > 1280) {
			playButton->hide();
			startButton->setImage("Images/restart.png");
			startButton->show();
			endButton->show();

			timer->stop();
			showMessage("선물 배달 성공~~~");
		}

		return true;
	});

	timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		playButton->hide();
		startButton->setImage("Images/restart.png");
		startButton->show();
		endButton->show();

		showMessage("헉, 선물 배달 실패!!!");
		return true;
	});

	startGame(scene);

	return 0;
}
