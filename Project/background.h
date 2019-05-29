#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class BackGround
{
    private:

        VertexArray lineX; // абцисса
        VertexArray lineY; // ордината
        VertexArray triangle[2]; //треугольники на концах ординаты

    public:

        BackGround();
        draw(RenderWindow&);
        update(Vector2f, bool);
};

#endif // BACKGROUND_H_INCLUDED
