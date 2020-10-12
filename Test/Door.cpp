#include "Door.h"

using namespace std;
using namespace bangtal;

DoorPtr Door::create(const string& openedImage, ScenePtr locatedScene, int x, int y,
	ScenePtr connectedScene, bool closed, const string& closedImage, bool shown)
{
	auto object = DoorPtr(new Door(openedImage, locatedScene, x, y, connectedScene, closed, closedImage, shown));
	Object::add(object);

	return object;
}

Door::Door(const string& openedImage, ScenePtr locatedScene, int x, int y, ScenePtr connectedScene, bool closed, const string& closedImage, bool shown)
	: Object(closed ? closedImage : openedImage, locatedScene, x, y, shown), _connectedScene(connectedScene), _closed(closed), _closedImage(closedImage), _openedImage(openedImage)
{
}

bool Door::onMouse(int x, int y, MouseAction action)
{
	if (!Object::onMouse(x, y, action)) {
		if (_closed) {
			if (!_openedImage.empty())
				setImage(_openedImage);
			_closed = false;
		}
		else {
			if (_connectedScene)
				_connectedScene->enter();
			else endGame();
		}
	}

	return true;
}
