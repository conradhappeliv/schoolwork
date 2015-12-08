class Node:
    def __init__(self, name, print_steps=True):
        self.print_steps = print_steps
        self.neighbors = {}  # { other_node -> capacity }
        self.name = str(name)  # for printing purposes only
        self.send_queue = []  # [ (destination, packet_size) ]
        self.in_progress = []  # [ {send_to, destination, amount_left, packet_size} ]
        self.recv_queue = {}  # { (src, dest) -> cur_amount }
        self.dont_do_yet = []  # [ dest ]

    def __repr__(self):
        return "Node " + str(self.name)

    def __lt__(self, other):
        return self.name < other.name

    def get_adjacent_nodes(self, network):
        """
        Sets up "neighbors" dict
        :param network: list of tuples of links (Node1, Node2)
        """
        for link in network:
            if link[0] is self or link[1] is self:
                if link[0] is self:
                    self.neighbors[link[1]] = link[2]
                else:  # link[1] is self
                    self.neighbors[link[0]] = link[2]

    def route_packets(self):
        for packet in self.send_queue[:]:
            for i in range(len(packet.path)):
                if packet.path[i] == self:
                    packet.next_node = packet.path[i+1]
                    self.in_progress.append(packet)
                    self.send_queue.remove(packet)
                    break
            else:
                if self.print_steps:
                    print("IMPOSSIBLE TO ROUTE FROM "+str(self)+" TO "+str(packet.destination))

    def process_queue(self, iteration_num):
        iteration_capacity = self.neighbors.copy()
        # transfer what you can (this might only be part of the packet)
        for packet in (p for p in self.in_progress if p.destination not in self.dont_do_yet):
            packet.time_waited += 1
            amount_possible = min(packet.amount_left, iteration_capacity[packet.next_node])
            if amount_possible:
                packet.time_waited -= 1
                if (self, packet.destination) not in packet.next_node.recv_queue:
                    packet.next_node.recv_queue[(self, packet.destination)] = 0
                if packet.amount_left - amount_possible == 0:  # it finishes sending on this iteration
                    del packet.next_node.recv_queue[(self, packet.destination)]
                    packet.next_node.dont_do_yet.append(packet.destination)
                    if packet.next_node is not packet.destination:
                        packet.next_node.send_queue.append(packet)
                packet.amount_left -= amount_possible
                iteration_capacity[packet.next_node] -= amount_possible
                if self.print_steps:
                    print("Node "+self.name+" transferred "+str(amount_possible)+" to "+str(packet.next_node)
                          +" (final dest: "+str(packet.destination)+", left: "+str(packet.amount_left)+")")

        # remove completed packets from queue
        for packet in self.in_progress[:]:
            if packet.amount_left == 0:
                packet.amount_left = packet.size
                packet.end_turn = iteration_num
                self.in_progress.remove(packet)

    def loop_step(self, iteration_num):
        self.route_packets()
        self.process_queue(iteration_num)
