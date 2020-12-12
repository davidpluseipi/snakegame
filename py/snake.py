from PIL import Image
import math
import pygame
import random
import sys
import time

pygame.init()

capture_radius = 15
clock = pygame.time.Clock()
fps = 15
game_over = False
offset = [0, 0]
score, dx, dy = 0, 0, 0
size = 10
snake_position = []
spacing = 20
tail = 1
window = (500, 500)  # width, height
words = ['BAM!', 'POW!', 'Nice!', 'Shazam!']
x = window[0]/2
y = window[1]/2

screen = pygame.display.set_mode(window)
# bg = pygame.Surface(window)

# load images
bg = pygame.image.load('bg.png')
snake = pygame.image.load('white_square.png')

# temp = Image.open('darth_vader.png')
# darth = temp.resize((16, 16))
# darth.save('darth_vader2.png')
darth = pygame.image.load('darth_vader.png')

# set default snake position
snake_top = screen.get_height()/2 - snake.get_height()
snake_left = screen.get_width()/2 - snake.get_width()/2

# draw the snake
screen.blit(snake, (snake_left, snake_top))

# set title bar caption
pygame.display.set_caption('Snake')

# define font
font = pygame.font.SysFont('arial', 20)

# define colors
black = (0, 0, 0)
light_grey = (200, 200, 200)
red = (213, 50, 80)


# function for outputting text to the screen
def draw_text(text, font_, text_color, position):
    img = font_.render(text, True, text_color)
    screen.blit(img, (position[0], position[1]))


def draw_the_snake(position, img):
    for j in position:
        screen.blit(img, (j[0] - img.get_width() / 2, j[1]))


def draw_fruit(position, img):
    screen.blit(img, (position[0] - img.get_width() / 2, position[1]))


def move_fruit():
    new_x = round(random.randrange(0, window[0] - size) / 10.0) * 10.0
    new_y = round(random.randrange(0, window[1] - size) / 10.0) * 10.0
    return new_x, new_y


def check_collisions():
    # end the game if they hit the side
    if x >= window[0] or x < 0 or y >= window[1] or y < 0:
        return True
    else:
        # end the game if they eat the tail
        for i in snake_position[:-1]:
            if i == head:
                return True
            else:
                return False


# place the first fruit
(fruit_x, fruit_y) = move_fruit()

while not game_over:
    clock.tick(fps)
    screen.blit(bg, (0, 0))

    for event in pygame.event.get():

        # check for quit events
        if event.type == pygame.QUIT:
            game_over = True

        # check for KEYDOWN events
        if event.type == pygame.KEYDOWN:

            if event.key == pygame.K_LEFT:
                dx = -size
                dy = 0

            if event.key == pygame.K_RIGHT:
                dx = size
                dy = 0

            if event.key == pygame.K_DOWN:
                dx = 0
                dy = size

            if event.key == pygame.K_UP:
                dx = 0
                dy = -size

    # update the head of the snake
    x += dx
    y += dy
    head = [x, y]
    snake_position.append(head)

    # update the tail
    if len(snake_position) > tail:
        del snake_position[0]

    # update the fruit
    distance = math.sqrt((x - fruit_x)**2 + (y - fruit_y)**2)
    if distance < capture_radius:

        # offset the fruit capture words based on snake position
        if x < screen.get_width()/2:
            offset[0] = spacing
        else:
            offset[0] = -spacing
        if y < screen.get_height()/2:
            offset[1] = -spacing
        else:
            offset[1] = spacing

        # display a randomly selected word on fruit capture
        selection = random.randrange(1, 4)
        draw_text(words[selection], font, light_grey, (fruit_x + offset[0], fruit_y + offset[1]))
        pygame.display.update()
        time.sleep(0.2)

        (fruit_x, fruit_y) = move_fruit()
        tail += 1

    # draw snake
    draw_the_snake(snake_position, snake)

    # draw fruit
    draw_fruit((fruit_x, fruit_y), darth)

    # update the screen
    pygame.display.update()

    # check for "collisions" / game enders
    game_over = check_collisions()

pygame.quit()
sys.exit()
