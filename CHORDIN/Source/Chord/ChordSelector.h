#pragma once

#include <JuceHeader.h>
#include <unordered_map>

class ChordSelector
{
public:
    // コンストラクタ
    ChordSelector(const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities,
        const juce::String& initialScale);

    // 優先順位を取得
    int getChordPriority(const juce::String& chordName) const;

    // スケールを更新
    void updateScale(const juce::String& newScale);

private:
    const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities;
    juce::String currentScale;

    static constexpr int defaultPriority = 0; // 優先順位が見つからない場合のデフォルト値
};
