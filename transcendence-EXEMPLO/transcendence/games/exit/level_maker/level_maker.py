import pygame
import os
import random
import sys
#import pyperclip # pyperclip.copy('The text to be copied to the clipboard.')

if len(sys.argv) == 2:
    blockSize = int(sys.argv[1])
else:
    blockSize = 40 #size of the grid block

WIDTH, HEIGHT = 840, 680 #the window size


# if no level to import : import_level = None if a level to import # -> l.31
import_level =[
[7, 7, 7, 7, 7, 7, 9, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 9, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
[7, 0, 0, 0, 0, 9, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1, 9, 0, 0, 0, 7, 7, 0, 0, 0, 0, 7],
[7, 0, 0, 0, 9, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 9, 0, 0, 0, 7, 0, 0, 0, 0, 7],
[7, 0, 0, 0, 9, 1, 2, 2, 3, 3, 9, 9, 9, 9, 9, 3, 3, 2, 2, 1, 9, 0, 0, 0, 0, 7, 0, 0, 0, 7],
[7, 0, 0, 9, 1, 1, 2, 3, 3, 9, 0, 7, 0, 0, 0, 9, 3, 3, 2, 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 7],
[7, 0, 0, 9, 9, 9, 2, 3, 9, 0, 0, 0, 0, 7, 0, 0, 9, 3, 2, 2, 1, 9, 0, 0, 0, 0, 0, 0, 0, 7],
[7, 0, 9, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0, 9, 3, 3, 2, 1, 9, 0, 0, 0, 0, 0, 0, 0, 7],
[7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 7, 9, 9, 3, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 7],
[7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 9, 0, 0, 9, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 7],
[7, 0, 9, 0, 0, 9, 9, 0, 0, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 7, 7],
[7, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 7, 7],
[7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 7, 0, 0, 0, 7],
[7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 7, 0, 9, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 7, 0, 0, 7],
[7, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 7, 0, 0, 7],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7],
[7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0, 0, 7],
[7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
]
import_level = None


#this level is draw if the user press the specific key ( = i). It will not delete the other block when 0.
import_level_bis = [
[5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],
[5, 1, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 5],
[5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 5],
[5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 0, 1, 0, 0, 3, 3, 3, 0, 0, 0, 1, 0, 0, 5],
[5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 2, 3, 9, 3, 3, 3, 0, 0, 1, 1, 1, 1],
[5, 1, 5, 0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 0, 0, 3, 0, 0, 5],
[5, 1, 1, 1, 1, 1, 2, 3, 9, 3, 3, 3, 0, 0, 0, 1, 0, 1, 1, 0, 3, 3, 3, 0, 0, 3, 3, 0, 0, 5],
[5, 5, 5, 0, 0, 1, 0, 3, 3, 3, 3, 3, 0, 0, 3, 1, 5, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 5],
[5, 1, 1, 5, 0, 1, 0, 0, 3, 3, 3, 0, 0, 3, 3, 1, 0, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5],
[5, 1, 1, 0, 0, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 5],
[5, 1, 1, 0, 0, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 1, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 5],
[5, 1, 1, 1, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5],
[5, 0, 1, 0, 0, 5, 0, 5, 5, 3, 3, 3, 3, 3, 0, 5, 5, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5],
[5, 0, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 1, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 5],
[5, 0, 5, 5, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 5],
[5, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5],
[5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],
]




pygame.font.init()


right_border = WIDTH//80  # the right border size (when small number : bigger) (for texture selection)
WIN = pygame.display.set_mode((WIDTH + WIDTH//right_border , HEIGHT + 40*2))
pygame.display.set_caption("level_maker")
WHITE = (200, 200, 200)
BLACK = (0, 0, 0)
line_color = (180,180,180)#color of the border line
bg_color_1, bg_color_2 ,bg_color_3 = 8,8,8
bg_color = (bg_color_1, bg_color_2 ,bg_color_3)


# brick_1 = "grass.png"
# brick_2 = "pierre_centre.png"
# brick_4 = "bois_seul.png"
# brick_7 = "planche_bois.png"
# brick_3 = "bloque_pierre.png"
# brick_8 = "chest.png"
# brick_6 = "bois_triangle.png"
# brick_9 = "vase.png"
# brick_5 = "bois_triangle_.png"

brick_1 = "color_1.png"
brick_2 = "color_2.png"
brick_3 = "color_3.png"
brick_4 = "color_4.png"
brick_5 = "color_5.png"
brick_6 = "color_6.png"
brick_7 = "color_7.png"
brick_8 = "color_8.png"
brick_9 = "color_9.png"





#load images
brick_n_1 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_1)),(blockSize,blockSize))
brick_n_2 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_2)),(blockSize,blockSize))
brick_n_3 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_3)),(blockSize,blockSize))
brick_n_4 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_4)),(blockSize,blockSize))
brick_n_5 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_5)),(blockSize,blockSize))
brick_n_6 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_6)),(blockSize,blockSize))
brick_n_7 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_7)),(blockSize,blockSize))
brick_n_8 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_8)),(blockSize,blockSize))
brick_n_9 = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_9)),(blockSize,blockSize))

#images for option icon
gride_icon =  pygame.transform.scale(pygame.image.load(os.path.join("assets", "gride_icon.png")),(40,40))
rgb_red_arrow =  pygame.transform.scale(pygame.image.load(os.path.join("assets", "rgb_red_arrow.png")),(40,40))
rgb_green_arrow =  pygame.transform.scale(pygame.image.load(os.path.join("assets", "rgb_green_arrow.png")),(40,40))
rgb_blue_arrow =  pygame.transform.scale(pygame.image.load(os.path.join("assets", "rgb_blue_arrow.png")),(40,40))
option_image_2 =  pygame.transform.scale(pygame.image.load(os.path.join("assets", "option_image_2.png")),(40,40))
option_finish_icon =  pygame.transform.scale(pygame.image.load(os.path.join("assets", "option_finish_icon.png")),(40,40))



texture_1 = True
texture_2 = False
texture_3 = False
texture_4 = False
texture_5 = False
texture_6 = False
texture_7 = False
texture_8 = False
texture_9 = False


FPS = 60
run = True
gride = True
block_number_switcher = False
rgb_step = 2

main_font = pygame.font.SysFont("coopbl", 21)
rgb_font = pygame.font.SysFont("coopbl", 21)
import_font = pygame.font.SysFont("coopbl", 17)
loading_font = pygame.font.SysFont("coopbl", 90)
list_pos_1 =[]
list_pos_2 =[]
list_pos_3 =[]
list_pos_4 =[]
list_pos_5 =[]
list_pos_6 =[]
list_pos_7 =[]
list_pos_8 =[]
list_pos_9 =[]
global_list = []




clock = pygame.time.Clock()

# def add_to_list(list_pos, texture_number): #
#     global global_list
#
#
#     if pos not in list_pos and texture_number == True and pos[0]< WIDTH // blockSize and pos[1]< HEIGHT // blockSize:
#         if pos in global_list:
#             if pos in list_pos_1:
#                 list_pos_1.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_2:
#                 list_pos_2.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_3:
#                 list_pos_3.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_4:
#                 list_pos_4.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_5:
#                 list_pos_5.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_6:
#                 list_pos_6.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_7:
#                 list_pos_7.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_8:
#                 list_pos_8.remove(pos)
#                 global_list.remove(pos)
#             if pos in list_pos_9:
#                 list_pos_9.remove(pos)
#                 global_list.remove(pos)
#         #list_pos.append(pos)
#         #global_list.append(list_pos[-1])
#     else:
#         if texture_number == True and pos[0]< WIDTH // blockSize and pos in global_list:
#             list_pos.remove(pos)
#             global_list.remove(pos)


def drag_and_place(list_pos, texture_number):
    pos_ = pygame.mouse.get_pos()
    pos_ =  (pos_[0] //blockSize , pos_[1] //blockSize )

    if pos_ not in list_pos and texture_number == True  and pos_[0]< WIDTH // blockSize and pos_[1]< HEIGHT // blockSize:
        if pos_ in global_list:
            if pos_ in list_pos_1:
                list_pos_1.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_2:
                list_pos_2.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_3:
                list_pos_3.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_4:
                list_pos_4.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_5:
                list_pos_5.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_6:
                list_pos_6.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_7:
                list_pos_7.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_8:
                list_pos_8.remove(pos_)
                global_list.remove(pos_)
            if pos_ in list_pos_9:
                list_pos_9.remove(pos_)
                global_list.remove(pos_)

        if pos_ not in global_list:
            list_pos.append(pos_)
            global_list.append(pos_)


def drag_and_remove():
    pos_ = pygame.mouse.get_pos()
    pos_ =  (pos_[0] //blockSize , pos_[1] //blockSize )
    if pos_ in global_list and pos_[0]< WIDTH // blockSize and pos_[1]< HEIGHT // blockSize:
        if pos_ in list_pos_1:
            list_pos_1.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_2:
            list_pos_2.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_3:
            list_pos_3.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_4:
            list_pos_4.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_5:
            list_pos_5.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_6:
            list_pos_6.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_7:
            list_pos_7.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_8:
            list_pos_8.remove(pos_)
            global_list.remove(pos_)
        if pos_ in list_pos_9:
            list_pos_9.remove(pos_)
            global_list.remove(pos_)



def texture_creator(list_pos,brick_texture):
    for i in range(len(list_pos)):
        rect = pygame.Rect(list_pos[i][0]* blockSize,list_pos[i][1] * blockSize, blockSize, blockSize)
        WIN.blit(brick_texture ,rect)


def image_to_level(list_pos, number_in_grid):
    for v in range(len(list_pos)):
        level_list[list_pos[v][1]][list_pos[v][0]] = number_in_grid


def texture_selector(brick_texture, pos_x, pos_y):
    brick_selector = pygame.transform.scale(pygame.image.load(os.path.join("assets", brick_texture)),(WIDTH//right_border - 40, WIDTH//right_border - 40))
    rect = pygame.Rect(pos_x, pos_y , 40, 40)
    WIN.blit(brick_selector ,rect)

#button for the texture selection
def textur_selector_button(button_number):
    space = (40/2 + WIDTH//right_border - 40) * (button_number-1)
    if pos_texture_selector[0] > WIDTH + 40/2 and pos_texture_selector[0] < WIDTH + 40/2 + WIDTH//right_border - 40:
        if pos_texture_selector[1] > 40/2 + space  and pos_texture_selector[1]  < 40/2 + WIDTH//right_border - 40 + space:
            return True

#detection if click on the button
def menu_option(button_n_option,button_size):
    global gride, block_number_switcher, bg_color_1, bg_color_2,bg_color_3,  level_list
    if button_size == "big":
        button_n_option = button_n_option-1
        if pos_texture_selector[0] >= 40/2 + (button_n_option*40/2*3) and  pos_texture_selector[0] < 40 + 40/2+ (button_n_option*40/2*3):
            if pos_texture_selector[1] >= HEIGHT +40/2 and  pos_texture_selector[1] <= HEIGHT +40/2 + 40:
                if button_n_option == 0: # for the first buton
                    if gride == False:
                        gride = True
                    else:gride = False
                if button_n_option == 1: # for the first buton
                    if block_number_switcher == False:
                        block_number_switcher = True
                    else:block_number_switcher = False
                if button_n_option == 2:
                    level_list = []

                    for j in range(int(HEIGHT / blockSize)): #int(HEIGHT / blockSize)
                        j = str(j)
                        j = []
                        j.clear()
                        j = []
                        for i in range(int(WIDTH / blockSize)): #int(WIDTH / blockSize)
                            j.append(0)
                        level_list.append(j)
                    image_to_level(list_pos_1,1)
                    image_to_level(list_pos_2,2)
                    image_to_level(list_pos_3,3)
                    image_to_level(list_pos_4,4)
                    image_to_level(list_pos_5,5)
                    image_to_level(list_pos_6,6)
                    image_to_level(list_pos_7,7)
                    image_to_level(list_pos_8,8)
                    image_to_level(list_pos_9,9)


                    # make the text to the good form
                    print("\nMy lord, your level is ready : \n")
                    print("[")
                    for b in range(len(level_list)):
                        print(str(level_list[b])+",")
                    print("]")



    if button_size == "small_up":
        button_n_option = button_n_option-1
        if pos_texture_selector[1] >= HEIGHT +40/2 and  pos_texture_selector[1] <= HEIGHT  + 40:
            if pos_texture_selector[0] >= 40/2 + (button_n_option*40/2*3) and  pos_texture_selector[0] < 40 + 40/2+ (button_n_option*40/2*3):
                if button_n_option == 3: # for the first buton
                    if bg_color_1 <=255-rgb_step :
                        bg_color_1 = bg_color_1 + rgb_step
                if button_n_option == 4: # for the first buton
                    if bg_color_2 <=255-rgb_step :
                        bg_color_2 = bg_color_2 + rgb_step
                if button_n_option == 5: # for the first buton
                    if bg_color_3 <=255-rgb_step:
                        bg_color_3 = bg_color_3 + rgb_step
    if button_size == "small_down":
        button_n_option = button_n_option-1
        if pos_texture_selector[1] >= HEIGHT +40 and  pos_texture_selector[1] <= HEIGHT  + 40 + 40/2:
            if pos_texture_selector[0] >= 40/2 + (button_n_option*40/2*3) and  pos_texture_selector[0] < 40 + 40/2+ (button_n_option*40/2*3):
                if button_n_option == 3: # for the first buton
                    if bg_color_1 >=0 + rgb_step :
                        bg_color_1 = bg_color_1 - rgb_step
                if button_n_option == 4: # for the first buton
                    if bg_color_2 >=0 + rgb_step :
                        bg_color_2 = bg_color_2 - rgb_step

                if button_n_option == 5: # for the first buton
                    if bg_color_3 >=0 + rgb_step:
                        bg_color_3 = bg_color_3 - rgb_step


#blit the image for the menu
def menu_option_button(button_n_option,option_image):
    button_n_option = button_n_option-1
    rect = pygame.Rect(40/2 + (button_n_option*40/2*3), HEIGHT + 40/2 , 40, 40)
    WIN.blit(option_image,rect)


    #make the gride between blocks
def gride_maker():
    if gride == True:
        for x in range(int(WIDTH/blockSize)):
            for y in range(int(HEIGHT/blockSize)):
                rect = pygame.Rect(x*blockSize, y*blockSize, blockSize, blockSize)
                pygame.draw.rect(WIN, WHITE, rect, 1)
    pygame.draw.line(WIN, (line_color),(WIDTH,0),(WIDTH, HEIGHT),2)
    pygame.draw.line(WIN, (line_color),(0,HEIGHT),(WIDTH, HEIGHT),2)




# to make that it is possible to import a previous made level
def grid_in_list(lev_import, level_list, number):
    if lev_import != None:
        for j, ligne in enumerate(lev_import):
            for i, case in enumerate(ligne):
                if case == number:
                    if (i,j) not in global_list:
                        level_list.append((i,j))
                        global_list.append(level_list[-1])

grid_in_list(import_level, list_pos_1,1)
grid_in_list(import_level, list_pos_2,2)
grid_in_list(import_level, list_pos_3,3)
grid_in_list(import_level, list_pos_4,4)
grid_in_list(import_level, list_pos_5,5)
grid_in_list(import_level, list_pos_6,6)
grid_in_list(import_level, list_pos_7,7)
grid_in_list(import_level, list_pos_8,8)
grid_in_list(import_level, list_pos_9,9)

while run:

    clock.tick(FPS)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

        if event.type == pygame.MOUSEBUTTONDOWN :
            pos = pygame.mouse.get_pos()
            pos =  (pos[0] //blockSize , pos[1] //blockSize )
            pos_texture_selector = pygame.mouse.get_pos()

            menu_option(1, "big")
            menu_option(2, "big")
            menu_option(3, "big")
            menu_option(4, "small_up")
            menu_option(5, "small_up")
            menu_option(6, "small_up")
            menu_option(4, "small_down")
            menu_option(5, "small_down")
            menu_option(6, "small_down")



            textur_selector_button(1)
            if textur_selector_button(1) == True:
                texture_1 = True
                texture_2 = False
                texture_3 = False
                texture_4 = False
                texture_5 = False
                texture_6 = False
                texture_7 = False
                texture_8 = False
                texture_9 = False


            textur_selector_button(2)
            if textur_selector_button(2) == True:
                texture_1 = False
                texture_2 = True
                texture_3 = False
                texture_4 = False
                texture_5 = False
                texture_6 = False
                texture_7 = False
                texture_8 = False
                texture_9 = False


            textur_selector_button(3)
            if textur_selector_button(3) == True:
                texture_1 = False
                texture_2 = False
                texture_3 = True
                texture_4 = False
                texture_5 = False
                texture_6 = False
                texture_7 = False
                texture_8 = False
                texture_9 = False


            textur_selector_button(4)
            if textur_selector_button(4) == True:
                texture_1,texture_2 = False, False
                texture_3 = False
                texture_4 = True
                texture_5 = False
                texture_6 = False
                texture_7 = False
                texture_8 = False
                texture_9 = False

            textur_selector_button(5)
            if textur_selector_button(5) == True:
                texture_1 = False
                texture_2 = False
                texture_3 = False
                texture_4 = False
                texture_5 = True
                texture_6 = False
                texture_7 = False
                texture_8 = False
                texture_9 = False

            textur_selector_button(6)
            if textur_selector_button(6) == True:
                texture_1 = False
                texture_2 = False
                texture_3 = False
                texture_4 = False
                texture_5 = False
                texture_6 = True
                texture_7 = False
                texture_8 = False
                texture_9 = False

            textur_selector_button(7)
            if textur_selector_button(7) == True:
                texture_1 = False
                texture_2 = False
                texture_3 = False
                texture_4 = False
                texture_5 = False
                texture_6 = False
                texture_7 = True
                texture_8 = False
                texture_9 = False

            textur_selector_button(8)
            if textur_selector_button(8) == True:
                texture_1 = False
                texture_2 = False
                texture_3 = False
                texture_4 = False
                texture_5 = False
                texture_6 = False
                texture_7 = False
                texture_8 = True
                texture_9 = False

            textur_selector_button(9)
            if textur_selector_button(9) == True:
                texture_1 = False
                texture_2 = False
                texture_3 = False
                texture_4 = False
                texture_5 = False
                texture_6 = False
                texture_7 = False
                texture_8 = False
                texture_9 = True

            # if event.type == pygame.MOUSEMOTION and  event.buttons[0]:
            #     print("yeabboy")

            # add_to_list(list_pos_1,texture_1)
            # add_to_list(list_pos_2,texture_2)
            # add_to_list(list_pos_3,texture_3)
            # add_to_list(list_pos_4,texture_4)
            # add_to_list(list_pos_5,texture_5)
            # add_to_list(list_pos_6,texture_6)
            # add_to_list(list_pos_7,texture_7)
            # add_to_list(list_pos_8,texture_8)
            # add_to_list(list_pos_9,texture_9)

        if event.type == pygame.MOUSEMOTION and  event.buttons[2] or  event.type == pygame.MOUSEBUTTONDOWN and event.button == 3:
            drag_and_remove()

        if event.type == pygame.MOUSEMOTION and  event.buttons[0] or  event.type == pygame.MOUSEBUTTONDOWN and event.button == 1: #when click and drag
            drag_and_place(list_pos_1, texture_1)
            drag_and_place(list_pos_2, texture_2)
            drag_and_place(list_pos_3, texture_3)
            drag_and_place(list_pos_4, texture_4)
            drag_and_place(list_pos_5, texture_5)
            drag_and_place(list_pos_6, texture_6)
            drag_and_place(list_pos_7, texture_7)
            drag_and_place(list_pos_8, texture_8)
            drag_and_place(list_pos_9, texture_9)



        #WIN.blit(WIN, (0,0)) #pour avoir le fond en image
        bg_color = (bg_color_1, bg_color_2 ,bg_color_3)
        WIN.fill(bg_color) # pour avoir un fond uni

        gride_maker()

        texture_creator(list_pos_1, brick_n_1)
        texture_creator(list_pos_2, brick_n_2)
        texture_creator(list_pos_3, brick_n_3)
        texture_creator(list_pos_4, brick_n_4)
        texture_creator(list_pos_5, brick_n_5)
        texture_creator(list_pos_6, brick_n_6)
        texture_creator(list_pos_7, brick_n_7)
        texture_creator(list_pos_8, brick_n_8)
        texture_creator(list_pos_9, brick_n_9)


        texture_selector(brick_1, WIDTH + 40/2 ,40/2)
        texture_selector(brick_2, WIDTH + 40/2 , WIDTH//right_border )
        texture_selector(brick_3, WIDTH + 40/2 , WIDTH//right_border *2 - 40/2 )
        texture_selector(brick_4, WIDTH + 40/2 , WIDTH//right_border *3 - 40 )
        texture_selector(brick_5, WIDTH + 40/2 , WIDTH//right_border *3 + 40/2 )
        texture_selector(brick_6, WIDTH + 40/2 , WIDTH//right_border *4  )
        texture_selector(brick_7, WIDTH + 40/2 , WIDTH//right_border *5 - 40/2 )
        texture_selector(brick_8, WIDTH + 40/2 , WIDTH//right_border *6 - 40 )
        texture_selector(brick_9, WIDTH + 40/2 , WIDTH//right_border *6 + 40/2 )

        menu_option_button(1,gride_icon)
        menu_option_button(2,option_image_2)
        menu_option_button(3,option_finish_icon)
        menu_option_button(4,rgb_red_arrow)
        menu_option_button(5,rgb_green_arrow)
        menu_option_button(6,rgb_blue_arrow)

        keys = pygame.key.get_pressed()
        if keys[pygame.K_i]:

            def loading(x): #juste for fun...
                rgb_together = bg_color_1+bg_color_2+bg_color_3
                bg_rgb_color =  255-rgb_together/3
                loading_text = loading_font.render("Loading.. " + str(x), 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
                WIN.fill(bg_color)
                texture_creator(list_pos_1, brick_n_1)
                texture_creator(list_pos_2, brick_n_2)
                texture_creator(list_pos_3, brick_n_3)
                texture_creator(list_pos_4, brick_n_4)
                texture_creator(list_pos_5, brick_n_5)
                texture_creator(list_pos_6, brick_n_6)
                texture_creator(list_pos_7, brick_n_7)
                texture_creator(list_pos_8, brick_n_8)
                texture_creator(list_pos_9, brick_n_9)
                WIN.blit(loading_text,(WIDTH/2-loading_text.get_width()/2,HEIGHT/2-loading_text.get_height()/2))
                pygame.display.update()
                pygame.time.wait(random.randint(60, 250))


                print("   "+str(x)+"%")
            print("")
            print(" loading...")
            print("")
            loading(10)
            loading(20)
            loading(30)
            loading(40)
            loading(50)
            loading(60)
            loading(70)
            loading(80)
            loading(90)
            loading(100)
            print("")
            print(" importation completed ")

            grid_in_list(import_level_bis, list_pos_1,1)
            grid_in_list(import_level_bis, list_pos_2,2)
            grid_in_list(import_level_bis, list_pos_3,3)
            grid_in_list(import_level_bis, list_pos_4,4)
            grid_in_list(import_level_bis, list_pos_5,5)
            grid_in_list(import_level_bis, list_pos_6,6)
            grid_in_list(import_level_bis, list_pos_7,7)
            grid_in_list(import_level_bis, list_pos_8,8)
            grid_in_list(import_level_bis, list_pos_9,9)


        if keys[pygame.K_RETURN] :
            level_list = []
            for j in range(int(HEIGHT / blockSize)): #int(HEIGHT / blockSize)
                j = str(j)
                j = []
                j.clear()
                j = []
                for i in range(int(WIDTH / blockSize)): #int(WIDTH / blockSize)
                    j.append(0)
                level_list.append(j)

            image_to_level(list_pos_1,1)
            image_to_level(list_pos_2,2)
            image_to_level(list_pos_3,3)
            image_to_level(list_pos_4,4)
            image_to_level(list_pos_5,5)
            image_to_level(list_pos_6,6)
            image_to_level(list_pos_7,7)
            image_to_level(list_pos_8,8)
            image_to_level(list_pos_9,9)


            # make the text to the good form
            print("\nMy lord, your level is ready : \n")
            print("[")
            for b in range(len(level_list)):
                print(str(level_list[b])+",")
            print("]")


        if block_number_switcher == True:
            rgb_together = bg_color_1+bg_color_2+bg_color_3
            bg_rgb_color =  255-rgb_together/3
            #block counter text
            block_number = main_font.render(f" {int(len(list_pos_1)+len(list_pos_2)+len(list_pos_3)+len(list_pos_4)+len(list_pos_5)+len(list_pos_6)+len(list_pos_7)+len(list_pos_8)+len(list_pos_9))} bricks", 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
            WIN.blit(block_number,(10 *40,HEIGHT+40/2))
            #rgb text
            rgb_number = rgb_font.render("R "+str(bg_color_1), 1, (bg_color_1,0,0))
            pygame.draw.rect(WIN, (bg_rgb_color,bg_rgb_color,bg_rgb_color),((5*(40)),HEIGHT+40*1.5,rgb_number.get_width(),rgb_number.get_height()))
            WIN.blit(rgb_number,(5*(40),HEIGHT+40*1.5))
            rgb_number = rgb_font.render("G "+str(bg_color_2), 1, (0,bg_color_2,0))
            pygame.draw.rect(WIN, (bg_rgb_color,bg_rgb_color,bg_rgb_color),((6.5*(40)),HEIGHT+40*1.5,rgb_number.get_width(),rgb_number.get_height()))
            WIN.blit(rgb_number,(6.5*(40),HEIGHT+40*2-40/2))
            rgb_number = rgb_font.render("B "+str(bg_color_3), 1, (0,0,bg_color_3))
            pygame.draw.rect(WIN, (bg_rgb_color,bg_rgb_color,bg_rgb_color),((8*(40)),HEIGHT+40*1.5,rgb_number.get_width(),rgb_number.get_height()))
            WIN.blit(rgb_number,(8*(40),HEIGHT+40*2-40/2))
            #info text
            rgb_number = rgb_font.render("grid", 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
            WIN.blit(rgb_number,(0.5*(40),HEIGHT+40*1.5))
            rgb_number = rgb_font.render("info", 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
            WIN.blit(rgb_number,(2*(40),HEIGHT+40*1.5))
            rgb_number = rgb_font.render("export", 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
            WIN.blit(rgb_number,(3.5*(40),HEIGHT+40*1.5))
            #block counter text
            import_level_bis_text = main_font.render("Press i to draw the import bis", 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
            WIN.blit(import_level_bis_text,(12.5 *40,HEIGHT+40/2))
            import_level_bis_text_bis = import_font.render("Be carfull, it can't be undo", 1, (bg_rgb_color,bg_rgb_color,bg_rgb_color))
            WIN.blit(import_level_bis_text_bis,(12.5 *40,HEIGHT+40))

        #fps_label = main_font.render(f"FPS: {int(clock.get_fps())}", 1, (255,200,0))
        #text fps
        #WIN.blit(fps_label, (WIDTH+ blockSize/4,HEIGHT-blockSize))
        pygame.display.update()
