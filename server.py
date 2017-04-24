import os
import cherrypy


class ImageMorpher(object):
    def upload(self, file_1, file_2):
        out = """<html>
        <body>
            myFile1 length: %s<br />
            myFile1 filename: %s<br />
            myFile1 mime-type: %s <br />
            myFile2 length: %s<br />
            myFile2 filename: %s<br />
            myFile2 mime-type: %s
        </body>
        </html>"""

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

        return out % (len(img1), file_1.filename, file_1.content_type, len(img2), file_2.filename, file_2.content_type)
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
