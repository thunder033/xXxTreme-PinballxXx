#A10 - Bounding Object Manager

Collider = MyBoundingObjectClass
 - a) GameObject is constructed from a MeshClass that instantiates a Collider with MeshClass instance vertex list
 - b) GameObject.renderDebugHelpers() draws the Collider AABB for that frame
 - c) Collider.getCenter() returns the center
 - d) Collider.getMin()/Collider.getMax() return the min/max points
 - e) Collider.setModelMatrix()/Collider.getAxisAlignedTransform()
 *- f) GameObject.setDebugColor() 
 - g) GameObject.renderDebugHelpers() draws the Collider
 - h) Collider.isColliding() checks for collision against another Collider
GameObject (static methods) = BoundingObjectManager
 - a) A new GameObject is instantiated with a MeshClass-based Collider
 - b) ???
 - c) GameObject::getGameObjectCount()