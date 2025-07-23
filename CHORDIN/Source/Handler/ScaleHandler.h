// CHORDIN ver 1.1
#pragma once

#include <JuceHeader.h>
#include <unordered_map>
#include <string>

//==============================================================================
// スケールの管理と操作を行うクラス
class ScaleHandler
{
public:
    ScaleHandler();
    ~ScaleHandler();

    void updateScale(const juce::String& newScale); // スケールを更新
    juce::Array<juce::String> getScaleNotes() const { return scaleNotes; } // 現在のスケールノートを取得
    juce::String getCurrentScale() const { return currentScale; } // 現在のスケール名を取得

private:
    juce::String currentScale; // 現在のスケール名
    juce::Array<juce::String> scaleNotes; // 現在のスケールノート
    std::unordered_map<juce::String, juce::Array<juce::String>> scaleMap;

    void initializeScaleMap(); 
};
