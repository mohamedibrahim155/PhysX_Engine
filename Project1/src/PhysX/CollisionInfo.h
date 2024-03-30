#pragma once
#include <vector>
#include <glm/glm.hpp>
class CollisionInfo
{
public :
	std::vector<glm::vec3> listOfCollisionPoints;
	std::vector<glm::vec3> listOfCollisionNormals;
};

