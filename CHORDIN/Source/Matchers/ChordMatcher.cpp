#include "ChordMatcher.h"
#include "../Handler/MidiHandler.h"

//==============================================================================
void ChordMatcher::initialize(
    const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
    const std::function<bool(const juce::Array<juce::String>&)>& chordMatchCallback)
{
    for (const auto& [chordName, expectedNotes] : chordDefinitions) {
        // コード名に対する一致判定ロジックを登録
        chordCheckers[chordName] = [expectedNotes, chordMatchCallback]() {
            return chordMatchCallback(expectedNotes);
            };
    }
}

//==============================================================================
// 現在のノートスナップショットに一致するコードを取得
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
// 指定されたノートがコードに一致するか判定
bool ChordMatcher::isChordMatch(const juce::Array<juce::String>& expectedNotes, const juce::Array<int>& activeNotes)
{
    // 必要なノートがすべてアクティブノートに含まれているか確認
    for (const auto& note : expectedNotes) {
        if (!MidiHandler::containsNote(activeNotes, note))
            return false;
    }

    // アクティブノートが余計なノートを含んでいないか確認
    for (int note : activeNotes) {
        juce::String noteName = MidiHandler::midiNoteNumberToNoteNameNoOctave(note);
        if (!expectedNotes.contains(noteName))
            return false;
    }

    return true;
}

//==============================================================================
// 現在のノートスナップショットを基にコード名を更新
juce::String ChordMatcher::updateChord(const juce::Array<int>& notesSnapshot)
{
    juce::String selectedChord = matchChord(notesSnapshot);
    if (!selectedChord.isEmpty()) {
        int lowestNote = MidiHandler::getLowestNote(notesSnapshot); // 最も低いノートを取得
        juce::String lowestNoteName = MidiHandler::midiNoteNumberToNoteNameNoOctave(lowestNote);
        return selectedChord + "/" + lowestNoteName;
    }
    return {};
}
