#pragma once

#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <Windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<vector>







#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClrError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClrError();
bool GLLogCall(const char* function, const char* file, int line);




