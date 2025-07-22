#pragma once
#include <JuceHeader.h>
#include <algorithm>

// MIDI ノート操作のユーティリティクラス
class MidiHandler
{
public:
    static juce::String midiNoteNumberToNoteName(int midiNoteNumber); // ノート番号を音名に変換
    static juce::String midiNoteNumberToNoteNameNoOctave(int midiNoteNumber); // ノート番号をオクターブなしの音名に変換
    static int getLowestNote(const juce::Array<int>& notes); // 最も低いノート番号を取得
    static bool containsNote(const juce::Array<int>& activeNotes, const juce::String& noteName); // 指定音名が含まれるか確認
};
