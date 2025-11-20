#include "Window.h"
#include <iostream>
#include "JsonParser.h"
#include "Fetcher.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int main()
{
    Fetcher fetcher;
    BaseParser* parser = new JsonParser;
    int account_id = 0;
    int limit = 0;
    Window window(500, 400, "Dota2Parser");
    std::vector<Data> matches;
    bool has_matches = false;
	Data_User* user_data = nullptr;
    int selectedMatchId = 0;
    bool showMatchDetails = false;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    while (!window.shouldClose())
    {
        window.clear(255.f, 192.f, 203.f, 255.f);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Dota2 Parser");

        ImGui::InputInt("Account ID", &account_id);
        ImGui::InputInt("Limit", &limit);

        if (ImGui::Button("Fetch"))
        {

            std::string data = fetcher.fetch(account_id, limit);
            parser->parse(data);
            matches = parser->get_matches();
            has_matches = !matches.empty();
			std::string user_data_str = fetcher.fetch_user(account_id);
            if (!user_data_str.empty()) {
                parser->parse_user(user_data_str);
                user_data = parser->get_users();
            }
        }
        if (has_matches)
        {
            if (user_data && !user_data->personaname.empty()) {
                ImGui::TextColored(ImVec4(1.0f, 0.41f, 0.71f, 1.0f), user_data->personaname.c_str());
            }
            else {
                ImGui::TextColored(ImVec4(1.0f, 0.41f, 0.71f, 1.0f), "Unknown player");
            }
            ImGui::BeginChild("Scrolling");
            for (const auto& m : matches)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.41f, 0.71f, 1.0f));
                std::string match_label = std::to_string(m.match_id);
                if (ImGui::Button(match_label.c_str())) {
                    selectedMatchId = m.match_id;
                    showMatchDetails = true;            
                }
                ImGui::PopStyleColor();
            }
            ImGui::EndChild();
        }

        ImGui::End();

   
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.swapBuffers();
        window.poolEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
}
