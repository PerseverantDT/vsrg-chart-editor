module;

#include <stdexcept>

export module ChartEditor.Core:TimingPoint;

namespace ChartEditor {
    /**
     * \class TimingPoint
     * \brief Represents a timing point in a chart for rhythm games.
     *
     * A TimingPoint object encapsulates the timing information at and after a specific beat in a chart's timing data.
     * It contains two primary attributes: the beat where the timing point occurs and the tempo at that point.
     *
     * \section invariants Invariants
     *
     * The class maintains the following invariants:
     * - The beat where the timing point is will always be on or after the first beat (i.e.: beat() >= 0). An exception
     *   will be thrown if an attempt to create a timing point earlier than the first beat is made.
     * - The tempo of a timing point is always a positive float value. An exception will be thrown if an attempt is
     *   made to set it to a non-positive value.
     *
     * \section usage Usage Example
     *
     * \code{.cpp}
     * try {
     *     ChartEditor::TimingPoint point(1.0, 120.0);  // Creates a timing point at beat 1.0 with a tempo of 120 BPM
     *     float currentTempo = point.tempo();  // Gets the tempo (120)
     *     point.tempo(150.0);  // Updates the tempo to 150 BPM
     * } catch (const std::invalid_argument& e) {
     *     // Handle exception for invalid tempo
     *     std::cerr << e.what() << std::endl;
     * }
     * \endcode
     */
    export class TimingPoint {
    private:
        float m_beat;
        float m_tempo;
    public:
        static constexpr float DEFAULT_TEMPO = 120.0F;

        /**
         * \brief Gets the beat where the timing point is located
         *
         * When placed in a timing data, all beats after this timing point, provided that there are no other timing
         * points located later than this, will have a tempo equal to the tempo of this timing point.
         *
         * \return The beat where the timing point is located
         */
        [[nodiscard]] float beat() const noexcept { return m_beat; }

        /**
         * \brief Gets the tempo of the timing point
         * \return The tempo of the timing point
         */
        [[nodiscard]] float tempo() const noexcept { return m_tempo; }

        /**
         * \brief Sets the tempo of the timing point
         * \param tempo The new tempo of the timing point
         *
         * \throws std::invalid_argument If the new tempo is 0 or less
         */
        void tempo(const float tempo) {
            if (tempo <= 0.0F) throw std::invalid_argument("Cannot set tempo to a non-positive value");
            m_tempo = tempo;
        }

        /**
         * \brief Creates a new timing point located at the provided beat.
         * \param beat The beat where the timing point is placed
         * \param tempo The tempo at the timing point. Defaults to 120
         *
         * \throws std::invalid_argument If either the beat is less than 0 or the tempo is 0 or less
         */
        explicit TimingPoint(const float beat, const float tempo = DEFAULT_TEMPO) : m_beat(beat), m_tempo(tempo) {
            if (beat < 0.0F) throw std::invalid_argument("Cannot create a timing point before the first beat");
            if (tempo <= 0.0F) throw std::invalid_argument("Cannot set tempo to a non-positive value");
        }
        virtual ~TimingPoint() = default;

        TimingPoint(const TimingPoint &) = default;
        TimingPoint(TimingPoint &&) = default;
        TimingPoint &operator=(const TimingPoint &) = default;
        TimingPoint &operator=(TimingPoint &&) = default;
    };
}
