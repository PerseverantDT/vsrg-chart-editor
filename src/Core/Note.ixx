module;

#include <memory>
#include <stdexcept>
#include <optional>

export module ChartEditor.Core:Note;

import :NoteType;

namespace ChartEditor {
    /**
     * \class Note
     * \brief Represents a musical note in a rhythm game chart.
     *
     * The Note class encapsulates the properties and behaviors associated with individual notes in a rhythm game chart.
     * It works in conjunction with the NoteType class to allow for customized note behaviors.
     *
     * \section properties Properties
     *
     * - \b Type: A weak pointer to a NoteType object, specifying the behavior this note should have. If the weak pointer is invalid, this will fall back to `NoteType::STANDARD()`.
     * - \b Beat: A floating-point value indicating the beat at which this note should be tapped. The first beat of the chart is indicated as beat 0.
     * - \b HoldLength: A floating-point value specifying how many beats this note should be held. A value of 0 means that the note does not have to be held.
     * - \b Lane: An unsigned 8-bit integer indicating which lane this note is in. Lane 0 indicates the leftmost lane of the chart.
     *
     * \section usage Usage Example
     *
     * \code{.cpp}
     * std::shared_ptr<ChartEditor::NoteType> stdNoteType = std::make_shared<ChartEditor::NoteType>("Standard");
     * ChartEditor::Note note1(stdNoteType, 5.0F, 0.0F, 3);  // Standard note at beat 5 in lane 3
     * ChartEditor::Note note2(5.0F, 3);  // Shortcut for a standard note at beat 5 in lane 3
     * \endcode
     *
     * \section invariant Class Invariants
     *
     * - The beat value (`m_beat`) is always non-negative. An exception will be thrown if an attempt to create a note before the first beat is made.
     * - The hold length value (`m_holdLength`) is always non-negative. An exception will be thrown if an attempt to set a note's hold length to a negative value is made.
     */
    export class Note {
    private:
        std::weak_ptr<NoteType> m_type;
        float m_beat;
        float m_holdLength;
        uint8_t m_lane;
    public:
        /**
         * \brief Gets the type of the note
         *
         * \return The type assigned to the note, or `NoteType::STANDARD()` if the assigned type is invalid.
         */
        [[nodiscard]] const NoteType &type() const noexcept {
            if (const auto type = m_type.lock(); type != nullptr) return *type;
            return NoteType::STANDARD();
        }

        /**
         * \brief Gets the beat where the note is located
         * \return The beat where the note is located. Will always be non-negative.
         */
        [[nodiscard]] float beat() const noexcept { return m_beat; }

        /**
         * \brief Gets the hold length of the note.
         * \return The hold length of the note in beats. Will always be non-negative. A hold length of 0 means that the note does not have to be held.
         */
        [[nodiscard]] float holdLength() const noexcept { return m_holdLength; }

        /**
         * \brief Gets the lane where the note is located
         * \return The 0-indexed lane where the note is located. Lane 0 indicates the leftmost lane.
         */
        [[nodiscard]] uint8_t lane() const noexcept { return m_lane; }

        /**
         * \brief Sets the type of the note.
         * \param type A weak pointer to the new type of the note.
         *
         * \remarks
         * This does not validate the weak pointer provided in the function.
         */
        void type(const std::weak_ptr<NoteType> &type) noexcept { m_type = type; }

        /**
         * \brief Sets the hold length of the note
         * \param holdLength The new hold length of the note in beats. Must not be negative.
         *
         * \throws std::invalid_argument If the provided hold length is negative.
         */
        void holdLength(const float holdLength) {
            if (holdLength < 0.0F) throw std::invalid_argument("Cannot set note hold length to a negative value");
            m_holdLength = holdLength;
        }

        /**
         * \brief Creates a new Note with the given type and hold length at the provided beat and lane
         * \param type The type of the note
         * \param beat The beat where the note is located. Must not be negative.
         * \param holdLength How long the note should be held, in beats. Must not be negative.
         * \param lane The 0-indexed lane where the note is. Lane 0 indicates the leftmost lane.
         *
         * \throws std::invalid_argument If either `beat` or `holdLength` is negative.
         */
        Note(const std::weak_ptr<NoteType> &type, const float beat, const float holdLength, const uint8_t lane) : m_type(type), m_beat(beat), m_lane(lane) {
            if (beat < 0.0F) throw std::invalid_argument("Cannot create note before the first beat");
            this->holdLength(holdLength);
        }

        /**
         * \brief Creates a new standard tap Note at the provided beat and lane
         * \param beat The beat where the note is located. Must not be negative.
         * \param lane The 0-indexed lane where the note is. Lane 0 indicates the leftmost lane.
         *
         * \throws std::invalid_argument If `beat` is negative.
         */
        Note(const float beat, const uint8_t lane) : Note({}, beat, 0.0F, lane) {}

        /**
         * \brief Creates a new standard Note with the given hold length at the provided beat and lane.
         * \param beat The beat where the note is located. Must not be negative.
         * \param holdLength How long the note should be held, in beats. Must not be negative.
         * \param lane The 0-indexed lane where the note is. Lane 0 indicates the leftmost lane.
         *
         * \throws std::invalid_argument If either `beat` or `holdLength` is negative.
         */
        Note(const float beat, const float holdLength, const uint8_t lane) : Note({}, beat, holdLength, lane) {}

        /**
         * \brief Creates a new tap Note with the given type at the provided beat and lane
         * \param type The type of the note
         * \param beat The beat where the note is located. Must not be negative.
         * \param lane The 0-indexed lane where the note is. Lane 0 indicates the leftmost lane.
         *
         * \throws std::invalid_argument If `beat` is negative.
         */
        Note(const std::weak_ptr<NoteType> &type, const float beat, const uint8_t lane) : Note(type, beat, 0.0F, lane) {}
        virtual ~Note() = default;

        Note(const Note &) = default;
        Note &operator=(const Note &) = default;
        Note(Note &&) = default;
        Note &operator=(Note &&) = default;
    };

    export const struct EditNoteParams final {
        std::optional<std::weak_ptr<NoteType>> type = std::nullopt;
        std::optional<float> holdLength = std::nullopt;
    };
}
