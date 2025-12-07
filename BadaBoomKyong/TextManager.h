#pragma once
#include "Singleton.h"
#include <glm.hpp>
#include <string>
#include <map>

struct Character
{
    unsigned int TextureID;
    glm::vec2 Size;
    glm::vec2 Bearing;
    unsigned int Advance;
};

class TextManager
{
public:
	SINGLETON(TextManager);
public:
    bool Init(const std::string& fontPath, unsigned int fontSize, int screenWidth, int screenHeight);
    void Render(const std::string& text, float x, float y, float scale, glm::vec3 color);
public:
    bool LoadShader();
    bool LoadFont(const std::string& fontPath, unsigned int fontSize);
    void SetupRenderData();
private:
    std::map<char, Character> Characters;

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int shaderID = 0;
};

