#ifndef IMGUIRENDERER_H
#define IMGUIRENDERER_H

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

#endif // IMGUIRENDERER_H
