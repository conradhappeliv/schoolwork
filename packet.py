class Packet:
    def __init__(self, turn, source, dest, size):
        self.turn = turn
        self.end_turn = None
        self.next_node = source
        self.source = source
        self.destination = dest
        self.amount_left = size
        self.size = size
        self.time_waited = 0
        self.path = list()

    def __repr__(self):
        return "Packet (Size "+self.size+", src: "+self.source+", dest: "+self.destination+")"
