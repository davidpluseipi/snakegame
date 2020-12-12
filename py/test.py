import pygame
import random
import sys

pygame.init()

clock = pygame.time.Clock()
fps = 10
game_over = False
score, dx, dy = 0, 0, 0
size = 10
snake_position = []
tail = 1
window = (500, 500)  # width, height
x = window[0]/2
y = window[1]/2

screen = pygame.display.set_mode(window)
# bg = pygame.Surface(window)
bg = pygame.image.load('bg.png')
snake = pygame.image.load('white_square.png')
snake_top = screen.get_height() - snake.get_height()
snake_left = screen.get_width()/2 - snake.get_width()/2
screen.blit(snake, (snake_left, snake_top))

pygame.display.set_caption('Snake Game')


# define font
font = pygame.font.SysFont('arial', 20)

# define colors
black = (0, 0, 0)
light_grey = (200, 200, 200)
red = (213, 50, 80)


# function for outputting text to the screen
def draw_text(text, font_, text_col, x_, y_):
    img = font_.render(text, True, text_col)
    screen.blit(img, (x_, y_))


def draw_the_snake(position):
    for j in position:
        pygame.draw.rect(screen, red, [j[0], j[1], size, size])


def move_fruit():
    new_x = round(random.randrange(0, window[0] - size) / 10.0) * 10.0
    new_y = round(random.randrange(0, window[1] - size) / 10.0) * 10.0
    return new_x, new_y


# place the first fruit
(fruit_x, fruit_y) = move_fruit()

while not game_over:
    clock.tick(fps)
    screen.blit(bg, (0, 0))
    screen.blit(snake, (x - snake.get_width()/2, snake_top))

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

    # erase the screen
    # screen.fill(black)

    # update the head of the snake
    x += dx
    y += dy
    # head = [x, y]
    # snake_position.append(head)

    # update the tail
    # if len(snake_position) > tail:
    #     del snake_position[0]
    #
    # # update the fruit
    # if x == fruit_x and y == fruit_y:
    #     (fruit_x, fruit_y) = move_fruit()
    #     tail += 1

    # screen.blit(background, (0, 0))  # draw background
    # draw snake
    # draw_the_snake(snake_position)

    # draw fruit
    # pygame.draw.rect(screen, red, [fruit_x, fruit_y, size, size])

    # update the screen
    pygame.display.update()

    # # end the game if they hit the side
    # if x >= window[0] or x < 0 or y >= window[1] or y < 0:
    #     game_over = True
    #
    # # end the game if they eat the tail
    # for i in snake_position[:-1]:
    #     if i == head:
    #         game_over = True


pygame.quit()
sys.exit()
