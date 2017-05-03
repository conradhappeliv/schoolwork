import csv
import random

from node import Node


class Network:
    def __init__(self, filename, print_steps=True):
        self.print_steps = print_steps
        self.node_list = []
        self.network = []
        self.names = []
        self.taken_up = [[]]  # index is turn -> {set(): wait}
        self.load_from_file(filename)
        self.set_up_network()

    def load_from_file(self, filename):
        with open(filename) as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                node1 = self.find_or_create_node(row[0])
                node2 = self.find_or_create_node(row[1])
                self.network.append((node1, node2, int(row[2])))

    def set_up_network(self):
        """
        Calculates each node's neighbors and outputs them (if print_steps)
        :return: None
        """
        for node in self.node_list:
            node.get_adjacent_nodes(self.network)
        if self.print_steps:
            for node in self.node_list:
                for neighbor, path_len in node.neighbors.items():
                    print(str(node)+" -> "+str(neighbor)+": "+str(path_len))

    def find_or_create_node(self, name):
        """
        Gets a node from the network or creates it if it doesn't exist yet
        :param name: str of node's name
        :return: Node
        """
        if name not in self.names:
            new_node = Node(name, self.print_steps)
            self.names.append(name)
            self.node_list.append(new_node)
            return new_node
        else:
            for node in self.node_list:
                if node.name == name:
                    return node

    def active(self):
        """
        Is the network being utilized right now? (are packets being sent or received?)
        :return: bool
        """
        for node in self.node_list:
            if node.send_queue or node.in_progress:
                return True
        return False

    def send_packet(self, packet):
        possibles = self.find_all_routes(packet.source, packet.destination)
        random.shuffle(possibles)
        possibles = sorted(possibles, key=lambda x: x[0])
        for possible in possibles:
            packet.path = possible[1]
            bad = False
            for i in range(len(packet.path) - 1):
                if i+1 < len(self.taken_up) and {packet.path[i], packet.path[i+1]} in self.taken_up[i+1]:
                    bad = True
                    break
            if not bad:
                break
        else:
            packet.path = possibles[0][1]

        if self.print_steps:
            print("Packet routing from "+str(packet.source)+" to "+str(packet.destination)+" path: "+str(packet.path))

        for i in range(len(packet.path)-1):
            if i+2 > len(self.taken_up):
                self.taken_up.append(list())
            self.taken_up[i+1].append({packet.path[i], packet.path[i+1]})
        packet.source.send_queue.append(packet)

    def find_all_routes(self, source, destination, cur_path=list(), cur_len=0):
        """
        Returns literally all available routes from a source to a destination.
        This is a very badly performing method - use sparingly (or on a small graph)
        :param source: Node
        :param destination: Node
        :param cur_path: used for recursion
        :param cur_len: used for recursion
        :return: list of tuples containing (length of path, list of nodes along path)
        """
        if not cur_path: cur_path = [source]
        res = list()
        q = list(set(source.neighbors.keys()) - set(cur_path))
        random.shuffle(q)
        for place in q:
            cur_path.append(place)
            path_len = cur_path[-2].neighbors[cur_path[-1]]
            cur_len += path_len
            if cur_path[-1] is destination:
                res.append((cur_len, cur_path[:]))
            else:
                res.extend(self.find_all_routes(place, destination, cur_path, cur_len))
            cur_len -= path_len
            cur_path.pop()
        return res

    def loop_step(self, it_num):
        for node in self.node_list:
            node.loop_step(it_num)
        for node in self.node_list:
            node.dont_do_yet = list()

        if self.taken_up:
            self.taken_up.pop(0)
