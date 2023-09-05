module;

#include <memory>
#include <string>
#include <vector>

module ChartEditor.Core;

import :Chart;
import :Difficulty;

std::shared_ptr<ChartEditor::Difficulty> ChartEditor::Chart::createDifficulty(const std::string &name) {
    auto diff = std::make_shared<ChartEditor::Difficulty>(name);
    m_difficulties.emplace_back(diff);

    return diff;
}

std::shared_ptr<ChartEditor::Difficulty> ChartEditor::Chart::getDifficulty(const std::string &name) const noexcept {
    for (const auto &diff : m_difficulties) {
        if (diff->name() == name) return diff;
    }

    return nullptr;
}

void ChartEditor::Chart::deleteDifficulty(const std::string &name) {
    std::erase_if(m_difficulties, [&name](const auto &diff) { return diff->name() == name; });
}
