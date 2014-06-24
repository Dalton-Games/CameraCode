Camera Code
===========

Pseudo isometric 3d camera that imitates Civilization 5 camera with a few extra features.

* WASD control (mapeable to other keys/controls by UE4)
* Q and E rotates camera (idem)
* Zoom by mouse wheel (idem)
* Right Click to move the camera to the location below the mouse
* Drag with right button to move the camera
* Added a interactive object to test Mouse Over and Mouse Click events on Actors
  * Highlighting it when mouse is over using a Dynamic Material parameter
  * Click on it show a debug message with "Click"
  * Added a Post Process material that allow to render a solid shape of the mesh if it must have "render to custom depth buffer" enabled. It will require to tweak "Bounds scale" value of the mesh to avoid that occlusion query hides the mesh when we need to allow to see the shape of he mesh.


TODO :

* Add logic to use fixed Z axis values depending of floors and hidden stuff that is over the actual floor. I like to use two fingers drag to move the camera like Right button drag. And Two finger rotation and zoom to control view zoom and rotation.
* Code for touch events (actually I can only test single finger touch events)

