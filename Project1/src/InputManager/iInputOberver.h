#pragma once

class iInputObserver
{
public:

	virtual ~iInputObserver() {};

	virtual void OnKeyPressed(const int& key) = 0;
	virtual void OnKeyReleased(const int& key) = 0;
	virtual void OnKeyHold(const int& key) = 0;

};
