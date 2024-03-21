#include "BaseCollider.h"
#include "BoxCollider.h"
void BaseCollider::DrawProperties()
{
}
void BaseCollider::SceneDraw()
{
}
BoxCollider* BaseCollider::AsBoxCollider()
{
	return (BoxCollider*)this;
}
