from pyglet.window import Window
import pyglet
from game import FBGame

window = Window(600, 800, caption='Flappy Bird')

game_dict = {
    'bird_x': 80,
    'bird_y': window.height/2,
    'bird_radius': 30,
    'pipe_x': 400,
    'pipe_size': 80,
    'window_width': window.width + 300,
    'window_height': window.height
}
game = FBGame(**game_dict)

@window.event
def on_key_press(symbol, modifiers):
    if symbol is pyglet.window.key.W:
        game.jump_bird()
    if symbol is pyglet.window.key.R:
        game.reset(**game_dict)

@window.event
def on_draw():
    window.clear()
    game.show()

pyglet.clock.schedule(game.update)
pyglet.app.run()    