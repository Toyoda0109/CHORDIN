#include "ChordPriorities.h"

ChordPriorities::ChordPriorities() {
    chordPriorities = {
        // Faugが最も頻繁に出るキー
        { "F Major",   { {"Faug", 1}, {"Aaug", 3}, {"C#aug", 2} } },  // FaugはIaugとして不安定さを強調し、C7に向かう準備和音として重要
        { "C Major",   { {"Faug", 1}, {"Aaug", 2}, {"C#aug", 3} } },  // FaugはIVaugとしてVに進行する前にテンションを持たせる
        { "A Minor",   { {"Faug", 1}, {"Aaug", 2}, {"C#aug", 3} } },  // FaugはVIaugとしてE7に進行する際に不安定感を生む
        { "D Minor",   { {"Faug", 1}, {"Aaug", 2}, {"C#aug", 3} } },  // FaugはVIaugとしてA7に進む際にテンションを作る

        // C#augが最も頻繁に出るキー
        { "A Major",   { {"C#aug", 1}, {"Aaug", 2}, {"Faug", 3} } },  // C#augはIII度の重要な変形和音
        { "E Major",   { {"C#aug", 1}, {"Aaug", 2}, {"Faug", 3} } },  // 同じくIII度として重要
        { "C# Major",  { {"C#aug", 1}, {"Aaug", 3}, {"Faug", 2} } },  // C#augは自然に含まれる
        { "G# Minor",  { {"C#aug", 1}, {"Aaug", 3}, {"Faug", 2} } },  // 同様にIII度として重要

        // Aaugが最も頻繁に出るキー
        { "C# Minor",  { {"Aaug", 1}, {"C#aug", 2}, {"Faug", 3} } },  // AaugはV度の代理で出現
        { "D Major",   { {"Aaug", 1}, {"Faug", 2},  {"C#aug", 3} } },  // III度としてAaugが重要

        // Caugに関連する優先順位
        { "C Major", { {"Caug", 1}, {"Eaug", 2}, {"G#aug", 3} } }, // CメジャーのトニックとしてCaugを優先
        { "G Major", { {"Caug", 1}, {"Eaug", 2}, {"G#aug", 3} } }, // CaugはGメジャーのサブドミナント（IVaug）
        { "F Major", { {"Caug", 1}, {"Eaug", 2}, {"G#aug", 3} } }, // CaugはFメジャーのドミナント（Vaug）

        // Eメジャー、AマイナーではEaugを優先
        { "E Major", { {"Eaug", 1}, {"Caug", 2}, {"G#aug", 3} } }, // EaugはEメジャーのトニックとして優先
        { "A Minor", { {"Eaug", 1}, {"Caug", 2}, {"G#aug", 3} } }, // EaugはAマイナーのドミナント（Vaug）

        // G#マイナー、C#メジャーではG#augを優先
        { "G# Minor", { {"G#aug", 1}, {"Caug", 2}, {"Eaug", 3} } }, // G#augはG#マイナーのトニックとして優先
        { "C# Major", { {"G#aug", 1}, {"Caug", 2}, {"Eaug", 3} } },  // G#augはC#メジャーのサブドミナント（IVaug）

        // Dメジャー、Gメジャー、AメジャーではDaugを優先
        { "D Major", { {"Daug", 1}, {"F#aug", 2}, {"A#aug", 3} } }, // DaugはDメジャーのトニックとして優先
        { "G Major", { {"Daug", 1}, {"F#aug", 2}, {"A#aug", 3} } }, // DaugはGメジャーのドミナント（Vaug）
        { "A Major", { {"Daug", 1}, {"F#aug", 2}, {"A#aug", 3} } }, // DaugはAメジャーのサブドミナント（IVaug）

        // F#メジャー、BマイナーではF#augを優先
        { "F# Major", { {"F#aug", 1}, {"Daug", 2}, {"A#aug", 3} } }, // F#augはF#メジャーのトニックとして優先
        { "B Minor", { {"F#aug", 1}, {"Daug", 2}, {"A#aug", 3} } },  // F#augはBマイナーのドミナント（Vaug）

        // A#メジャー、D#マイナーではA#augを優先
        { "A# Major", { {"A#aug", 1}, {"Daug", 2}, {"F#aug", 3} } }, // A#augはA#メジャーのトニックとして優先
        { "D# Minor", { {"A#aug", 1}, {"Daug", 2}, {"F#aug", 3} } },  // A#augはD#マイナーのドミナント（Vaug）

        // D#augに関する優先順位
        { "D# Major",  { {"D#aug", 1}, {"Baug", 2}, {"Gaug", 3} } },  // D#augはトニックとして最も重要
        { "G Minor",   { {"D#aug", 1}, {"Baug", 2}, {"Gaug", 3} } },  // D#augはV度の変形として登場

        // Gaugが最も頻繁に出るキー
        { "G Major",   { {"Gaug", 1}, {"D#aug", 2}, {"Baug", 3} } },  // Gaugはトニックとして重要
        { "C Major",   { {"Gaug", 1}, {"Baug", 2}, {"D#aug", 3} } },  // GaugはV度として重要

        // Baugが最も頻繁に出るキー
        { "B Major",   { {"Baug", 1}, {"D#aug", 2}, {"Gaug", 3} } },  // Baugはトニックとして最も重要
        { "E Minor",   { {"Baug", 1}, {"D#aug", 2}, {"Gaug", 3} } }   // BaugはV度として重要
    };
}

const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& ChordPriorities::getChordPriorities() const {
    return chordPriorities;
}
