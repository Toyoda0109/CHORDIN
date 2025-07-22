#include "MidiHandler.h"

//==============================================================================
// ノート番号を音名 (オクターブなし) に変換
juce::String MidiHandler::midiNoteNumberToNoteNameNoOctave(int midiNoteNumber) {
    static const juce::StringArray noteNames = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    return noteNames[midiNoteNumber % 12];
}

//==============================================================================
// ノート番号を音名 (オクターブ付き) に変換
juce::String MidiHandler::midiNoteNumberToNoteName(int midiNoteNumber) {
    int octave = (midiNoteNumber / 12) - 1; // オクターブを計算
    return midiNoteNumberToNoteNameNoOctave(midiNoteNumber) + juce::String(octave);
}

//==============================================================================
// 配列内の最も低いノート番号を取得
int MidiHandler::getLowestNote(const juce::Array<int>& notes) {
    return notes.isEmpty() ? -1 : *std::min_element(notes.begin(), notes.end());
}

//==============================================================================
// 指定した音名が配列内に存在するか確認
bool MidiHandler::containsNote(const juce::Array<int>& activeNotes, const juce::String& noteName) {
    return std::any_of(activeNotes.begin(), activeNotes.end(),
        [&noteName](int note) {
            return midiNoteNumberToNoteNameNoOctave(note) == noteName;
        });
}
