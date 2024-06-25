#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

class Game;
class Monster;

/*Les rooms peuvent avoir trois �tats :
* Undiscovered quand le joueur n'est jamais rentr� dans la pi�ce
* Active les monstres sont vivants
* Cleared quand plus aucun monstre ne se trouve dans la pi�ce
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

    void discover(); //Permet de changer l'�tat de la pi�ce lorsque l'on rentre dedans : s'il y a des monstres, la salle est Active, sinon Cleared

    void killMonster(Entity* monster); //Appel�e par Game lorsqu'un projectile rentre en collision avec un monstre .

    std::string dump(std::string const& indent) const;

    //On s�pare les entities et les doors, pour pouvoir n'afficher les portes que lorsque la room a le statut Cleared
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> doors;

    std::string getLabel() const { return label; }
    Room_State getState() const { return state; }

private:
    std::string label;
    Room_State state = Room_State::Undiscovered;
    int monster = 0; //Retient le nombre de monstres dans la pi�ce pour g�rer son statut (incr�ment� lors de l'initialisation, d�cr�ment� lors de la mort du monstre)

    void clearRoom(); //Appel� lorsque le nombre de monstre vaut 0, pour changer le statut de la pi�ce et g�rer les �v�nements associ�s
};

