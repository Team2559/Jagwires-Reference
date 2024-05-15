#include <units/time.h>

namespace Blinkin {
    namespace PalletePattern {
        constexpr units::microsecond_t RAINBOW             = 1005_us;
        // constexpr units::microsecond_t RAINBOW_RAINBOW_THEME = RAINBOW + RAINBOW_THEME
        // constexpr units::microsecond_t RAINBOW_PARTY_THEME   = RAINBOW + PARTY_THEME;
        // constexpr units::microsecond_t RAINBOW_OCEAN_THEME   = RAINBOW + OCEAN_THEME;
        // constexpr units::microsecond_t RAINBOW_LAVA_THEME    = RAINBOW + LAVA_THEME;
        // constexpr units::microsecond_t RAINBOW_FOREST_THEME  = RAINBOW + FOREST_THEME;
        // constexpr units::microsecond_t RAINBOW_AND_GLITTER   = RAINBOW + GLITTER_THEME;
        constexpr units::microsecond_t CONFETTI            = 1065_us;
        constexpr units::microsecond_t SHOT_RED            = 1075_us;
        constexpr units::microsecond_t SHOT_BLUE           = 1085_us;
        constexpr units::microsecond_t SHOT_WHITE          = 1095_us;
        constexpr units::microsecond_t SINELON             = 1105_us;
        // ... Palletes
        constexpr units::microsecond_t BPM                 = 1155_us;
        // ... Palletes
        constexpr units::microsecond_t FIRE_MEDIUM         = 1205_us;
        constexpr units::microsecond_t FIRE_LARGE          = 1215_us;
        constexpr units::microsecond_t TWINKLES            = 1225_us;
        // ... Palletes
        constexpr units::microsecond_t COLOR_WAVES         = 1275_us;
        // ... Palletes
        constexpr units::microsecond_t LARSON_SCANNER_RED  = 1325_us;
        constexpr units::microsecond_t LARSON_SCANNER_GRAY = 1335_us;
        constexpr units::microsecond_t LIGHT_CHASE_RED     = 1345_us;
        constexpr units::microsecond_t LIGHT_CHASE_BLUE    = 1355_us;
        constexpr units::microsecond_t LIGHT_CHASE_GRAY    = 1365_us;
        constexpr units::microsecond_t HEARTBEAT_RED       = 1375_us;
        constexpr units::microsecond_t HEARTBEAT_BLUE      = 1385_us;
        constexpr units::microsecond_t HEARTBEAT_WHITE     = 1395_us;
        constexpr units::microsecond_t HEARTBEAT_GRAY      = 1405_us;
        constexpr units::microsecond_t BREATH_RED          = 1415_us;
        constexpr units::microsecond_t BREATH_BLUE         = 1425_us;
        constexpr units::microsecond_t BREATH_GRAY         = 1435_us;
        constexpr units::microsecond_t STROBE_RED          = 1445_us;
        constexpr units::microsecond_t STROBE_BLUE         = 1455_us;
        constexpr units::microsecond_t STROBE_GOLD         = 1465_us;
        constexpr units::microsecond_t STROBE_WHITE        = 1475_us;
    }
    
    // Add-in to some PalletePatterns
    namespace PalleteThemes {
        constexpr units::microsecond_t RAINBOW_THEME = 0_us;
        constexpr units::microsecond_t PARTY_THEME   = 10_us;
        constexpr units::microsecond_t OCEAN_THEME   = 20_us;
        constexpr units::microsecond_t LAVA_THEME    = 30_us;
        constexpr units::microsecond_t FOREST_THEME  = 40_us;
    }

    namespace SingleColorPattern {
        constexpr units::microsecond_t ETE_BLEND_TO_BLACK = 1485_us;
        constexpr units::microsecond_t LARSON_SCANNER     = 1495_us;
        constexpr units::microsecond_t LIGHT_CHASE        = 1505_us;
        constexpr units::microsecond_t HEARTBEAT_SLOW     = 1515_us;
        constexpr units::microsecond_t HEARTBEAT_MEDIUM   = 1525_us;
        constexpr units::microsecond_t HEARTBEAT_FAST     = 1535_us;
        constexpr units::microsecond_t BREATH_SLOW        = 1545_us;
        constexpr units::microsecond_t BREATH_FAST        = 1555_us;
        constexpr units::microsecond_t SHOT               = 1565_us;
        constexpr units::microsecond_t STROBE             = 1575_us;
    }

    // Add-in to any SingleColorPattern
    namespace SingleColorTheme {
        constexpr units::microsecond_t COLOR_1 = 0_us;
        constexpr units::microsecond_t COLOR_2 = 100_us;
    }
    
    namespace DualColorTheme {
        constexpr units::microsecond_t SPARKLE_C1_ON_C2   = 1685_us;
        constexpr units::microsecond_t SPARKLE_C2_ON_C1   = 1695_us;
        constexpr units::microsecond_t COLOR_GRADIENT     = 1705_us;
        constexpr units::microsecond_t BPM                = 1715_us;
        constexpr units::microsecond_t ETE_BLEND_C1_TO_C2 = 1725_us;
        constexpr units::microsecond_t ETE_BLEND_C2_TO_C1 = 1735_us;
        constexpr units::microsecond_t NO_BLEND_SETUP     = 1745_us;
        constexpr units::microsecond_t TWINKLES           = 1755_us;
        constexpr units::microsecond_t COLOR_WAVES        = 1765_us;
        constexpr units::microsecond_t SINELON            = 1785_us;
    }

    namespace Solid {
        constexpr units::microsecond_t HOT_PINK    = 1785_us;
        constexpr units::microsecond_t DARK_RED    = 1795_us;
        constexpr units::microsecond_t RED         = 1805_us;
        constexpr units::microsecond_t RED_ORANGE  = 1815_us;
        constexpr units::microsecond_t ORANGE      = 1825_us;
        constexpr units::microsecond_t GOLD        = 1835_us;
        constexpr units::microsecond_t YELLOW      = 1845_us;
        constexpr units::microsecond_t LAWN_GREEN  = 1855_us;
        constexpr units::microsecond_t LIME        = 1865_us;
        constexpr units::microsecond_t DARK_GREEN  = 1875_us;
        constexpr units::microsecond_t GREEN       = 1885_us;
        constexpr units::microsecond_t BLUE_GREEN  = 1895_us;
        constexpr units::microsecond_t AQUA        = 1905_us;
        constexpr units::microsecond_t SKY_BLUE    = 1915_us;
        constexpr units::microsecond_t DARK_BLUE   = 1925_us;
        constexpr units::microsecond_t BLUE        = 1935_us;
        constexpr units::microsecond_t BLUE_VIOLET = 1945_us;
        constexpr units::microsecond_t VIOLET      = 1955_us;
        constexpr units::microsecond_t WHITE       = 1965_us;
        constexpr units::microsecond_t GRAY        = 1975_us;
        constexpr units::microsecond_t DARK_GRAY   = 1985_us;
        constexpr units::microsecond_t BLACK       = 1995_us;
    }
}