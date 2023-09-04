module;

#include <memory>
#include <string>
#include <vector>

export module ChartEditor.Core:Difficulty;

import :Note;
import :NoteType;

namespace ChartEditor {
    export class Difficulty {
    private:
        std::string m_name; 
        std::vector<std::shared_ptr<NoteType>> m_noteTypes;
        std::vector<Note> m_notes;
    public:
        [[nodiscard]] const std::string &name() const noexcept { return m_name; }
        [[nodiscard]] const std::vector<std::shared_ptr<NoteType>> &noteTypes() const noexcept { return m_noteTypes; }
        [[nodiscard]] const std::vector<Note> &notes() const noexcept { return m_notes; }

        void name(const std::string &name) { m_name = name; }

        void addNote(const float beat, const uint8_t lane) { addNote({}, beat, 0.0F, lane); }
        void addNote(const float beat, const float holdLength, const uint8_t lane) { addNote({}, beat, holdLength, lane); }
        void addNote(std::weak_ptr<NoteType> noteType, const float beat, const uint8_t lane) { addNote(noteType, beat, 0.0F, lane); }
        void addNote(std::weak_ptr<NoteType> noteType, float beat, float holdLength, uint8_t lane);
        void editNote(float beat, uint8_t lane, EditNoteParams params);
        void removeNote(float beat, uint8_t lane);

        std::shared_ptr<NoteType> addNoteType(const std::string &name, bool isMine, bool isRoll);
        [[nodiscard]] std::shared_ptr<NoteType> getNoteType(const std::string &name) const;
        void removeNoteType(const std::string &name);

        explicit Difficulty(const std::string &name) : m_name(name) {}
        virtual ~Difficulty() = default;

        Difficulty(const Difficulty &) = delete;
        Difficulty(Difficulty &&) = delete;
        Difficulty &operator=(const Difficulty &) = delete;
        Difficulty &operator=(Difficulty &&) = delete;
    };
}
