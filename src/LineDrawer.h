#pragma once
#include <vector>
#include <glm/glm.hpp>


class Line {
    Shader shader;
    unsigned int VBO, VAO;
    std::pair<glm::vec3, glm::vec3> points;
    glm::mat4 MVP;
    glm::vec4 lineColor;
public:
    Line(glm::vec3 start, glm::vec3 end) : 
        shader{ Shader{ "Line.vs", "Line.fs" } } 
    {
        points.first = start;
        points.second = end;

        lineColor = glm::vec4(1, 1, 1, 1);
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, &points.first, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void setMVP(glm::mat4 mvp) {
        MVP = mvp;
    }
    
    void setColor(glm::vec3 color) {
        lineColor = glm::vec4(color, 1.0);

    }

    void setColor(glm::vec4 color) {
        lineColor = color;
    }

    int draw() {
        shader.use();
        shader.setMat4("MVP", MVP);
        shader.setVec4("color", lineColor);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        return 0;
    }

    ~Line() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};