cmake_minimum_required(VERSION 3.14)

project(risk_v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

    # Validation functions
    src/core/validation/ValidateTerritorySelection.cpp
    src/core/validation/ValidateAttackInput.cpp
    src/core/validation/ValidateDiceInput.cpp
    src/core/validation/ValidateReinforceInput.cpp
    src/core/validation/ValidateSetInput.cpp
    src/core/validation/ValidateFortifyInput.cpp
)

target_include_directories(risk_v1 PRIVATE
    include
)

# -----------------------------
# Google Test
# -----------------------------

include(FetchContent)

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
)

target_include_directories(unit_tests PRIVATE
    include
)

target_link_libraries(unit_tests
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(unit_tests)