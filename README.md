# Animation-Project-1

Project 1 for GDP-6045 (Animation)

Build Instructions:
- Built using Visual Studio 17 (2022) - Retarget solution if necessary.
- All build requirements and other files are included within the project.

Animation Info:
- The project contains 3 animations which are applied to multiple objects at once.
- The animations follow a main animation time.
- The objects being animated change color based on the type of easing that is applied.
- The colors represent: Red: Ease-In, Yellow: Ease-Out, Green: Ease-InOut.
- A null key frame is added which gets called post each animation cycle.
- This null key frame prints a message to the console upon getting executed.

Controls:
- Initially the speed of all the animations will be zero.
- Numeric keys 1-5 will speed up or slow down all the animations. (The numeric keys will also start the animation.)
- Spacebar will play/pause all the animations.
- The Backtick/Grave Accent key (`) will play the animations in reverse, depending on the previous speed (when it was playing as normal).
- The free camera can be moved around with the "W,A,S,D,Q,E" keys in combination.

General Controls:
- Pressing X will turn all the meshes in the scene into wireframe.
- Pressing and holding Left_Alt will display the mouse cursor (to maximize the game window).
- Pressing F1 will enable/disable turning camera with the mouse.