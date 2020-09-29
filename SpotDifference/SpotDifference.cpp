#include <bangtal>
using namespace bangtal;

class Rect {
	int centerX, centerY;
	int radius;

public:
	Rect(int cx, int cy, int r) : centerX(cx), centerY(cy), radius(r) {};
	bool checkIn(int x, int y) const {
		return (x > centerX - radius && x < centerX + radius && y > centerY - radius && y < centerY + radius);
	}
};

ScenePtr scene = nullptr;
const auto check_radius = 25;

class DifferencePoint {
	Rect left_rect, right_rect;
	ObjectPtr left_check, right_check;
	bool shown = false;

public:
	DifferencePoint(int lcx, int rcx, int cy, int r) : left_rect(lcx, cy, r), right_rect(rcx, cy, r) {
		left_check = Object::create("Images/check.png", scene, lcx - check_radius, cy - check_radius, false);
		right_check = Object::create("Images/check.png", scene, rcx - check_radius, cy - check_radius, false);
	}
	bool checkIn(int x, int y) const {
		return left_rect.checkIn(x, y) || right_rect.checkIn(x, y);
	}
	void show() {
		left_check->show();
		right_check->show();

		shown = true;
	}
	bool found() const { return shown; }
};

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	scene = Scene::create("틀린그림찾기", "Images/problem.png");

	auto problem = Object::create("Images/problem.png", scene, 0, 0);
	const auto num_of_differences = 7;

	DifferencePoint points[num_of_differences] = {
		{ 568, 1186, 594, 54 },
		{ 99, 717, 551, 17 },
		{ 383, 1001, 482, 16 },
		{ 401, 1019, 158, 27 },
		{ 61, 679, 255, 36 },
		{ 592, 1210, 421, 35 },
		{ 320, 938, 117, 13 },
	};

	auto count = 0;
	problem->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		auto wrong = true;
		for (auto i = 0; i < num_of_differences; ++i) {
			if (points[i].checkIn(x, y)) {
				if (!points[i].found()) {
					points[i].show();
					count++;
				}
				wrong = false;
			}
		}

		if (wrong) {
			endGame();
		}

		if (count == num_of_differences) {
			showMessage("성공, 다 찾았다!!!");
		}

		return true;
	});

	showMessage("좌우에 틀린 곳을 찾아보세요.");
	startGame(scene);

	return 0;
}