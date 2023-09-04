module;

#include <vector>

export module ChartEditor.Core:TimingData;

import :TimingPoint;

namespace ChartEditor {
    export class TimingData {
    private:
        std::vector<TimingPoint> m_timingPoints;
        float m_offset;
    public:
        /**
         * \brief Gets the list of timing points in the timing data.
         * \return A readonly list of timing points.
         */
        [[nodiscard]] const std::vector<TimingPoint> &timingPoints() const noexcept { return m_timingPoints; }
        /**
         * \brief Gets the offset of the timing data.
         *
         * The offset of the timing data indicates the position of the first beat of the music. Higher offset values
         * push beat 0 later into the music.
         *
         * \return The offset of the timing data, in seconds.
         */
        [[nodiscard]] float offset() const noexcept { return m_offset; }

        /**
         * \brief Sets the offset of the timing data.
         *
         * The offset of the timing data indicates the position of the first beat of the music. Higher offset values
         * push beat 0 later into the music.
         *
         * \param offset The new offset of the timing data, in seconds.
         */
        void offset(const float offset) { m_offset = offset; }

        /**
         * \brief Gets the beat at the provided time.
         *
         * The beat at the provided time is calculated from the offset of the timing data and the timing points in the
         * timing data. If the provided time is earlier than the offset, the beat will be negative.
         *
         * \param time The time to get the beat at, in seconds
         * \return The beat at the provided time
         */
        float beat(float time) const noexcept;

        /**
         * \brief Gets the time at the provided beat.
         *
         * The time at the provided beat is calculated from the offset of the timing data and the timing points in the
         * timing data. If the provided beat is before the first beat, the time will be earlier than the timing data's
         * offset.
         *
         * \param beat The beat to get the time at.
         * \return The time at the provided beat, in seconds.
         */
        float time(float beat) const noexcept;

        /**
         * \brief Gets the tempo at the provided beat
         * \param beat The beat to get the tempo at
         * \return The tempo of the last timing point found earlier in the timing data
         *
         * \remarks If the beat is before the first beat, the tempo will be 0.
         */
        float tempo(float beat) const noexcept;

        /**
         * \brief Sets the tempo at the provided beat
         *
         * \param beat The beat to set the tempo at
         * \param tempo The new tempo at the provided beat
         *
         * \remarks If the tempo is not greater than 0, or if the beat is less than 0, nothing will be changed in the
         * timing data.
         */
        void tempo(float beat, float tempo);

        /**
         * \brief Creates a new TimingData object
         *
         * \param initialTempo The tempo at the first beat
         * \param offset The offset of the first beat. Higher offset values push the first beat later into the music.
         */
        explicit TimingData(float initialTempo = TimingPoint::DEFAULT_TEMPO, float offset = 0);
        virtual ~TimingData() = default;

        TimingData(const TimingData &) = default;
        TimingData(TimingData &&) = default;
        TimingData &operator=(const TimingData &) = default;
        TimingData &operator=(TimingData &&) = default;
    };
}
