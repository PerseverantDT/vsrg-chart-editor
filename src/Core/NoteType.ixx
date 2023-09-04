module;

#include <string>

export module ChartEditor.Core:NoteType;

namespace ChartEditor {
    export class NoteType {
    private:
        std::string m_name;
        bool m_mine;
        bool m_roll;
    public:
        static const NoteType &DEFAULT() {
            static const NoteType DEFAULT_NOTETYPE("", false, false);
            return DEFAULT_NOTETYPE;
        }
        [[nodiscard]] const std::string &name() const noexcept { return m_name; }
        [[nodiscard]] bool isMine() const noexcept { return m_mine; }
        [[nodiscard]] bool isRoll() const noexcept { return m_roll; }

        void name(const std::string &name) { m_name = name; }
        void isMine(bool mine) { m_mine = mine; }
        void isRoll(bool roll) { m_roll = roll; }

        NoteType(const std::string &name, bool mine, bool roll) : m_name(name), m_mine(mine), m_roll(roll) {}
        virtual ~NoteType() = default;

        NoteType(const NoteType &) = default;
        NoteType &operator=(const NoteType &) = default;
        NoteType(NoteType &&) = default;
        NoteType &operator=(NoteType &&) = default;
    };
}
