#include "../REFramework.hpp"

#include "REFrameworkConfig.hpp"

std::shared_ptr<REFrameworkConfig>& REFrameworkConfig::get() {
     static std::shared_ptr<REFrameworkConfig> instance{std::make_shared<REFrameworkConfig>()};
     return instance;
}

std::optional<std::string> REFrameworkConfig::on_initialize() {
    namespace fs = std::filesystem;
    fonts.clear();
    fonts.push_back("DEFAULT");

    const auto fonts_path = REFramework::get_persistent_dir() / "reframework" / "fonts";
    fs::create_directories(fonts_path);

    for (const auto& entry : fs::directory_iterator(fonts_path)) {
        if (fs::is_regular_file(entry)) {
            const auto ext = entry.path().extension();
            if (ext == ".otf" || ext == ".ttf") {
                fonts.push_back(entry.path().filename().string());
            }
        }
    }

    m_font_file = ModComboString::create(generate_name("FontFile"), fonts, "DEFAULT");

    g_framework->set_font(m_font_file->value());

    m_options.push_back(*m_font_file);

    return Mod::on_initialize();
}

void REFrameworkConfig::on_draw_ui() {
    if (!ImGui::CollapsingHeader("配置")) {
        return;
    }

    ImGui::TreePush("配置");

    bool changed = false;

    changed |= m_menu_key->draw("菜单按键");
    changed |= m_show_cursor_key->draw("显示光标按键");
    changed |= m_remember_menu_state->draw("记住菜单开关状态");
    changed |= m_always_show_cursor->draw("打开菜单时显示光标");

    if (m_font_file->draw("字体")) {
        g_framework->set_font(m_font_file->value());
        changed = true;
    }

    if (m_font_size->draw("字体大小")) {
        g_framework->set_font_size(m_font_size->value());

        const auto display_size = g_framework->get_main_window_display_size();
        if (display_size.x > 0.0f && display_size.y > 0.0f) {
            set_ui_layout_state(
                static_cast<int32_t>(display_size.x),
                static_cast<int32_t>(display_size.y),
                g_framework->get_font_size());
        }

        changed = true;
    }

    if (changed) {
        g_framework->request_save_config();
    }

    ImGui::TreePop();
}

void REFrameworkConfig::on_frame() {
    if (m_show_cursor_key->is_key_down_once()) {
        m_always_show_cursor->toggle();
    }
}

void REFrameworkConfig::on_config_load(const utility::Config& cfg) {
    for (IModValue& option : m_options) {
        option.config_load(cfg);
    }

    if (m_remember_menu_state->value()) {
        g_framework->set_draw_ui(m_menu_open->value(), false);
    }
    
    g_framework->set_font(m_font_file->value());
    const auto saved_font_size = m_ui_font_size->value() > 0.0f
        ? m_ui_font_size->value()
        : static_cast<float>(m_font_size->value());
    g_framework->set_font_size_for_display(saved_font_size, static_cast<float>(m_ui_monitor_height->value()));
}

void REFrameworkConfig::on_config_save(utility::Config& cfg) {
    for (IModValue& option : m_options) {
        option.config_save(cfg);
    }
}
