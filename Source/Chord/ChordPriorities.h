#pragma once
#include <unordered_map>
#include <string>
#include <juce_core/juce_core.h>

class ChordPriorities {
public:
    ChordPriorities();

    const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& getChordPriorities() const;

private:
    std::unordered_map<juce::String, std::unordered_map<juce::String, int>> chordPriorities;
};
