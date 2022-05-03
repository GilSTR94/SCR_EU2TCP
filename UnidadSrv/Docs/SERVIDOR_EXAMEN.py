#CREACION DEL SERVIDOR_EXAMEN_


from socketserver import BaseRequestHandler, TCPServer


class ReceptorPeticiones(BaseRequestHandler):

    def handle(self):
        print('Hemos recibido una conexion desde{}'.format(self.client_address))
        while True:
            mensaje = self.request.recv(8192)
            if not mensaje:
                break
            self.request.send(mensaje)

if  __name__  == '__main__':
    servidor = TCPServer(('',20064),ReceptorPeticiones)
    print('SE INICIO EL SERVIDOR')
    servidor.serve_forever()
