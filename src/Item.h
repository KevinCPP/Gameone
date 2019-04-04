#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <ostream>

class Item{
private:
    sf::Sprite      itemSprite;     //stores the sprite that will represent the item
    sf::Texture     itemTexture;    //stores the sprite's texture
    sf::Vector2f    position;       //stores the position of the item (real coordinates, relative to window not room).
    sf::Vector2f    Size;           //stores the size of the item length*width

    bool collected; //boolean that stores weather the item was collected.
    int itemID;     //the item's unique numeric ID.
    uint32_t value; //the item's currency value.
public:

    /* enum that stores the different types of items,
     * enum class was not needed, and it is shorter to
     * type in other classes:
    */
    enum Item_Type{
        Weapon = 0,
        Usable,
        Money,
        Collectible
    };

    Item_Type itemType; //stores what type of item it is - weapon, usable, money, or Collectible.

    Item(const int& iID);   //constructor that only takes the item ID

    //constructor for Item
    Item(const sf::Texture* tx,     //initializes the item's texture
         const sf::Vector2f& pos,   //initializes the item's position
         const int& iID,            //initializes the item's ID.
         Item_Type type,            //initializes the item's type (see: Item_Type)
         const int& v);             //initializes the item's value.

    //ostream operator overload:
    friend std::ostream& operator<< (std::ostream& o, const Item& item);
    friend std::istream& operator>> (std::istream& i, Item& item);

    //getters:
    sf::FloatRect getCollision() const;   //returns the item's collision rectangle.
    sf::Vector2f getPosition() const;     //returns the position of the item (real coordinates, x and y)
    sf::Vector2f getSize() const;         //returns the item's size length*width.
    Item_Type getType() const;            //returns the item's type.
    int getTypeInt() const;               //returns the item's type as an int.
    int getItemID() const;                //returns the item's unique numeric ID.
    int getValue() const;                 //returns the item's value.


    //setters:
    void setPosition(const sf::Vector2f& pos);  //sets the item's position.
    void setTexture(const sf::Texture* tx);     //sets the item's texture to be used on it's sprite
    void setSize(const sf::Vector2f& sz);       //sets the item's size width and height.
    void setValue(const uint32_t& v);           //sets the currency value of the item (value var)
    void setItemType(Item_Type type);           //sets the item type and takes an Item_Type
    void setItemType(int type);                 //sets the item type with an int that corresponds with an item in the enum Item_Type.

    int collect();  //collects the item and returns it's unique numeric ID and sets collected to true.
    void draw();    //draws the item to the window (as long as collected == false).
};

#endif // ITEMS_H_INCLUDED
