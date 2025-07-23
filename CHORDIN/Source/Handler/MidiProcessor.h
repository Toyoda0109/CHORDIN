// CHORDIN ver 1.1
#pragma once
#include <JuceHeader.h>
#include <mutex>

//==============================================================================
// MIDI メッセージの処理とアクティブノートの管理を行うクラス
class MidiProcessor
{
public:
    MidiProcessor() = default;

    // MIDI メッセージを処理してアクティブノートを取得
    juce::Array<int> processAndGetActiveNotes(const juce::MidiBuffer& midiMessages);

    // 現在のアクティブノートを取得
    juce::Array<int> getActiveNotes() const;

private:
    mutable std::mutex activeNotesMutex; // スレッド安全性を確保するためのミューテックス
    juce::Array<int> activeNotes; 
};
