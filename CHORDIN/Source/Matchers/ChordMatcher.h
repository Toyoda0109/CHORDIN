// CHORDIN ver 1.1
#pragma once

#include <JuceHeader.h>
#include <unordered_map>
#include <functional>

//==============================================================================
// �R�[�h�i�a���j�̈�v����ƊǗ����s���N���X
class ChordMatcher {
public:
    // �R�[�h�`�F�b�J�[��������
    void initialize(
        const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
        const std::function<bool(const juce::Array<juce::String>&)>& chordMatchCallback);

    // ���݂̃m�[�g�X�i�b�v�V���b�g�����v����R�[�h���擾
    juce::String matchChord(const juce::Array<int>& notesSnapshot);

    // ���݂̃m�[�g�X�i�b�v�V���b�g����ɃR�[�h�����X�V
    juce::String updateChord(const juce::Array<int>& notesSnapshot);

    // �w�肳�ꂽ�m�[�g���R�[�h�Ɉ�v���邩�𔻒�
    bool isChordMatch(const juce::Array<juce::String>& expectedNotes, const juce::Array<int>& activeNotes);

private:
    std::unordered_map<juce::String, std::function<bool()>> chordCheckers;
};
