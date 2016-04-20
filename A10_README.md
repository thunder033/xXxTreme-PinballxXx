#A10 - Bounding Object Manager

Collider = MyBoundingObjectClass
 - a) GameObject is constructed from a MeshClass that instantiates a Collider with MeshClass instance vertex list
 - b) GameObject.RenderDebugHelpers() draws the Collider AABB for that frame
 - c) Collider.GetCenter() returns the center
 - d) Collider.GetMin()/Collider.getMax() return the min/max points
 - e) Collider.SetModelMatrix()/Collider.getAxisAlignedTransform()
 *- f) GameObject.SetDebugColor(color) 
 - g) GameObject.RenderDebugHelpers() draws the Collider
 - h) Collider.IsColliding() checks for collision against another Collider
GameObject (static methods) = BoundingObjectManager
 - a) A new GameObject is instantiated with a MeshClass-based Collider
 - b) ???
