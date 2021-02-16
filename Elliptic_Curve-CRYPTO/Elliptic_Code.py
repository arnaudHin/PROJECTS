import numpy as np
import matplotlib.pyplot as plt
from tkinter import *
clé=[]
clé1=[]
"""
class Calculpoint(object):
   def __init__(self, a, b,ymi,yma,xmi,xma):
      
# vérification que la coubre est continue:
      self.a = a
      self.b = b
      self.ymi=ymi
      self.yma=yma
      self.xmi=xmi
      self.xma=xma
"""

def relpoint(a,b,ymi,yma,xmi,xma):
   
   i=0
   j=0
   for i in range (1,xma-xmi):
       for j in range (1,yma-ymi):
           d=i-1+xmi
           p=j-1+ymi
           if p**2-d**3-a*d-b==0:
             clé.append(d)
             clé.append(p)
 
   for k in range (0,len(clé)-1,2):
      clé1.append([clé[k],clé[k+1]])
      
   return print(clé,clé1)

   
class EllipticCurve(object):
   def __init__(self, a, b):
      
      self.a = a
      self.b = b

# définition du discriminant et affichage d'un message d'erreur si non continu   
      self.discriminant = -16 * (4 * (a**3) + 27 * (b**2))
      if not self.continu():
         print("La courbe n'est pas continue!" % self)
         #raise Exception("La courbe n'est pas continue!" % self)

#fonction qui vérifie que la courbe est continue Δ ≠ 0
   def continu(self):
      return self.discriminant != 0

#fonction vérifiant que le point appartient a la courbe
   def testPoint(self, x, y):
      return (y**2) == (x**3) + self.a * x + self.b


 # Afficher (avec print) notre objet dans l'interpréteur (le %G premet d'afficher
 # a et b dans l'équation):

   def __str__(self):
      return 'y^2 = x^3 + %Gx + %G' % (self.a, self.b)

'------------------------------------------------------------------------------------------'

class Point(object):
    
   def __init__(self, curve, x, y): #Le point est définie en fonction de x,y et de la courbe
        self.curve = curve # la courbe contient le point (x,y)
        self.x = x
        self.y = y
        
# message d'erreur si le point n'appartient pas à la courbe 
        if not curve.testPoint(x,y):
           print("Le point %s n'est pas sur la courbe %s" % (self, curve))
         #raise Exception("Le point %s n'est pas sur la courbe %s" % (self, curve))

# fonction qui retourne le point symétrique par rapport aux abscisses
   def __neg__(self):
      return Point(self.curve, self.x, -self.y)
   
# fonction qui ajoute le point Q et retourne self si Q correspond au point à l'infini
   def __add__(self, Q):
      #if type(Q) is types.InfiniType:   
      if isinstance(Q, Infini):
         return self
      
# on rentre les coordonnées de P (x_1, y_1) et Q(x_2, y_2) dans des variables
      x_1, y_1, x_2, y_2 = self.x, self.y, Q.x, Q.y
 
      if (x_1, y_1) == (x_2, y_2): # cas 3 
         if y_1 == 0: # cas 4
            print("Point à l'infini")
            return Infini(self.curve) # point à l'infini
 
         # équation de la tangente:
         s = (3 * (x_1**2) + self.curve.a) / (2 * y_1) #cas 3
      else:
         if x_1 == x_2: # cas 2
            print("Point à l'infini")
            return Infini(self.curve) # ligne verticale
 
         # équation de la tangente dans le cas génréral (cas 1)
         
         s = (y_2 - y_1) / (x_2 - x_1) #S
         
      x_3 = (s**2) - x_2 - x_1
      y_3 = s*(x_3 - x_1) + y_1 # coordonnées du troisèeme point R(x_3, yx3)
      R = (x_3,y_3) # coordonnées de R
      R1 = (x_3,-y_3)#coordonnées de R'
      print("R =",R)
      print("R' =",R1) # affiche les coordonnées de R'
      return Point(self.curve, x_3, -y_3) # retourne R', opposé de R



# fonction qui retourne l'opposé (permettre d'utiliser la soustraction)
   def __sub__(self, Q):
      return self + -Q

'-------------------------------------------------------------------------------------------'

# Représentation du point à l'infini (0,1,0) avec une sousclasse: 
class Infini(Point):
   def __init__(self, curve):
      self.curve = curve
      
#définition de caractéristiques propres au poitn à l'infini:
   
# on affiche Infini lorsqu'on appelle la classe dans l'interpréteur
   def __str__(self):
      return "Point à l'infini"

# l'opposé du point à l'infini est lui-même
   def __neg__(self):
      return self
   
# on ajoute le point Q
   def __add__(self, Q):
      return Q

# Même chose avec le point à l'infini
   def __mul__(self, n):
        if not isinstance(n, int):
            print("Un point ne peut être multiplié que par un entier")
            #raise Exception("Can't scale a point by something which isn't an int!")
        else:
            return

# retourne l'opposé de Q (permet la soustraction)
   def __sub__(self, Q):
      return self + -Q

'------------------------------------------------------------------------------------------'
#On obtient finalement des nombres à virgules ce qui pose probleme
#Pour résoudre cela on va utiliser les 'shield' ou plus précisément l'inverse modulaire

#Fonction définissant l'inverse modulaire (a(a-1) = 1 mod(m)
class Inverse (object):
   def _init_ (self, a, m):
      self.a = a
      self.m = m
      
   def mod_inverse(a, m):
   # Retourne l'inverse de a premier modulo m
   
    if m == 0:
    #if abs(m) == 0: #test Z/mZ
        return (1, 0, a)

    while abs(m) > 0: #sinon
        q, r = divmod(a, m) #donne le quotient et le reste de la division euclidienne de a par m (revient  (a//m,a%m)
        x = x2 - q * x1
        y = y2 - q * y1
        a, m, x_2, x_1, y_2, y_1 = m, r, x_1, x, y_1, y
      
    return x2 % m
    print(x2 % m)

 """
def affichecp(clé):
   z=StringVar(fen)
   z.set(clé[0])
   menu1=OptionMenu(fen,z,*clé)
   menu.grip(column=1,row=14,sticky='w')
"""


def saisie():
      global a,b
      a = eval(fonction1.get())
      b = eval(fonction2.get())
      xmi=eval(xmin.get())
      xma=eval(xmax.get())
      ymi=eval(ymin.get())
      yma=eval(ymax.get())
      P=str(t.get())
      i=P.replace(" ","")
      i=i.replace("[","")
      i=i.replace("]","")
      i=i.replace("(","")
      i=i.replace(")","")
      y=i.split(",")
      
      Q=str(u.get())
      vi=Q.replace(" ","")
      vi=vi.replace("[","")
      vi=vi.replace("]","")
      vi=vi.replace("(","")
      vi=vi.replace(")","")
      vi=vi.split(",")
      print(a,b,xmi,xma,ymi,yma,y[0],y[1],vi[0],vi[1])
      
      
      x = np.linspace(0.2,10,100)
      fig, ax = plt.subplots()
      # set the x-spine (see below for more info on set_position)
      ax.spines['left'].set_position('zero')
      # turn off the right spine/ticks
      ax.spines['right'].set_color('none')
      ax.yaxis.tick_left()
      # set the y-spine
      ax.spines['bottom'].set_position('zero')
      # turn off the top spine/ticks
      ax.spines['top'].set_color('none')
      ax.xaxis.tick_bottom()
      y, x = np.ogrid[xmi:xma:100j, ymi:yma:100j]
      plt.contour(x.ravel(), y.ravel(), pow(y, 2) - pow(x, 3) - x * a - b, [0])
      plt.contour(x.ravel(), y.ravel(), pow(y, 1) - pow(x, 3) - x * a - b, [0])
      plt.grid()
      plt.show()
          
"""      

if _name_ == '_main_':
    main()

esp=[x,y]
print(esp)
"""
def trace0():
   
   a = eval(fonction1.get())
   b = eval(fonction2.get())
   xmi=eval(xmin.get())
   xma=eval(xmax.get())
   ymi=eval(ymin.get())
   yma=eval(ymax.get())
   print(EllipticCurve(a,b))
   relpoint(a,b,ymi,yma,xmi,xma)
   
   menu1=OptionMenu(fen, t,*clé1)
   menu1.grid(column=1,row=12,sticky='w')
   
   menu2=OptionMenu(fen, u,*clé1)
   menu2.grid(column=3,row=12,sticky='w')

   
   
def trace():
    saisie()

# fenêtre principale    
fen = Tk()

fen.title('Traceur de courbes')
fen.grid_columnconfigure(0,weight=1) # les 4 lignes ci-contre permettent, lors d'un redimensionnement de la fenêtre,
fen.grid_columnconfigure(1,weight=1) # que les colonnes de la grille se redimensionnent elles-aussi automatiquement.
fen.grid_columnconfigure(2,weight=1) # Les widgets sont donc toujours placés de la même façon, quelque soit la taille de la fenêtre...
fen.grid_columnconfigure(3,weight=1) # Un "poids" ( weight ) de 1 indique que toutes les colonnes se redimensionnent dans la même proportion

# étiquette + menu déroulant choix prédéfinis de fonctions
lb1 = Label(fen,text='Choix prédéfinis :')
lb1.grid(column=0,row=0,sticky='e') # l'option "sticky" permet d'aligner le widget dans la colonne, ici à droite ( 'e' = east )

listeOptions = ['y^2=x^3+ax+b',''] # liste contenant les choix proposés
v = StringVar(fen) # variable de contrôle attachée au menu
v.set(listeOptions[0])# élément sélectionnée par défaut  ( ici, celui d'index 0, donc le premier de la liste )
w=StringVar(fen)
w.set(listeOptions[1])
y=StringVar(fen)
y.set(listeOptions[1])
t=StringVar(fen)
t.set("")
u=StringVar(fen)
u.set("")
menu = OptionMenu(fen, v, *listeOptions) # syntaxe à respecter, l'astérisque est nécessaire...
menu.grid(column=1,row=0,sticky='w') # alignement à gauche ( 'w' = west )

# étiquette + champ entrée expression perso. de fonction
lb2 = Label(fen,text='Fonction personnalisée :')
lb2.grid(column=0,row=2,sticky='e')

fonction = Entry( fen , textvariable = v ) # même variable de contrôle que la liste de choix pour "répercuter" les changements de l'un vers l'autre
fonction.grid(column=1,row=2,sticky='w')

# choix couleur de ligne


# motif de ligne
lb4 = Label( fen , text ='Choix des paramètres a et b :')
lb4.grid(column = 0, row = 5, columnspan = 4)
fonction1 = Entry( fen )
fonction1.grid(column=1,row=6, columnspan=4, sticky='w')
fonction2 = Entry( fen , textvariable = y ) # même variable de contrôle que la liste de choix pour "répercuter" les changements de l'un vers l'autre
fonction2.grid(column=3,row=6, sticky='w')
lb6 = Label( fen , text ='a :')
lb6.grid(column = 0, row = 6, columnspan = 4, sticky='w')
lb7 = Label( fen , text ='b :')
lb7.grid(column = 2, row = 6, columnspan = 4, sticky='w')
lb8 = Label( fen , text ='xmin :')
lb8.grid(column = 0, row = 11, columnspan = 4, sticky='w')
lb9 = Label( fen , text ='xmax :')
lb9.grid(column = 1, row = 11, columnspan = 4, sticky='w')
lb10 = Label( fen , text ='ymin :')
lb10.grid(column = 2, row = 11, columnspan = 4, sticky='w')
lb11 = Label( fen , text ='ymax :')
lb11.grid(column = 3, row = 11, columnspan =4, sticky='w')
lb12 = Label( fen , text ='Clé P :')
lb12.grid(column = 0, row = 12, columnspan =4, sticky='w')
lb13 = Label( fen , text ='Clé Q :')
lb13.grid(column = 2, row = 12, columnspan =4, sticky='w')
z=StringVar(fen)

valider1 = Button(fen, text='Calculer', command=trace0)
valider1.grid(column=0,row=15,columnspan=4)
valider = Button(fen, text='valider', command=trace)
valider.grid(column=0,row=16,columnspan=4)





xmin = Spinbox( fen , width = 5 , from_=-20, to = 20 , increment = 1 , wrap = True )
xmin.grid(column = 0 , row = 11)
xmax = Spinbox( fen , width = 5 , from_=-20 , to = 20 , increment = 1 , wrap = True)
xmax.grid(column = 1 , row = 11 )
ymin = Spinbox( fen , width = 5 , from_=-20 , to = 20 , increment = 1 , wrap = True)
ymin.grid(column = 2 , row = 11)
ymax = Spinbox( fen , width = 5 , from_=-20 , to = 20 , increment = 1 , wrap = True)
ymax.grid(column = 3 , row = 11)

fen.mainloop()