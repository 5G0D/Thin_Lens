#include "background.h"
#include "Image.h"
#include "Interface.h"
#include <string>

int main()
{
    RenderWindow window(VideoMode(1000, 600), L"Построение изображения предмета в тонкой линзе");
    window.setFramerateLimit(70);
    ImGui::SFML::Init(window);

    BackGround bg;
    image im;

    View view;
    view.setCenter(500,300);
    view.setSize(1000,600);
    Par par;
    bool update, sob; //update - обновление графика; sob - собирающая линза (если true, тогда да)
    Clock deltaClock;
    int lowest_priority = 1; // наименьший приоритет переменной
    while (window.isOpen())
    {
        char F[8], f[8], d[8], H[8];
        int a = par.F, b = par.f, c = par.d, e = par.H;
        sprintf(F, "%d", a);
        sprintf(f, "%d", b);
        sprintf(d, "%d", c);
        sprintf(H, "%d", e);
        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelMoved)
            {
                view.zoom(1 - 0.04*event.mouseWheel.delta);
            }
        }

        par = InterfaceUpdate(deltaClock, window, F, f, d, H, update, lowest_priority);
        if (update) im.update(view.getSize(), par, lowest_priority);
        sob = (par.f * par.d > 0 || par.d < par.F) ? true : false;
        bg.update(view.getSize(),sob);
        window.setView(view);
        window.clear(Color::White);
        bg.draw(window);
        im.draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}
