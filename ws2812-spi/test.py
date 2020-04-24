import treehopper.api
import colorsys
import time

board = treehopper.api.find_boards()[0]
board.connect()
board.spi.enabled = True

numLeds = 50

frameBuffer = [0] * numLeds * 3

time = 1000

def setRGB(idx, r, g, b):
    frameBuffer[idx * 3 + 0] = int(g)
    frameBuffer[idx * 3 + 1] = int(r)
    frameBuffer[idx * 3 + 2] = int(b)


def flush():
    board.spi.send_receive(frameBuffer, None, 0, 0.49, 0, 0)


for j in range(0, 500):
    for i in range(0, numLeds):
        rgb = colorsys.hls_to_rgb((i/numLeds) + j/100, 0.01, 1.0)
        setRGB(i, 255.0*rgb[0], 255.0*rgb[1], 255.0*rgb[2])
    flush()
    time.sleep(0.01)
