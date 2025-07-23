// CHORDIN ver 1.1
#pragma once

#include <JuceHeader.h>
#include "../AudioProcessor/PluginProcessor.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel() {}

    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};


class YourPluginAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    YourPluginAudioProcessorEditor(YourPluginAudioProcessor&);
    ~YourPluginAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void showScaleMenu();

private:
    YourPluginAudioProcessor& processorRef;

    juce::ImageButton settingsButton;
    juce::TextButton scaleSelectButton;
    juce::Label notesLabel;
    juce::Label chordLabel;
    juce::Label intervalLabel;
    juce::Label midiTextLabel;
    juce::Label intervalTextLabel;
    juce::Label scaleNotesLabel;
    juce::Label midiNoteLabel;
    juce::Label degreeLabel;
    juce::ToggleButton midiNoteToggleButton;
    juce::ToggleButton intervalToggleButton;
    bool showScaleNotes = true;
    bool showInterval = true;
    juce::Font currentFont;

    void initializeLabel(juce::Label& label, juce::Justification justification, float fontSize, juce::Colour colour, juce::String text = "");
    void initializeToggleButton(juce::ToggleButton& toggleButton, CustomLookAndFeel& lookAndFeel, bool initialState);
    void initializeTextLabel(juce::Label& label, juce::String text, float fontSize, juce::Justification justification);

    void updateScaleNotesLabel();
    void timerCallback() override;
    void showWindowSizeMenu();

    void paintBackground(juce::Graphics& g);

    void paintBar(juce::Graphics& g);
    void paintChordBox(juce::Graphics& g);
    void paintLabels(juce::Graphics& g);
    void paintLabelWithText(juce::Graphics& g, juce::Label& label, const juce::Rectangle<int>& bounds, const juce::String& text, int offset);

    float calculateScaleFactor();
    void setButtonBounds(float scaleFactor);
    void setLabelFontsAndBounds(float scaleFactor);
    void setToggleButtonsAndLabelsBounds(float scaleFactor);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YourPluginAudioProcessorEditor)
};