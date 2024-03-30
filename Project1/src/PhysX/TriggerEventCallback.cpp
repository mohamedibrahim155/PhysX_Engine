#include "TriggerEventCallback.h"
#include <iostream>
#include "PhysXObject.h"
void CollisionEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
    std::cout << "On Contraint break" << std::endl;
}

void CollisionEventCallback::onWake(PxActor** actors, PxU32 count)
{
    std::cout << "On wake" << std::endl;
}

void CollisionEventCallback::onSleep(PxActor** actors, PxU32 count)
{
    std::cout << "On Sleep" << std::endl;
}

void CollisionEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{

    std::vector<PxContactPairPoint> contactPoints;

    PhysXObject* collisionObject = static_cast<PhysXObject*>(pairHeader.actors[0]->userData);
    PhysXObject* otherObject = static_cast<PhysXObject*>(pairHeader.actors[1]->userData);


    for (PxU32 i = 0; i < nbPairs; i++)
    {
        PxU32 contactCount = pairs[i].contactCount;
        if (contactCount)
        {
            contactPoints.resize(contactCount);
            pairs[i].extractContacts(&contactPoints[0], contactCount);

            for (PxU32 j = 0; j < contactCount; j++)
            {
                //gContactPositions.push_back(contactPoints[j].position);
                //gContactImpulses.push_back(contactPoints[j].impulse);
            }
        }
    }

    for (PxU32 i = 0; i < nbPairs; i++)
    {
        PxContactPair pair = pairs[i];

        if (pair.flags & PxContactPairFlag::eACTOR_PAIR_HAS_FIRST_TOUCH)

        {
            collisionObject->OnCollisionEnter(otherObject);
            otherObject->OnCollisionEnter(collisionObject);
        }
        else if (pair.flags & PxContactPairFlag::eACTOR_PAIR_LOST_TOUCH)
        {
            collisionObject->OnCollisionExit(otherObject);
            otherObject->OnCollisionExit(collisionObject);
        }

    }
}

    


void CollisionEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
    PhysXObject* triggerActor = nullptr;
    PhysXObject* otherActor = nullptr;
    for (PxU32 i = 0; i < count; i++) 
    {
        const PxTriggerPair& pair = pairs[i];

       triggerActor = (PhysXObject*)pair.triggerActor->userData;
       otherActor = (PhysXObject*)pair.otherActor->userData;

        if (pair.status & PxPairFlag::eNOTIFY_TOUCH_FOUND) 
        {
            triggerActor->OnTriggerEnter(otherActor);
            otherActor->OnTriggerEnter(triggerActor);
        }
        else if (pair.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            triggerActor->OnTriggerExit(otherActor);
            otherActor->OnTriggerExit(triggerActor);
        }

    }


}

void CollisionEventCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
}
