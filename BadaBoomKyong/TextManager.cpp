#include "TextManager.h"
#include "TextManager.h"
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "RenderManager.h"
#include <iostream>


TextManager::TextManager()
{
}

TextManager::~TextManager()
{
}

bool TextManager::Init(const std::string& fontPath, unsigned int fontSize, int screenWidth, int screenHeight)
{
    if (!LoadShader())
        return false;

    glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
    glUseProgram(shaderID);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, &projection[0][0]);

    if (!LoadFont(fontPath, fontSize))
        return false;

    SetupRenderData();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void TextManager::Render(const std::string& text, float x, float y, float scale, glm::vec3 color)
{
    glUseProgram(shaderID);
    glUniform3f(glGetUniformLocation(shaderID, "textColor"), color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (char c : text)
    {
        Character ch = Characters[c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float verts[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
}

bool TextManager::LoadShader()
{
    shaderID = RenderManager::GetInstance()->GetTextShader();
    if (shaderID <= 0)
        return false;
    return true;
}

bool TextManager::LoadFont(const std::string& fontPath, unsigned int fontSize)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "FreeType init failed!\n";
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
    {
        std::cout << "Failed to load font: " << fontPath << "\n";
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Characters.clear();

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "Failed to load glyph: " << c << "\n";
            continue;
        }

        unsigned int tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        Character character{
            tex,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };

        Characters.insert({ c, character });
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

void TextManager::SetupRenderData()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
