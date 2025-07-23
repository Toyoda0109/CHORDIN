// CHORDIN ver 1.1
#include "MidiProcessor.h"

//==============================================================================
// MIDI メッセージを処理し、アクティブノートを更新して返す
juce::Array<int> MidiProcessor::processAndGetActiveNotes(const juce::MidiBuffer& midiMessages)
{
    std::lock_guard<std::mutex> lock(activeNotesMutex);

    for (const auto& metadata : midiMessages)
    {
        auto message = metadata.getMessage();

        if (message.isNoteOn()) // ノートオンの場合、リストに追加
        {
            int noteNumber = message.getNoteNumber();
            if (!activeNotes.contains(noteNumber))
            {
                activeNotes.add(noteNumber);
            }
        }
        else if (message.isNoteOff()) // ノートオフの場合、リストから削除
        {
            int noteNumber = message.getNoteNumber();
            activeNotes.removeAllInstancesOf(noteNumber);
        }
    }

    // アクティブノートの数が多すぎる場合はリセット
    if (activeNotes.size() > 10)
    {
        activeNotes.clear();
    }

    return activeNotes;
}

//==============================================================================
// 現在のアクティブノートを返す（スレッド安全）
juce::Array<int> MidiProcessor::getActiveNotes() const
{
    std::lock_guard<std::mutex> lock(activeNotesMutex);
    return activeNotes;
}
