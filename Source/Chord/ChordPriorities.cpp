#include "ChordPriorities.h"

ChordPriorities::ChordPriorities() {
    chordPriorities = {
        // Faug���ł��p�ɂɏo��L�[
        { "F Major",   { {"Faug", 1}, {"Aaug", 3}, {"C#aug", 2} } },  // Faug��Iaug�Ƃ��ĕs���肳���������AC7�Ɍ����������a���Ƃ��ďd�v
        { "C Major",   { {"Faug", 1}, {"Aaug", 2}, {"C#aug", 3} } },  // Faug��IVaug�Ƃ���V�ɐi�s����O�Ƀe���V��������������
        { "A Minor",   { {"Faug", 1}, {"Aaug", 2}, {"C#aug", 3} } },  // Faug��VIaug�Ƃ���E7�ɐi�s����ۂɕs���芴�𐶂�
        { "D Minor",   { {"Faug", 1}, {"Aaug", 2}, {"C#aug", 3} } },  // Faug��VIaug�Ƃ���A7�ɐi�ލۂɃe���V���������

        // C#aug���ł��p�ɂɏo��L�[
        { "A Major",   { {"C#aug", 1}, {"Aaug", 2}, {"Faug", 3} } },  // C#aug��III�x�̏d�v�ȕό`�a��
        { "E Major",   { {"C#aug", 1}, {"Aaug", 2}, {"Faug", 3} } },  // ������III�x�Ƃ��ďd�v
        { "C# Major",  { {"C#aug", 1}, {"Aaug", 3}, {"Faug", 2} } },  // C#aug�͎��R�Ɋ܂܂��
        { "G# Minor",  { {"C#aug", 1}, {"Aaug", 3}, {"Faug", 2} } },  // ���l��III�x�Ƃ��ďd�v

        // Aaug���ł��p�ɂɏo��L�[
        { "C# Minor",  { {"Aaug", 1}, {"C#aug", 2}, {"Faug", 3} } },  // Aaug��V�x�̑㗝�ŏo��
        { "D Major",   { {"Aaug", 1}, {"Faug", 2},  {"C#aug", 3} } },  // III�x�Ƃ���Aaug���d�v

        // Caug�Ɋ֘A����D�揇��
        { "C Major", { {"Caug", 1}, {"Eaug", 2}, {"G#aug", 3} } }, // C���W���[�̃g�j�b�N�Ƃ���Caug��D��
        { "G Major", { {"Caug", 1}, {"Eaug", 2}, {"G#aug", 3} } }, // Caug��G���W���[�̃T�u�h�~�i���g�iIVaug�j
        { "F Major", { {"Caug", 1}, {"Eaug", 2}, {"G#aug", 3} } }, // Caug��F���W���[�̃h�~�i���g�iVaug�j

        // E���W���[�AA�}�C�i�[�ł�Eaug��D��
        { "E Major", { {"Eaug", 1}, {"Caug", 2}, {"G#aug", 3} } }, // Eaug��E���W���[�̃g�j�b�N�Ƃ��ėD��
        { "A Minor", { {"Eaug", 1}, {"Caug", 2}, {"G#aug", 3} } }, // Eaug��A�}�C�i�[�̃h�~�i���g�iVaug�j

        // G#�}�C�i�[�AC#���W���[�ł�G#aug��D��
        { "G# Minor", { {"G#aug", 1}, {"Caug", 2}, {"Eaug", 3} } }, // G#aug��G#�}�C�i�[�̃g�j�b�N�Ƃ��ėD��
        { "C# Major", { {"G#aug", 1}, {"Caug", 2}, {"Eaug", 3} } },  // G#aug��C#���W���[�̃T�u�h�~�i���g�iIVaug�j

        // D���W���[�AG���W���[�AA���W���[�ł�Daug��D��
        { "D Major", { {"Daug", 1}, {"F#aug", 2}, {"A#aug", 3} } }, // Daug��D���W���[�̃g�j�b�N�Ƃ��ėD��
        { "G Major", { {"Daug", 1}, {"F#aug", 2}, {"A#aug", 3} } }, // Daug��G���W���[�̃h�~�i���g�iVaug�j
        { "A Major", { {"Daug", 1}, {"F#aug", 2}, {"A#aug", 3} } }, // Daug��A���W���[�̃T�u�h�~�i���g�iIVaug�j

        // F#���W���[�AB�}�C�i�[�ł�F#aug��D��
        { "F# Major", { {"F#aug", 1}, {"Daug", 2}, {"A#aug", 3} } }, // F#aug��F#���W���[�̃g�j�b�N�Ƃ��ėD��
        { "B Minor", { {"F#aug", 1}, {"Daug", 2}, {"A#aug", 3} } },  // F#aug��B�}�C�i�[�̃h�~�i���g�iVaug�j

        // A#���W���[�AD#�}�C�i�[�ł�A#aug��D��
        { "A# Major", { {"A#aug", 1}, {"Daug", 2}, {"F#aug", 3} } }, // A#aug��A#���W���[�̃g�j�b�N�Ƃ��ėD��
        { "D# Minor", { {"A#aug", 1}, {"Daug", 2}, {"F#aug", 3} } },  // A#aug��D#�}�C�i�[�̃h�~�i���g�iVaug�j

        // D#aug�Ɋւ���D�揇��
        { "D# Major",  { {"D#aug", 1}, {"Baug", 2}, {"Gaug", 3} } },  // D#aug�̓g�j�b�N�Ƃ��čł��d�v
        { "G Minor",   { {"D#aug", 1}, {"Baug", 2}, {"Gaug", 3} } },  // D#aug��V�x�̕ό`�Ƃ��ēo��

        // Gaug���ł��p�ɂɏo��L�[
        { "G Major",   { {"Gaug", 1}, {"D#aug", 2}, {"Baug", 3} } },  // Gaug�̓g�j�b�N�Ƃ��ďd�v
        { "C Major",   { {"Gaug", 1}, {"Baug", 2}, {"D#aug", 3} } },  // Gaug��V�x�Ƃ��ďd�v

        // Baug���ł��p�ɂɏo��L�[
        { "B Major",   { {"Baug", 1}, {"D#aug", 2}, {"Gaug", 3} } },  // Baug�̓g�j�b�N�Ƃ��čł��d�v
        { "E Minor",   { {"Baug", 1}, {"D#aug", 2}, {"Gaug", 3} } }   // Baug��V�x�Ƃ��ďd�v
    };
}

const std::unordered_map<juce::String, std::unordered_map<juce::String, int>>& ChordPriorities::getChordPriorities() const {
    return chordPriorities;
}
