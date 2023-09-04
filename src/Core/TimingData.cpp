module;

#include <vector>

module ChartEditor.Core;

import :TimingData;
import :TimingPoint;

float ChartEditor::TimingData::beat(const float time) const noexcept {
    if (time <= m_offset) {
        const TimingPoint &tp = m_timingPoints.at(0);
        return (time - m_offset) / (tp.tempo() / 60.0F);
    }

    float previousTime = m_offset;
    float currentTime = m_offset;
    float previousBeat = m_timingPoints[0].beat();
    float previousTempo = m_timingPoints[0].tempo();

    for (const auto &tp : m_timingPoints) {
        currentTime += (tp.beat() - previousBeat) / previousTempo * 60.0F;
        if (currentTime > time) break;

        previousBeat = tp.beat();
        previousTempo = tp.tempo();
        previousTime = currentTime;
    }

    return previousBeat + ((time - previousTime) / 60.0F * previousTempo);
}

float ChartEditor::TimingData::time(const float beat) const noexcept {
    if (beat <= 0.0F) {
        const TimingPoint &tp = m_timingPoints.at(0);
        return (beat / tp.tempo() * 60.0F) + m_offset;
    }

    float currentTime = m_offset;
    float previousBeat = m_timingPoints[0].beat();
    float previousTempo = m_timingPoints[0].beat();

    for (const auto &tp : m_timingPoints) {
        if (tp.beat() > beat) break;

        currentTime += (tp.beat() - previousBeat) / previousTempo * 60.0F;
        previousBeat = tp.beat();
        previousTempo = tp.tempo();
    }

    return currentTime + ((beat - previousBeat) / previousTempo * 60.0F);
}

float ChartEditor::TimingData::tempo(const float beat) const noexcept {
    for (auto it = m_timingPoints.crbegin(); it != m_timingPoints.crend(); ++it) {
        if (it->beat() > beat) break;

        return it->tempo();
    }

    return 0.0F;
}

void ChartEditor::TimingData::tempo(const float beat, const float tempo) {
    if (tempo < 0.0F) return;
    if (beat < 0.0F) return;
    if (beat == 0.0F) {
        m_timingPoints[0].tempo(tempo);
        return;
    }

    for (auto i = static_cast<ptrdiff_t>(m_timingPoints.size()); i >= 0; --i) {
        TimingPoint &tp = m_timingPoints[i];
        if (tp.beat() > beat) continue;

        if (tp.beat() == beat) {
            const TimingPoint &prev = m_timingPoints[i - 1];
            if (prev.tempo() == tempo) m_timingPoints.erase(m_timingPoints.cbegin() + 1);
            else tp.tempo(tempo);

            return;
        }

        m_timingPoints.emplace(m_timingPoints.cbegin() + i + 1, beat, tempo);
        return;
    }

    m_timingPoints.emplace_back(beat, tempo);
}
