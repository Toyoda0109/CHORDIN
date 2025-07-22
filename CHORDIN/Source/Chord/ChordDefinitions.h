#pragma once

#include <JuceHeader.h>
#include <unordered_map>

class ChordDefinitions {
public:
    ChordDefinitions();

    // �R�[�h��`�f�[�^�̎擾
    const std::unordered_map<juce::String, juce::Array<juce::String>>& getChordDefinitions() const;

private:
    std::unordered_map<juce::String, juce::Array<juce::String>> chordDefinitions;

    void initializeChordDefinitions();
};
