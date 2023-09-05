module;

#include <memory>
#include <string>
#include <vector>

export module ChartEditor.Core:Chart;

import :TimingPoint;
import :TimingData;
import :Difficulty;

namespace ChartEditor {
    export class Chart {
    private:
        std::string m_title;
        std::string m_subtitle;
        std::string m_artist;
        std::string m_credit;
        std::string m_musicFile;
        TimingData m_timingData;
        std::vector<std::shared_ptr<Difficulty>> m_difficulties;
    public:
        [[nodiscard]] const std::string &title() const noexcept { return m_title; }
        [[nodiscard]] const std::string &subtitle() const noexcept { return m_subtitle; }
        [[nodiscard]] const std::string &artist() const noexcept { return m_artist; }
        [[nodiscard]] const std::string &credit() const noexcept { return m_credit; }
        [[nodiscard]] const std::string &musicFile() const noexcept { return m_musicFile; }

        [[nodiscard]] const std::vector<TimingPoint> &timingPoints() const noexcept { return m_timingData.timingPoints(); }
        [[nodiscard]] float offset() const noexcept { return m_timingData.offset(); }

        [[nodiscard]] const std::vector<std::shared_ptr<Difficulty>> &difficulties() const noexcept { return m_difficulties; }

        void title(const std::string &title) noexcept { m_title = title; }
        void subtitle(const std::string &subtitle) noexcept { m_subtitle = subtitle; }
        void artist(const std::string &artist) noexcept { m_artist = artist; }
        void credit(const std::string &credit) noexcept { m_credit = credit; }
        void musicFile(const std::string &musicFile) noexcept { m_musicFile = musicFile; }

        void offset(const float offset) noexcept { m_timingData.offset(offset); }

        [[nodiscard]] float beat(const float time) const noexcept { return m_timingData.beat(time); }
        [[nodiscard]] float time(const float beat) const noexcept { return m_timingData.time(beat); }
        [[nodiscard]] float tempo(const float beat) const noexcept { return m_timingData.tempo(beat); }
        void tempo(const float beat, const float tempo) { m_timingData.tempo(beat, tempo); }

        [[nodiscard]] std::shared_ptr<Difficulty> getDifficulty(const std::string &name) const noexcept;
        std::shared_ptr<Difficulty> createDifficulty(const std::string &name);
        void deleteDifficulty(const std::string &name);
    };
}
