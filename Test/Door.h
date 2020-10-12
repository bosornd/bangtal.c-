#pragma once
#include <Object.h>

#include <memory>

class Door;
typedef std::shared_ptr<Door> DoorPtr;

class Door : public bangtal::Object
{
public:
	static DoorPtr create(const std::string& openedImage, bangtal::ScenePtr locatedScene = nullptr, int x = 0, int y = 0,
		bangtal::ScenePtr connectedScene = nullptr, bool closed = false, const std::string& closedImage = "", bool shown = true);

protected:
	Door(const std::string& openedImage, bangtal::ScenePtr locatedScene, int x, int y, bangtal::ScenePtr connectedScene, bool closed, const std::string& closedImage, bool shown);

public:
	virtual bool onMouse(int x, int y, MouseAction action);
	bool getClosed() const { return _closed; };

protected:
	bool _closed;
	std::string _closedImage, _openedImage;
	bangtal::ScenePtr _connectedScene;
};