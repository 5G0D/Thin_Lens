
#include "Interface.h"

Par InterfaceUpdate(Clock& deltaClock, RenderWindow& window, char F[8], char f[8], char d[8], char h[8], bool& update, int& lowest_priority)
{
        update = false;
        Par par;
        static int theme = 3;
        static bool slide = false, rt = false;

        switch (theme)
        {
            case 1: ImGui::StyleColorsClassic(); break;
            case 2: ImGui::StyleColorsDark(); break;
            case 3: ImGui::StyleColorsLight(); break;
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(160,175), ImGuiSetCond_Once);
        ImGui::SetNextWindowPos(ImVec2(830,05), ImGuiSetCond_Once);

        ImGui::Begin("Options");

        if (!slide)
        {
            ImGui::InputText("F", F, 7);
            ImGui::InputText("f", f, 7);
            ImGui::InputText("d", d, 7);
            ImGui::InputText("h", h, 7);
            ImGui::Text("Lowest priority : ");
            ImGui::SameLine(0,0);
            switch (lowest_priority)
            {
                case 1: ImGui::Text("F"); break;
                case 2: ImGui::Text("f"); break;
                case 3: ImGui::Text("d"); break;
            }
            ImGui::SliderInt("", &lowest_priority, 1, 3);
            ImGui::SameLine(0,0);
            char desc[] = "Need to input height and two of three other options.\nIf you will input incorrect data, var with lowest priority\nwill define automatically.";
            ImGui::TextDisabled(" (?)");
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 100.0f);
                ImGui::TextUnformatted(desc);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
            par.F = atoi(F);
            par.f = atoi(f);
            par.d = atoi(d);
            par.H = atoi(h);
        }
        else
        {
            int t = atoi(F);
            ImGui::SliderInt("F", &t, -1000, 1000);
            par.F = t;
            t = atoi(f);
            ImGui::SliderInt("f", &t, -1000, 1000);
            par.f = t;
            t = atoi(d);
            ImGui::SliderInt("d", &t, -1000, 1000);
            par.d = t;
            t = atoi(h);
            ImGui::SliderInt("h", &t, -1000, 1000);
            par.H = t;
            ImGui::Text("Lowest priority : ");
            ImGui::SameLine(0,0);
            switch (lowest_priority)
            {
                case 1: ImGui::Text("F"); break;
                case 2: ImGui::Text("f"); break;
                case 3: ImGui::Text("d"); break;
            }
            ImGui::SliderInt("", &lowest_priority, 1, 3);
            ImGui::SameLine(0,0);
            char desc[] = "Need to input height and two of three other options.\nIf you will input incorrect data, var with lowest priority\nwill define automatically.";
            ImGui::TextDisabled(" (?)");
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 100.0f);
                ImGui::TextUnformatted(desc);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
        }

        ImGui::End();

        switch (theme)
        {
            case 1: ImGui::StyleColorsClassic(); break;
            case 2: ImGui::StyleColorsDark(); break;
            case 3: ImGui::StyleColorsLight(); break;
        }

        ImGui::SetNextWindowSize(ImVec2(150,100), ImGuiSetCond_Once);
        ImGui::SetNextWindowPos(ImVec2(840,190), ImGuiSetCond_Once);

        ImGui::Begin("Customize");

        ImGui::SliderInt("Theme", &theme, 1, 3);
        ImGui::Checkbox("Slider", &slide);
        ImGui::Checkbox("Real time update", &rt);

        ImGui::End();

        if (!rt)
        {
            ImGui::SetNextWindowSize(ImVec2(70,60), ImGuiSetCond_Once);
            ImGui::SetNextWindowPos(ImVec2(920,310), ImGuiSetCond_Once);
            ImGui::Begin("Update");

                if (ImGui::Button(" Click "))
                    update = true;

            ImGui::End();
        }
        else update = true;
        ImGui::SetNextWindowSize(ImVec2(130,90), ImGuiSetCond_Once);
        ImGui::SetNextWindowPos(ImVec2(860,380), ImGuiSetCond_Once);

        if (par.f != -par.d)
        {
            ImGui::Begin ( (par.f * par.d > 0 || par.d < par.F) ? "Converging lens" : "Diverging lens");
            ImGui::BulletText(((par.f * par.d > 0 || (par.d > par.F) && par.F > 0)) ? "Actual" : "Fake");
            if (par.f != par.d)ImGui::BulletText((abs((par.f/par.F)*abs(par.H) - abs(par.H)) > abs(par.H)) ? "Increased" : "Decreased");
            ImGui::BulletText(((par.f * par.d > 0 || (par.d > par.F) && par.F > 0)) ? "Upside - Down" : "Straight");
            ImGui::End();
        }
        else
        {
            ImGui::Begin("No image");
            ImGui::Text("\n     (?_?)");
            ImGui::End();
        }
        return par;
}
