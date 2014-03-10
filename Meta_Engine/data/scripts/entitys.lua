--Small guy
local enemy = res:createEntity("lv0")
enemy.mAtk          = 2
enemy.mDef          = 0
enemy.mHp           = 3
enemy.mSpeedCost    = 150
enemy:changeSprite(1,0)
--Angry small guy
enemy       = res:createEntity("lv1")
enemy.mAtk          = 4
enemy.mDef          = 0
enemy.mHp           = 2
enemy.mSpeedCost    = 150
enemy:changeSprite(2,0)
--Medium guy
enemy       = res:createEntity("lv2")
enemy.mAtk          = 3
enemy.mDef          = 1
enemy.mHp           = 6
enemy.mSpeedCost    = 200
enemy.mRange        = 4
enemy:changeSprite(3,0)
--Angry Medium guy
enemy       = res:createEntity("lv3")
enemy.mAtk          = 6
enemy.mDef          = 0
enemy.mHp           = 4
enemy.mSpeedCost    = 200
enemy.mRange        = 4
enemy:changeSprite(4,0)
--Big guy
enemy       = res:createEntity("lv4")
enemy.mAtk          = 5
enemy.mDef          = 2
enemy.mHp           = 10
enemy.mSpeedCost    = 250
enemy.mRange        = 3
enemy:changeSprite(5,0)
--Angry Big guy
enemy       = res:createEntity("lv5")
enemy.mAtk          = 10
enemy.mDef          = 1
enemy.mHp           = 5
enemy.mSpeedCost    = 250
enemy.mRange        = 3
enemy:changeSprite(6,0)
