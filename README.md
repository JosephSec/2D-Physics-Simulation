This is V.1 of a 2D Space Physics Simulation made in c++ with the SFML Graphics Library.

//BIO
This version uses integrated graphics to render and physically
simulate nearly 1 million particles.

//UI TOOL
Use the UI Tool inspired by and created specifically for this project to fully customize the rendering and simulation.
Editable text values are displayed with a lighter gray background. Toggle bool values with the green/red squares.
Change RGBA Color values with the colored rectanlge.
Get Full customization of the RGBA values with the Color Select UI window by clicking on the Color Rectangle.

//SIMULATION
The simulation window offers a variety of options to control how the simulation plays out.

View how many simulated bodies are in the space.

Pause the simulation to take a moment and make changes
Change the Time Scale to speed up or slow down the speed of the simulation.
The Time Scale changes how many frames play out to keep the accuracy of the simulation.

Change whether or not the window limits the space where simulated bodies can go with the Window Bounds.

Toggle Earth Gravity and apply a constant downward force to all the bodies in space.

Change the overall Gravity value that applies to ALL forces in the space.

Use the Black hole preset to make your own mini galaxy.
Change the mass and watch the size of the black represent a (semi) realistic black hole radius.

Use the cursor to move and control the bodies in the simulation how you want.
Change the mass of cursor to control how strong the pulling and pushing force is applied from the mouse.
Use the Scale By World Zoom to make the cursor mass scale by the World Zoom to keep a consistent force.


//RENDERING
Change the way you see the space with the 2D camera. Move around the infinite space with WASD or the arrow keys.
Magnify the view with the World Zoom to see the smallest changes, or zoom out and get a more spacious view.

Visualize the velocity applied to the space by a force with any resolution (that your pc can handle).
Change the sensitivity to see even the smallest forces applied. Or make only the strongest forces visible.

Visualize the velocity to get a more colorful view of all the objects.
Change the colors to get more interesting visuals, or change the base color to get a more simple view.


//SYSTEM
View the overall performance of the program with the System menu. Get the current FPS of the program.
View the Draw Time to see how long it took to Render the simulation.
View the Move Time to see how long it took to Simulate and apply the physics of the simulation.
Also view how many thread are being used by the program.

Also Comes with a extra Fill Screen option to fill the screen with simulated points for and extra, fun option.
