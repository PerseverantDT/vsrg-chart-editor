module;

#include <memory>
#include <string>
#include <vector>
#include <ranges>

module ChartEditor.Core;

import :Difficulty;
import ChartEditor.Exceptions;

void ChartEditor::Difficulty::addNote(std::weak_ptr<NoteType> noteType, const float beat, const float holdLength, const uint8_t lane) {
    if (std::ranges::find_if(m_notes, [beat, lane](const auto &note) { return note.beat() == beat && note.lane() == lane; }) != m_notes.end()) throw ChartEditor::NoteAlreadyExistsException(beat, lane);

    m_notes.emplace_back(noteType, beat, holdLength, lane);
}

void ChartEditor::Difficulty::editNote(const float beat, const uint8_t lane, EditNoteParams params) {
    const auto note = std::ranges::find_if(m_notes, [beat, lane](const auto &note) { return note.beat() == beat && note.lane() == lane; });
    if (note == m_notes.end()) return;

    if (params.type.has_value()) note->type(params.type.value());
    if (params.holdLength.has_value()) note->holdLength(params.holdLength.value());
}

void ChartEditor::Difficulty::removeNote(const float beat, const uint8_t lane) {
    std::erase_if(m_notes, [beat, lane](const auto &note) { return note.beat() == beat && note.lane() == lane; });
}

std::shared_ptr<ChartEditor::NoteType> ChartEditor::Difficulty::addNoteType(const std::string &name, bool isMine, bool isRoll) {
    auto noteType = std::make_shared<ChartEditor::NoteType>(name, isMine, isRoll);
    m_noteTypes.emplace_back(noteType);

    return noteType;
}

std::shared_ptr<ChartEditor::NoteType> ChartEditor::Difficulty::getNoteType(const std::string &name) const {
    for (const auto &noteType : m_noteTypes) {
        if (noteType->name() == name) return noteType;
    }

    return nullptr;
}

void ChartEditor::Difficulty::removeNoteType(const std::string &name) {
    std::erase_if(m_noteTypes, [name](const auto &noteType) { return noteType->name() == name; });
}
