// CHORDIN ver 1.1
#pragma once

#include <JuceHeader.h>
#include <unordered_map>

class ChordDefinitions {
public:
    ChordDefinitions();


    // コード定義データの取得
    const std::unordered_map<juce::String, juce::Array<juce::String>>& getChordDefinitions() const;

private:
    std::unordered_map<juce::String, juce::Array<juce::String>> chordDefinitions;

    void initializeChordDefinitions();
};
