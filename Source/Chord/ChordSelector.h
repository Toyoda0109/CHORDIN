#pragma once

#include <JuceHeader.h>
#include <unordered_map>

class ChordSelector
{
public:
    // �R���X�g���N�^
    ChordSelector(const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities,
        const juce::String& initialScale);

    // �D�揇�ʂ��擾
    int getChordPriority(const juce::String& chordName) const;

    // �X�P�[�����X�V
    void updateScale(const juce::String& newScale);

private:
    const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& chordPriorities;
    juce::String currentScale;

    static constexpr int defaultPriority = 0; // �D�揇�ʂ�������Ȃ��ꍇ�̃f�t�H���g�l
};
