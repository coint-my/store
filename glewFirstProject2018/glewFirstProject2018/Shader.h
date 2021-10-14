#pragma once

// GLEW
#define GLEW_STATIC
#include "gl/glew.h"

#include "gl/glfw3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct color3f
{
	GLfloat r, g, b;
	color3f() : r(0), g(0), b(0) { }
	color3f(GLfloat _r, GLfloat _g, GLfloat _b) : r(_r), g(_g), b(_b) { }
};

struct color4f
{
	GLfloat r, g, b, a;
	color4f() : r(0), g(0), b(0), a(1.0f) { }
	color4f(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a) : r(_r), g(_g), b(_b), a(_a) { }
};

class Shader
{
private: GLuint program;
private: color4f col;

public: Shader() { }

public: Shader(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	col = color4f(r, g, b, a);
	this->program = LoadShaders("shader\\vertexShader.txt", "shader\\fragmentShader.txt");
}

public: Shader(GLchar* v_shader, GLchar* f_shader)
{
	this->program = LoadShaders(v_shader, f_shader);
}

public: GLuint getProgram() { return program; }

public: void Use() 
{ 
	glUseProgram(this->program);
	GLint setVal = glGetUniformLocation(this->program, "setColor");
	glUniform4f(setVal, col.r, col.g, col.b, col.a);
}

public: void setColor(color4f _col)
{
	col = _col;
}

private: GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
	setlocale(LC_ALL, "Russian");
	// ������� �������
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// ��������� ��� ���������� ������� �� �����
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}

	// ��������� ��� ������������ ������� �� �����
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// ����������� ��������� ������
	printf("���������� �������: %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// ��������� �������� ���������� �������
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
	}

	// ����������� ����������� ������
	printf("���������� �������: %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// ��������� ����������� ������
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
	}

	// ������� ��������� ��������� � ����������� ������� � ���
	fprintf(stdout, "������� ��������� ��������� � ����������� ������� � ���\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// ��������� ��������� ���������
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

};