import os
import cherrypy
from io import BytesIO
from PIL import Image
from uuid import uuid4

from giffy import make_gif, save_gif


class ImageMorpher(object):
    def upload(self, file_1, file_2):
        def readall(file_obj):
            img = bytes()
            while True:
                data = file_obj.file.read(8192)
                if not data:
                    break
                img = img + data
            return img

        img1 = readall(file_1)
        img2 = readall(file_2)

        img1 = Image.open(BytesIO(img1))
        img2 = Image.open(BytesIO(img2))

        imgs = make_gif(img1, img2)
        uuid = uuid4().hex
        save_gif(imgs, 'static/generated/'+uuid+'.gif')

        raise cherrypy.HTTPRedirect("/static/generated/"+uuid+".gif")

    upload.exposed = True

if __name__ == '__main__':
    conf = {
        '/': {
            'tools.staticdir.on': True,
            'tools.staticdir.dir': '',
            'tools.staticdir.root': os.path.abspath(os.getcwd()),
            'tools.staticdir.index': 'static/index.html'
        },
        '/static': {
            'tools.staticdir.on': True,
            'tools.staticdir.dir': 'static'
        }
    }
    cherrypy.quickstart(ImageMorpher(), '/', conf)
