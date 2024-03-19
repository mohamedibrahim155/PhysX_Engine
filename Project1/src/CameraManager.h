#pragma once
#include "Camera.h"


class CameraManager
{
public:
	
	static CameraManager& GetInstance();
	static int CameraID;

	void AddCamera(Camera* camera);
	void RemoveCamera(Camera* camera);

	Camera* GetMainCamera();

	std::vector<Camera*> GetCameras();
private:

	std::vector<Camera*> listOfCameras;

	Camera* mainCamera = nullptr;

};

