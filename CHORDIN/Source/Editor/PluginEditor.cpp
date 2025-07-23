// CHORDIN ver 1.1
#include "PluginEditor.h"
#include "BinaryData.h"
#include "../Handler/MidiHandler.h"
#include "../Handler/ScaleHandler.h"
#include "../Handler/MidiProcessor.h"

//==============================================================================
void CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    (void)shouldDrawButtonAsHighlighted;
    (void)shouldDrawButtonAsDown;

    auto bounds = button.getLocalBounds().reduced(10);
    auto lineThickness = bounds.getHeight() / 5;
    auto lineY = bounds.getCentreY();
    auto lineLength = bounds.getWidth() - bounds.getHeight();
    bool isOn = button.getToggleState();

    // ボタンの状態に応じて線の色を設定
    juce::Colour lineColour = isOn ? juce::Colour::fromRGB(255, 46, 91) : juce::Colours::white;
    g.setColour(lineColour);
    g.fillRect(bounds.getX() + bounds.getHeight() / 2, lineY - lineThickness / 2, lineLength, lineThickness);

    // トグルボタンの色と位置を設定
    juce::Colour buttonColour = juce::Colour::fromRGB(43, 50, 59);
    auto toggleSize = bounds.getHeight() / 2;
    auto toggleX = isOn ? (bounds.getX() + lineLength) : (bounds.getX() + bounds.getHeight() / 2);
    auto toggleBounds = juce::Rectangle<int>(toggleX, lineY - toggleSize / 2, toggleSize, toggleSize);

    g.setColour(buttonColour);
    g.fillRect(toggleBounds);
}

//==============================================================================
YourPluginAudioProcessorEditor::YourPluginAudioProcessorEditor(YourPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    static CustomLookAndFeel customLookAndFeel;

    // スケール選択ボタンの設定
    addAndMakeVisible(scaleSelectButton);
    scaleSelectButton.setButtonText("Select Scale");
    scaleSelectButton.onClick = [this]() { showScaleMenu(); };

    // 設定ボタンの設定
    juce::Image gearIcon = juce::ImageCache::getFromMemory(BinaryData::gear_png, BinaryData::gear_pngSize);
    addAndMakeVisible(settingsButton);
    settingsButton.setImages(true, true, true, gearIcon, 1.0f, juce::Colours::transparentBlack, gearIcon, 1.0f, juce::Colours::transparentBlack, gearIcon, 1.0f, juce::Colours::transparentBlack);
    settingsButton.onClick = [this]() { showWindowSizeMenu(); };

    // フォントの設定
    currentFont = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Cornerstone_ttf, BinaryData::Cornerstone_ttfSize));

    // ラベルの設定
    initializeLabel(notesLabel, juce::Justification::centredLeft, 20.0f, juce::Colour::fromRGB(43, 50, 59));
    initializeLabel(chordLabel, juce::Justification::centred, 120.0f, juce::Colour::fromRGB(43, 50, 59));
    initializeLabel(degreeLabel, juce::Justification::centredLeft, 20.0f, juce::Colour::fromRGB(43, 50, 59), "Interval");
    initializeLabel(intervalLabel, juce::Justification::centredLeft, 20.0f, juce::Colour::fromRGB(43, 50, 59));
    initializeLabel(midiNoteLabel, juce::Justification::centredLeft, 20.0f, juce::Colour::fromRGB(43, 50, 59), "Midi Note");
    initializeLabel(scaleNotesLabel, juce::Justification::centredLeft, 20.0f, juce::Colour::fromRGB(43, 50, 59));

    // トグルボタンの設定
    initializeToggleButton(midiNoteToggleButton, customLookAndFeel, true);
    initializeToggleButton(intervalToggleButton, customLookAndFeel, true);

    // テキストラベルの設定
    initializeTextLabel(midiTextLabel, "MIDI", 20.0f, juce::Justification::centredLeft);
    initializeTextLabel(intervalTextLabel, "INTE", 20.0f, juce::Justification::centredLeft);

    // トグルボタンの動作設定
    midiNoteToggleButton.onClick = [this]() {
        showScaleNotes = midiNoteToggleButton.getToggleState();
        if (!showScaleNotes) {
            notesLabel.setText("", juce::dontSendNotification);
        }
        repaint();
        };

    intervalToggleButton.onClick = [this]() {
        showInterval = intervalToggleButton.getToggleState();
        repaint();
        };

    // ウィンドウサイズの設定
    setSize(400, 400);
    startTimerHz(30);
}

void YourPluginAudioProcessorEditor::initializeLabel(juce::Label& label, juce::Justification justification, float fontSize, juce::Colour colour, juce::String text)
{
    addAndMakeVisible(label); // ラベルを表示
    label.setJustificationType(justification); // ラベルの位置
    label.setFont(currentFont.withHeight(fontSize)); // フォントサイズを設定
    label.setColour(juce::Label::textColourId, colour); // テキストの色を設定
    if (!text.isEmpty())
        label.setText(text, juce::dontSendNotification); // 初期テキストを設定
}

// トグルボタンを設定する処理
void YourPluginAudioProcessorEditor::initializeToggleButton(juce::ToggleButton& toggleButton, CustomLookAndFeel& lookAndFeel, bool initialState)
{
    addAndMakeVisible(toggleButton);
    toggleButton.setLookAndFeel(&lookAndFeel);
    toggleButton.setToggleState(initialState, juce::dontSendNotification);
}

// テキストラベルを設定する処理
void YourPluginAudioProcessorEditor::initializeTextLabel(juce::Label& label, juce::String text, float fontSize, juce::Justification justification)
{
    addAndMakeVisible(label);
    label.setText(text, juce::dontSendNotification);
    label.setFont(currentFont.withHeight(fontSize));
    label.setJustificationType(justification);
}

YourPluginAudioProcessorEditor::~YourPluginAudioProcessorEditor()
{
    midiNoteToggleButton.setLookAndFeel(nullptr);
    intervalToggleButton.setLookAndFeel(nullptr);
}

void YourPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    paintBackground(g);               // 背景描画
    paintBar(g);                      // バー描画
    paintChordBox(g);                 // コードボックスの描画
    paintLabels(g);                   // ラベルやテキストの描画
}

// 背景を描画する処理
void YourPluginAudioProcessorEditor::paintBackground(juce::Graphics& g)
{
    juce::Colour backgroundColour = juce::Colour::fromRGB(230, 232, 234);
    g.fillAll(backgroundColour);
}

// 上部のバーを描画する処理
void YourPluginAudioProcessorEditor::paintBar(juce::Graphics& g)
{
    int barHeight = static_cast<int>(2.0f * (getHeight() / 400.0f));
    int barY = static_cast<int>(50 * (getHeight() / 400.0f));
    juce::Rectangle<int> barArea(0, barY, getWidth(), barHeight);
    g.setColour(juce::Colour::fromRGB(43, 50, 59));
    g.fillRect(barArea);

    juce::DropShadow shadow(juce::Colours::black.withAlpha(0.5f), 3, juce::Point<int>(0, 2));
    shadow.drawForRectangle(g, barArea);
}

// コードボックスおよびその周りの描画
void YourPluginAudioProcessorEditor::paintChordBox(juce::Graphics& g)
{
    int chordBoxSize = static_cast<int>(juce::jmin(getWidth() / 2.0f, getHeight() / 2.0f));
    int offsetY = static_cast<int>(-30.0f * (getHeight() / 400.0f));
    juce::Rectangle<int> chordBox((getWidth() - chordBoxSize) / 4, (getHeight() - chordBoxSize) / 2 + offsetY,
        chordBoxSize + (chordBoxSize / 2), chordBoxSize - static_cast<int>(25 * (getHeight() / 400.0f)));

    g.setColour(juce::Colour::fromRGB(255, 46, 91));
    g.drawRoundedRectangle(chordBox.toFloat(), 10.0f * (getHeight() / 400.0f), 2.0f * (getHeight() / 400.0f));

    // コードテキストエリア
    int textX = chordBox.getX();
    int textY = chordBox.getY() - static_cast<int>(10.0f * (getHeight() / 400.0f));
    int textWidth = chordBox.getWidth();
    int textHeight = static_cast<int>(20.0f * (getHeight() / 400.0f));

    juce::Colour backgroundColour = juce::Colour::fromRGB(230, 232, 234);
    g.setColour(backgroundColour);
    g.fillRect(textX + static_cast<int>(50 * (getWidth() / 400.0f)), textY, textWidth - static_cast<int>(100 * (getWidth() / 400.0f)), textHeight);

    g.setFont(currentFont.withHeight(20.0f * (getHeight() / 400.0f)));
    g.setColour(juce::Colour::fromRGB(43, 50, 59));
    g.drawText("Chords", textX, textY, textWidth, textHeight, juce::Justification::centred);
}

// ラベルやMIDI、インターバルの描画
void YourPluginAudioProcessorEditor::paintLabels(juce::Graphics& g)
{
    paintLabelWithText(g, midiNoteLabel, midiNoteLabel.getBounds(), ":", 10);
    paintLabelWithText(g, degreeLabel, degreeLabel.getBounds(), ":", 10);

    juce::Colour labelBarColour = juce::Colour::fromRGB(43, 50, 59);
    int labelBarHeight = 2;
    int spacing = 5;

    // MIDIとインターバルバーの描画
    juce::Rectangle<int> midiNoteBarArea = midiNoteLabel.getBounds().withY(midiNoteLabel.getBottom() + spacing).withHeight(labelBarHeight);
    midiNoteBarArea.setWidth(getWidth() - midiNoteLabel.getX() * 2);
    g.setColour(labelBarColour);
    g.fillRect(midiNoteBarArea);

    juce::Rectangle<int> intervalBarArea = intervalLabel.getBounds().withX(midiNoteLabel.getX()).withY(intervalLabel.getBottom() + spacing).withHeight(labelBarHeight);
    intervalBarArea.setWidth(getWidth() - midiNoteLabel.getX() * 2);
    g.setColour(labelBarColour);
    g.fillRect(intervalBarArea);
}

// テキストとラベルを描画する処理
void YourPluginAudioProcessorEditor::paintLabelWithText(juce::Graphics& g, juce::Label& label, const juce::Rectangle<int>& bounds, const juce::String& text, int offset)
{
    g.setFont(currentFont.withHeight(20.0f * (getHeight() / 400.0f)));
    g.setColour(juce::Colour::fromRGB(43, 50, 59));
    g.drawText(text, bounds.getRight() - static_cast<int>(offset * (getWidth() / 400.0f)),
        bounds.getY(), static_cast<int>(10 * (getWidth() / 400.0f)),
        bounds.getHeight(), juce::Justification::centredLeft);
}

void YourPluginAudioProcessorEditor::resized()
{
    float scaleFactor = calculateScaleFactor();

    setButtonBounds(scaleFactor);             // ボタンの位置を設定
    setLabelFontsAndBounds(scaleFactor);      // ラベルのフォントと位置を設定
    setToggleButtonsAndLabelsBounds(scaleFactor); // トグルボタンとラベルの位置を設定
}

// スケーリングファクターを計算する処理
float YourPluginAudioProcessorEditor::calculateScaleFactor()
{
    return juce::jmin(getWidth() / 400.0f, getHeight() / 400.0f);
}

// ボタンの位置を設定する処理
void YourPluginAudioProcessorEditor::setButtonBounds(float scaleFactor)
{
    int buttonWidth = static_cast<int>(40 * scaleFactor);
    int buttonHeight = static_cast<int>(40 * scaleFactor);
    int buttonX = getWidth() - buttonWidth - static_cast<int>(2 * scaleFactor);
    int buttonY = getHeight() - buttonHeight - static_cast<int>(scaleFactor);
    settingsButton.setBounds(buttonX, buttonY, buttonWidth, buttonHeight);
}

// ラベルのフォントと位置を設定する処理
void YourPluginAudioProcessorEditor::setLabelFontsAndBounds(float scaleFactor)
{
    float baseFontSize = 20.0f;
    float chordLabelFontSize = 50.0f * scaleFactor;

    notesLabel.setFont(currentFont.withHeight(baseFontSize * scaleFactor));
    chordLabel.setFont(juce::Font("Tahoma", chordLabelFontSize, juce::Font::plain));
    degreeLabel.setFont(currentFont.withHeight(baseFontSize * scaleFactor));
    intervalLabel.setFont(currentFont.withHeight(baseFontSize * scaleFactor));
    midiNoteLabel.setFont(currentFont.withHeight(baseFontSize * scaleFactor));
    scaleNotesLabel.setFont(currentFont.withHeight(baseFontSize * scaleFactor));

    int labelWidth = static_cast<int>(120 * scaleFactor);
    int labelHeight = static_cast<int>(30 * scaleFactor);
    int spacing = static_cast<int>(15 * scaleFactor);
    int startY = static_cast<int>((getHeight() / 2.0f) + (70.0f * scaleFactor));

    midiNoteLabel.setBounds(static_cast<int>(10 * scaleFactor), startY, labelWidth, labelHeight);
    notesLabel.setBounds(labelWidth + static_cast<int>(20 * scaleFactor), startY, getWidth() - labelWidth - static_cast<int>(30 * scaleFactor), labelHeight);

    degreeLabel.setBounds(static_cast<int>(10 * scaleFactor), startY + labelHeight + spacing, labelWidth, labelHeight);
    intervalLabel.setBounds(labelWidth + static_cast<int>(20 * scaleFactor), startY + labelHeight + spacing, getWidth() - labelWidth - static_cast<int>(30 * scaleFactor), labelHeight);

    scaleSelectButton.setBounds(static_cast<int>(10 * scaleFactor), static_cast<int>(10 * scaleFactor), static_cast<int>(150 * scaleFactor), static_cast<int>(30 * scaleFactor));
    scaleNotesLabel.setBounds(static_cast<int>(170 * scaleFactor), static_cast<int>(10 * scaleFactor), getWidth() - static_cast<int>(180 * scaleFactor), static_cast<int>(30 * scaleFactor));

    chordLabel.setBounds(getWidth() / 4, getHeight() / 2 - static_cast<int>(75 * scaleFactor), getWidth() / 2, static_cast<int>(60 * scaleFactor));
}

// トグルボタンとラベルの位置を設定する処理
void YourPluginAudioProcessorEditor::setToggleButtonsAndLabelsBounds(float scaleFactor)
{
    int toggleButtonWidth = static_cast<int>(60 * scaleFactor);
    int toggleButtonHeight = static_cast<int>(30 * scaleFactor);
    int labelWidth = static_cast<int>(120 * scaleFactor);
    int labelHeight = static_cast<int>(30 * scaleFactor);
    int spacing = static_cast<int>(15 * scaleFactor);
    int startY = static_cast<int>((getHeight() / 2.0f) + (70.0f * scaleFactor));
    int toggleButtonY = startY + labelHeight + spacing + labelHeight + spacing;

    juce::Colour textColor = juce::Colour::fromRGB(43, 50, 59);
    float fontSize = 15.0f * scaleFactor;

    midiTextLabel.setFont(currentFont.withHeight(fontSize));
    midiTextLabel.setColour(juce::Label::textColourId, textColor);
    midiTextLabel.setBounds(static_cast<int>(10 * scaleFactor), toggleButtonY, static_cast<int>(40 * scaleFactor), toggleButtonHeight);

    midiNoteToggleButton.setBounds(static_cast<int>(50 * scaleFactor), toggleButtonY, toggleButtonWidth, toggleButtonHeight);

    intervalTextLabel.setFont(currentFont.withHeight(fontSize));
    intervalTextLabel.setColour(juce::Label::textColourId, textColor);
    intervalTextLabel.setBounds(static_cast<int>(110 * scaleFactor), toggleButtonY, static_cast<int>(40 * scaleFactor), toggleButtonHeight);

    intervalToggleButton.setBounds(static_cast<int>(150 * scaleFactor), toggleButtonY, toggleButtonWidth, toggleButtonHeight);
}


void YourPluginAudioProcessorEditor::updateScaleNotesLabel()
{

    juce::String scaleNotesText;
    for (const auto& note : processorRef.getScaleNotes())
    {
        scaleNotesText += note + " ";
    }
    scaleNotesLabel.setText(scaleNotesText.trim(), juce::dontSendNotification);
}



void YourPluginAudioProcessorEditor::timerCallback()
{
    auto activeNotes = processorRef.getActiveNotes();

    if (showScaleNotes)
    {
        juce::String allNotes;
        for (int note : processorRef.getActiveNotes())
        {
            allNotes += MidiHandler::midiNoteNumberToNoteName(note) + " ";

        }
        notesLabel.setText(allNotes.trim(), juce::dontSendNotification);
    }
    else
    {
        notesLabel.setText("", juce::dontSendNotification);
    }

    chordLabel.setText(processorRef.getChordName().isEmpty() ? "" : processorRef.getChordName(), juce::dontSendNotification);

    juce::String scaleNotesText;
    for (const auto& note : processorRef.getScaleNotes())
    {
        scaleNotesText += note + " ";
    }
    scaleNotesLabel.setText(scaleNotesText.trim(), juce::dontSendNotification);

    if (showInterval)
    {
        juce::String intervalText = "";

        if (activeNotes.size() == 2)
        {
            int distance = std::abs(activeNotes[1] - activeNotes[0]);

            switch (distance)
            {
            case 0: intervalText = "Unison"; break;
            case 1: intervalText = "Minor 2nd"; break;
            case 2: intervalText = "Major 2nd"; break;
            case 3: intervalText = "Minor 3rd"; break;
            case 4: intervalText = "Major 3rd"; break;
            case 5: intervalText = "Perfect 4th"; break;
            case 6: intervalText = "Tritone"; break;
            case 7: intervalText = "Perfect 5th"; break;
            case 8: intervalText = "Minor 6th"; break;
            case 9: intervalText = "Major 6th"; break;
            case 10: intervalText = "Minor 7th"; break;
            case 11: intervalText = "Major 7th"; break;
            case 12: intervalText = "Octave"; break;
            case 13: intervalText = "Minor 9th"; break;
            default: intervalText = "Unknown Interval"; break;
            }
        }

        intervalLabel.setText(intervalText, juce::dontSendNotification);
    }
    else
    {
        intervalLabel.setText("", juce::dontSendNotification);
    }
}

void YourPluginAudioProcessorEditor::showWindowSizeMenu()
{

    juce::PopupMenu menu;
    menu.addItem("(300x300)", [this] { setSize(300, 300); });
    menu.addItem("(400x400)", [this] { setSize(400, 400); });
    menu.addItem("(500x500)", [this] { setSize(500, 500); });
    menu.addItem("(600x600)", [this] { setSize(600, 600); });

    menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&settingsButton));
}

void YourPluginAudioProcessorEditor::showScaleMenu()
{
    juce::PopupMenu menu;



    auto addScaleItems = [&](juce::PopupMenu& subMenu, const juce::StringArray& scales) {
        for (const auto& scale : scales)
        {
            subMenu.addItem(scale, [this, scale] { processorRef.updateScale(scale);
                });
        }
        };

    juce::StringArray majorScales = { "C Major", "C# Major", "D Major", "D# Major", "E Major", "F Major", "F# Major", "G Major", "G# Major", "A Major", "A# Major", "B Major" };
    juce::StringArray minorScales = { "C Minor", "C# Minor", "D Minor", "D# Minor", "E Minor", "F Minor", "F# Minor", "G Minor", "G# Minor", "A Minor", "A# Minor", "B Minor" };

    juce::PopupMenu majorMenu, minorMenu;
    addScaleItems(majorMenu, majorScales);
    addScaleItems(minorMenu, minorScales);

    menu.addSubMenu("Major Scales", majorMenu);
    menu.addSubMenu("Minor Scales", minorMenu);



    menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&scaleSelectButton));
}