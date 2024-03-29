#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Event.h"
#include "SceneData.h"
#include "Renderer/Image.h"

namespace PathTracing
{
void createCornellBoxScene(std::shared_ptr<SceneData> scene);

class Editor
{
public:
    Editor();

    const std::shared_ptr<SceneData> getSceneData() const { return m_sceneData; }

    void onGuiRender();

    void setRenderDuration(float renderDuration) { m_renderDuration = renderDuration; }

private:
    void makeSlider1(const std::string& name, const std::string& sliderName, float* value, float min, float max);
    void makeSlider2(const std::string& name, const std::string& sliderName, const glm::vec2& value, float min, float max);
    void makeSlider3(const std::string& name, const std::string& sliderName, const glm::vec3& value, float min, float max);
    void makeColorPicker3(const std::string& name, const std::string& colorPickerName, const glm::vec3& value);
    void makeInputInt1(const std::string& name, const std::string& inputIntName, int* value);
    void makeCombo(const std::string& name, const std::string& comboName,
                   const std::vector<const char*>& itemList, int currentItem,
                   void(*comboboxCallback)(int, SceneObjectData&), SceneObjectData& sceneObject);

    void makeGuiForResetButton(const std::string& name, void(*resetFunction)(SceneData&));
    void makeGuiForSceneObject(SceneObjectData& sceneObject);
    void makeGuiForPrimitive(const std::string& name, std::shared_ptr<PrimitiveData> primitiveData);

private:
    struct GuiLayoutSettings
    {
        const float sliderWidth         = 300.0f;
        const float colorPickerWidth    = sliderWidth;
        const float inputValueWidth     = 100.0f;
        const float comboWidth          = sliderWidth;
        const float resetButtonWidth    = 80.0f;
    };

private:
    // render time in second
    float m_renderDuration = 0.0f;

    std::shared_ptr<SceneData> m_sceneData;

    GuiLayoutSettings m_guiLayoutSettings;
};

}
