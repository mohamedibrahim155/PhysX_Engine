#include "PhysicsMaterial.h"


PxCombineMode::Enum PxCombineToLocal(PhysicsMaterial::CombineMode mode)
{
    switch (mode)
    {
    case PhysicsMaterial::AVERAGE:
        return  PxCombineMode::eAVERAGE;
        break;
    case PhysicsMaterial::MINUMUM:
        return  PxCombineMode::eMIN;
        break;
    case PhysicsMaterial::MULTIPLY:
        return  PxCombineMode::eMULTIPLY;
        break;
    case PhysicsMaterial::MAXIMUM:
        return  PxCombineMode::eMAX;
        break;
    }
}