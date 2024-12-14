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
    return defaultPriority; // �D�揇�ʂ�������Ȃ��ꍇ�̓f�t�H���g�l��Ԃ�
}

void ChordSelector::updateScale(const juce::String& newScale)
{
    currentScale = newScale;
}
