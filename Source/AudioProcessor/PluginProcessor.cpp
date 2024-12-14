#include "PluginProcessor.h"
#include "../Editor/PluginEditor.h"
#include "../Handler/MidiHandler.h"
#include "../Chord/ChordDefinitions.h"
#include "../Handler/ScaleHandler.h"
#include "../Matchers/ChordMatcher.h"
#include "../Handler/MidiProcessor.h"
#include <functional>

//==============================================================================

YourPluginAudioProcessor::YourPluginAudioProcessor()
    : AudioProcessor(/*...*/)
    , scaleHandler()    // スケール処理の管理クラス
    , chordMatcher()    // コードマッチングのロジック
    , midiProcessor()   // MIDI メッセージの処理
{
}

YourPluginAudioProcessor::~YourPluginAudioProcessor() = default;

//==============================================================================
// プラグイン初期化とリソース解放

void YourPluginAudioProcessor::prepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // コードマッチャーの初期化: コード定義とコールバックを設定
    chordMatcher.initialize(
        chordDefinitions.getChordDefinitions(),
        [this](const juce::Array<juce::String>& expectedNotes) {
            return chordMatcher.isChordMatch(expectedNotes, midiProcessor.getActiveNotes());
        }
    );
}

void YourPluginAudioProcessor::releaseResources()
{
}

//==============================================================================
// バスレイアウトのサポート判定

bool YourPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // モノラルまたはステレオ出力のみをサポート
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

//==============================================================================
// オーディオ処理メインループ

void YourPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // オーディオバッファは使用しない場合もあるため明示的に無視
    (void)buffer;

    // MIDI メッセージを処理してアクティブノートを取得
    auto notesSnapshot = processMidiMessages(midiMessages);

    // アクティブノートに基づいてコード名を更新
    updateChordName(notesSnapshot);
}

//==============================================================================
// MIDI メッセージの処理とアクティブノート取得

juce::Array<int> YourPluginAudioProcessor::processMidiMessages(juce::MidiBuffer& midiMessages)
{
    return midiProcessor.processAndGetActiveNotes(midiMessages);
}

//==============================================================================
// コード名の更新ロジック

void YourPluginAudioProcessor::updateChordName(const juce::Array<int>& notesSnapshot)
{
    // スレッド安全性を確保しつつコード名を更新
    std::lock_guard<std::mutex> lock(this->chordNameMutex);
    this->chordName = chordMatcher.updateChord(notesSnapshot);
}

//==============================================================================
// 公開メソッド: コード名とスケールノート取得

juce::String YourPluginAudioProcessor::getChordName() const
{
    // スレッド安全性を確保してコード名を返す
    std::lock_guard<std::mutex> lock(chordNameMutex);
    return chordName;
}

juce::Array<juce::String> YourPluginAudioProcessor::getScaleNotes() const
{
    return scaleHandler.getScaleNotes();
}

//==============================================================================
// スケール更新（Editor 側から呼び出し）

void YourPluginAudioProcessor::updateScale(const juce::String& newScale)
{
    scaleHandler.updateScale(newScale);
}

//==============================================================================
// アクティブノートの取得（Editor 側での表示用）

juce::Array<int> YourPluginAudioProcessor::getActiveNotes() const
{
    return midiProcessor.getActiveNotes();
}

//==============================================================================
// Editor 関連の設定

juce::AudioProcessorEditor* YourPluginAudioProcessor::createEditor()
{
    return new YourPluginAudioProcessorEditor(*this);
}

bool YourPluginAudioProcessor::hasEditor() const
{
    return true;
}

//==============================================================================
// プラグインの基本情報

const juce::String YourPluginAudioProcessor::getName() const { return JucePlugin_Name; }
bool YourPluginAudioProcessor::acceptsMidi() const { return true; }
bool YourPluginAudioProcessor::producesMidi() const { return true; }
bool YourPluginAudioProcessor::isMidiEffect() const { return false; }
double YourPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

//==============================================================================
// プログラム関連

int YourPluginAudioProcessor::getNumPrograms() { return 1; }
int YourPluginAudioProcessor::getCurrentProgram() { return 0; }
void YourPluginAudioProcessor::setCurrentProgram(int) {}
const juce::String YourPluginAudioProcessor::getProgramName(int) { return {}; }
void YourPluginAudioProcessor::changeProgramName(int, const juce::String&) {}

//==============================================================================
// 状態保存と復元

void YourPluginAudioProcessor::getStateInformation(juce::MemoryBlock&)
{
}

void YourPluginAudioProcessor::setStateInformation(const void*, int)
{
}

//==============================================================================
// ファクトリ関数

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new YourPluginAudioProcessor();
}
