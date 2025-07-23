// CHORDIN ver 1.1
#include "ChordMatcher.h"
#include "../Handler/MidiHandler.h"

//==============================================================================
void ChordMatcher::initialize(
    const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
    const std::function<bool(const juce::Array<juce::String>&)>& chordMatchCallback)
{
    for (const auto& [chordName, expectedNotes] : chordDefinitions) {
        // �R�[�h���ɑ΂����v���胍�W�b�N��o�^
        chordCheckers[chordName] = [expectedNotes, chordMatchCallback]() {
            return chordMatchCallback(expectedNotes);
            };
    }
}

//==============================================================================
// ���݂̃m�[�g�X�i�b�v�V���b�g�Ɉ�v����R�[�h���擾
juce::String ChordMatcher::matchChord(const juce::Array<int>& notesSnapshot)
{
    for (const auto& [chordName, checker] : chordCheckers) {
        if (checker()) {
            return chordName;
        }
    }
    return {};
}

//==============================================================================
// �w�肳�ꂽ�m�[�g���R�[�h�Ɉ�v���邩����
bool ChordMatcher::isChordMatch(const juce::Array<juce::String>& expectedNotes, const juce::Array<int>& activeNotes)
{
    // �K�v�ȃm�[�g�����ׂăA�N�e�B�u�m�[�g�Ɋ܂܂�Ă��邩�m�F
    for (const auto& note : expectedNotes) {
        if (!MidiHandler::containsNote(activeNotes, note))
            return false;
    }

    // �A�N�e�B�u�m�[�g���]�v�ȃm�[�g���܂�ł��Ȃ����m�F
    for (int note : activeNotes) {
        juce::String noteName = MidiHandler::midiNoteNumberToNoteNameNoOctave(note);
        if (!expectedNotes.contains(noteName))
            return false;
    }

    return true;
}

//==============================================================================
// ���݂̃m�[�g�X�i�b�v�V���b�g����ɃR�[�h�����X�V
juce::String ChordMatcher::updateChord(const juce::Array<int>& notesSnapshot)
{
    juce::String selectedChord = matchChord(notesSnapshot);
    if (!selectedChord.isEmpty()) {
        int lowestNote = MidiHandler::getLowestNote(notesSnapshot); // �ł��Ⴂ�m�[�g���擾
        juce::String lowestNoteName = MidiHandler::midiNoteNumberToNoteNameNoOctave(lowestNote);
        return selectedChord + "/" + lowestNoteName;
    }
    return {};
}
