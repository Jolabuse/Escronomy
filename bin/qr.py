import numpy as numpy
import pyzbar.pyzbar as pyzbar
import cv2

mon_fichier = open("qr.txt", "w") 

camera = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_PLAIN #mets le truc que tu veux meme calibri stu pref
while True:
    _, frame = camera.read()

    decodedObjects = pyzbar.decode(frame)
    if(decodedObjects):
        for obj in decodedObjects:
            mon_fichier.write(str(obj.data))
        break
   
        
    #c galere a faire afficher l'image mais faut juste bien placer la carte quoi et pas qu'il y ai de reflet de soleil

    cv2.waitKey(1)
    
mon_fichier.close()
camera.release()
cv2.destroyAllWindows()
