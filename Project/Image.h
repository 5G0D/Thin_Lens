#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

struct Par
{
    double f = 200;
    double d = 200;
    double F = 100;
    double H = 100;
};

class image
{
    private:

        double size, F, d, f, H;
        vector<CircleShape> pointF; // Точки фокусо
        VertexArray tree[2]; //Тело изображения
        VertexArray line[3]; //Линии для построения
        VertexArray tree_triangles[2]; //Треугольники на изображении
        Font font;
        Text textF[4]; // надписи фокусов

    public:

        image();
        update(Vector2f, Par&, int&);
        draw(RenderWindow&);
};

#endif // IMAGE_H_INCLUDED
