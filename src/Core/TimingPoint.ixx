module;

export module ChartEditor.Core:TimingPoint;

namespace ChartEditor {
    export class TimingPoint {
    private:
        float m_beat;
        float m_tempo;
    public:
        static constexpr float DEFAULT_TEMPO = 120.0F;

        [[nodiscard]] float beat() const noexcept { return m_beat; }
        [[nodiscard]] float tempo() const noexcept { return m_tempo; }

        void tempo(const float tempo) noexcept { m_tempo = tempo; }

        explicit TimingPoint(const float beat, const float tempo = DEFAULT_TEMPO) : m_beat(beat), m_tempo(tempo) {}
        virtual ~TimingPoint() = default;

        TimingPoint(const TimingPoint &) = default;
        TimingPoint(TimingPoint &&) = default;
        TimingPoint &operator=(const TimingPoint &) = default;
        TimingPoint &operator=(TimingPoint &&) = default;
    };
}
