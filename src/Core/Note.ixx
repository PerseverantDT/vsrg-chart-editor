module;

#include <memory>

export module ChartEditor.Core:Note;

import :NoteType;

namespace ChartEditor {
    export class Note {
    private:
        std::weak_ptr<NoteType> m_type;
        float m_beat;
        float m_holdLength = 0.0F;
        uint8_t m_lane;
    public:
        [[nodiscard]] const NoteType &getType() const noexcept {
            if (const auto type = m_type.lock(); type != nullptr) return *type;
            return NoteType::DEFAULT();
        }
        [[nodiscard]] float getBeat() const noexcept { return m_beat; }
        [[nodiscard]] float getHoldLength() const noexcept { return m_holdLength; }
        [[nodiscard]] uint8_t getLane() const noexcept { return m_lane; }

        void setType(const std::weak_ptr<NoteType> &type) noexcept { m_type = type; }
        void setHoldLength(const float holdLength) noexcept { m_holdLength = holdLength; }

        Note(const float beat, const uint8_t lane) : m_beat(beat), m_lane(lane) {}
        Note(const float beat, const float holdLength, const uint8_t lane) : m_beat(beat), m_holdLength(holdLength), m_lane(lane) {}
        Note(const std::weak_ptr<NoteType> &type, const float beat, const uint8_t lane) : m_type(type), m_beat(beat), m_lane(lane) {}
        Note(const std::weak_ptr<NoteType> &type, const float beat, const float holdLength, const uint8_t lane) : m_type(type), m_beat(beat), m_holdLength(holdLength), m_lane(lane) {}
        virtual ~Note() = default;

        Note(const Note &) = default;
        Note &operator=(const Note &) = default;
        Note(Note &&) = default;
        Note &operator=(Note &&) = default;
    };
}
