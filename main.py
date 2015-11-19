import random
import csv

PRINT_STEPS = True


class Packet:
    def __init__(self, turn, source, dest, size):
        self.turn = turn
        self.next_node = source
        self.source = source
        self.destination = dest
        self.amount_left = size
        self.size = size
        self.time_waited = 0

    def __repr__(self):
        return "Packet (Size "+self.size+", src: "+self.source+", dest: "+self.destination+")"


class Node:
    def __init__(self, name):
        self.neighbors = dict()  # { other_node -> capacity }
        self.lookup_table = dict()  # { destination -> (which node this node sends to, total length) }
        self.name = str(name)  # for printing purposes only
        self.send_queue = list()  # [ (destination, packet_size) ]
        self.in_progress = list()  # [ {send_to, destination, amount_left, packet_size} ]
        self.recv_queue = dict()  # { (src, dest) -> cur_amount }
        self.dont_do_yet = list()  # [ dest ]

    def __repr__(self):
        return "Node " + str(self.name)

    def get_adjacent_nodes(self, network):
        for link in network:
            if link[0] is self or link[1] is self:
                if link[0] is self:
                    self.neighbors[link[1]] = link[2]
                else:  # link[1] is self
                    self.neighbors[link[0]] = link[2]

    def add_lookup(self, destination, send_to, path_len):
        self.lookup_table[destination] = (send_to, path_len)

    def route_packets(self):
        for packet in self.send_queue[:]:
            if packet.destination in self.lookup_table:
                packet.next_node = self.lookup_table[packet.destination][0]
                self.in_progress.append(packet)
            else:
                print("IMPOSSIBLE TO ROUTE FROM "+str(self)+" TO "+str(packet.destination))
            self.send_queue.remove(packet)

    def order_queue(self):
        self.smallest_first()
        self.in_progress.sort(key=lambda x: x.amount_left == x.size)

    def biggest_first(self):
        self.in_progress.sort(key=lambda x: -x.size)
        self.in_progress.sort(key=lambda x: x.size > self.neighbors[x.next_node])

    def smallest_first(self):
        self.in_progress.sort(key=lambda x: x.size)

    def process_queue(self):
        iteration_capacity = self.neighbors.copy()
        self.order_queue()
        # transfer what you can
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
                if PRINT_STEPS:
                    print("Node "+self.name+" transferred "+str(amount_possible)+" to "+str(packet.next_node)
                          +" (final dest: "+str(packet.destination)+", left: "+str(packet.amount_left)+")")

        # remove completed packets from queue
        for packet in self.in_progress[:]:
            if packet.amount_left == 0:
                self.in_progress.remove(packet)

    def loop_step(self):
        self.route_packets()
        self.process_queue()


def create_network(nodes=9, fixed_capacity=0):
    """
    :param nodes: how many nodes in the network
    :param fixed_capacity: should there be a fixed capacity between nodes (int)
    :return: list of Nodes, list of (node1, node2, capacity of link)
    """
    network = list()
    node_list = list()
    for i in range(nodes):
        node_list.append(Node(i))
    for i in range(len(node_list)):
        for j in range(i+1, len(node_list)):
            # add paths randomly between nodes
            if (nodes-1) and random.uniform(0, 1) < 1./(nodes-1):
                network.append((node_list[i], node_list[j], fixed_capacity if fixed_capacity else random.randint(1, 10)))

    # check if any nodes were left out
    for node in node_list:
        for link in network:
            if node is link[0] or node is link[1]:
                break
        else:
            network.append((node, random.choice(list(n for n in node_list if n is not node)), fixed_capacity if fixed_capacity else random.randint(1, 10)))
    if PRINT_STEPS:
        print("Created network with "+str(nodes)+" nodes.")
    return node_list, network


def calculate_paths(node_list, source):
    """
    modified implementation of dijkstra's
    :param node_list:
    :param source:
    :return: { destination -> (first node on path, path length) }
    """
    result = {n: (None, float("inf")) for n in node_list}
    result[source] = (None, 0)
    node_list = node_list[:]  # make a copy for use in here
    while node_list:
        min_node = None
        min_node_dist = float("inf")

        # find min distanced node
        for node in node_list:
            if result[node][1] < min_node_dist:
                min_node = node
                min_node_dist = result[node][1]
        if min_node:  # check for disconnected graph
            node_list.remove(min_node)
            for neighbor, dist in min_node.neighbors.items():
                new_dist = result[min_node][1] + dist
                if new_dist < result[neighbor][1]:
                    if min_node is source or min_node in source.neighbors:
                        send_to = min_node
                    else:
                        send_to = result[min_node][0]
                    result[neighbor] = (send_to, new_dist)
        else:
            break

    return result


def set_up_network(node_list, network):
    for node in node_list:
        node.get_adjacent_nodes(network)
    for node in node_list:
        paths = calculate_paths(node_list, node)
        for dest, (send_to, path_len) in paths.items():
            if send_to:
                node.add_lookup(dest, send_to if send_to is not node else dest, path_len)
    if PRINT_STEPS:
        for node in node_list:
            for neighbor, path_len in node.neighbors.items():
                print(str(node)+" -> "+str(neighbor)+": "+str(path_len))


def find_or_create_node(name, node_list, names):
    if name not in names:
        new_node = Node(name)
        names.add(name)
        node_list.append(new_node)
        return new_node
    else:
        for node in node_list:
            if node.name == name:
                return node


def load_from_file(filename):
    node_list = list()
    network = list()
    names = set()
    with open(filename) as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            node1 = find_or_create_node(row[0], node_list, names)
            node2 = find_or_create_node(row[1], node_list, names)
            network.append((node1, node2, int(row[2])))
    return node_list, network


def send_packet(packet):
    packet.source.send_queue.append(packet)


def network_active(node_list):
    for node in node_list:
        if node.send_queue or node.in_progress:
            return True


def main(filename=""):
    if filename:
        node_list, network = load_from_file(filename)
    else:
        node_list, network = create_network(nodes=9, fixed_capacity=1)
    set_up_network(node_list, network)

    packets_to_send = [  # (iteration#, source, dest, size)
        Packet(0, node_list[0], node_list[8], 1),
        Packet(0, node_list[0], node_list[8], 1),
        Packet(0, node_list[0], node_list[8], 9),
        Packet(0, node_list[0], node_list[8], 1),
        Packet(0, node_list[0], node_list[8], 5),
        Packet(0, node_list[0], node_list[8], 7),
        Packet(0, node_list[0], node_list[8], 5),
        Packet(0, node_list[0], node_list[8], 5),
        Packet(0, node_list[0], node_list[8], 4),
        Packet(0, node_list[0], node_list[8], 2),
        Packet(0, node_list[0], node_list[8], 2),
        Packet(0, node_list[0], node_list[8], 4),
        Packet(0, node_list[0], node_list[8], 10),
        Packet(0, node_list[0], node_list[8], 5),
        Packet(0, node_list[0], node_list[8], 5),
        Packet(0, node_list[0], node_list[8], 10),
        Packet(0, node_list[0], node_list[8], 3),
        Packet(0, node_list[0], node_list[8], 2),
        Packet(0, node_list[0], node_list[8], 8),
        Packet(0, node_list[0], node_list[8], 4),
        Packet(0, node_list[0], node_list[8], 5),
        Packet(0, node_list[0], node_list[8], 9),
        Packet(0, node_list[0], node_list[8], 10),
        Packet(0, node_list[0], node_list[8], 5),
    ]
    all_packets = [p for p in packets_to_send]
    iteration_num = 0
    # MAIN LOOP
    while packets_to_send or network_active(node_list):
        if PRINT_STEPS:
            print("ITERATION "+str(iteration_num+1))
        # send packets if it's their turn
        for packet in packets_to_send[:]:
            if iteration_num == packet.turn:
                send_packet(packet)
                packets_to_send.remove(packet)
        for node in node_list:
            node.loop_step()
        for node in node_list:
            node.dont_do_yet = list()
        iteration_num += 1
    total_time_waited = sum([p.time_waited for p in all_packets])
    print("Simulation took "+str(iteration_num)+" iterations. Total time waited: "+str(total_time_waited))


if __name__ == "__main__":
    main(filename="/home/conrad/PycharmProjects/CSE4344/testNetwork.csv")
