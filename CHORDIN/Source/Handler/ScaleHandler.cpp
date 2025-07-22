#include "ScaleHandler.h"

//==============================================================================
ScaleHandler::ScaleHandler()
{
    initializeScaleMap();
}

ScaleHandler::~ScaleHandler() = default;

//==============================================================================
void ScaleHandler::initializeScaleMap()
{
    scaleMap = {
        { "C Major", {"C", "D", "E", "F", "G", "A", "B"} },
        { "C# Major", {"C#", "D#", "F", "F#", "G#", "A#", "C"} },
        { "D Major", {"D", "E", "F#", "G", "A", "B", "C#"} },
        { "D# Major", {"D#", "F", "G", "G#", "A#", "C", "D"} },
        { "E Major", {"E", "F#", "G#", "A", "B", "C#", "D#"} },
        { "F Major", {"F", "G", "A", "A#", "C", "D", "E"} },
        { "F# Major", {"F#", "G#", "A#", "B", "C#", "D#", "E#"} },
        { "G Major", {"G", "A", "B", "C", "D", "E", "F#"} },
        { "G# Major", {"G#", "A#", "C", "C#", "D#", "F", "G"} },
        { "A Major", {"A", "B", "C#", "D", "E", "F#", "G#"} },
        { "A# Major", {"A#", "C", "D", "D#", "F", "G", "A"} },
        { "B Major", {"B", "C#", "D#", "E", "F#", "G#", "A#"} },
        { "C Minor", {"C", "D", "D#", "F", "G", "G#", "A#"} },
        { "C# Minor", {"C#", "D#", "E", "F#", "G#", "A", "B"} },
        { "D Minor", {"D", "E", "F", "G", "A", "A#", "C"} },
        { "D# Minor", {"D#", "E#", "F#", "G#", "A#", "B", "C#"} },
        { "E Minor", {"E", "F#", "G", "A", "B", "C", "D"} },
        { "F Minor", {"F", "G", "G#", "A#", "C", "C#", "D#"} },
        { "F# Minor", {"F#", "G#", "A", "B", "C#", "D", "E"} },
        { "G Minor", {"G", "A", "A#", "C", "D", "D#", "F"} },
        { "G# Minor", {"G#", "A#", "B", "C#", "D#", "E", "F#"} },
        { "A Minor", {"A", "B", "C", "D", "E", "F", "G"} },
        { "A# Minor", {"A#", "C", "C#", "D#", "F", "F#", "G#"} },
        { "B Minor", {"B", "C#", "D", "E", "F#", "G", "A"} }
    };
}

//==============================================================================
void ScaleHandler::updateScale(const juce::String& newScale)
{
    currentScale = newScale;

    auto it = scaleMap.find(newScale);
    if (it != scaleMap.end())
    {
        scaleNotes = it->second;
    }
    else
    {
        scaleNotes.clear(); // 無効なスケールの場合は空にする
    }
}
