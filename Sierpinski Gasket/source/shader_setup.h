#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"GL\glew.h"


GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
static char* readShaderSource(const char* shaderFile);
