module;

#include <string>

export module ChartEditor.Core:NoteType;

namespace ChartEditor {
    /**
     * \class NoteType
     * \brief Represents a custom note behavior in rhythm game charts.
     *
     * The NoteType class captures the distinctive behaviors that can be applied to notes in different rhythm game formats.
     * It is designed to be extensible to accommodate non-standard note types and is particularly useful for games or chart formats
     * that support complex note behaviors beyond the traditional tap and hold mechanics.
     *
     * \section supported-behaviors Supported Behaviors
     *
     * This class facilitates the encoding of the following note behaviors:
     *
     * - \b Name: A string identifier for the note type. In extensible formats, the name is often used to differentiate between various custom note types.
     * - \b Miss-on-Hit: A boolean flag that, when set, causes the note to register as a miss when hit.
     * - \b Roll: A boolean flag that, when set, changes the behavior of hold notes (notes with a hold length greater than 0) to require rapid tapping. Does nothing on non-hold notes.
     *
     * \section limitations Limitations
     *
     * While this class provides a generic representation of note behaviors, it cannot fully support game-specific or format-specific behaviors such as those requiring scripts in FNF charts.
     *
     * \section usage Usage Example
     *
     * \code{.cpp}
     * ChartEditor::NoteType mineType("Mine", true, false);  // Create a "Mine" type note, which registers as a miss when hit
     * bool isMine = mineType.isMine();  // Should return true
     * \endcode
     *
     * \section invariant Class Invariants
     *
     * - The name of the NoteType, stored in `m_name`, can be any string but is intended to be unique when used in the context of a chart.
     * - The behavior flags `m_mine` and `m_roll` are boolean and can be independently toggled to configure the note's behavior.
     */
    export class NoteType {
    private:
        std::string m_name;
        bool m_missOnHit;
        bool m_roll;
    public:
        /**
         * \brief Gets a standard note type
         *
         * This note type has an empty string as a name and has both `m_missOnHit` and `m_roll` set to `false`. Notes which
         * do not have a valid note type will default to this type.
         *
         * \return A standard note type
         */
        static const NoteType &STANDARD() {
            static const NoteType DEFAULT_NOTETYPE("", false, false);
            return DEFAULT_NOTETYPE;
        }

        /**
         * \brief Gets a note type that represents a note that registers as a miss when hit
         *
         * This note type has a name of "Hurt Note" (the built-in hurt note in FNF) and `m_missOnHit` set to `true`.
         *
         * \return A note type that registers as a miss when hit
         */
        static const NoteType &HURT_NOTE() {
            static const NoteType DEFAULT_HURT("Hurt Note", true, false);
            return DEFAULT_HURT;
        }

        /**
         * \brief Gets a note type that represents roll notes.
         *
         * This note type has a name of "Roll Note" and `m_roll` set to `true`.
         *
         * \return A note type that represents roll notes.
         */
        static const NoteType &ROLL_NOTE() {
            static const NoteType DEFAULT_ROLL("Roll Note", false, true);
            return DEFAULT_ROLL;
        }

        /**
         * \brief Gets the identifier of the note type
         * \return The name of the note type
         */
        [[nodiscard]] const std::string &name() const noexcept { return m_name; }

        /**
         * \brief Gets whether the note type represents a note that registers as a miss when hit
         * \return `true` if the note should miss on hit, `false` otherwise
         */
        [[nodiscard]] bool shouldMissOnHit() const noexcept { return m_missOnHit; }

        /**
         * \brief Gets whether the a hold note with this type should be rolled rather than held
         * \return `true` if the note should be a roll note, `false` otherwise
         */
        [[nodiscard]] bool isRoll() const noexcept { return m_roll; }

        /**
         * \brief Sets the identifier of the name type
         * \param name The new name of the note type
         *
         * \remarks While `name` can be any string, it is recommended that this name be different from any other note
         * types used in the same chart.
         */
        void name(const std::string &name) { m_name = name; }

        /**
         * \brief Sets whether the note type should represent a note that misses when hit
         * \param mine `true` if the note should miss on hit, `false` otherwise
         */
        void shouldMissOnHit(bool mine) { m_missOnHit = mine; }

        /**
         * \brief Sets whether hold notes with this type should be rolled rather than held
         * \param roll `true` if hold notes should be rolled, `false` otherwise
         */
        void isRoll(bool roll) { m_roll = roll; }

        /**
         * \brief Creates a new note type
         * \param name An identifier for the note type
         * \param mine Should this note type represent a note that counts as a miss when hit? Defaults to `false`.
         * \param roll Should hold notes with this type be repeatedly tapped rather than held? Defaults to `false`.
         */
        explicit NoteType(const std::string &name, bool mine = false, bool roll = false) : m_name(name), m_missOnHit(mine), m_roll(roll) {}
        virtual ~NoteType() = default;

        NoteType(const NoteType &) = default;
        NoteType &operator=(const NoteType &) = default;
        NoteType(NoteType &&) = default;
        NoteType &operator=(NoteType &&) = default;
    };
}
