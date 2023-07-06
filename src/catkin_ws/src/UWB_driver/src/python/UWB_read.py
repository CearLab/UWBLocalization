#!/usr/bin/env python
# license removed for brevity

# ros imports
import rospy
import roslib
import logging
from gtec_msgs.msg import Ranging
from visualization_msgs.msg import MarkerArray
from visualization_msgs.msg import Marker

# general imports
import serial
import time
import sys
import time
import numpy as np
import binascii

# write buffer size
BUFSIZE = 4

# anchors ID dictionary
ID = ['C693','8A1E','1D16','91AE']

# send commands and read output
def serialWrite(srl, data, sleepTime):
    
    # refresh serial
    srl.flushInput()
    srl.flushOutput()

    # start timer
    t0 = time.time()

    # splid data to be sent in chunks
    chunks = [data[i:i+BUFSIZE] for i in range(0, len(data), BUFSIZE)]

    # cycle over the chunks
    for ck in chunks:

        # write single chunk
        srl.write(ck)
        logger.info('Send: ' + ck)

        # check if the chunk is sent correctly
        # NB: it seems that to send the next chunk, you need to read the previous one 
        # is there a reason?
        dt = time.time() - t0
        while dt < sleepTime:
            dt = time.time() - t0
            if (srl.in_waiting > 0):
                data = srl.readline().decode().strip()

    # refresh serial
    srl.close()
    srl.open()

# read the dstances (lec already called)
def serialRead(srl, stopTime, D, A):

    # start timer
    t0 = time.time()

    # read for for the duration of sleepTime
    dt = time.time() - t0
    empty = True
    while (dt < stopTime) or (empty == True):
        
        dt = time.time() - t0
        if (srl.in_waiting > 0):

            # get data and split in chunks separated by a comma (lec mode)
            data = srl.readline().decode().strip()
            if len(data) > 0:
                empty = False
                items = data.split(',')
            
                # assign anchors and distances
                for i in range(4):

                    # get the ID
                    id = ID[i]
                    #logger.info('HERE: ' + str(i))

                    try:
                        # find if anchor was read
                        pos = items.index(id)

                        # set anchors
                        A[0][i] = float(items[pos+1])
                        A[1][i] = float(items[pos+2])
                        A[2][i] = float(items[pos+3])

                        # set D
                        D[0][i] = float(items[pos+4])

                    except:
                        # if not
                        logger.info('Missing measure from: ' + id)

    return A,D

def talker():

    # logger
    global logger
    logger = logging.getLogger('rosout')
    console_handler = logging.StreamHandler()
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    console_handler.setFormatter(formatter)
    logger.addHandler(console_handler)

    # general stuff init
    cnt = 0
    rate = 5 #(Hz)
    sleepLong = 2 #(s)
    stopTime = 0.8/float(rate) #(s) slightly less than freq for overhead

    # input vals
    argc = len(sys.argv)

    # gparse args
    if argc < 1:
        logger.fatal('Insufficient number of parameters for UWB setup')
    else:
        # name
        nodeName = sys.argv[1]
        # id
        tagID = sys.argv[2]


    # Check and get params
    try:
        # Serial Port
        p = nodeName + '/UWB_read_SerialPort'
        SerialPort = rospy.get_param(p)

        # BaudRate
        p = nodeName + '/UWB_read_BaudRate'
        BaudRate = rospy.get_param(p)

        # topicNameA
        p = nodeName + '/UWB_read_pubA'
        topicNameA = rospy.get_param(p)

        # topicNameD
        p = nodeName + '/UWB_read_pubD'
        topicNameD = rospy.get_param(p)

        # Nanchors
        p = nodeName + '/UWB_read_Nanchors'
        Nanchors = rospy.get_param(p)

    except:
        logger.fatal('Params missing')
        return -1

    # set arrays
    A = np.zeros((3,int(Nanchors)))
    D = np.zeros((1,int(Nanchors)))

    # ros::init() the node 
    pubD = rospy.Publisher(topicNameD, Ranging, queue_size=10)
    pubA = rospy.Publisher(topicNameA, MarkerArray, queue_size=10)
    rospy.init_node('UWB_read') 
    r = rospy.Rate(rate)   

    # start serial
    myserial = serial.Serial(SerialPort, BaudRate, timeout=0.5, 
    parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,  bytesize=serial.EIGHTBITS)
    # refresh serial
    myserial.flushInput()
    myserial.flushOutput()
    
    # Check if the serial port is open
    if not myserial.is_open:
        logger.fatal('Failed to open serial port!')
        return -1
    else:
        logger.info('Connected to: ' + SerialPort)

    # start the configuration - go to cli mode
    data = '\x0D\x0D'
    serialWrite(myserial, data, sleepLong)

    # start reading - send lec
    data = 'lec\x0D'
    serialWrite(myserial, data, sleepLong)

    # message definition
    msgD = Ranging()
    msgA = MarkerArray()

    tmpMarker = Marker()
    for i in range(int(Nanchors)):
        msgA.markers.append(tmpMarker)

    cnt = 0

    # loop
    while not rospy.is_shutdown():
        try:
            # get measurement
            A, D = serialRead(myserial, stopTime, D, A)

            cnt = cnt +1

            # fill anchors and publish
            for i in range(int(Nanchors)):

                tmpMarker = Marker()
                tmpMarker.header.seq = cnt
                tmpMarker.header.stamp = rospy.get_rostime()   
                tmpMarker.header.frame_id = "world"         
                tmpMarker.id = i

                tmpMarker.pose.position.x = float(A[0][i])
                tmpMarker.pose.position.y = float(A[1][i])
                tmpMarker.pose.position.z = float(A[2][i])

                tmpMarker.pose.orientation.w = 1
                tmpMarker.pose.orientation.x = 0
                tmpMarker.pose.orientation.y = 0
                tmpMarker.pose.orientation.z = 0

                tmpMarker.scale.x = 0.05
                tmpMarker.scale.y = 0.05
                tmpMarker.scale.z = 0.05

                tmpMarker.color.r = 200
                tmpMarker.color.g = 0
                tmpMarker.color.b = 0
                tmpMarker.color.a = 1

                msgA.markers.pop(0)
                msgA.markers.append(tmpMarker)

            #logger.info(msgA)
            pubA.publish(msgA)
                  
            # fill distances
            for i in range(int(Nanchors)):
                msgD.seq = 0
                msgD.rss = 0
                msgD.errorEstimation = 0
                msgD.anchorId = i
                msgD.tagId = int(tagID)
                msgD.range = (int)(D[0][i]*1000)

                #logger.info(msgD)
                pubD.publish(msgD)
            
            
        except Exception as e:
            # nothing special
            logger.fatal(e)

        # cycle
        r.sleep()

    # stop reading
    data = 'lec\x0D'
    serialWrite(myserial, data, sleepLong)

    # Close the serial port
    logger.info('Close serial')
    myserial.close()

    return 0

if __name__ == '__main__':
    talker()
