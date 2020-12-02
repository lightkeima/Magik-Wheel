#ifndef CLIENT_GUICONTROLLER_H
#define CLIENT_GUICONTROLLER_H

#include <vector>
#include <string>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlProperty>

class GUIController
{
private:
    QObject* root;
public:
    GUIController(QObject* root);
    //Word Display Controll


    /**
     * @brief Init the keyword and flip it back on the keyword panel.
     * @param word: the word that needs to be displayed
     */
    void SetWord(std::string word);

    /**
     * @brief Show a character at given position
     * @param position: the character's position that needs to be displayed
     */
    void ShowResultAtPosition(unsigned int position);

    /**
     * @brief Show hint
     * @param hint: a term which is hint for the keyword
     */
    void ShowHint(std::string hint);

    /**
     * @brief Create a player list bases on the number of players
     * @param number_of_player: the number of players which is the number of items on the list
     */
    void CreatePlayerList(unsigned int number_of_player);
    /**
     * @brief Change the name of the player at the  player_index position
     * @param player_index
     * @param name: the name that will replace the old name
     */
    void ChangePlayerName(unsigned int player_index, std::string name);
    /**
     * @brief Mofify the score of the player at the  player_index position. New score = current_score + point.
     * @param player_index
     * @param point: the point that  need to be added
     */
    void UpdatePlayerScore(unsigned int player_index, unsigned int point);
    void SetPlayerScore(unsigned int player_index, unsigned int point);
    /**
     * @brief Renew all information on the player list
     */
    void RenewPlayerList();

    /**
     * @brief Hightlight the player
     * @param player_index
     */
    void MarkPlayer(unsigned int player_index);
    /**
     * @brief Hightlight a disqualified player
     */
    void MarkPlayerDisqualified(unsigned int player_index);
    /**
     * @brief Flip the corresponding character on the guess panel
     * @param character
     */
    void FlipCharacter(char character);

    int GetMaxClient();

    bool AcceptClicked();
};

#endif // CLIENT_GUICONTROLLER_H
