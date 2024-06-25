#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

class Game;
class Monster;

/*Les rooms peuvent avoir trois états :
* Undiscovered quand le joueur n'est jamais rentré dans la pièce
* Active les monstres sont vivants
* Cleared quand plus aucun monstre ne se trouve dans la pièce
*/
enum class Room_State {
    Undiscovered,
    Active,
    Cleared
};

class Room 
{

public:
    explicit(false) Room(pugi::xml_node node, Game* game, Player* player);

    void render(sf::RenderWindow* mWindow) const;

    void discover(); //Permet de changer l'état de la pièce lorsque l'on rentre dedans : s'il y a des monstres, la salle est Active, sinon Cleared

    void killMonster(Entity* monster); //Appelée par Game lorsqu'un projectile rentre en collision avec un monstre .

    std::string dump(std::string const& indent) const;

    //On sépare les entities et les doors, pour pouvoir n'afficher les portes que lorsque la room a le statut Cleared
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> doors;

    std::string getLabel() const { return label; }
    Room_State getState() const { return state; }

private:
    std::string label;
    Room_State state = Room_State::Undiscovered;
    int monster = 0; //Retient le nombre de monstres dans la pièce pour gérer son statut (incrémenté lors de l'initialisation, décrémenté lors de la mort du monstre)

    void clearRoom(); //Appelé lorsque le nombre de monstre vaut 0, pour changer le statut de la pièce et gérer les évènements associés
};

