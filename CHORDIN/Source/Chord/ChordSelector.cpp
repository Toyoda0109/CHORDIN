// CHORDIN ver 1.1
#include "ChordSelector.h"

ChordSelector::ChordSelector(const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities,
    const juce::String& initialScale)
    : chordPriorities(chordPriorities), currentScale(initialScale)
{
}

int ChordSelector::getChordPriority(const juce::String& chordName) const
{
    auto scaleIt = chordPriorities.find(currentScale);
    if (scaleIt != chordPriorities.end())
    {
        const auto& priorityMap = scaleIt->second;
        auto chordIt = priorityMap.find(chordName);
        if (chordIt != priorityMap.end())
        {
            return chordIt->second;
        }
    }
    return defaultPriority; // 優先順位が見つからない場合はデフォルト値を返す
}

void ChordSelector::updateScale(const juce::String& newScale)
{
    currentScale = newScale;
}
