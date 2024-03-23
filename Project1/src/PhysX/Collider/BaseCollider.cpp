#include "BaseCollider.h"
#include "BoxCollider.h"

BoxCollider* BaseCollider::AsBoxCollider()
{
	return (BoxCollider*)this;
}
