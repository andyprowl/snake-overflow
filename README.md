## Snake Overflow

Snake Overflow is a 3D snake game. Unlike classical snake games, Snake Overflow lets you control the snake by using *only two keys*: the left arrow and the right arrow (or the 'A' and 'D' keys, alternatively). These respectively turn the snake left or right *relative to its current direction of movement*, and not relative to the observer's viewpoint.

In order to follow the snake as it moves up and down the terrain, you can use the mouse to *rotate the camera* around the center of the terrain. To do so, hold the left mouse button and drag the cursor around; the camera will rotate correspondingly. You can use the mouse wheel to *zoom in and out* or, alternatively, the keys 'W' and 'S'.

The goal of the game is to score as many points as possible. The game ends when the snake bites its tail, unless an *invulnerability bonus* applies - as explained in the following. Once the game ends, it is possible to start a new game by pressing 'Enter' or 'F5'.

Several items are spawned at random intervals on the terrain's surface, and picking them up will bring you particular benefits depending on the kind of item:

 - **Fruit**: Picking a fruit will increase both your score *and* the length of the snake by its nutrition value. Each fruit has a random nutrition value ranging from 1 to 5. The size of the fruit's shape is proportional to its nutrition value. Fruit are the most frequent kind of item that will be spawned.
 - **Diet pill**: Picking a diet pill will reduce the size of the snake by 5 units, but never to a length lower than two units. Diet pills are quite common, but definitely not as common as fruit. 
 - **Invulnerability bonus**: Picking an invulnerability bonus will allow you to survive an otherwise lethal self-bite, but its effect will cease after the next bite! Also, invulnerability bonuses are not cumulative: picking two or three of them will only make you invulnerable to the next bite. When the snake is invulnerable, the color of its skin assumes a pulsing tone of red. Invulnerability bonuses are spawned relatively rarely.
 
All items have a random lifetime, with invulnerability bonuses . When the lifetime of an item expires, the item will disappear from the terrain.

# Installation instructions

The quickest way to play Snake Overflow is to:

 1. Download the `snake_overflow.zip` file from the `/deploy` subfolder in this repository.
 2. Unzip it to some local folder. 
 3. Start the `snake_overflow.exe` executable from the unzipped `/snake_overflow` folder.

Alternatively, you can build the program from the sources. To build the projects you will need Visual Studio 2013 and [Cinder 0.8.6](http://libcinder.org/blog/posts/9_cinder-086-released/).
