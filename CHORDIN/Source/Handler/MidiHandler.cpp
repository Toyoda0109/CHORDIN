// CHORDIN ver 1.1
#include "MidiHandler.h"

//==============================================================================
// �m�[�g�ԍ������� (�I�N�^�[�u�Ȃ�) �ɕϊ�
juce::String MidiHandler::midiNoteNumberToNoteNameNoOctave(int midiNoteNumber) {
    static const juce::StringArray noteNames = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    return noteNames[midiNoteNumber % 12];
}

//==============================================================================
// �m�[�g�ԍ������� (�I�N�^�[�u�t��) �ɕϊ�
juce::String MidiHandler::midiNoteNumberToNoteName(int midiNoteNumber) {
    int octave = (midiNoteNumber / 12) - 1; // �I�N�^�[�u���v�Z
    return midiNoteNumberToNoteNameNoOctave(midiNoteNumber) + juce::String(octave);
}

//==============================================================================
// �z����̍ł��Ⴂ�m�[�g�ԍ����擾
int MidiHandler::getLowestNote(const juce::Array<int>& notes) {
    return notes.isEmpty() ? -1 : *std::min_element(notes.begin(), notes.end());
}

//==============================================================================
// �w�肵���������z����ɑ��݂��邩�m�F
bool MidiHandler::containsNote(const juce::Array<int>& activeNotes, const juce::String& noteName) {
    return std::any_of(activeNotes.begin(), activeNotes.end(),
        [&noteName](int note) {
            return midiNoteNumberToNoteNameNoOctave(note) == noteName;
        });
}
