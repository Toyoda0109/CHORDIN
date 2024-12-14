#include "ChordCheckerInitializer.h"

//==============================================================================
// �R�[�h��`�ƈ�v�m�F�R�[���o�b�N���󂯎�菉���������s
ChordCheckerInitializer::ChordCheckerInitializer(
    const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
    const std::function<bool(const juce::Array<juce::String>&)>& isChordMatch)
{
    initializeCheckers(chordDefinitions, isChordMatch);
}

//==============================================================================
// �e�R�[�h���ɑΉ�����`�F�b�J�[�֐����쐬���AchordCheckers �Ɋi�[
void ChordCheckerInitializer::initializeCheckers(
    const std::unordered_map<juce::String, juce::Array<juce::String>>& chordDefinitions,
    const std::function<bool(const juce::Array<juce::String>&)>& isChordMatch)
{
    for (const auto& [chordName, expectedNotes] : chordDefinitions)
    {
        // �e�R�[�h���ɑΉ�����`�F�b�J�[��ݒ�
        chordCheckers[chordName] = [expectedNotes, &isChordMatch] {
            return isChordMatch(expectedNotes);
            };
    }
}

//==============================================================================
// �������ς݂̃R�[�h�`�F�b�J�[��Ԃ�
const std::unordered_map<juce::String, std::function<bool()>>& ChordCheckerInitializer::getChordCheckers() const
{
    return chordCheckers;
}
