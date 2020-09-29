#pragma once
#include <Object.h>

class Door : public bangtal::Object
{
public:
	static bangtal::ObjectPtr create(const std::string& openedImage, bangtal::ScenePtr locatedScene = nullptr, int x = 0, int y = 0,
		bangtal::ScenePtr connectedScene = nullptr, bool closed = false, const std::string& closedImage = "", bool shown = true);

protected:
	Door(const std::string& openedImage, bangtal::ScenePtr locatedScene, int x, int y, bangtal::ScenePtr connectedScene, bool closed, const std::string& closedImage, bool shown);

public:
	virtual bool onMouse(int x, int y, MouseAction action);

protected:
	bool _closed;
	std::string _closedImage, _openedImage;
	bangtal::ScenePtr _connectedScene;
};