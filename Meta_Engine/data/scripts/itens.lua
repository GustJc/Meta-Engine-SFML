local item = resources:createItem("mana potion1")
item.mMp = 3
item.mIsBuff = true
item:changeSprite(0,2)

item = resources:createItem("potion1")
item.mHp = 3
item.mIsBuff = true
item:changeSprite(1,2)

item = resources:createItem("mana potion2")
item.mMp = 3
item.mIsBuff = true
item:changeSprite(2,2)

item = resources:createItem("potion2")
item.mHp = 3
item.mIsBuff = true
item:changeSprite(3,2)

--Buff stats
item = resources:createItem("dagger")
item.mAtk = 1
item.mIsBuff = false
item:changeSprite(0,1)

item = resources:createItem("helmet")
item.mDef = 1
item.mIsBuff = false
item:changeSprite(1,1)

--item2 = resources:getItem("mana potion")
--print("Mana potion: " .. item2.mMp);
