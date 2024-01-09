#pragma once

namespace PathTracing
{

class ImGuiRenderer
{
public:
    ImGuiRenderer();
    ~ImGuiRenderer();

    void OnNewFrame();
    void onRender();

private:
    float m_time;
};

}
