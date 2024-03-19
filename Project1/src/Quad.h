#pragma once
#include "Renderer.h"
class Quad
{
  public:
	  static Quad& GetInstance();
   unsigned int quadVAO = 0;
   unsigned int quadVBO;
   void RenderQuad();
   
};

