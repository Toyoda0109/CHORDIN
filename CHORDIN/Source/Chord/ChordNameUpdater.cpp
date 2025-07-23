// CHORDIN ver 1.1
#include "ChordNameUpdater.h"

ChordNameUpdater::ChordNameUpdater(
    const std::unordered_map<juce::String, std::function<bool()>>& chordCheckers,
    const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities,
    const juce::String& currentScale,
    const std::function<juce::String(int)>& noteToNameFunc)
    : chordCheckers(chordCheckers),
    chordPriorities(chordPriorities),
    currentScale(currentScale),
    noteToNameFunc(noteToNameFunc)
{
}

juce::String ChordNameUpdater::updateChordName(const juce::Array<int>& notesSnapshot)
{
    juce::String selectedChord = selectBestChord();

    if (!selectedChord.isEmpty())
    {
        return buildChordName(selectedChord, notesSnapshot);
    }
    return {};
}

juce::String ChordNameUpdater::selectBestChord() const
{
    juce::String selectedChord;
    int bestPriority = INT_MAX;

    for (const auto& [chordName, checker] : chordCheckers)
    {
        if (checker())
        {
            auto it = chordPriorities.find(currentScale);
            if (it != chordPriorities.end())
            {
                const auto& priorityMap = it->second;
                auto priorityIt = priorityMap.find(chordName);
                int priority = (priorityIt != priorityMap.end()) ? priorityIt->second : INT_MAX;

                if (priority < bestPriority)
                {
                    bestPriority = priority;
                    selectedChord = chordName;
                }
            }
        }
    }

    return selectedChord;
}

juce::String ChordNameUpdater::buildChordName(const juce::String& chordName, const juce::Array<int>& notesSnapshot) const
{
    int lowestNote = notesSnapshot.isEmpty() ? -1 : *std::min_element(notesSnapshot.begin(), notesSnapshot.end());
    juce::String lowestNoteName = noteToNameFunc(lowestNote);
    return chordName + "/" + lowestNoteName;
}
