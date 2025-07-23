// CHORDIN ver 1.1
#pragma once

#include <JuceHeader.h>
#include <unordered_map>
#include <functional>
#include <mutex>

class ChordNameUpdater
{
public:
    ChordNameUpdater(
        const std::unordered_map<juce::String, std::function<bool()>>& chordCheckers,
        const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities,
        const juce::String& currentScale,
        const std::function<juce::String(int)>& noteToNameFunc);

    juce::String updateChordName(const juce::Array<int>& notesSnapshot);

private:
    const std::unordered_map<juce::String, std::function<bool()>>& chordCheckers;
    const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities;
    juce::String currentScale;
    const std::function<juce::String(int)> noteToNameFunc;

    juce::String selectBestChord() const;
    juce::String buildChordName(const juce::String& chordName, const juce::Array<int>& notesSnapshot) const;
};
