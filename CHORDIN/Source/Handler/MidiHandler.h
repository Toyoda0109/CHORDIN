// CHORDIN ver 1.1
#pragma once
#include <JuceHeader.h>
#include <algorithm>

// MIDI �m�[�g����̃��[�e�B���e�B�N���X
class MidiHandler
{
public:
    static juce::String midiNoteNumberToNoteName(int midiNoteNumber); // �m�[�g�ԍ��������ɕϊ�
    static juce::String midiNoteNumberToNoteNameNoOctave(int midiNoteNumber); // �m�[�g�ԍ����I�N�^�[�u�Ȃ��̉����ɕϊ�
    static int getLowestNote(const juce::Array<int>& notes); // �ł��Ⴂ�m�[�g�ԍ����擾
    static bool containsNote(const juce::Array<int>& activeNotes, const juce::String& noteName); // �w�艹�����܂܂�邩�m�F
};
