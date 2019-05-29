
#include "background.h"

BackGround::BackGround()
{
    lineX.resize(2);
    lineX.setPrimitiveType(Lines);
    lineX[0].color = Color::Black;
    lineX[1].color = Color::Black;
    lineX[0].position = {0,300};
    lineX[1].position = {1000,300};

    lineY.resize(2);
    lineY.setPrimitiveType(Lines);
    lineY[0].color = Color::Blue;
    lineY[1].color = Color::Blue;
    lineY[0].position = {500,100};
    lineY[1].position = {500,500};

    triangle[0].resize(3);
    triangle[0].setPrimitiveType(Triangles);
    triangle[0][0].color = Color::Blue;
    triangle[0][1].color = Color::Blue;
    triangle[0][2].color = Color::Blue;
    triangle[0][0].position = {505,100};
    triangle[0][1].position = {500,90};
    triangle[0][2].position = {495,100};

    triangle[1].resize(3);
    triangle[1].setPrimitiveType(Triangles);
    triangle[1][0].color = Color::Blue;
    triangle[1][1].color = Color::Blue;
    triangle[1][2].color = Color::Blue;
    triangle[1][0].position = {505,500};
    triangle[1][1].position = {495,500};
    triangle[1][2].position = {500,510};
}

BackGround::draw(RenderWindow& window)
{
    window.draw(lineX);
    window.draw(lineY);
    for (int i = 0; i < 2; i++)
        window.draw(triangle[i]);
}

BackGround::update(Vector2f size, bool sob)
{
    double x = size.x/1000;

    lineX[0].position = {500-size.x,300};
    lineX[1].position = {500+size.x,300};
    lineY[0].position = {500, 300 - 200*x};
    lineY[1].position = {500, 300 + 200*x};
    triangle[0][0].position = {500 + 5*x,300 - 200*x};
    triangle[0][2].position = {500 - 5*x,300 - 200*x};
    triangle[1][0].position = {500 + 5*x,300 + 200*x};
    triangle[1][2].position = {500 - 5*x,300 + 200*x};
    if (sob)
    {
        triangle[0][1].position = {500      ,300 - 210*x};
        triangle[1][1].position = {500      ,300 + 210*x};
    }
    else
    {
        triangle[0][1].position = {500      ,300 - 190*x};
        triangle[1][1].position = {500      ,300 + 190*x};
    }
}
