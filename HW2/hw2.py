import cv2
import numpy as np
import time

imgA = cv2.imread('images/women.jpg')
imgB = cv2.imread('images/cheetah.jpg')
imgC = cv2.imread('images/woman.jpg')

clr = (0,250,0) #BGR
#facial features
featA = []
featB = []
featC = []


#draw algorithm------------------------------------------------------------------------------------
drawing = False
ix, iy = -1, -1
current_idx=''
start_end = []
def draw_line(event, x, y, flags, param):
    global ix, iy, drawing, current_image, current_idx, start_end
    sx, sy = 0, 0
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            if(len(start_end)==0):
                tmp = (ix,iy)
                start_end.append(tmp)
            cv2.line(current_image, (ix, iy), (x, y), (0, 255, 0), 2)
            ix, iy = x, y
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        tmp = (ix,iy)
        start_end.append(tmp)
        if current_idx=='A':
            featA.append(tuple(start_end))
        elif current_idx=='B':
            featB.append(tuple(start_end))
        elif current_idx=='C':
            featC.append(tuple(start_end))
        start_end = []
        cv2.line(current_image, (ix, iy), (x, y), (0, 255, 0), 2)


draw = input("Draw Feature Lines(T/F)?")
if draw == "T":
    cv2.namedWindow('Draw image')
    cv2.setMouseCallback('Draw image', draw_line)
    for i in range(3):
        while True:
            if i==0:
                cv2.imshow('Draw image', imgA)
                current_image = imgA
                current_idx = 'A'
            elif i==1:
                cv2.imshow('Draw image', imgB)
                current_image = imgB
                current_idx = 'B'
            else:
                cv2.imshow('Draw image', imgC)
                current_image = imgC
                current_idx = 'C'
            key = cv2.waitKey(1) & 0xFF

            if key == 27:  # Press 'Esc' to exit
                break
    cv2.destroyAllWindows()
if (len(featA)==0 or len(featB)==0 or len(featC)==0) or not (len(featA)==len(featB) and len(featB)==len(featC)):
    if draw=='T':
        print('Input error exist! Use default feature lines')
    featA = [((60, 45), (170, 45)), ((116, 70), (116, 100)), ((92, 132), (143, 132))]
    featB = [((31, 15), (225, 15)), ((130, 55), (130, 130)), ((90, 180), (163, 180))]
    featC = [((105, 80), (170, 80)), ((140, 92), (140, 108)), ((120, 127), (155, 127))]

print("featA:\n",featA)
print("featB:\n",featB)
print("featC:\n",featC)
#--------------------------------------------------------------------------------------------------

# implement warpping algorithm---------------------------------------------------------------------
imgA, imgB, imgC = cv2.imread('images/women.jpg'), cv2.imread('images/cheetah.jpg'), cv2.imread('images/woman.jpg')
warpA, warpB, warpC = np.zeros_like(imgA), np.zeros_like(imgB), np.zeros_like(imgC)
height, width = imgA.shape[:2]

def perp(vect):
    return np.array([-vect[1], vect[0]])
def shortest(x,p,q):
    a = perp(p-q)
    val = np.dot(p,a)
    t = (val-np.dot(a,x))/np.dot(a,a)
    return t*np.linalg.norm(a)

def color(source_image, x, y):
    if x>=height:
        x = height-1
    elif x<0:
        x=0
    if y>=width:
        y = width-1
    elif y<0:
        y=0
    return source_image[x, y]

def warp(feat1,feat2,alpha,srcImage,warpped):
    for x in range(height):
        for y in range(width):
            DSum=np.array([0.0,0.0])
            weightSum = 0.0
            constA, constB, constP = -0.0086, 3, 3
            for i in range(len(feat1)):
                Ps, Qs = np.array(feat1[i][0]),np.array(feat1[i][1])
                Pd, Qd = np.array(feat2[i][0]),np.array(feat2[i][1])
                Xd = np.array([x,y])
                u = np.dot((Xd-Pd),(Qd-Pd))/np.dot((Qd-Pd),(Qd-Pd))
                v = np.dot((Xd-Pd),perp(Qd-Pd))/np.dot((Qd-Pd),(Qd-Pd))
                Xs = Ps + u*(Qs-Ps)+v*perp(Qs-Ps)
                Di = np.array(Xs-Xd)
                #dist = shortest(Xd,Pd,Qd)
                dist = v
                weight = (np.linalg.norm(Pd-Qd)**constP/(constA+dist))**constB
                DSum += Di*weight
                weightSum += weight
            Xs = np.array([x,y]) + DSum/weightSum*alpha
            warpped[x ,y] = color(srcImage, int(np.round(Xs[0])), int(np.round(Xs[1])))
    return warpped

#--------------------------------------------------------------------------------------------------

#animation record
AniA = []
AniBA = []
AniBC = []
AniC = []


def showDefault():
    alp=float(input("Alpha Value? "))
    warpAB = np.zeros_like(imgA)
    warpBA = np.zeros_like(imgB)
    warpAB = warp(featA,featB,alp,imgA,warpAB)
    warpBA = warp(featB,featA,(1-alp),imgB,warpBA)
    cv2.imshow("warpped 1",warpAB)
    cv2.imshow("warpped 2",warpBA)
    result = cv2.addWeighted(warpAB,alp,warpBA,(1-alp),1)
    cv2.imshow("Final Result", result)
    cv2.waitKey(0)

def warpAniAB():
    a=0
    while a<=1:
        w1 = np.zeros_like(imgA)
        w2 = np.zeros_like(imgB)
        warp(featA,featB,a,imgA,w1)
        warp(featB,featA,a,imgB,w2)
        AniA.append(w1)
        AniBA.append(w2)
        cv2.waitKey(1)
        a += 0.1

def warpAniBC():
    a=0
    while a<=1:
        w1 = np.zeros_like(imgB)
        w2 = np.zeros_like(imgC)
        warp(featB,featC,a,imgB,w1)
        warp(featC,featB,a,imgC,w2)
        AniBC.append(w1)
        AniC.append(w2)
        cv2.waitKey(1)
        a += 0.1

def playAni(ani1,ani2):
    for i in range(len(ani1)):
        cv2.imshow("Warp Animation",cv2.addWeighted(ani1[i],(1-i*0.1),ani2[10-i],i*0.1,0))
        cv2.waitKey(1)
        time.sleep(0.1)

#"""
if __name__=="__main__":
    act = ["0. Exit","1. Default output","2. Draw A->B animation","3. Draw A->B->C animation","4. Play A->B animation","5. Play A->B->C animation","6. Three images morphing"]
    for x in act:
        print(x)
    action=int(input("Choose? "))
    while action!=0:
        if action==1:
            showDefault()
        elif action==2:
            warpAniAB()
        elif action==3:
            if len(AniA)==0:
                warpAniAB()
            warpAniBC()
        elif action==4:
            playAni(AniA,AniBA)
            cv2.destroyAllWindows()
        elif action==5:
            playAni(AniA,AniBA)
            playAni(AniBC,AniC)
            cv2.destroyAllWindows()
        elif action==6:
            morA,morC = np.zeros_like(imgA),np.zeros_like(imgA)
            morA = warp(featA,featB,1,imgA,morA)
            morC = warp(featC,featB,1,imgC,morC)
            result = cv2.addWeighted(morA,0.5,imgB,0.5,0)
            result = cv2.addWeighted(result,0.667,morC,0.333,0)
            cv2.imshow('A',morA)
            cv2.imshow('B',imgB)
            cv2.imshow('C',morC)
            cv2.imshow("Morphing",result)
            cv2.waitKey(0)
        else:
            continue
        for x in act:
            print(x)
        action=int(input("Choose? "))

#"""
