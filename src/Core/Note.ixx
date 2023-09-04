module;

#include <memory>
#include <stdexcept>
#include <optional>

export module ChartEditor.Core:Note;

import :NoteType;
import ChartEditor.Exceptions;

namespace ChartEditor {
    export class Note {
    private:
        std::weak_ptr<NoteType> m_type;
        float m_beat;
        float m_holdLength = 0.0F;
        uint8_t m_lane;
    public:
        [[nodiscard]] NoteType type() const noexcept {
            if (const auto type = m_type.lock(); type != nullptr) return *type;
            return const_cast<NoteType &>(NoteType::DEFAULT());
        }
        [[nodiscard]] float beat() const noexcept { return m_beat; }
        [[nodiscard]] float holdLength() const noexcept { return m_holdLength; }
        [[nodiscard]] uint8_t lane() const noexcept { return m_lane; }

        void type(const std::weak_ptr<NoteType> &type) noexcept { m_type = type; }
        void holdLength(const float holdLength) noexcept { m_holdLength = holdLength; }

        Note(const std::weak_ptr<NoteType> &type, const float beat, const float holdLength, const uint8_t lane) : m_type(type), m_beat(beat), m_holdLength(holdLength), m_lane(lane) {
            if (beat < 0.0F) throw std::invalid_argument("Cannot create note before the first beat");
            if (holdLength < 0.0F) throw std::invalid_argument("Cannot create note with negative hold length");
        }

        Note(const float beat, const uint8_t lane) : Note({}, beat, 0.0F, lane) {}
        Note(const float beat, const float holdLength, const uint8_t lane) : Note({}, beat, holdLength, lane) {}
        Note(const std::weak_ptr<NoteType> &type, const float beat, const uint8_t lane) : Note(type, beat, 0.0F, lane) {}
        virtual ~Note() = default;

        Note(const Note &) = default;
        Note &operator=(const Note &) = default;
        Note(Note &&) = default;
        Note &operator=(Note &&) = default;
    };
}
