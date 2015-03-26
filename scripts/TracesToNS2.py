#!/usr/bin/python

import sys, getopt
from math import sqrt, pow

# CONSTANTS
T_FACTOR = 0.03048   # Transform factor (feet to meters)
# END CONSTANTS

# GLOBAL VARIABLES
dictNodeRename = {}
# END GLOBAL VARIABLES

class Params(object):
    ifile = ""
    ofile = ""

class Coords(object):
    xCoord = 0.0
    yCoord = 0.0

class Node(object):

    def __init__(self, id=0, prevCoord=0, currCoord=0, currTime=0, prevTime=0, velocity=0):
        self.id = id
        self.prevCoord = Coords()
        self.prevCoord.xCoord = prevCoord.xCoord
        self.prevCoord.yCoord = prevCoord.yCoord
        self.currCoord = Coords()
        self.currCoord.xCoord = currCoord.xCoord
        self.currCoord.yCoord = currCoord.yCoord
        self.currTime = currTime
        self.prevTime = prevTime
        self.velocity = velocity

    def __str__(self):
        return "id: %s, prevCoord(x: %s, y: %s), currCord(x: %s, y: %s), prevTime: %s, currTime: %s, velocity: %s" % (self.id, self.prevCoord.xCoord, self.prevCoord.yCoord, self.currCoord.xCoord, self.currCoord.yCoord, self.prevTime, self.currTime, self.velocity)

def parseInput(argv):
    params = Params()
    exit = False
    try:
        opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
    except getopt.GetoptError:
        exit = True
    for opt, arg in opts:
        if opt == '-h':
            exit = True
            break
        elif opt in ("-i", "--ifile"):
            params.ifile = arg
        elif opt in ("-o", "--ofile"):
            params.ofile = arg
    if (params is None or params.ifile == "" or params.ofile == ""):
        exit = True

    if exit:
        print 'test.py -i <inputfile> -o <outputfile>'
        sys.exit(2)
    return params

def parseTime2Seconds(time):
    timeH = int(time[1])
    timeM = int(time[2])
    timeS = int(time[3])
    seconds = (timeH * 3600 + timeM * 60 + timeS)
    return seconds

def computeVelocity(node):
    velo = 0
    nodeDiff = (node.currTime - node.prevTime)
    if nodeDiff != 0:
        velo = sqrt(pow(node.currCoord.xCoord - node.prevCoord.xCoord, 2) + pow(node.currCoord.yCoord - node.prevCoord.yCoord, 2)) / nodeDiff
    return velo

def initNode(nodeId, secs, coords):
    if dictNodeRename.get(nodeId) is None:
        # Node not initialized yet
        newNode = Node(len(dictNodeRename), coords, coords, secs, secs)
        dictNodeRename[nodeId] = newNode
        return True
    else:
        node = dictNodeRename[nodeId]
        node.prevTime = node.currTime
        node.prevCoord.xCoord = node.currCoord.xCoord
        node.prevCoord.yCoord = node.currCoord.yCoord
        node.currTime = secs
        node.currCoord.xCoord = coords.xCoord
        node.currCoord.yCoord = coords.yCoord
        node.velocity = computeVelocity(node)
        return False

def initializationEntry(node):
    # $node_(0) set X_
    ini =  "$node_(" + str(node.id) + ") set X_ "+ str(node.currCoord.xCoord) + "\n"
    ini += "$node_(" + str(node.id) + ") set Y_ "+ str(node.currCoord.yCoord) + "\n"
    return ini

def movementsEntry(node):
    return "$ns_ at " + str(node.currTime) + " $node_(" + str(node.id) + ") setdest " + str(node.currCoord.xCoord) + " " + str(node.currCoord.yCoord) + " " + str(node.velocity) + "\n"

def export2File(ofile, initialization, movements):
    f = open(ofile, 'w')
    f.write(initialization)
    f.write(movements)
    f.close()

def main():
    first = True
    iniSeconds = 0
    coords = Coords()
    secs = 0
    nodeId = 0
    initialization = ""
    movements = ""

    params = parseInput(sys.argv[1:])
    with open(params.ifile) as ifile:
        for line in ifile:
            splLine = line.split()
            if (first):
                iniSeconds = parseTime2Seconds(splLine[0].split(":"))
                secs = iniSeconds
                first = False
            else:
                secs = parseTime2Seconds(splLine[0].split(":")) - iniSeconds
            nodeId = splLine[1]
            coords.xCoord = float(splLine[4]) * T_FACTOR
            coords.yCoord = float(splLine[5]) * T_FACTOR
            newNode = initNode(nodeId, secs, coords)
            
            if newNode:
                # Save new initializations of a new nodes
                initialization += initializationEntry(dictNodeRename[nodeId])
            else:
                # Save new movements of the nodes
                movements += movementsEntry(dictNodeRename[nodeId])
    export2File(params.ofile, initialization, movements)

if __name__ == "__main__":
    main()