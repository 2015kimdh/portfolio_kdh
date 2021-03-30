from tkinter import *
from urllib.request import urlopen
from PIL import Image, ImageTk
from io import BytesIO


def make_googlemap_url(center, zoom=16, maptype='roadmap'):
    key = 'AIzaSyA9gjC63ldBuHDwYM6flkFJDbTq6vQhFdg'
    point = str(center[1]) + ',' + str(center[0])
    size = (500, 500)

    url = "http://maps.google.com/maps/api/staticmap?"
    url += "center=%s&" % point
    url += "zoom=%i&" % zoom
    url += 'scale=1&'
    url += "size=" + str(size[0]) + 'x' + str(size[1]) + '&'
    url += 'maptype=' + maptype + '&'
    url += '&markers=color:red%7Clabel:C%7C' + point + '&'
    url += 'key=' + key

    return url

def show_map(longitude, latitude, height=600, width=400, bg="white", zoom=16):
    # longitude : 경도
    # latitude : 위도
    # 나머지는 봐서 알 것
    global map_image

    map_url = make_googlemap_url((longitude, latitude), zoom=zoom)

    with urlopen(map_url) as u:
        raw_data = u.read()
    im = Image.open(BytesIO(raw_data))
    map_image = ImageTk.PhotoImage(im)

    return map_image

    #Label(frame, image=map_image, height=height, width=width, background=bg).pack()
    mainloop()