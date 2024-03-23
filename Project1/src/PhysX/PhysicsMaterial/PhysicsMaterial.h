#pragma once
#include <PxMaterial.h>
using namespace physx;

struct PhysicsMaterial
{
    enum CombineMode
    {
        AVERAGE = 0,
        MINUMUM =1,
        MULTIPLY =2,
        MAXIMUM =3
    };

    float staticFriction = 0.6f;
    float dynamicFriction = 0.6f;
    float bounciness =0;

    CombineMode frictionCombine = AVERAGE;
    CombineMode bounceCombine = AVERAGE;


};


extern PxCombineMode::Enum PxCombineToLocal(PhysicsMaterial::CombineMode mode);

