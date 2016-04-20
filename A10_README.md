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
 - b) F5 and F6 cycle through the current BO's F7 and F8 toggle the visibility of the current selection
 - c) The number of BO's is printed after "Number of Game Objects" on the top left of the screen
 - d) The color of a game object can be set through GameObject::SetDebugColor();
 - e) F7 and F8 change the visibility of the AABB and NAB, respectively, of the current selection
 - f) F9 and F10 toglle the visibility of all of the AABB's and NAB's, respectively
 - g) GameObject::UpdateAll checks collisions for all Game Objects
 - h) The color of a colliding BO is changed to Red

 The blue cone can be move around with arrow keys and rotated with the MMB
