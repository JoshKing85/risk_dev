#include "risk/graphics/ui/ProfileUI.h"

#include "risk/graphics/components/PlayerProfile.h"

#include <stdexcept>
#include <string>

namespace risk {

    ProfileUI::ProfileUI(
        sf::Font& font)
        : font(font),
        backgroundSprite(backgroundTexture),
        musterBoardSprite(musterBoardTexture),
        playerText(font),
        playerNumberText(font),
        nameLabel(font),
        nameText(font),
        avatarLabel(font),
        startText(font),
        avatarSprites{
            sf::Sprite(avatarTextures[0]),
            sf::Sprite(avatarTextures[1]),
            sf::Sprite(avatarTextures[2]),
            sf::Sprite(avatarTextures[3]),
            sf::Sprite(avatarTextures[4]),
            sf::Sprite(avatarTextures[5])
        }
    {
        //=====================================================
        // Background
        //=====================================================

        if (!backgroundTexture.loadFromFile(
            "data/graphics/components/CampaignTent.png"))
        {
            throw std::runtime_error(
                "Could not load CampaignTent.png");
        }

        backgroundSprite.setTexture(
            backgroundTexture,
            true);

        backgroundTexture.setSmooth(true);

        sf::Vector2u backgroundSize =
            backgroundTexture.getSize();

        backgroundSprite.setScale({
            1920.f /
                static_cast<float>(
                    backgroundSize.x),

            1080.f /
                static_cast<float>(
                    backgroundSize.y)
            });

        backgroundSprite.setPosition({
            0.f,
            0.f
            });

        //=====================================================
        // Muster board
        //=====================================================

        if (!musterBoardTexture.loadFromFile(
            "data/graphics/components/MusterBoard.png"))
        {
            throw std::runtime_error(
                "Could not load MusterBoard.png");
        }

        musterBoardSprite.setTexture(
            musterBoardTexture,
            true);

        musterBoardTexture.setSmooth(true);

        sf::Vector2u musterSize =
            musterBoardTexture.getSize();

        const float targetHeight =
            1050.f;

        const float musterScale =
            targetHeight /
            static_cast<float>(
                musterSize.y);

        musterBoardSprite.setScale({
            musterScale,
            musterScale
            });

        sf::FloatRect musterBounds =
            musterBoardSprite.getGlobalBounds();

        musterBoardSprite.setPosition({
            (1920.f -
                musterBounds.size.x) /
                2.f,

            (1080.f -
                musterBounds.size.y) /
                2.f
            });

        //=====================================================
        // Player title
        //=====================================================

        playerText.setString(
            "PLAYER");

        playerText.setCharacterSize(
            52);

        playerText.setFillColor(
            sf::Color(
                225,
                204,
                158));

        playerNumberText.setString(
            "1");

        playerNumberText.setCharacterSize(
            60);

        playerNumberText.setFillColor(
            sf::Color(
                225,
                204,
                158));

        sf::FloatRect playerBounds =
            playerText.getLocalBounds();

        sf::FloatRect numberBounds =
            playerNumberText.getLocalBounds();

        const float titleGap =
            12.f;

        const float totalTitleWidth =
            playerBounds.size.x +
            titleGap +
            numberBounds.size.x;

        const float titleStartX =
            960.f -
            (totalTitleWidth / 2.f);

        playerText.setPosition({
            titleStartX,
            180.f
            });

        playerNumberText.setPosition({
            titleStartX +
                playerBounds.size.x +
                titleGap,
            164.f
            });

        //=====================================================
        // Name label
        //=====================================================

        nameLabel.setString(
            "ENTER YOUR NAME");

        nameLabel.setCharacterSize(
            20);

        nameLabel.setFillColor(
            sf::Color(
                225,
                204,
                158));

        nameLabel.setPosition({
            665.f,
            255.f
            });

        //=====================================================
        // Name box
        //=====================================================

        nameBox.setSize({
            590.f,
            52.f
            });

        nameBox.setPosition({
            665.f,
            285.f
            });

        nameBox.setFillColor(
            sf::Color(
                38,
                34,
                30,
                210));

        nameBox.setOutlineThickness(
            2.f);

        nameBox.setOutlineColor(
            sf::Color(
                128,
                105,
                65));

        //=====================================================
        // Name text
        //=====================================================

        nameText.setCharacterSize(
            24);

        nameText.setFillColor(
            sf::Color(
                225,
                204,
                158));

        nameText.setPosition({
            680.f,
            295.f
            });

        //=====================================================
        // Avatar heading
        //=====================================================

        avatarLabel.setString(
            "CHOOSE YOUR COMMANDER");

        avatarLabel.setCharacterSize(
            22);

        avatarLabel.setFillColor(
            sf::Color(
                225,
                204,
                158));

        //=====================================================
        // Avatar layout
        //=====================================================

        const float avatarWidth =
            250.f;

        const float avatarHeight =
            250.f;

        const float avatarGapX =
            20.f;

        const float avatarGapY =
            15.f;

        const float totalWidth =
            (3.f * avatarWidth) +
            (2.f * avatarGapX);

        const float startX =
            960.f -
            (totalWidth / 2.f);

        const float startY =
            395.f;

        const std::array<std::string, 6>
            avatarPaths =
        {
            "data/graphics/avatars/NapoleonAvatar.png",
            "data/graphics/avatars/WellingtonAvatar.png",
            "data/graphics/avatars/BulcherAvatar.png",
            "data/graphics/avatars/VonAvatar.png",
            "data/graphics/avatars/NeedleAvatar.png",
            "data/graphics/avatars/AlexanderAvatar.png"
        };

        for (int i = 0;
            i < 6;
            ++i)
        {
            const int row =
                i / 3;

            const int column =
                i % 3;

            const float x =
                startX +
                column *
                (avatarWidth +
                    avatarGapX);

            const float y =
                startY +
                row *
                (avatarHeight +
                    avatarGapY);

            avatarBoxes[i].setSize({
                avatarWidth,
                avatarHeight
                });

            avatarBoxes[i].setPosition({
                x,
                y
                });

            avatarBoxes[i].setFillColor(
                sf::Color(
                    38,
                    34,
                    30,
                    210));

            avatarBoxes[i].setOutlineThickness(
                2.f);

            avatarBoxes[i].setOutlineColor(
                sf::Color(
                    128,
                    105,
                    65));

            if (!avatarTextures[i].loadFromFile(
                avatarPaths[i]))
            {
                throw std::runtime_error(
                    "Could not load avatar: " +
                    avatarPaths[i]);
            }

            avatarTextures[i].setSmooth(
                true);

            avatarSprites[i].setTexture(
                avatarTextures[i],
                true);

            avatarSprites[i].setScale({
                1.f,
                1.f
                });

            sf::FloatRect spriteBounds =
                avatarSprites[i]
                .getGlobalBounds();

            avatarSprites[i].setPosition({
                x +
                    (avatarWidth -
                        spriteBounds.size.x) /
                        2.f,

                y +
                    (avatarHeight -
                        spriteBounds.size.y) /
                        2.f
                });
        }

        //=====================================================
        // Avatar heading position
        //=====================================================

        sf::FloatRect avatarLabelBounds =
            avatarLabel.getLocalBounds();

        avatarLabel.setOrigin({
            avatarLabelBounds.position.x +
                avatarLabelBounds.size.x /
                2.f,

            avatarLabelBounds.position.y +
                avatarLabelBounds.size.y /
                2.f
            });

        avatarLabel.setPosition({
            960.f,
            370.f
            });

        //=====================================================
        // Start button
        //=====================================================

        startButton.setSize({
            260.f,
            60.f
            });

        startButton.setPosition({
            830.f,
            935.f
            });

        startButton.setFillColor(
            sf::Color(
                30,
                28,
                26,
                180));

        startButton.setOutlineThickness(
            2.f);

        startButton.setOutlineColor(
            sf::Color(
                90,
                80,
                65));

        startText.setString(
            "START");

        startText.setCharacterSize(
            26);

        startText.setFillColor(
            sf::Color(
                110,
                105,
                95));

        sf::FloatRect startTextBounds =
            startText.getLocalBounds();

        startText.setOrigin({
            startTextBounds.position.x +
                startTextBounds.size.x /
                2.f,

            startTextBounds.position.y +
                startTextBounds.size.y /
                2.f
            });

        sf::FloatRect startButtonBounds =
            startButton.getGlobalBounds();

        startText.setPosition({
            startButtonBounds.position.x +
                startButtonBounds.size.x /
                2.f,

            startButtonBounds.position.y +
                startButtonBounds.size.y /
                2.f
            });

        debugGrid.emplace();
    }


    //=========================================================
    // Event Router
    //=========================================================

    void ProfileUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        PlayerProfile& profile,
        const std::vector<PlayerProfile>& profiles)
    {
        handleNameEntry(
            event,
            profile);

        handleAvatarSelection(
            event,
            window,
            profile,
            profiles);

        handleStart(
            event,
            window,
            profile);
    }


    //=========================================================
    // Name Entry
    //=========================================================

    void ProfileUI::handleNameEntry(
        const sf::Event& event,
        PlayerProfile& profile)
    {
        if (const auto* textEntered =
            event.getIf<sf::Event::TextEntered>())
        {
            const char32_t unicode =
                textEntered->unicode;

            if (unicode == 8)
            {
                if (!profile.playerName.empty())
                {
                    profile.playerName.pop_back();
                }
            }
            else if (unicode >= 32 &&
                unicode <= 126)
            {
                if (profile.playerName.size() < 20)
                {
                    profile.playerName +=
                        static_cast<char>(
                            unicode);
                }
            }

            nameText.setString(
                profile.playerName);
        }
    }


    //=========================================================
    // Avatar Selection
    //=========================================================

    void ProfileUI::handleAvatarSelection(
        const sf::Event& event,
        sf::RenderWindow& window,
        PlayerProfile& profile,
        const std::vector<PlayerProfile>& profiles)
    {
        if (const auto* mouseButton =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition =
                window.mapPixelToCoords(
                    mouseButton->position);

            for (int avatarID = 0;
                avatarID < 6;
                ++avatarID)
            {
                if (!avatarBoxes[avatarID]
                    .getGlobalBounds()
                    .contains(mousePosition))
                {
                    continue;
                }

                bool avatarInUse =
                    false;

                for (const auto& existingProfile :
                    profiles)
                {
                    if (existingProfile.confirmed &&
                        existingProfile.playerID !=
                        profile.playerID &&
                        existingProfile.avatarID ==
                        avatarID)
                    {
                        avatarInUse =
                            true;

                        break;
                    }
                }

                if (avatarInUse)
                {
                    return;
                }

                setAvatar(
                    avatarID,
                    profile);

                return;
            }
        }
    }


    //=========================================================
    // Set Avatar
    //=========================================================

    void ProfileUI::setAvatar(
        int avatarID,
        PlayerProfile& profile)
    {
        profile.avatarID =
            avatarID;

        for (auto& avatarBox :
            avatarBoxes)
        {
            avatarBox.setOutlineThickness(
                2.f);

            avatarBox.setOutlineColor(
                sf::Color(
                    128,
                    105,
                    65));
        }

        avatarBoxes[avatarID]
            .setOutlineThickness(
                5.f);

        avatarBoxes[avatarID]
            .setOutlineColor(
                sf::Color(
                    155,
                    70,
                    55));
    }


    //=========================================================
    // Start
    //=========================================================

    void ProfileUI::handleStart(
        const sf::Event& event,
        sf::RenderWindow& window,
        PlayerProfile& profile)
    {
        if (const auto* mouseButton =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition =
                window.mapPixelToCoords(
                    mouseButton->position);

            if (!startButton
                .getGlobalBounds()
                .contains(mousePosition))
            {
                return;
            }

            const bool canStart =
                !profile.playerName.empty() &&
                profile.avatarID != -1 &&
                !profile.confirmed;

            if (!canStart)
            {
                return;
            }

            confirmProfile(
                profile);
        }
    }


    //=========================================================
    // Confirm Profile
    //=========================================================

    void ProfileUI::confirmProfile(
        PlayerProfile& profile)
    {
        profile.confirmed =
            true;
    }


    //=========================================================
    // Reset Profile
    //=========================================================

    void ProfileUI::resetProfile()
    {
        for (auto& avatarBox :
            avatarBoxes)
        {
            avatarBox.setOutlineThickness(
                2.f);

            avatarBox.setOutlineColor(
                sf::Color(
                    128,
                    105,
                    65));
        }

        nameText.setString(
            "");
    }


    //=========================================================
    // Draw
    //=========================================================

    void ProfileUI::profileUIdraw(
        sf::RenderWindow& window,
        int playerID,
        const std::vector<PlayerProfile>& profiles)
    {
        //=====================================================
        // Current profile
        //=====================================================

        const PlayerProfile& currentProfile =
            profiles.at(playerID);

        playerNumberText.setString(
            std::to_string(
                playerID + 1));

        nameText.setString(
            currentProfile.playerName);

        //=====================================================
        // Start button state
        //=====================================================

        const bool canStart =
            !currentProfile.playerName.empty() &&
            currentProfile.avatarID != -1 &&
            !currentProfile.confirmed;

        if (canStart)
        {
            startButton.setFillColor(
                sf::Color(
                    105,
                    38,
                    32,
                    235));

            startButton.setOutlineColor(
                sf::Color(
                    190,
                    155,
                    85));

            startText.setFillColor(
                sf::Color(
                    235,
                    215,
                    170));
        }
        else
        {
            startButton.setFillColor(
                sf::Color(
                    30,
                    28,
                    26,
                    180));

            startButton.setOutlineColor(
                sf::Color(
                    90,
                    80,
                    65));

            startText.setFillColor(
                sf::Color(
                    110,
                    105,
                    95));
        }

        //=====================================================
        // Background
        //=====================================================

        window.draw(
            backgroundSprite);

        window.draw(
            musterBoardSprite);

        //=====================================================
        // Player
        //=====================================================

        window.draw(
            playerText);

        window.draw(
            playerNumberText);

        //=====================================================
        // Name
        //=====================================================

        window.draw(
            nameLabel);

        window.draw(
            nameBox);

        window.draw(
            nameText);

        //=====================================================
        // Avatar heading
        //=====================================================

        window.draw(
            avatarLabel);

        //=====================================================
        // Avatars
        //=====================================================

        for (int i = 0;
            i < 6;
            ++i)
        {
            // Reset visual state
            avatarBoxes[i].setOutlineThickness(
                2.f);

            avatarBoxes[i].setOutlineColor(
                sf::Color(
                    128,
                    105,
                    65));

            // Current player's selected avatar
            if (currentProfile.avatarID == i)
            {
                avatarBoxes[i]
                    .setOutlineThickness(
                        5.f);

                avatarBoxes[i]
                    .setOutlineColor(
                        sf::Color(
                            155,
                            70,
                            55));
            }

            window.draw(
                avatarBoxes[i]);

            window.draw(
                avatarSprites[i]);

            //=================================================
            // Previous confirmed player owns avatar
            //=================================================

            bool avatarInUse =
                false;

            for (const auto& profile :
                profiles)
            {
                if (profile.confirmed &&
                    profile.playerID != playerID &&
                    profile.avatarID == i)
                {
                    avatarInUse =
                        true;

                    break;
                }
            }

            if (avatarInUse)
            {
                sf::RectangleShape unavailableOverlay;

                unavailableOverlay.setSize(
                    avatarBoxes[i].getSize());

                unavailableOverlay.setPosition(
                    avatarBoxes[i].getPosition());

                unavailableOverlay.setFillColor(
                    sf::Color(
                        0,
                        0,
                        0,
                        140));

                window.draw(
                    unavailableOverlay);
            }
        }

        //=====================================================
        // Start
        //=====================================================

        window.draw(
            startButton);

        window.draw(
            startText);

        //=====================================================
        // Debug Grid
        //=====================================================

        /*debugGrid->draw(
            window);*/
    }

} // namespace risk