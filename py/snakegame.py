import pygame
import random

pygame.init()
# Variable declarations
clock = pygame.time.Clock()  # used to control speed of while loop
dx = 0
dy = 0
game_over = False
h = 400  # height
tail = 1  # starting snake length
size = 10  # size of snake
snake_pos = []  # list
v = 5  # velocity of snake
w = 600  # width
x = w / 2
y = h / 2  # starting position


# function definitions
def draw_the_snake(s, pos):
    for j in pos:
        pygame.draw.rect(dis, (200, 200, 200), [j[0], j[1], s, s])


def move_fruit():
    new_x = round(random.randrange(0, w - size) / 10.0) * 10.0
    new_y = round(random.randrange(0, h - size) / 10.0) * 10.0
    return new_x, new_y


# main program
dis = pygame.display.set_mode((w, h))
pygame.display.set_caption('Snake Game')
f = pygame.font.SysFont("arial", 20)  # font for score
(fruit_x, fruit_y) = move_fruit()
while not game_over:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  # closes the game if user presses X to close
            game_over = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_a:
                dx = -size
                dy = 0
            elif event.key == pygame.K_d:
                dx = size
                dy = 0
            elif event.key == pygame.K_w:
                dx = 0
                dy = -size
            elif event.key == pygame.K_s:
                dx = 0
                dy = size
    x += dx  # increment the location of the snake
    y += dy
    dis.fill((0, 0, 0))  # clear the board before redrawing

    pygame.draw.rect(dis, (213, 50, 80), [fruit_x, fruit_y, size, size])  # draw the fruit

    head = [x, y]

    snake_pos.append(head)  # put the head at the end of the list

    if len(snake_pos) > tail:  # remove the oldest part of the snake
        del snake_pos[0]

    for i in snake_pos[:-1]:  # end the game if you eat your tail
        if i == head:
            game_over = True

    draw_the_snake(size, snake_pos)

    dis.blit(f.render(str(tail - 1), True, (200, 200, 200)), [0, 0])  # display score

    pygame.display.update()

    if x == fruit_x and y == fruit_y:  # if you eat the fruit, move it and get a point
        (fruit_x, fruit_y) = move_fruit()
        tail += 1

    clock.tick(v)  # control the speed of the game

    if x >= w or x < 0 or y >= h or y < 0:  # end the game if you touch side
        game_over = True

pygame.quit()
quit()
