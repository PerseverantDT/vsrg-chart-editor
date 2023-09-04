module;

#include <stdexcept>
#include <string>

export module ChartEditor.Exceptions;

namespace ChartEditor {
    export class NoteAlreadyExistsException : public std::runtime_error {
    public:
        NoteAlreadyExistsException(const float beat, const uint8_t lane) : std::runtime_error("Note already exists at beat " + std::to_string(beat) + " and lane " + std::to_string(static_cast<int>(lane))) {}
    };
}
