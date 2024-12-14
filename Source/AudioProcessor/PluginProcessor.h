#pragma once

#include <JuceHeader.h>
#include "../Chord/ChordDefinitions.h"
#include "../Handler/ScaleHandler.h"
#include "../Matchers/ChordMatcher.h"
#include "../Handler/MidiProcessor.h"

#include <mutex>

//==============================================================================
// MIDI メッセージの処理、コード認識、スケール情報管理を行うプラグイン
class YourPluginAudioProcessor : public juce::AudioProcessor
{
public:
    YourPluginAudioProcessor();
    ~YourPluginAudioProcessor() override;

    juce::String getChordName() const;                        // 現在のコード名

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    juce::Array<int> getActiveNotes() const;                  // 現在のアクティブノート
    void updateScale(const juce::String& newScale);
    juce::Array<juce::String> getScaleNotes() const;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    juce::Array<int> processMidiMessages(juce::MidiBuffer& midiMessages); // MIDI メッセージの処理
    void updateChordName(const juce::Array<int>& notesSnapshot);          // コード名の更新

    juce::Array<int> activeNotes;
    juce::Array<juce::String> scaleOutNotes;
    juce::String chordName;

    mutable std::mutex activeNotesMutex;
    mutable std::mutex chordNameMutex;

    ChordDefinitions chordDefinitions;
    ScaleHandler scaleHandler;
    ChordMatcher chordMatcher;
    MidiProcessor midiProcessor;
};