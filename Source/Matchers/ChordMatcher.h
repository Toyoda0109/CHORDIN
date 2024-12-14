#pragma once

#include <JuceHeader.h>
#include <unordered_map>
#include <functional>

//==============================================================================
// コード（和音）の一致判定と管理を行うクラス
class ChordMatcher {
public:
    // コードチェッカーを初期化
    void initialize(
        const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
        const std::function<bool(const juce::Array<juce::String>&)>& chordMatchCallback);

    // 現在のノートスナップショットから一致するコードを取得
    juce::String matchChord(const juce::Array<int>& notesSnapshot);

    // 現在のノートスナップショットを基にコード名を更新
    juce::String updateChord(const juce::Array<int>& notesSnapshot);

    // 指定されたノートがコードに一致するかを判定
    bool isChordMatch(const juce::Array<juce::String>& expectedNotes, const juce::Array<int>& activeNotes);

private:
    std::unordered_map<juce::String, std::function<bool()>> chordCheckers;
};
