import pyglet
from collections import deque
from bird import Bird
from pipe import Pipe

class FBGame():


    def __init__(self, **kwargs):
        """Class that controls the Flappy Bird Pacman."""
        self.bird = Bird(x=kwargs['bird_x'], y=kwargs['bird_y'], radius=kwargs['bird_radius'], height=kwargs['window_height'])
        self.pipes_pop = self._create_pipes_population(**kwargs)
        self.height, self.width, self.pipe_size = kwargs['window_height'], kwargs['window_width'], kwargs['pipe_size']
        self.lost = False

    def update(self, dt):
        """Updates the state of the game, updates bird and pipes."""
        #checks if the birds hit one of the pipes
        if self.bird.hits(self.pipes_pop[0]):
            self.lost = True
        self.bird.updates()
        for pipe in self.pipes_pop:
            pipe.updates()
        #
        if self.pipes_pop[0].x + self.pipe_size < 0:
            self.pipes_pop.popleft()
            self._append_new_pipe()

    def jump_bird(self):
        """Makes the bird jump if the game is not over."""
        if not self.lost:
            self.bird.apply_force(5)

    def show(self):
        """Shows the bird and the pipes."""
        self.bird.show()
        for pipe in self.pipes_pop:
            pipe.show()
        if self.lost:
            self._game_over()
    
    def reset(self, **kwargs):
        """Resets the game to initial state."""
        self.__init__(**kwargs)

    def _game_over(self):
        """Draws the Game Over message."""
        pyglet.text.Label('Game Over',font_name='Times New Roman',font_size=60,x=self.width/2, y=self.height/2, color=(255,0,0,255),
                                  anchor_x='right', anchor_y='center').draw()

    def _append_new_pipe(self):
        """Appends a new pipe to the game."""
        self.pipes_pop.append(Pipe(x=self.pipes_pop[-1].x + 5*self.pipe_size, size=self.pipe_size, height=self.height))

    def _create_pipes_population(self, **kwargs):
        """Creates the inital population of pipes."""
        return deque([Pipe(x=kwargs['pipe_x'] + dx, height=kwargs['window_height'], size=kwargs['pipe_size'])
                                        for dx in range(kwargs['pipe_x'], kwargs['window_width'], 5*kwargs['pipe_size'])])    