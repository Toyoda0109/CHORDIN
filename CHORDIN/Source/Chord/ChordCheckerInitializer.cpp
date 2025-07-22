#include "ChordCheckerInitializer.h"

//==============================================================================
// コード定義と一致確認コールバックを受け取り初期化を実行
ChordCheckerInitializer::ChordCheckerInitializer(
    const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
    const std::function<bool(const juce::Array<juce::String>&)>& isChordMatch)
{
    initializeCheckers(chordDefinitions, isChordMatch);
}

//==============================================================================
// 各コード名に対応するチェッカー関数を作成し、chordCheckers に格納
void ChordCheckerInitializer::initializeCheckers(
    const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
    const std::function<bool(const juce::Array<juce::String>&)>& isChordMatch)
{
    for (const auto& [chordName, expectedNotes] : chordDefinitions)
    {
        // 各コード名に対応するチェッカーを設定
        chordCheckers[chordName] = [expectedNotes, &isChordMatch] {
            return isChordMatch(expectedNotes);
            };
    }
}

//==============================================================================
// 初期化済みのコードチェッカーを返す
const std::unordered_map<juce::String, std::function<bool()>>& ChordCheckerInitializer::getChordCheckers() const
{
    return chordCheckers;
}
