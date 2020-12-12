import pygame
# import time

pygame.init()

clock = pygame.time.Clock()
dx, dy = 0, 0
game_over = False
width, height = 500, 500
size = 10
v = 5
x = int(round(width/2))
y = int(round(height/2))
window = (width, height)

screen = pygame.display.set_mode(window)
background = pygame.Surface(window)
screen.blit(background, (0, 0))

while not game_over:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game_over = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_a:
                dx = -size
                dy = 0
    x += dx
    y += dy
    pygame.draw.rect(background, (200, 200, 200), (x, y, size, size))
    screen.blit(background, (0, 0))
    pygame.display.update()
    clock.tick(v)
pygame.quit()
quit()

