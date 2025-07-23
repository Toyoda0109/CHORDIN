// CHORDIN ver 1.1
#pragma once

#include <JuceHeader.h>
#include <unordered_map>
#include <functional>

//==============================================================================
// コード定義に基づきコードチェッカーを初期化するクラス
class ChordCheckerInitializer
{
public:
    // コンストラクタ: コード定義と一致確認のコールバックを使用して初期化
    ChordCheckerInitializer(
        const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
        const std::function<bool(const juce::Array<juce::String>&)>& isChordMatch);

    // 初期化されたコードチェッカーを取得
    const std::unordered_map<juce::String, std::function<bool()>>& getChordCheckers() const;

private:
    std::unordered_map<juce::String, std::function<bool()>> chordCheckers;

    // コード定義に基づいてチェッカーを初期化
    void initializeCheckers(
        const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
        const std::function<bool(const juce::Array<juce::String>&)>& isChordMatch);
};

