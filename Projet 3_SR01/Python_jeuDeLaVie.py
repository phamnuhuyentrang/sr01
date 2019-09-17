from time import sleep
from Tkinter import *
from random import *


def initPlateau(plateau, POP=15):
    for i in range(nbElemLin):
        for j in range(nbElemCol):
            if (randrange(0,100) % POP == 0):
                plateau[i][j] = 1
            else:
                plateau[i][j] = 0
    return plateau

def calcul_voisin(row, col, voisin):
    count = 0
    rows = len(voisin)
    cols = len(voisin)

    for rr in range(row-1, row+2):
        if rr < 0:
            r = rows-1
        elif rr > rows-1:
            r = 0
        else:
            r = rr
        for cc in range(col-1, col+2):
            if cc < 0:
                c = cols-1
            elif cc > cols-1:
                c = 0
            else:
                c = cc
            if not (r == row and c == col):  
                if voisin[r][c] == 1:
                    if not (rr != r or cc != c):
                        count += 1                    
    return count

def gener(plateau):
    rows = len(plateau)
    cols = len(plateau)
    for row in range(rows):
        for col in range(cols):
            cs = calcul_voisin(row, col, plateau)
            if plateau[row][col] == 1 and cs < 2:
                plateau[row][col] = 0
            elif plateau[row][col] == 1 and cs > 3:
                plateau[row][col] = 0
            elif plateau[row][col] == 0 and cs == 3:
                plateau[row][col] = 1
            else:
                plateau[row][col] = plateau[row][col]
    return plateau

def afficher(vie,can1):
    global hPlateau, lPlateau
    x=0
    y=0
    for i in range(len(vie)):
        for j in range(len(vie)):
            if (vie[i][j]):
                couleur = "red"
            else:
                couleur = defColor
            can1.itemconfig(cellules[i][j], fill=couleur, outline = "black")

def letsGo(value=None):
    global voisin,plateau,flag
    afficher(plateau,can1)
    gener(plateau)
    if flag > 0:
        fen.after(vitesse.get(),letsGo)

def triggerletsGo():
    global flag
    flag = 1
    fen.after(50,letsGo)

def stop():
    global flag
    flag = 0

def tailletab(value=None):
    nbElemLin = taille.get()
    nbElemCol= nbElemLin
    plateau = [[0] * nbElemCol for i in range(nbElemLin)]
    voisin = [[0] * nbElemCol for i in range(nbElemLin)]
    cellules = [[0] * nbElemCol for i in range(nbElemLin)]
    for i in range(nbElemLin):
         for j in range(nbElemCol):
            x = i*(lPlateau/nbElemCol)
            dx = (i+1)*(lPlateau/nbElemCol)
            y = j*(hPlateau/nbElemLin)
            dy =(j+1)*(hPlateau/nbElemLin)
            cellules[i][j] = can1.create_rectangle(x, y, dx, dy, width=1, fill=defColor,outline ="black")
    afficher(plateau,can1)

def vie(value=None):
    global plateau 
    for row in range(len(plateau)):
        for col in range(len(plateau)):
            if(randint(0, 100) > vie.get()):
                plateau[row][col] = 0
            else:
                plateau[row][col] = 1
    afficher(plateau,can1)

fen = Tk()
fen.title("Jeu de la vie")

hPlateau = 600
lPlateau = hPlateau
defColor = "white"
nbElemCol = 100
nbElemLin = nbElemCol

plateau = [[0] * nbElemCol for i in range(nbElemLin)]
voisin = [[0] * nbElemCol for i in range(nbElemLin)]

can1 = Canvas(fen,bg=defColor,height=hPlateau,width=lPlateau)

cellules = [[0] * nbElemCol for i in range(nbElemLin)]
for i in range(nbElemLin):
    for j in range(nbElemCol):
        x = i*(lPlateau/nbElemCol)
        dx = (i+1)*(lPlateau/nbElemCol)
        y = j*(hPlateau/nbElemLin)
        dy =(j+1)*(hPlateau/nbElemLin)
        cellules[i][j] = can1.create_rectangle(x, y, dx, dy, width=1, fill=defColor,outline ="black")

can1 = Canvas(fen,bg=defColor,height=hPlateau,width=lPlateau)
can1.pack(side=LEFT)

flag = 0

Button(fen,text = 'Initialisation',width= 12,command = lambda: afficher(initPlateau(plateau),can1)).pack(side=TOP)
Button(fen,text = 'Lancer',width = 12,command = triggerletsGo).pack(side=TOP)
Button(fen,text = 'Arreter',width = 12,command = stop).pack(side=TOP)
Button(fen,text = 'Quitter',width = 12,command = fen.destroy).pack(side=TOP)


vitesse=Scale(fen, from_=100,to=1000, orient=HORIZONTAL, resolution=10,label='Vitesse', command=letsGo)
vitesse.pack(side=BOTTOM)

vie=Scale(fen, from_=10, to=100, orient=HORIZONTAL, resolution=10, label='% de vie', command=vie)
vie.pack(side=BOTTOM)

taille=Scale(fen, from_=10, to=100, orient=HORIZONTAL, resolution=10, label='Taille de la grille', command=tailletab)
taille.pack(side=BOTTOM)

afficher(plateau,can1)

fen.mainloop()
