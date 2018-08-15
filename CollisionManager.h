#ifndef _CollisionManager_
#define _CollisionManager_

class GameObject;

class CollisionManager {

public:
    //returns / creates singleton instance
    static CollisionManager* Instance();

    //returns true if two rectangles are colliding
    bool isCollidingRectRect(GameObject* rectA, GameObject* rectB, int buffer);

    bool isCollidingBulletInvader(GameObject* rectA, GameObject* rectB);
    
private:
    static CollisionManager* s_pInstance;
};

typedef CollisionManager TheCollManager;

#endif
