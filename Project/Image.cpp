
#include "Image.h"

image::image()
{
    pointF.resize(4);
    for (int i = 0; i < 4; i++)
    {
        pointF[i].setFillColor(Color::Black);
        pointF[i].setOrigin(5,5);
        pointF[i].setRadius(5);
    }
    for (int i = 0; i < 2; i++)
    {
        pointF[i].setPosition(500 + 100*(i+1), 300);
        pointF[i+2].setPosition(500 - 100*(i+1), 300);
        textF[i].setPosition(500 + 100*(i+1), 270);
        textF[i+2].setPosition(500 - 100*(i+1), 270);
        tree[i].resize(2);
        tree[i].setPrimitiveType(Lines);
        tree_triangles[i].resize(3);
        tree_triangles[i].setPrimitiveType(Triangles);
        tree[i][0].color = Color::Black;
        tree[i][1].color = Color::Black;
        tree_triangles[i][0].color = Color::Black;
        tree_triangles[i][1].color = Color::Black;
        tree_triangles[i][2].color = Color::Black;
    }
    for (int i = 0; i < 3; i++)
    {
        line[i].resize(3);
        line[i].setPrimitiveType(LineStrip);
    }

    line[0][0].color = Color::Red;
    line[0][1].color = Color::Red;
    line[0][2].color = Color::Red;
    line[1][0].color = Color::Green;
    line[1][1].color = Color::Green;
    line[1][2].color = Color::Green;

    font.loadFromFile("Font.ttf");
    textF[0].setString("F");
    textF[1].setString("2F");
    textF[2].setString("F");
    textF[3].setString("2F");
    textF[0].setOrigin(6,6);
    textF[1].setOrigin(12,6);
    textF[2].setOrigin(6,6);
    textF[3].setOrigin(12,6);
    for (int i = 0; i < 4; i++)
    {
        textF[i].setFont(font);
        textF[i].setCharacterSize(30);
        textF[i].setFillColor(Color::Red);
    }

}

image::draw(RenderWindow& window)
{
    for (int i = 0; i < pointF.size(); i++)
        window.draw(pointF[i]);
    for (int i = 0; i < 2; i++)
        window.draw(tree[i]);
    for (int i = 0; i < 2; i++)
        window.draw(tree_triangles[i]);
    for (int i = 0; i < 4; i++)
        window.draw(textF[i]);
    for (int i = 0; i < 2; i++)
        window.draw(line[i]);
}

image::update(Vector2f size, Par& par, int& lowest_priority)
{
    // Расчет переменных

    if (par.f == 0)
        par.f = pow(1/par.F - 1/par.d, -1);
    if (par.F == 0)
        par.F = pow(1/par.f + 1/par.d, -1);
    if (par.d == 0)
        par.d = pow(1/par.F - 1/par.f, -1);
    if (par.f == -par.d)
        par.F = 0;

    if (par.f != -par.d)
        switch (lowest_priority)
        {
            case 1:
                if (pow(par.F, -1) != pow(par.f,-1) + pow(par.d, -1))
                    par.F = pow(1/par.f + 1/par.d, -1);
                break;
            case 2:
                if (pow(par.f, -1) != pow(par.F, -1) - pow(par.d, -1))
                    if (par.f == par.d) break;
                    par.f = pow(1/par.F - 1/par.d, -1);
                break;
            case 3:
                if (pow(par.d, -1) != pow(par.F, -1) - pow(par.f, -1))
                    par.d = pow(1/par.F - 1/par.f, -1);
                break;
        }

    double h = (par.f/par.F)*par.H;

    //Обновление изображения

    textF[0].setPosition(500 - par.F,270);
    textF[1].setPosition(500 - 2*par.F,270);
    textF[2].setPosition(500 + par.F,270);
    textF[3].setPosition(500 + 2*par.F,270);

    pointF[0].setPosition(500 - par.F,300);
    pointF[1].setPosition(500 - 2*par.F,300);
    pointF[2].setPosition(500 + par.F,300);
    pointF[3].setPosition(500 + 2*par.F,300);

    tree[0][0].position = {500 - par.d,300};
    tree[0][1].position = {500 - par.d,300 - par.H};
    tree[1][0].position = {500 + par.f,300};
    tree[1][1].position = {500 + par.f,300 - par.H + h};

    tree_triangles[0][0].position = {500 - par.d + par.H/20,300 - par.H + par.H/10};
    tree_triangles[0][1].position = {500 - par.d - par.H/20,300 - par.H + par.H/10};
    tree_triangles[0][2].position = {500 - par.d,300 - par.H};

    tree_triangles[1][0].position = {500 + par.f + (h-par.H)/20,300 - par.H + h - (h-par.H)/10};
    tree_triangles[1][1].position = {500 + par.f - (h-par.H)/20,300 - par.H + h - (h-par.H)/10};
    tree_triangles[1][2].position = {500 + par.f,300 - par.H + h};

    line[0][0].position = {500 - par.d,300 - par.H};
    line[0][1].position = {500,300 - par.H};
    line[0][2].position = {500 + par.f,300 - par.H + h};

    line[1][0].position = {500 - par.d,300 - par.H};
    line[1][1].position = {500,300};
    line[1][2].position = {500 + par.f,300 - par.H + h};

}
