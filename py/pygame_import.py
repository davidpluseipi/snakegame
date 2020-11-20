from pygame import base
import sys

module = 'pygame.base'

if module in sys.modules:
    print("OK")
else:
    print("KO")