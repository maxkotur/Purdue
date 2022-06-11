import numpy as np
import traceback
import random
def loadData(fileX,filey):
    X , y = [],[]
    with open(fileX, "r") as fin:
        content = fin.readline()
        while content:
            content = content.rstrip().split()
            content = [float(f) for f in content]
            X.append(content)
            content = fin.readline()
    with open(filey, "r") as fin:
        content = fin.readline()
        while content:
            content = content.rstrip().split()
            content = [float(f) for f in content]
            y.append(content)
            content = fin.readline()
    X,y=np.array(X),np.array(y)
    return np.array(X),np.array(y)

# kfoldcv
def test_1(dataX,datay):
    from kfoldcv import run as kfrun
    from sol_kfoldcv import run as sol_kfrun
    totalX = len(dataX)
    kvalues = [5, 10, 20]
    totalMatch = 0
    totalTest = 0
    vector_format = 1
    score = 0.0

    for k in kvalues:
        for t in range(0, totalX):
            try:
                X, y = dataX[t], datay[t]
                (n, dim) = np.shape(X)
                z1 = kfrun(k, X, y)
                z2 = sol_kfrun(k, X, y)
                if isinstance(z1, list):
                    z1 = np.asarray(z1)
                    vector_format = 2
                elif isinstance(z1, set):
                    z1 = np.asarray(list(z1))
                    vector_format = 3

                if (np.shape(z1) == (k, 1)):
                    pass
                else:
                    z1 = z1.reshape(k, 1)
                    vector_format = 4
                # Measuere correlation with z from solution
                # print np.shape(z1),np.shape(z2)
                cf = np.corrcoef(z1.T, z2.T)
                cf = cf[0, 1]
                if (cf >= 0.9):
                    score += 1.0
                elif (not (cf < 0)):
                    score += (cf / 0.9)
            except:
                return 0, 0
    return 3.0 * score / (totalX * len(kvalues)), vector_format


# bootstrapping
def test_2(dataX,datay):
    from bootstrapping import run as bsrun
    from sol_bootstrapping import run as sol_bsrun
    totalX=len(dataX)
    Bvalues = [5,10,20]
    totalMatch = 0
    totalTest = 0
    vector_format = 1
    score = 0.0
    for B in Bvalues:
        for t in range(0,totalX):
            try:
                X,y=dataX[t],datay[t]
                (n,dim) = np.shape(X)
                np.random.seed(28)
                random.seed(28)
                z1 = bsrun(B,X,y)
                np.random.seed(28)
                random.seed(28)
                z2 = sol_bsrun(B,X,y)
                if isinstance(z1, list):
                    z1 = np.asarray(z1)
                    vector_format = 2
                elif isinstance(z1,set):
                    z1 = np.asarray(list(z1))
                    vector_format = 3

                if(np.shape(z1)==(B,1)):
                    pass
                else:
                    z1=z1.reshape(B,1)
                    vector_format = 4
                # Measuere correlation with z from solution
                cf = np.corrcoef(z1.T,z2.T)
                cf=cf[0,1]
                if(cf>=0.9):
                    score+=1
                elif(not (cf<0)):
                    score+=(cf/0.9)
            except:
                return 0,0
    return 4.0*score/(totalX*len(Bvalues)),vector_format

def test_3(dataX, datay):
    from hypotest import run as hprun
    from sol_hypotest import run as sol_hprun
    from sol_kfoldcv import run as sol_kfrun
    from sol_bootstrapping import run as sol_bsrun
    totalX=len(dataX)
    Avalues = [0.05,0.1,0.45]
    totalMatch = 0
    totalTest = 0
    vector_format = 1
    score = 0.0
    for alpha in Avalues:
        for t in range(0,totalX):
            try:
                X,y=dataX[t],datay[t]
                (n,dim) = np.shape(X)
                np.random.seed(28)
                random.seed(28)
                a = sol_kfrun(5,X,y)
                b = sol_bsrun(5,X,y)
                z1 = hprun(a,b,alpha)
                np.random.seed(28)
                random.seed(28)
                z2 = sol_hprun(a,b,alpha)
                if isinstance(z1, list):
                    z1 = np.asarray(z1)
                    vector_format = 2
                elif isinstance(z1,set):
                    z1 = np.asarray(list(z1))
                    vector_format = 3

                if(isinstance(z1,int)):
                    pass
                else:
                    try:
                        z1 = int(z1)
                    except:
                        return 0
                # Measuere correlation with z from solution
                if z1==z2:
                    score += 1
            except:
                return 0,0
    return 3.0*score/(totalX*len(Avalues)),1


def gradeHW(stdID=""):
    print("Grading "+stdID)
    fileNamesX=["Xs_100_10.txt","Xs_1000_15.txt","Xs_2000_15.txt","Xns_1000_15.txt"]
    fileNamesy=["ys_100_10.txt","ys_1000_15.txt","ys_2000_15.txt","yns_1000_15.txt"]
    dataX,datay=[],[]
    totalX=len(fileNamesX)
    for i in range(0,totalX):
        X,y=loadData(fileNamesX[i],fileNamesy[i])
        dataX.append(X)
        datay.append(y) 
    prob1,prob1_dim=0,0
    prob2,prob2_dim=0,0
    prob3,prob3_dim=0,0
    gf = open(gradeFile, "a")
    log = open('log.txt', "a")
    log.write("------------------------"+"\n")
    log.write("Grading "+stdID+"\n")
    try:
        prob1,prob1_dim=test_1(dataX,datay)
        # pass
    except Exception as e:
        log.write("Problem1")
        traceback.print_exc()
        log.write(traceback.format_exc())
        pass
    try:
        prob2,prob2_dim=test_2(dataX,datay)
        # pass
    except Exception as e:
        log.write("Problem2")
        traceback.print_exc()
        log.write(traceback.format_exc())
        pass
    try:
        prob3,prob3_dim=test_3(dataX,datay)
        pass
    except Exception as e:
        log.write("Problem3")
        traceback.print_exc()
        log.write(traceback.format_exc())
        pass
    print(prob1,prob1_dim),(prob2,prob2_dim),(prob3,prob3_dim)
    score=(prob1+prob2+prob3)
    deducted = 0.25
    if((prob1_dim==0 or prob1_dim==1) and (prob2_dim==0 or prob2_dim==1) and (prob3_dim==0 or prob3_dim==1)):
        deducted=0.0
        # print("deducted %f"%deducted)
    score-=deducted
    score=str.format("%.1f"%score)
    print("Problem 1: %f\nProblem 1 vector dimension: %d"%(prob1,prob1_dim))
    print("Problem 2: %f\nProblem 2 vector dimension: %d"%(prob2,prob2_dim))
    print("Problem 3: %f\nProblem 3 vector dimension: %d"%(prob3,prob3_dim))
    print("Deduction for wrong vector dimension: %.2f\nFinal score (rounded): %s"%(deducted,score))
    gf.write("%s,%s,%s,%s,%s,%s,%s,%s,%s\n"%(str(stdID),str(prob1),str(prob1_dim),str(prob2),str(prob2_dim),str(prob3),str(prob3_dim),deducted,score))

if __name__ == "__main__":
    np.random.seed(26)
    random.seed(26)
    import sys
    import os
    gradeFile = "hw4_grades.csv"
    exists = os.path.isfile(gradeFile)
    if not os.path.isfile(gradeFile):
      with open(gradeFile,"a") as gf:
        gf.write("id,problem1,problem1_dim,problem2,problem2_dim,problem3,problem3_dim,deducted,score\n")
    print(sys.argv)
    if(len(sys.argv)==2):
        gradeHW(sys.argv[1])
    elif(len(sys.argv)==1):
        gradeHW()

