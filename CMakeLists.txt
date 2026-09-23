cmake_minimum_required(VERSION 3.14)

project(risk_v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# FetchContent
# -----------------------------

include(FetchContent)

# -----------------------------
# SFML
# -----------------------------

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

set(BUILD_SHARED_LIBS ON)

FetchContent_MakeAvailable(SFML)

set(BUILD_SHARED_LIBS OFF)

# -----------------------------
# Main Game Executable
# -----------------------------

add_executable(risk_v1

    src/main.cpp

    # Entity classes
    src/entities/Territory.cpp
    src/entities/Player.cpp
    src/entities/Card.cpp

    # World classes
    src/world/Continent.cpp
    src/world/Map.cpp
    src/world/MapLoader.cpp
    src/world/Deck.cpp
    src/world/DeckLoader.cpp

    # Order classes
    src/core/orders/Order.cpp
    src/core/orders/AttackOrder.cpp
    src/core/orders/CashSetOrder.cpp
    src/core/orders/FortifyOrder.cpp
    src/core/orders/ReinforceOrder.cpp
    src/core/orders/RollDiceOrder.cpp
    src/core/orders/MoveTroopsOrder.cpp

    # Manager classes
    src/core/managers/GameStateManager.cpp
    src/core/managers/AttackManager.cpp
    src/core/managers/LogManager.cpp
    src/core/managers/TroopManager.cpp
    

    # Session classes
    src/core/session/GameInitializer.cpp
    src/core/session/GameSession.cpp
    src/core/session/GameState.cpp
    src/core/session/GameSetupState.cpp

    # Graphic element classes
    src/graphics/game_elements/BoardGraphics.cpp
    src/graphics/game_elements/TerritoryGraphics.cpp
    src/graphics/game_elements/PlayerGraphics.cpp
    src/graphics/game_elements/CardGraphics.cpp
    

    # Graphic UI classes
    src/graphics/ui/GameWindow.cpp
    src/graphics/ui/MenuUI.cpp
    src/graphics/ui/LUIExchange.cpp
    src/graphics/ui/LoadingUI.cpp
    src/graphics/ui/ProfileUI.cpp
    src/graphics/ui/GameSessionUI.cpp
    src/graphics/ui/GameSetupUI.cpp
    src/graphics/ui/ReinforceUI.cpp

    # Graphic component classes
    src/graphics/components/PlayerIndicator.cpp
    src/graphics/components/SetupControls.cpp 
    src/graphics/components/ContinentValueBoard.cpp
    src/graphics/components/ReinforceControls.cpp
    src/graphics/components/CardContainer.cpp

    # Validation functions
    src/core/validation/ValidateTerritorySelection.cpp
    src/core/validation/ValidateAttackInput.cpp
    src/core/validation/ValidateDiceInput.cpp
    src/core/validation/ValidateReinforceInput.cpp
    src/core/validation/ValidateSetInput.cpp
    src/core/validation/ValidateFortifyInput.cpp

    # Utility functions
    src/core/utils/TerritoryConverter.cpp
    src/core/utils/ContinentConverter.cpp
   
   )

target_include_directories(risk_v1 PRIVATE
    include
)

target_link_libraries(risk_v1 PRIVATE
    SFML::Graphics
)

# Copy SFML DLLs beside risk_v1.exe after build
add_custom_command(TARGET risk_v1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SFML::Graphics>
        $<TARGET_FILE:SFML::Window>
        $<TARGET_FILE:SFML::System>
        $<TARGET_FILE_DIR:risk_v1>
)

# -----------------------------
# Google Test
# -----------------------------

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# -----------------------------
# Test Executable
# -----------------------------

add_executable(unit_tests
    
    # Entity tests
    tests/entityTests/CardTests.cpp
    tests/entityTests/PlayerTests.cpp
    tests/entityTests/TerritoryTests.cpp

    # World tests
   tests/worldTests/ContinentTests.cpp
   tests/worldTests/DeckTests.cpp
   tests/worldTests/DeckLoaderTests.cpp
   tests/worldTests/MapTests.cpp
   tests/worldTests/MapLoaderTests.cpp

    # Order tests
    tests/coreTests/orderTests/AttackOrderTests.cpp
    tests/coreTests/orderTests/CashSetOrderTests.cpp
    tests/coreTests/orderTests/FortifyOrderTests.cpp
    tests/coreTests/orderTests/ReinforceOrderTests.cpp
    tests/coreTests/orderTests/RollDiceOrderTests.cpp
    tests/coreTests/orderTests/MoveTroopsOrderTests.cpp

    # Manager tests
    tests/coreTests/managerTests/GameStateManagerTests.cpp
    tests/coreTests/managerTests/AttackManagerTests.cpp
    tests/coreTests/managerTests/TroopManagerTests.cpp

    # Session tests
    tests/coreTests/sessionTests/GameInitializerTests.cpp

    # Validation tests
    tests/coreTests/validationTests/ValidationTests.cpp

    # Entity source files
    src/entities/Card.cpp
    src/entities/Player.cpp
    src/entities/Territory.cpp

    # World source files
    src/world/Continent.cpp
    src/world/Deck.cpp
    src/world/DeckLoader.cpp
    src/world/Map.cpp
    src/world/MapLoader.cpp

    # Order source files
    src/core/orders/Order.cpp
    src/core/orders/AttackOrder.cpp
    src/core/orders/CashSetOrder.cpp
    src/core/orders/FortifyOrder.cpp
    src/core/orders/ReinforceOrder.cpp
    src/core/orders/RollDiceOrder.cpp
    src/core/orders/MoveTroopsOrder.cpp

    # Manager source files
    src/core/managers/GameStateManager.cpp
    src/core/managers/AttackManager.cpp
    src/core/managers/TroopManager.cpp

    # Session source files
    src/core/session/GameInitializer.cpp
   

    # Validation source files
    src/core/validation/ValidateTerritorySelection.cpp
    src/core/validation/ValidateAttackInput.cpp
    src/core/validation/ValidateDiceInput.cpp
    src/core/validation/ValidateReinforceInput.cpp
    src/core/validation/ValidateSetInput.cpp
    src/core/validation/ValidateFortifyInput.cpp

   # Utils source files
   src/core/utils/ContinentConverter.cpp
   src/core/utils/TerritoryConverter.cpp
   
 "include/risk/graphics/components/PlayerIndicator.h")

target_include_directories(unit_tests PRIVATE
    include
)

target_link_libraries(unit_tests
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(unit_tests)