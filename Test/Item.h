#pragma once
#include <Object.h>

class Item : public bangtal::Object
{
public:
	static bangtal::ObjectPtr create(const std::string& image, bangtal::ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true);

protected:
	Item(const std::string& image, bangtal::ScenePtr scene, int x, int y, bool shown);

public:
	virtual bool onMouse(int x, int y, MouseAction action);
};

