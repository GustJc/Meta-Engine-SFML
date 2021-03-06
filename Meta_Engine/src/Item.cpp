#include "Item.h"
#include "Player.h"
#include "TextureManager.h"
Item::Item()
{
    //ctor
    type = TYPE_ITEM;
    mIsBuff = true;
    mHp = mAtk = 0;
    mMp = mDef = 0;
    mGold = 0;
    setTexture(TextureManager::TextureControl.get(Textures::ID::ITENS));
}

Item::Item(bool buff, int hpAtk, int mpDef, int idX, int idY)
{
    type = TYPE_ITEM;
    mGold = 0;
    mIsBuff = buff;
    mHp = mAtk = hpAtk;
    mMp = mDef = mpDef;
    setTexture(TextureManager::TextureControl.get(Textures::ID::ITENS));

    if(idY >= 0)
        changeSprite(idX, idY);
    else
        changeSprite(idX);

}
Item::Item(int gold, int idX, int idY)
{
    type = TYPE_ITEM;
    mIsBuff = true;
    mHp = mAtk = 0;
    mMp = mDef = 0;
    mGold = gold;
    setTexture(TextureManager::TextureControl.get(Textures::ID::ITENS));

    if(idY >= 0)
        changeSprite(idX, idY);
    else
        changeSprite(idX);

}
Item::~Item()
{
    //dtor
}

void Item::useItem()
{
    if(mIsBuff)
    {
        Player::PlayerControl->mHP += mHp;
        Player::PlayerControl->mMP += mMp;
        Player::PlayerControl->mGold += mGold;
    }
    //temp, add status permanete
    else
    {
        Player::PlayerControl->mAtk += mAtk;
        Player::PlayerControl->mDef += mDef;
    }

    removeFromTileReference();
    removeFromObjectList(); //deleta item
}
